// <copyright file="CarScript.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class CarScript
{
	private float m_terjeRadiationUpdate = 0;
	private float m_terjeRadiationServer = 0;
	private int m_terjeRadiationSynch = 0;
	
	void CarScript()
	{
		RegisterNetSyncVariableInt("m_terjeRadiationSynch", 0, TerjeRadiationConstants.RADIATION_VEHICLE_ACCUMULATOR_SYNCH_MAX);
	}
	
	override bool AddTerjeRadiation(float rAmount)
	{
		if (GetGame().IsDedicatedServer() && IsTerjeRadiationAccumulated())
		{
			if (ConfigIsExisting("terjeStaticRadiationValue"))
			{
				return false; // Disable radiation increment/decrement for items with a static radiation value.
			}
			
			m_terjeRadiationServer = Math.Clamp(m_terjeRadiationServer + rAmount, 0, TerjeRadiationConstants.RADIATION_VEHICLE_ACCUMULATOR_SERVER_MAX);
			
			int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_VEHICLE_ACCUMULATOR_SYNCH_DIVIDER);
			if (newRadiationSynchValue != m_terjeRadiationSynch)
			{
				m_terjeRadiationSynch = newRadiationSynchValue;
				SetSynchDirty();
			}
			
			return true;
		}

		return false;
	}
	
	override float GetTerjeRadiation()
	{
		if (ConfigIsExisting("terjeStaticRadiationValue"))
		{
			return ConfigGetFloat("terjeStaticRadiationValue");
		}
		
		if (GetGame().IsDedicatedServer())
		{
			return m_terjeRadiationServer;
		}
		else
		{
			return m_terjeRadiationSynch * TerjeRadiationConstants.RADIATION_VEHICLE_ACCUMULATOR_SYNCH_DIVIDER;
		}
	}
	
	override bool IsTerjeRadiationAccumulated()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_DO_VEHICLES_ACCUMULATE);
	}
	
	override void OnUpdate( float dt )
	{
		super.OnUpdate(dt);
		
		if (GetGame().IsDedicatedServer())
		{
			m_terjeRadiationUpdate += dt;
			if (m_terjeRadiationUpdate > 30)
			{
				PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
				if (plugin)
				{
					float currentRadiation = GetTerjeRadiation();
					float radioactiveGlobalModifier = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_AREAS_POWER_MOD);
					float rAmount = plugin.CalculateTerjeEffectValue(this, "rad") * radioactiveGlobalModifier;
					rAmount -= GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_ITEM_LOSE_PER_SEC);
					
					if (rAmount > 0)
					{
						float maxAccumulatedRadLimit = rAmount * GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_ZONE_POWER_TO_RAD_LIMIT);
						if (currentRadiation < maxAccumulatedRadLimit)
						{
							AddTerjeRadiation(Math.Clamp(rAmount * m_terjeRadiationUpdate, 0, maxAccumulatedRadLimit - currentRadiation));
						}
					}
					else
					{
						AddTerjeRadiation(rAmount * m_terjeRadiationUpdate);
					}
				}
				
				m_terjeRadiationUpdate = 0;
			}
		}
	}
	
	override void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		super.OnTerjeStoreSave(ctx);
		ctx.WriteFloat("rad", m_terjeRadiationServer);
	}
	
	override void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		super.OnTerjeStoreLoad(ctx);
		ctx.ReadFloat("rad", m_terjeRadiationServer);
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_VEHICLE_ACCUMULATOR_SYNCH_DIVIDER);
		if (newRadiationSynchValue != m_terjeRadiationSynch)
		{
			m_terjeRadiationSynch = newRadiationSynchValue;
			SetSynchDirty();
		}
	}
}