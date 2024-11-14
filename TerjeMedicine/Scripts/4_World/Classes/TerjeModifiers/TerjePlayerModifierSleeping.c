// <copyright file="TerjePlayerModifierSleeping.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierSleeping : TerjePlayerModifierBase
{
	private float m_sleepingLastValue = -1;
	private float m_terjeMedicineSleepingSoundTimer = 0;
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		// Handle visual stats
		float currentSleepingValue = player.GetTerjeStats().GetSleepingValue();
		if (m_sleepingLastValue < 0)
		{
			m_sleepingLastValue = currentSleepingValue;
		}
		
		int sleepTendency = 0;
		int sleepLevel = 0;
		float sleepingDiffTend = currentSleepingValue - m_sleepingLastValue;
		if (sleepingDiffTend < 0)
		{
			if (sleepingDiffTend > TerjeMedicineConstants.SLEEPING_TENDENCY_MINUS_STAGE1) sleepTendency = -1;
			else if (sleepingDiffTend > TerjeMedicineConstants.SLEEPING_TENDENCY_MINUS_STAGE2) sleepTendency = -2;
			else sleepTendency = -3;
		}
		else if (sleepingDiffTend > 0)
		{
			if (sleepingDiffTend < TerjeMedicineConstants.SLEEPING_TENDENCY_PLUS_STAGE1) sleepTendency = 1;
			else if (sleepingDiffTend < TerjeMedicineConstants.SLEEPING_TENDENCY_PLUS_STAGE2) sleepTendency = 2;
			else sleepTendency = 3;
		}

		if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_LEVEL5) sleepLevel = 5;
		else if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_LEVEL4) sleepLevel = 4;
		else if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_LEVEL3) sleepLevel = 3;
		else if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_LEVEL2) sleepLevel = 2;
		else sleepLevel = 1;

		player.GetTerjeStats().SetSleepingLevelAndTendency(sleepLevel, sleepTendency);
		m_sleepingLastValue = currentSleepingValue;
		
		// Handle energy-drink effects
		float sleepingIncValue;
		float sleepingIncTimer;
		bool isEnergedMarker = (sleepLevel == 1);
		if (player.GetTerjeStats().GetSleepingIncrement(sleepingIncValue, sleepingIncTimer))
		{
			sleepingIncTimer -= deltaTime;
			if (sleepingIncTimer <= 0)
			{
				sleepingIncValue = 0;
			}
			
			if (sleepingIncValue > 0)
			{
				currentSleepingValue += sleepingIncValue * deltaTime;
				isEnergedMarker = true;
			}
			
			player.GetTerjeStats().SetSleepingIncrement(sleepingIncValue, sleepingIncTimer);
		}
		
		// Handle action stats
		float sleepingDiff = 0;
		float sleepingDecPerSec = 0;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_DEC_PER_SEC_COMMON, sleepingDecPerSec);
		
		sleepingDiff = sleepingDiff - (sleepingDecPerSec * deltaTime);	
		if (player.GetTerjeStats().GetRadiationLevel() > 0)
		{
			float sleepingDecRadSick = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_DEC_PER_SEC_RADIATION, sleepingDecRadSick);
			sleepingDiff = sleepingDiff - (sleepingDecRadSick * deltaTime);
		}

		TerjeMedicineSleepingLevel sleepingLevel = TerjeMedicineSleepingLevel.TERJESL_NONE;	
		bool isUnconsciousMarker = player.IsUnconscious();
		bool isSleepingMarker = (player.GetEmoteManager() && player.GetEmoteManager().IsPlayerSleeping());
		if (isSleepingMarker || isUnconsciousMarker || isEnergedMarker)
		{
			float perkFsleepMod;
			if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("immunity", "fsleep", perkFsleepMod))
			{
				perkFsleepMod = 1.0 + perkFsleepMod;
			}
			else
			{
				perkFsleepMod = 1.0;
			}
			
			float heatValue = player.GetStatHeatComfort().Get();
			if (player.HasTerjeSicknesOrInjures())
			{
				sleepingLevel = TerjeMedicineSleepingLevel.TERJESL_SICK;
			}
			else if (isEnergedMarker)
			{
				sleepingLevel = TerjeMedicineSleepingLevel.TERJESL_ENERGED;
			}
			else if (heatValue < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)
			{
				sleepingLevel = TerjeMedicineSleepingLevel.TERJESL_COLD;
			}
			else if (heatValue > PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_CRITICAL)
			{
				sleepingLevel = TerjeMedicineSleepingLevel.TERJESL_HOT;
			}
			else if (player.GetHeatBufferStage() > 0)
			{
				float sleepingIncComfort = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_INC_COMFORT, sleepingIncComfort);
				sleepingLevel = TerjeMedicineSleepingLevel.TERJESL_PERFECT;
				sleepingDiff = sleepingDiff + (sleepingIncComfort * perkFsleepMod * deltaTime);
			}
			else
			{
				float sleepingIncCommon = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_INC_COMMON, sleepingIncCommon);
				sleepingLevel = TerjeMedicineSleepingLevel.TERJESL_COMFORT;
				sleepingDiff = sleepingDiff + (sleepingIncCommon * perkFsleepMod * deltaTime);
			}
		}
		
		int sleepingLevelInt = (int)sleepingLevel;
		player.GetTerjeStats().SetSleepingState(sleepingLevelInt);
		
		if (sleepingLevelInt > 0 && !isUnconsciousMarker)
		{
			m_terjeMedicineSleepingSoundTimer = m_terjeMedicineSleepingSoundTimer + deltaTime;
			if (m_terjeMedicineSleepingSoundTimer >= 5)
			{
				m_terjeMedicineSleepingSoundTimer = 0;
				if (player.IsMale()) GetGame().CreateObject("TerjeSoundEmitter_SleepingMale", player.GetPosition());
				else GetGame().CreateObject("TerjeSoundEmitter_SleepingFemale", player.GetPosition());
			}
			
			float sleepingIncHealth = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_HEALTH_INC, sleepingIncHealth);
			player.AddHealth("GlobalHealth", "Health", sleepingIncHealth * deltaTime);
		}
		else
		{
			m_terjeMedicineSleepingSoundTimer = -10;
		}
		
		currentSleepingValue = currentSleepingValue + sleepingDiff;
		player.GetTerjeStats().SetSleepingValue(currentSleepingValue);
		
		if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_UNCONSCIOUS) 
		{
			player.SetHealth("GlobalHealth","Shock",0);
		}
		
		if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_CRITICAL) 
		{
			float sleepingHealthDecCritical = 1;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_HEALTH_DEC, sleepingHealthDecCritical);
			player.DecreaseHealth("GlobalHealth", "Health", sleepingHealthDecCritical);
		}
	}
};
