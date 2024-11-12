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
		RegisterNetSyncVariableInt("m_terjeRadiationSynch", 0, TerjeMedicineConstants.RADIATION_VEHICLE_ACCUMULATOR_SYNCH_MAX);
	}
	
	override bool AddTerjeRadiation(float rAmount)
	{
		if (GetGame().IsDedicatedServer() && IsTerjeRadiationAccumulated())
		{
			m_terjeRadiationServer = Math.Clamp(m_terjeRadiationServer + rAmount, 0, TerjeMedicineConstants.RADIATION_VEHICLE_ACCUMULATOR_SERVER_MAX);
			
			int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeMedicineConstants.RADIATION_VEHICLE_ACCUMULATOR_SYNCH_DIVIDER);
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
		if (GetGame().IsDedicatedServer())
		{
			return m_terjeRadiationServer;
		}
		else
		{
			return m_terjeRadiationSynch * TerjeMedicineConstants.RADIATION_VEHICLE_ACCUMULATOR_SYNCH_DIVIDER;
		}
	}
	
	override bool IsTerjeRadiationAccumulated()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_RADIATION_DO_VEHICLES_ACCUMULATE);
	};
	
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
					float radioactiveGlobalModifier = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIOACTIVE_AREAS_POWER_MOD);
					AddTerjeRadiation(plugin.CalculateTerjeEffectValue(this, "rad") * radioactiveGlobalModifier * m_terjeRadiationUpdate);
				}
				
				m_terjeRadiationUpdate = 0;
			}
		}
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_terjeRadiationServer);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
		{
			return false;
		}
		
		if (!ctx.Read(m_terjeRadiationServer))
		{
			m_terjeRadiationServer = 0;
			return false;
		}
		
		return true;
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeMedicineConstants.RADIATION_VEHICLE_ACCUMULATOR_SYNCH_DIVIDER);
		if (newRadiationSynchValue != m_terjeRadiationSynch)
		{
			m_terjeRadiationSynch = newRadiationSynchValue;
			SetSynchDirty();
		}
	}
};