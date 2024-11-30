// <copyright file="PluginTerjeScriptableAreas.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeScriptableAreas : PluginBase 
{
	private int m_currentIndex = int.MIN;
	private ref map<string, ref map<int, TerjeScriptableArea>> m_scriptableAreas = new map<string, ref map<int, TerjeScriptableArea>>;
	
	override void OnInit()
	{
		super.OnInit();
		if (GetGame().IsDedicatedServer())
		{
			MakeDirectory("$mission:terje_config");
			string errorMessage;
			string configPath = "$mission:terje_config/spawn_scriptable_areas.json";
			PluginTerjeScriptableAreas_Config configData;
			if (FileExist(configPath))
			{
				if (JsonFileLoader<PluginTerjeScriptableAreas_Config>.LoadFile(configPath, configData, errorMessage))
				{
					if (configData.Areas != null)
					{
						foreach (ref PluginTerjeScriptableAreas_ConfigEntry readedEntry : configData.Areas)
						{
							if (readedEntry.Active != 1)
							{
								continue;
							}
							
							if (readedEntry.SpawnChance < Math.RandomFloat01())
							{
								continue;
							}
							
							TerjeScriptableArea spawnableObject;
							vector pos = Vector( readedEntry.Position[0], readedEntry.Position[1], readedEntry.Position[2] );
							if (pos[1] == 0)
							{
								pos[1] = GetGame().SurfaceRoadY( pos[0], pos[2] );
								Class.CastTo( spawnableObject, GetGame().CreateObjectEx( readedEntry.Classname, pos, ECE_PLACE_ON_SURFACE ) );
							}
							else
							{
								Class.CastTo( spawnableObject, GetGame().CreateObjectEx( readedEntry.Classname, pos, ECE_NONE ) );
							}
							
							if (spawnableObject && readedEntry.Data != null)
							{
								spawnableObject.SetTerjeParameters(readedEntry.Data);
							}
						}
					}
				}
				else
				{
					ErrorEx(errorMessage);
				}
			}
			else
			{
				ref PluginTerjeScriptableAreas_ConfigEntry configEntry = new PluginTerjeScriptableAreas_ConfigEntry;
				configEntry.Active = 0;
				configEntry.Classname = "Put scriptable area classname here. For example TerjePsionicScriptableArea from TerjeMedicine or TerjeRadioactiveScriptableArea from TerjeRadiation mod.";
				configEntry.Position = "341 0 9401";
				configEntry.SpawnChance = 1.0;
				configEntry.Data = new map<string, float>;
				configEntry.Data.Insert("InnerRadius", 50);
				configEntry.Data.Insert("OuterRadius", 150);
				configEntry.Data.Insert("HeightMin", -100);
				configEntry.Data.Insert("HeightMax", 100);
				configEntry.Data.Insert("Power", 2.5);
				
				configData = new PluginTerjeScriptableAreas_Config;
				configData.Areas = new array<ref PluginTerjeScriptableAreas_ConfigEntry>;
				configData.Areas.Insert(configEntry);

				if (!JsonFileLoader<PluginTerjeScriptableAreas_Config>.SaveFile(configPath, configData, errorMessage))
				{
					ErrorEx(errorMessage);
				}
			}
		}
	}
	
	override void OnDestroy()
	{
		m_scriptableAreas.Clear();
		super.OnDestroy();
	}
	
	int RegisterScriptableArea(TerjeScriptableArea scriptableArea)
	{
		string type = scriptableArea.GetTerjeScriptableAreaType();
		if (!m_scriptableAreas.Contains(type))
		{
			m_scriptableAreas.Insert(type, new map<int, TerjeScriptableArea>);
		}
		
		m_currentIndex = m_currentIndex + 1;
		m_scriptableAreas.Get(type).Insert(m_currentIndex, scriptableArea);
		return m_currentIndex;
	}
	
	void UnregisterScriptableArea(string type, int index)
	{
		if (m_scriptableAreas.Contains(type))
		{
			m_scriptableAreas.Get(type).Remove(index);
		}
	}
	
	float CalculateTerjeEffectValue(EntityAI entity, string filter)
	{
		float result = 0;
		ref map<int, TerjeScriptableArea> filteredAreas;
		if (entity != null && m_scriptableAreas.Find(filter, filteredAreas))
		{
			vector entityPos = entity.GetWorldPosition();
			foreach (int index, TerjeScriptableArea scriptableArea : filteredAreas)
			{
				if (scriptableArea)
				{
					result += scriptableArea.CalculateTerjeEffectValue(entityPos);
				}
			}
		}
		
		return result;
	}
	
	void TransferTerjeRadiation(EntityAI from, EntityAI to, float modifier)
	{
		AddTerjeRadiationToEntity(to, GetTerjeRadiationFromEntity(from) * modifier);
	}
	
	void CleanTerjeRadiationFromEntity(EntityAI entity, float power, bool recursive, bool addWet)
	{
		if (power > 0)
		{
			power *= -1;
		}
		
		if (AddTerjeRadiationToEntity(entity, power))
		{
			if (addWet)
			{
				entity.AddWet(entity.GetWetMax() * 0.1);
			}
			
			if (recursive)
			{
				GameInventory inv = entity.GetInventory();
				if (inv)
				{
					int attCount = inv.AttachmentCount();
					for ( int attIdx = 0; attIdx < attCount; attIdx++ )
					{
						EntityAI attachment = inv.GetAttachmentFromIndex( attIdx );
						if ( attachment )
						{
							CleanTerjeRadiationFromEntity(attachment, power, recursive, addWet);
						}
					}
					
					CargoBase cargo = inv.GetCargo();
					if (cargo)
					{
						for ( int ittIdx = 0; ittIdx < cargo.GetItemCount(); ittIdx++ )
						{
							EntityAI item = cargo.GetItem( ittIdx );
							if (item)
							{
								CleanTerjeRadiationFromEntity(item, power, recursive, addWet);
							}
						}
					}
				}
			}
		}
	}
	
	bool AddTerjeRadiationToEntity(EntityAI entity, float rAmount)
	{
		if (entity)
		{
			if (entity.IsInherited(PlayerBase))
			{
				return PlayerBase.Cast(entity).AddTerjeRadiation(rAmount);
			}
			else if (entity.IsInherited(ItemBase))
			{
				return ItemBase.Cast(entity).AddTerjeRadiation(rAmount);
			}
			else if (entity.IsInherited(ZombieBase))
			{
				return ZombieBase.Cast(entity).AddTerjeRadiation(rAmount);
			}
			else if (entity.IsInherited(CarScript))
			{
				return CarScript.Cast(entity).AddTerjeRadiation(rAmount);
			}
			else if (entity.IsInherited(AnimalBase))
			{
				return AnimalBase.Cast(entity).AddTerjeRadiation(rAmount);
			}
		}
		
		return false;
	}
	
	float GetTerjeRadiationFromEntity(EntityAI entity)
	{
		if (entity)
		{
			if (entity.IsInherited(PlayerBase))
			{
				return PlayerBase.Cast(entity).GetTerjeRadiation();
			}
			else if (entity.IsInherited(ItemBase))
			{
				return ItemBase.Cast(entity).GetTerjeRadiation();
			}
			else if (entity.IsInherited(ZombieBase))
			{
				return ZombieBase.Cast(entity).GetTerjeRadiation();
			}
			else if (entity.IsInherited(CarScript))
			{
				return CarScript.Cast(entity).GetTerjeRadiation();
			}
			else if (entity.IsInherited(AnimalBase))
			{
				return AnimalBase.Cast(entity).GetTerjeRadiation();
			}
		}
		
		return 0;
	}
	
	float IsTerjeRadiationSupportedForEntity(EntityAI entity)
	{
		if (entity)
		{
			if (entity.IsInherited(PlayerBase))
			{
				return true;
			}
			else if (entity.IsInherited(ItemBase))
			{
				return true;
			}
			else if (entity.IsInherited(ZombieBase))
			{
				return true;
			}
			else if (entity.IsInherited(CarScript))
			{
				return true;
			}
			else if (entity.IsInherited(AnimalBase))
			{
				return true;
			}
		}
		
		return false;
	}
	
	float CalculateTerjeRadiationFromNearestEntities(EntityAI owner, float radius, bool ignoreOwnerRadioactivity)
	{
		float result = 0;
		if (owner && radius > 0)
		{
			PlayerBase playerObj;
			ItemBase itemObj;
			ZombieBase zombieObj;
			CarScript vehicleObj;
			AnimalBase animalObj;
			vector ownerPos = owner.GetWorldPosition();
			ref array<Object> nearestObjects = new array<Object>;
			GetGame().GetObjectsAtPosition3D(ownerPos, radius, nearestObjects, null);
			foreach (Object obj : nearestObjects)
			{
				if (owner == obj && ignoreOwnerRadioactivity)
				{
					continue;
				}
				
				// Sorry for that shitty if-else spagettie.
				// I can't make interface for GetTerjeRadiation inside EntityAI because Bohemia won't let me mod this class.
				// Fuck you Bohemia =)
				if (PlayerBase.CastTo(playerObj, obj))
				{
					result += playerObj.GetTerjeRadiationAdvanced(true, true, true) * CalculateDistanceModToPlayer(playerObj, ownerPos, radius);
				}
				else if (ItemBase.CastTo(itemObj, obj))
				{
					result += itemObj.GetTerjeRadiation() * CalculateDistanceModToObject(obj, ownerPos, radius);
				}
				else if (ZombieBase.CastTo(zombieObj, obj))
				{
					result += zombieObj.GetTerjeRadiation() * CalculateDistanceModToZombie(zombieObj, ownerPos, radius);
				}
				else if (CarScript.CastTo(vehicleObj, obj))
				{
					result += vehicleObj.GetTerjeRadiation() * CalculateDistanceModToObject(obj, ownerPos, radius);
				}
				else if (AnimalBase.CastTo(animalObj, obj))
				{
					result += animalObj.GetTerjeRadiation() * CalculateDistanceModToObject(obj, ownerPos, radius);
				}
			}
		}
		
		return result * 0.001; // Convert rengens to mrg
	}
	
	float CalculatePlayerBodyProtection(PlayerBase player, string protectionType, float power)
	{
		ref TerjeScriptableProtection tsp = TerjeScriptableProtection.GetInstance();
		float feetWeight = tsp.GetWeight(protectionType, "Feet");
		float legsWeight = tsp.GetWeight(protectionType, "Legs");
		float bodyWeight = tsp.GetWeight(protectionType, "Body");
		float glovesWeight = tsp.GetWeight(protectionType, "Gloves");
		float headgearWeight = tsp.GetWeight(protectionType, "Headgear");
		float maskWeight = tsp.GetWeight(protectionType, "Mask");
		float totalWeight = Math.Max(1.0, feetWeight + legsWeight + bodyWeight + glovesWeight + headgearWeight + maskWeight);

		float totalProtection = 0;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.FEET, protectionType, "Feet", power) * feetWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.LEGS, protectionType, "Legs", power) * legsWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.BODY, protectionType, "Body", power) * bodyWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.GLOVES, protectionType, "Gloves", power) * glovesWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.HEADGEAR, protectionType, "Headgear", power) * headgearWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.MASK, protectionType, "Mask", power) * maskWeight;
		
		return Math.Clamp(totalProtection / totalWeight, 0, 1);
	}
	
	float CalculatePlayerPartProtection(PlayerBase player, int slot, string protectionType, string partType, float power)
	{
		float bodyProtection = TerjeScriptableProtection.GetInstance().GetBodyProtection(protectionType, partType, power);
		ItemBase attachment = ItemBase.Cast(player.GetInventory().FindAttachment(slot));
		if (attachment)
		{
			bodyProtection += attachment.GetTerjeProtectionLevel(protectionType);
		}
		
		return Math.Clamp(bodyProtection, 0, 1);
	}
	
	private float CalculateDistanceModToObject(Object obj, vector ownerPos, float radius)
	{
		return 1.0 - Math.Clamp(vector.Distance(obj.GetWorldPosition(), ownerPos) / radius, 0, 1);
	}
	
	private float CalculateDistanceModToZombie(ZombieBase zombie, vector ownerPos, float radius)
	{
		vector zombiePos = zombie.GetWorldPosition();
		zombiePos[1] = zombiePos[1] + 1.5;
		return 1.0 - Math.Clamp(vector.Distance(zombiePos, ownerPos) / radius, 0, 1);
	}
	
	private float CalculateDistanceModToPlayer(PlayerBase player, vector ownerPos, float radius)
	{
		vector headBonePos;
		MiscGameplayFunctions.GetHeadBonePos(player, headBonePos);
		return 1.0 - Math.Clamp(vector.Distance(headBonePos, ownerPos) / radius, 0, 1);
	}
}

class PluginTerjeScriptableAreas_Config
{
	ref array<ref PluginTerjeScriptableAreas_ConfigEntry> Areas;
}

class PluginTerjeScriptableAreas_ConfigEntry
{
	int Active;
	string Classname;
	vector Position;
	float SpawnChance;
	ref map<string, float> Data;
}

PluginTerjeScriptableAreas GetTerjeScriptableAreas() 
{
    return PluginTerjeScriptableAreas.Cast(GetPlugin(PluginTerjeScriptableAreas));
}