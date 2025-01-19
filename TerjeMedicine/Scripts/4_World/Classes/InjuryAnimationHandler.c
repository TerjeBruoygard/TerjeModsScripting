// <copyright file="InjuryAnimationHandler.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class InjuryAnimationHandler
{
	override eInjuryHandlerLevels GetInjuryLevel(float health)
	{
		eInjuryHandlerLevels result = super.GetInjuryLevel(health);
		
		if (m_Player && m_Player.GetTerjeStats() != null && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_INJURY_ANIM))
		{
			eInjuryHandlerLevels sleepingState = CalculateSleepingState();
			eInjuryHandlerLevels mindState = CalculateMindState();
			eInjuryHandlerLevels painState = CalculatePainState();
			eInjuryHandlerLevels overdoseState = CalculateOverdoseState();
			eInjuryHandlerLevels waterEnergy = CalculateLowEnergyWaterState();
			eInjuryHandlerLevels zVirusSickness = CalculateVirusZState();
			eInjuryHandlerLevels sepsisSickness = CalculateSepsisState();
			eInjuryHandlerLevels contusionSickness = CalculateContusionState();
			eInjuryHandlerLevels hematomasSickness = CalculateHematomasState();
			eInjuryHandlerLevels influenzaSickness = CalculateInfluenzaState();
			eInjuryHandlerLevels rabiesSickness = CalculateRabiesState();
			eInjuryHandlerLevels psionicSickness = CalculatePsionicState();
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(sleepingState))
			{
				result = sleepingState;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(mindState))
			{
				result = mindState;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(painState))
			{
				result = painState;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(overdoseState))
			{
				result = overdoseState;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(waterEnergy))
			{
				result = waterEnergy;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(zVirusSickness))
			{
				result = zVirusSickness;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(sepsisSickness))
			{
				result = sepsisSickness;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(contusionSickness))
			{
				result = contusionSickness;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(hematomasSickness))
			{
				result = hematomasSickness;
			}
				
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(influenzaSickness))
			{
				result = influenzaSickness;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(rabiesSickness))
			{
				result = rabiesSickness;
			}
			
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(psionicSickness))
			{
				result = psionicSickness;
			}
		}
		
		return result;
	}
	
	private eInjuryHandlerLevels CalculateSleepingState()
	{
		int sleepLevel = m_Player.GetTerjeStats().GetSleepingLevel();
		if (sleepLevel == 5)
		{
			return eInjuryHandlerLevels.RUINED;
		}
		
		if (sleepLevel == 4)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculateMindState()
	{
		int mindLevel = m_Player.GetTerjeStats().GetMindLevel();
		if (mindLevel == 5)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}
		
		if (mindLevel == 4)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculatePainState()
	{
		int painLevel = m_Player.GetTerjeStats().GetPainLevel();
		if (painLevel == 1)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		if (painLevel == 2)
		{
			return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		
		if (painLevel == 3)
		{
			return eInjuryHandlerLevels.RUINED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculateOverdoseState()
	{
		if (m_Player.GetTerjeStats().GetOverdoseLevel() == 3)
		{
			return eInjuryHandlerLevels.RUINED;
		}
		
		if (m_Player.GetTerjeStats().GetOverdoseLevel() == 2)
		{
			return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		
		if (m_Player.GetTerjeStats().GetOverdoseLevel() == 1)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculateLowEnergyWaterState()
	{
		if (m_Player.GetStatEnergy().Get() <= PlayerConstants.SL_ENERGY_CRITICAL || m_Player.GetStatWater().Get() <= PlayerConstants.SL_WATER_CRITICAL)
		{
			return eInjuryHandlerLevels.RUINED;
		}
		
		if (m_Player.GetStatEnergy().Get() <= PlayerConstants.SL_ENERGY_LOW || m_Player.GetStatWater().Get() <= PlayerConstants.SL_WATER_LOW)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}

		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculateSepsisState()
	{
		int sepLevel = m_Player.GetTerjeStats().GetSepsisLevel();
		
		if (sepLevel == 1)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		if (sepLevel == 2)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}
		
		if (sepLevel == 3)
		{
			return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculateVirusZState()
	{
		int zvirusLevel = m_Player.GetTerjeStats().GetZVirusLevel();
		if (zvirusLevel == 1)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}
		
		if (zvirusLevel == 2)
		{
			return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		
		if (zvirusLevel == 3)
		{
			return eInjuryHandlerLevels.RUINED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculateContusionState()
	{
		if (m_Player.GetTerjeStats().GetContusion())
		{
			return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculateHematomasState()
	{
		int hematomasCount = m_Player.GetTerjeStats().GetHematomasCount();
		if (hematomasCount >= TerjeMedicineConstants.HEMATOMAS_CRITICAL_COUNT)
		{
			return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		else if (hematomasCount >= TerjeMedicineConstants.HEMATOMAS_BAD_COUNT)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}
		else if (hematomasCount >= TerjeMedicineConstants.HEMATOMAS_PAIN_COUNT)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculateInfluenzaState()
	{
		int level = m_Player.GetTerjeStats().GetInfluenzaLevel();
		if (level == 2)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		if (level == 3)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculateRabiesState()
	{
		int level = m_Player.GetTerjeStats().GetRabiesLevel();
		if (level == 1)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		if (level == 2)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}
		
		if (level == 3)
		{
			return eInjuryHandlerLevels.RUINED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculatePsionicState()
	{
		int level = m_Player.GetTerjeStats().GetMindTendency();
		
		if (level == -1)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		if (level == -2)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}
		
		if (level == -3)
		{
			return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
}