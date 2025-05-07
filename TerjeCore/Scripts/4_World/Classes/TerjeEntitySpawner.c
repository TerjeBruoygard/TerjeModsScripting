// <copyright file="TerjeEntitySpawner.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeEntitySpawner
{
	/**
	\brief Spawn entity on ground from xml
		@param xml entity description
		@param pos to be spawned in the world.
		\return created object or null on error.
	*/
	EntityAI SpawnOnGroundFromXml(TerjeXmlObject xml, vector pos)
	{
		if (!xml.IsObjectNode())
		{
			return null;
		}
		
		if (xml.GetName() != "Item")
		{
			TerjeLog_Error("TerjeEntitySpawner::SpawnInInventoryFromXml - Invalid XML item type '" + xml.GetName() + "'. Only 'Item' is supported here.");
			return null;
		}
		
		string classname;
		if (!xml.FindAttribute("classname", classname))
		{
			TerjeLog_Error("TerjeEntitySpawner::SpawnInInventoryFromXml - Missing required 'classname' attribute for XML item.");
			return null;
		}
		
		Object spawnedObject = GetGame().CreateObject(classname, pos);
		if (!spawnedObject)
		{
			TerjeLog_Warning("TerjeEntitySpawner::SpawnInInventoryFromXml - Failed to spawn '" + classname + "' entity.");
			return null;
		}
		
		EntityAI spawnedEntity = EntityAI.Cast(spawnedObject);
		if (!spawnedEntity)
		{
			// Delete object when not inherited from EntityAI.
			TerjeLog_Warning("TerjeEntitySpawner::SpawnInInventoryFromXml - Failed to spawn '" + classname + "' entity.");
			GetGame().ObjectDelete(spawnedObject);
			return null;
		}
		
		ApplyEntityParametersFromXml(xml, spawnedEntity);
		
		for (int i = 0; i < xml.GetChildrenCount(); i++)
		{
			SpawnInInventoryFromXml(xml.GetChild(i), spawnedEntity);
		}
		
		Weapon_Base weapon;
		if (Weapon_Base.CastTo(weapon, spawnedEntity))
		{
			weapon.RandomizeFSMState();
			weapon.Synchronize();
		}
		
		return spawnedEntity;
	}
	
	/**
	\brief Spawn entity in the target inventory from xml
		@param xml entity description
		@param target in whose inventory the object will be created.
		\return created object or null on error.
	*/
	EntityAI SpawnInInventoryFromXml(TerjeXmlObject xml, EntityAI target)
	{
		if (!target || !target.GetInventory())
		{
			return null;
		}
		
		if (!xml.IsObjectNode())
		{
			return null;
		}
		
		if (xml.GetName() != "Item")
		{
			TerjeLog_Error("TerjeEntitySpawner::SpawnInInventoryFromXml - Invalid XML item type '" + xml.GetName() + "'. Only 'Item' is supported here.");
			return null;
		}
		
		string classname;
		if (!xml.FindAttribute("classname", classname))
		{
			TerjeLog_Error("TerjeEntitySpawner::SpawnInInventoryFromXml - Missing required 'classname' attribute for XML item.");
			return null;
		}
		
		EntityAI spawnedEntity;
		string position;
		if (xml.FindAttribute("position", position) && (position != string.Empty))
		{
			spawnedEntity = SpawnEntityInInventoryByPosition(classname, target, position);
		}
		else if (target.IsInherited(Weapon_Base))
		{
			spawnedEntity = target.GetInventory().CreateAttachment(classname);
		}
		else
		{
			spawnedEntity = target.GetInventory().CreateInInventory(classname);
		}
		
		if (!spawnedEntity)
		{
			TerjeLog_Warning("TerjeEntitySpawner::SpawnInInventoryFromXml - Failed to spawn '" + classname + "' entity.");
			return null;
		}
		
		if (!spawnedEntity.GetHierarchyParent())
		{
			// Delete object when spawned on the ground.
			TerjeLog_Warning("TerjeEntitySpawner::SpawnInInventoryFromXml - Failed to spawn '" + classname + "' entity inside " + target);
			GetGame().ObjectDelete(spawnedEntity);
			return null;
		}
		
		ApplyEntityParametersFromXml(xml, spawnedEntity);
		
		for (int i = 0; i < xml.GetChildrenCount(); i++)
		{
			SpawnInInventoryFromXml(xml.GetChild(i), spawnedEntity);
		}
		
		Weapon_Base weapon;
		if (Weapon_Base.CastTo(weapon, spawnedEntity))
		{
			weapon.RandomizeFSMState();
			weapon.Synchronize();
		}
		
		return spawnedEntity;
	}
	
	/**
	\brief Sets entity parameters from xml
		@param xml entity description
		@param target entity.
	*/
	void ApplyEntityParametersFromXml(TerjeXmlObject xml, EntityAI entity)
	{
		if (!entity)
		{
			return;
		}

		string ammoType;
		string attrValue;
		ItemBase item;
		PlayerBase player;
		Ammunition_Base ammo;
		Magazine magazine;
		Weapon_Base weapon;
		
		if (xml.FindAttribute("health", attrValue))
		{
			entity.SetHealth01("", "", Math.Clamp(TerjeStringHelper.ParseFloatRangeIdentifier(attrValue), 0, 1));
		}
		
		if (xml.FindAttribute("temperature", attrValue))
		{
			entity.SetTemperature(TerjeStringHelper.ParseFloatRangeIdentifier(attrValue));
		}
		
		if (ItemBase.CastTo(item, entity))
		{
			if (xml.FindAttribute("quantity", attrValue))
			{
				item.SetQuantityNormalized(Math.Clamp(TerjeStringHelper.ParseFloatRangeIdentifier(attrValue), 0, 1));
			}
			
			if (xml.FindAttribute("count", attrValue))
			{
				item.SetQuantity(TerjeStringHelper.ParseIntRangeIdentifier(attrValue));
			}
			
			if (xml.FindAttribute("foodStage", attrValue) && item.HasFoodStage())
			{
				int foodStageIndex = EnumTools.StringToEnum(FoodStageType, attrValue);
				if (foodStageIndex != -1)
				{
					item.GetFoodStage().SetFoodStageType(foodStageIndex);
				}
			}
			
			if (xml.FindAttribute("disinfected", attrValue))
			{
				item.SetCleanness(TerjeStringHelper.ParseIntRangeIdentifier(attrValue));
			}
			
			if (xml.FindAttribute("liquid", attrValue))
			{
				int liquidIndex;
				LiquidInfo liquidInfo;
				if (TerjeCustomLiquids.GetInstance().FindLiquidIndexByType(attrValue, liquidIndex))
				{
					item.SetTerjeLiquidType(liquidIndex);
				}
				else if (Liquid.m_LiquidInfosByName.Find(attrValue, liquidInfo))
				{
					item.SetLiquidType(liquidInfo.m_LiquidType);
				}
				else
				{
					TerjeLog_Warning("TerjeEntitySpawner::ApplyEntityParametersFromXml - Unknown liquid classname '" + attrValue + "'");
				}
			}
			
			if (xml.FindAttribute("agents", attrValue))
			{
				array<string> aggentNames();
				attrValue.Split(",", aggentNames);
				foreach (string agentName : aggentNames)
				{
					int agentIndex = EnumTools.StringToEnum(eAgents, agentName.Trim());
					if (agentIndex != -1)
					{
						item.InsertAgent(agentIndex);
					}
				}
			}
			
			if (xml.FindAttribute("quickbar", attrValue))
			{
				int quickbarIndex = attrValue.ToInt();
				if (Class.CastTo(player, item.GetHierarchyRootPlayer()) && (quickbarIndex >= 0) && (quickbarIndex < 10))
				{
					player.SetQuickBarEntityShortcut(item, quickbarIndex);
				}
			}
			
			if (Ammunition_Base.CastTo(ammo, item))
			{
				if (xml.FindAttribute("ammoCount", attrValue))
				{
					ammo.ServerSetAmmoCount(TerjeStringHelper.ParseIntRangeIdentifier(attrValue));
				}
			}
			else if (Magazine.CastTo(magazine, item))
			{
				int ammoCountMag = magazine.GetAmmoMax();
				if (xml.FindAttribute("ammoCount", attrValue))
				{
					ammoCountMag = TerjeStringHelper.ParseIntRangeIdentifier(attrValue);
				}
				
				if (xml.FindAttribute("ammoType", attrValue))
				{
					if (ResolveBulletAmmoType(attrValue, ammoType))
					{
						magazine.ServerSetAmmoCount(0);
						for (int i1 = 0; i1 < ammoCountMag; i1++)
						{
							magazine.ServerStoreCartridge(0, ammoType);
						}
					}
					else
					{
						TerjeLog_Warning("TerjeEntitySpawner::ApplyEntityParametersFromXml - Invalid ammo type '" + attrValue + "' for magazine " + entity);
					}
				}
				else
				{
					magazine.ServerSetAmmoCount(ammoCountMag);
				}
			}
			else if (Weapon_Base.CastTo(weapon, item))
			{
				if (xml.FindAttribute("ammoType", attrValue))
				{
					if (ResolveBulletAmmoType(attrValue, ammoType))
					{
						int muzzleCount = weapon.GetMuzzleCount();
						for (int muzzleId = 0; muzzleId < muzzleCount; muzzleId++)
						{
							if (weapon.PushCartridgeToChamber(muzzleId, 0, ammoType))
							{
								if (weapon.HasInternalMagazine(muzzleId) && xml.FindAttribute("ammoCount", attrValue))
								{
									int ammoCountWpn = TerjeStringHelper.ParseIntRangeIdentifier(attrValue);
									for (int i2 = 0; i2 < ammoCountWpn; i2++)
									{
										weapon.PushCartridgeToInternalMagazine(muzzleId, 0, ammoType);
									}
								}
								
								break;
							}
						}
					}
					else
					{
						TerjeLog_Warning("TerjeEntitySpawner::ApplyEntityParametersFromXml - Invalid ammo type '" + attrValue + "' for weapon " + entity);
					}
				}
			}
		}
	}
	
	void BakeXml(TerjeXmlObject xml, bool recursive)
	{
		BakeXmlIntAttribute(xml, "count");
		BakeXmlIntAttribute(xml, "ammoCount");
		BakeXmlFloatAttribute(xml, "quantity");
		BakeXmlFloatAttribute(xml, "health");
		BakeXmlFloatAttribute(xml, "temperature");
		
		if (recursive)
		{
			for (int i = 0; i < xml.GetChildrenCount(); i++)
			{
				BakeXml(xml.GetChild(i), recursive);
			}
		}
	}
	
	protected void BakeXmlIntAttribute(TerjeXmlObject xml, string attrName)
	{
		string attrValue;
		if (xml.FindAttribute(attrName, attrValue))
		{
			xml.SetAttribute(attrName, TerjeStringHelper.ParseIntRangeIdentifier(attrValue).ToString());
		}
	}
	
	protected void BakeXmlFloatAttribute(TerjeXmlObject xml, string attrName)
	{
		string attrValue;
		if (xml.FindAttribute(attrName, attrValue))
		{
			xml.SetAttribute(attrName, TerjeStringHelper.ParseFloatRangeIdentifier(attrValue).ToString());
		}
	}
	
	protected bool ResolveBulletAmmoType(string rawAmmoType, out string resolvedAmmoType)
	{
		if (rawAmmoType == string.Empty)
		{
			return false;
		}
		
		if (GetGame().ConfigIsExisting("CfgAmmo " + rawAmmoType))
		{
			resolvedAmmoType = rawAmmoType;
			return true;
		}
		
		if (GetGame().ConfigIsExisting("CfgMagazines " + rawAmmoType))
		{
			return GetGame().ConfigGetTextRaw("CfgMagazines " + rawAmmoType + " ammo", resolvedAmmoType);
		}
		
		return false;
	}
	
	protected EntityAI SpawnEntityInInventoryByPosition(string classname, EntityAI target, string position)
	{
		InventoryLocation loc;
		if (position == "@InHands")
		{
			PlayerBase player = PlayerBase.Cast(target);
			if (!player)
			{
				player = PlayerBase.Cast(target.GetHierarchyRootPlayer());
			}
			
			if (!player)
			{
				TerjeLog_Warning("TerjeEntitySpawner::SpawnEntityByPosition - Failed to spawn entity '" + classname + "' in player hands.");
				return null;
			}
			
			if (player.GetItemInHands())
			{
				TerjeLog_Warning("TerjeEntitySpawner::SpawnEntityByPosition - Failed to spawn entity '" + classname + "' because player already has another item in hands.");
				return null;
			}
			
			return player.GetHumanInventory().CreateInHands(classname);
		}
		else if (position == "@Cargo")
		{
			loc = new InventoryLocation();
			if (!target.GetInventory().FindFirstFreeLocationForNewEntity(classname, FindInventoryLocationType.CARGO, loc))
			{
				TerjeLog_Warning("TerjeEntitySpawner::SpawnEntityByPosition - Failed to found free position in cargo to spawn entity '" + classname + "' inside " + target);
				return null;
			}
	
			return loc.GetParent().GetInventory().CreateEntityInCargoEx(classname, loc.GetIdx(), loc.GetRow(), loc.GetCol(), loc.GetFlip());
		}
		else if (position == "@Attachment")
		{
			loc = new InventoryLocation();
			if (!target.GetInventory().FindFirstFreeLocationForNewEntity(classname, FindInventoryLocationType.ATTACHMENT, loc))
			{
				TerjeLog_Warning("TerjeEntitySpawner::SpawnEntityByPosition - Failed to found free attachment slot to spawn entity '" + classname + "' inside " + target);
				return null;
			}
	
			return loc.GetParent().GetInventory().CreateAttachmentEx(classname, loc.GetSlot());
		}
		else if (position.IndexOf("@Cargo:") == 0)
		{
			array<string> cargoArgs();
			position.Split(":", cargoArgs);
			
			int row = 0;
			int col = 0;
			bool flip = false;
			if (cargoArgs.Count() > 1)
			{
				col = cargoArgs.Get(1).ToInt();
			}
			
			if (cargoArgs.Count() > 2)
			{
				row = cargoArgs.Get(2).ToInt();
			}
			
			if (cargoArgs.Count() > 3)
			{
				flip = (cargoArgs.Get(3) == "v");
			}
			
			return target.GetInventory().CreateEntityInCargoEx(classname, -1, row, col, flip);
		}
		
		int attachmentSlotId = InventorySlots.GetSlotIdFromString(position);
		if (attachmentSlotId != InventorySlots.INVALID)
		{
			return target.GetInventory().CreateAttachmentEx(classname, attachmentSlotId);
		}
		
		TerjeLog_Error("TerjeEntitySpawner::SpawnEntityByPosition - Unknown position value '" + position + "' to spawn item '" + classname + "'.");
		return null;
	}
}