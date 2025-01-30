// <copyright file="ItemBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ItemBase
{
	private int m_terjeClientIndex;
	private int m_terjeLiquidType;
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		if (IsLiquidContainer() && GetQuantity() > 0)
		{
			m_terjeLiquidType = GetTerjeCustomLiquidTypeInit();
			if (m_terjeLiquidType > 0)
			{
				m_VarLiquidType = LIQUID_TERJE_CUSTOM;
			}
		}
		
		RegisterNetSyncVariableInt("m_terjeLiquidType");
	}
	
	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame().IsClient() && IsTerjeClientUpdateRequired())
		{
			m_terjeClientIndex = GetTerjeClientItemsCore().RegisterItem(this);
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (GetGame().IsClient() && IsTerjeClientUpdateRequired())
		{
			GetTerjeClientItemsCore().UnregisterItem(m_terjeClientIndex);
		}
	}
	
	// Calls every second on the client side only when IsTerjeClientUpdateRequired() is true
	void OnTerjeClientUpdate(float deltaTime)
	{
	
	}
	
	bool IsTerjeClientUpdateRequired()
	{
		return false;
	}
	
	bool IsDisinfected()
	{
		return m_Cleanness > m_CleannessMin && m_Cleanness <= m_CleannessMax;
	}
	
	bool AddTerjeRadiation(float rAmount)
	{
		// Universal interface to insert radiation agents into the item.
		// Implemented in TerjeRadiation mod.
		return false;
	}
	
	float GetTerjeRadiation()
	{
		// Universal interface to get radiation agents from the item.
		// Implemented in TerjeRadiation mod.
		return 0;
	}
	
	bool IsTerjeRadiationAccumulated()
	{
		// Can item accumulate radiation inside
		return false;
	}
	
	float GetTerjeRadiationInventoryIsolation()
	{
		// Value from 0 to 1
		// Determines what percentage of radiation will be isolated when transfering to/from inventory.
		return 0;
	}
	
	void SetTerjeLiquidClassname(string terjeLiquidClassName, bool allow_client = false)
	{
		SetTerjeLiquidType(TerjeCustomLiquids.GetInstance().GetLiquidIndexByType(terjeLiquidClassName), allow_client);
	}
	
	void SetTerjeLiquidType(int terjeLiquidType, bool allow_client = false)
	{
		if (!IsServerCheck(allow_client))
			return;
		
		if (GetLiquidType() != LIQUID_TERJE_CUSTOM)
		{
			SetLiquidType(LIQUID_TERJE_CUSTOM, allow_client);
		}

		int oldLiquidType = m_terjeLiquidType;
		m_terjeLiquidType = terjeLiquidType;
		if (oldLiquidType != terjeLiquidType)
		{
			OnTerjeLiquidTypeChanged(oldLiquidType, terjeLiquidType);
		}
		
		SetSynchDirty();
	}
	
	override int GetLiquidTypeInit()
	{
		if (GetTerjeCustomLiquidTypeInit() > 0)
		{
			return LIQUID_TERJE_CUSTOM;
		}
		
		return super.GetLiquidTypeInit();
	}
	
	int GetTerjeCustomLiquidTypeInit()
	{
		return TerjeCustomLiquids.GetInstance().GetLiquidIndexByType(ConfigGetString("varTerjeCustomLiquidTypeInit"));
	}
	
	int GetTerjeLiquidType()
	{
		if (GetLiquidType() == LIQUID_TERJE_CUSTOM)
		{
			return m_terjeLiquidType;
		}
		else
		{
			return 0;
		}
	}
	
	string GetTerjeLiquidClassname()
	{
		return TerjeCustomLiquids.GetInstance().GetLiquidClassname(GetTerjeLiquidType());
	}
	
	override void SetLiquidType(int value, bool allow_client = false)
	{
		int old = m_VarLiquidType;
		super.SetLiquidType(value, allow_client);
		
		if (value != LIQUID_TERJE_CUSTOM && old == LIQUID_TERJE_CUSTOM)
		{
			m_terjeLiquidType = 0; // Reset
		}
	}
	
	override float GetTemperatureFreezeThreshold()
	{
		if (IsLiquidContainer() && GetTerjeLiquidType() > 0)
		{
			return TerjeCustomLiquids.GetInstance().GetFreezeThreshold(GetTerjeLiquidType());
		}
		
		return super.GetTemperatureFreezeThreshold();
	}
	
	override float GetTemperatureThawThreshold()
	{
		if (IsLiquidContainer() && GetTerjeLiquidType() > 0)
		{
			return TerjeCustomLiquids.GetInstance().GetThawThreshold(GetTerjeLiquidType());
		}
		
		return super.GetTemperatureThawThreshold();
	}
	
	override float GetItemOverheatThreshold()
	{
		if (IsLiquidContainer() && GetTerjeLiquidType() > 0)
		{
			return TerjeCustomLiquids.GetInstance().GetBoilThreshold(GetTerjeLiquidType());
		}
		
		return super.GetItemOverheatThreshold();
	}
	
	ItemBase GetTerjeProtectionElement(string protectionType)
	{
		if (!GetGame() || IsDamageDestroyed() || (HasQuantity() && GetQuantity() <= 0))
		{
			return null;
		}
		
		if (GetInventory().GetAttachmentSlotsCount() != 0 && GetInventory().HasAttachmentSlot(InventorySlots.GetSlotIdFromString("GasMaskFilter")))
		{
			return ItemBase.Cast(FindAttachmentBySlotName("GasMaskFilter"));
		}
		
		return this;
	}
	
	float GetTerjeProtectionLevel(string protectionType)
	{
		ItemBase item = GetTerjeProtectionElement(protectionType);
		if (item)
		{
			return GetGame().ConfigGetFloat("CfgVehicles " + item.GetType() + " Protection " + protectionType);
		}
		
		return 0;
	}
	
	float GetTerjeProtectionAdvanced(string protectionType, float power)
	{		
		ItemBase item = GetTerjeProtectionElement(protectionType);
		if (item)
		{
			string configPath = "CfgVehicles " + item.GetType() + " Protection " + protectionType;
			if (GetGame().ConfigIsExisting(configPath + "Values") && GetGame().ConfigIsExisting(configPath + "Thresholds"))
			{
				array<float> protectionValues();
				GetGame().ConfigGetFloatArray(configPath + "Values", protectionValues);
				
				array<float> protectionThresholds();
				GetGame().ConfigGetFloatArray(configPath + "Thresholds", protectionThresholds);
				
				for (int i = 0; i < protectionThresholds.Count(); i++)
				{
					if (power < protectionThresholds.Get(i))
					{
						return protectionValues.Get(i);
					}
				}
				
				return 0;
			}
			else
			{
				return GetGame().ConfigGetFloat(configPath);
			}
		}
		
		return 0;
	}
	
	protected void OnTerjeLiquidTypeChanged(int oldType, int newType)
	{
	
	}
	
	InventoryLocationType GetTerjeCurrentInventoryLocationType()
	{
		InventoryLocation il = new InventoryLocation();
		GetInventory().GetCurrentInventoryLocation( il );
		return il.GetType();
	}
	
	void ApplyTerjeConsumableEffects(PlayerBase player, float amount)
	{
		if (GetGame().IsDedicatedServer())
		{
			TerjeConsumableEffects medEffects = new TerjeConsumableEffects();
			if (IsLiquidContainer())
			{
				int liquid_type = GetLiquidType();
				if (liquid_type == LIQUID_TERJE_CUSTOM)
				{
					string customLiquidClassName = GetTerjeLiquidClassname();
					medEffects.Apply(null, "CfgTerjeCustomLiquids " + customLiquidClassName, player, amount);
				}
				else
				{
					string vanillaLiquidClassName = Liquid.GetLiquidClassname(liquid_type);
					medEffects.Apply(null, "CfgLiquidDefinitions " + vanillaLiquidClassName, player, amount);
				}
			}
			else
			{
				medEffects.Apply(this, "CfgVehicles " + GetType(), player, amount);
			}
		}
	}
	
	// 0 - Do not override
	// 1 - Override with consumable effect
	// 2 - Override with default description + consumable effect
	int TerjeOverrideDescriptionByConsumableEffects()
	{
		return 0;
	}
	
	override bool DescriptionOverride(out string output)
	{
		int overrideType = TerjeOverrideDescriptionByConsumableEffects();
		if (overrideType > 0)
		{
			if (overrideType == 2)
			{
				output = ConfigGetString("descriptionShort") + "<br/>";
			}
			else
			{
				output = "";
			}
			
			TerjeConsumableEffects medEffects = new TerjeConsumableEffects;
			if (IsLiquidContainer())
			{
				int liquid_type = GetLiquidType();
				string liquidClassName = Liquid.GetLiquidClassname(liquid_type);
				output = output + medEffects.Describe(null, "CfgLiquidDefinitions " + liquidClassName);
			}
			else
			{
				output = output + medEffects.Describe(this, "CfgVehicles " + GetType());
			}
			
			return true;
		}
		
		return super.DescriptionOverride(output);
	}
	
	void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		string terjeLiquidClassname = GetTerjeLiquidClassname();
		if (terjeLiquidClassname != "")
		{
			ctx.WriteString("liquid", terjeLiquidClassname);
		}
	}
	
	void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		string terjeLiquidClassname;
		if (ctx.ReadString("liquid", terjeLiquidClassname))
		{
			m_terjeLiquidType = TerjeCustomLiquids.GetInstance().GetLiquidIndexByType(terjeLiquidClassname);
		}
		else
		{
			m_terjeLiquidType = 0;
		}
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		TerjeStorageHelpers.SetActualTerjeStorageVersion();
		if (TerjeStorageHelpers.GetTerjeStorageVersion() == 1)
		{
			TerjeStorageWritingContext terjeStorageCtx();
			OnTerjeStoreSave(terjeStorageCtx);
			terjeStorageCtx.OnStoreSave(ctx);
		}
		
		super.OnStoreSave(ctx);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		int terjeStorageVersion = TerjeStorageHelpers.GetTerjeStorageVersion();
		if (terjeStorageVersion == 1)
		{
			TerjeStorageReadingContext terjeStorageCtx();
			if (!terjeStorageCtx.OnStoreLoad(ctx))
			{
				return false;
			}
			
			OnTerjeStoreLoad(terjeStorageCtx);
		}
		
		return super.OnStoreLoad(ctx, version);
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		if (m_terjeLiquidType > 0)
		{
			SetTerjeLiquidType(m_terjeLiquidType);
		}
	}

	
	bool IsTerjeWholeFish()
	{
		return ConfigGetBool("wholeFish");
	}
}