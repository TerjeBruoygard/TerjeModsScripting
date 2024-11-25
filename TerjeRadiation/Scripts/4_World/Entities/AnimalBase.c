// <copyright file="AnimalBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class AnimalBase
{
	private const int TERJE_RAD_STORE_BEGIN_MARKER_V1 = 1850662830;
	private const int TERJE_RAD_STORE_END_MARKER_V1 = 1697783151;
	private float m_terjeRadiationUpdate = 0;
	private float m_terjeRadiationServer = 0;
	private int m_terjeRadiationSynch = 0;
	
	void AnimalBase()
	{
		RegisterNetSyncVariableInt("m_terjeRadiationSynch", 0, TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SYNCH_MAX);
	}
	
	override bool AddTerjeRadiation(float rAmount)
	{
		if (GetGame().IsDedicatedServer())
		{
			m_terjeRadiationServer = Math.Clamp(m_terjeRadiationServer + rAmount, 0, TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SERVER_MAX);
			
			int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SYNCH_DIVIDER);
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
			return m_terjeRadiationSynch * TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SYNCH_DIVIDER;
		}
	}
	
	override void CommandHandler(float dt, int currentCommandID, bool currentCommandFinished)
	{
		super.CommandHandler(dt, currentCommandID, currentCommandFinished);
		
		if (GetGame().IsDedicatedServer())
		{
			m_terjeRadiationUpdate += dt;
			if (m_terjeRadiationUpdate > 30)
			{
				PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
				if (plugin)
				{
					float radioactiveGlobalModifier = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_AREAS_POWER_MOD);
					AddTerjeRadiation(plugin.CalculateTerjeEffectValue(this, "rad") * radioactiveGlobalModifier * m_terjeRadiationUpdate);
				}
				
				m_terjeRadiationUpdate = 0;
			}
			
			if (m_terjeRadiationServer > TerjeRadiationConstants.RADIATION_ANIMALS_DAMAGE_THRESHOLD && GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_DAMAGE_ANIMALS))
			{
				DecreaseHealth("", "", TerjeRadiationConstants.RADIATION_ANIMALS_DAMAGE_PER_SEC * dt);
			}
		}
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		TerjeStorageSafeMarkup.WriteMarker(ctx, TERJE_RAD_STORE_BEGIN_MARKER_V1);
		ctx.Write(m_terjeRadiationServer);
		TerjeStorageSafeMarkup.WriteMarker(ctx, TERJE_RAD_STORE_END_MARKER_V1);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
		{
			return false;
		}
		
		if (!TerjeStorageSafeMarkup.VerifyMarker(ctx, TERJE_RAD_STORE_BEGIN_MARKER_V1))
		{
			return false;
		}
		
		if (!ctx.Read(m_terjeRadiationServer))
		{
			m_terjeRadiationServer = 0;
			return false;
		}
		
		if (!TerjeStorageSafeMarkup.VerifyMarker(ctx, TERJE_RAD_STORE_END_MARKER_V1))
		{
			return false;
		}
		
		return true;
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SYNCH_DIVIDER);
		if (newRadiationSynchValue != m_terjeRadiationSynch)
		{
			m_terjeRadiationSynch = newRadiationSynchValue;
			SetSynchDirty();
		}
	}
}