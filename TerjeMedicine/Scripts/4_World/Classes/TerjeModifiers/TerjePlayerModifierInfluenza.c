// <copyright file="TerjePlayerModifierInfluenza.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierInfluenza : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	
	override float GetTimeout()
	{
		return 1.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		int antibioticLevel = 0;
		float antibioticTime = 0;
		if (player.GetTerjeStats().GetAntibiotic(antibioticLevel, antibioticTime))
		{
			if (antibioticTime > 0)
			{
				player.GetTerjeStats().SetAntibiotic(antibioticLevel, antibioticTime - deltaTime);
			}
			else if (antibioticLevel > 0)
			{
				player.GetTerjeStats().SetAntibiotic(0, 0);
			}
		}
		
		float vacineTime = player.GetTerjeStats().GetInfluenzaVacineValue();
		if (vacineTime > 0)
		{
			player.GetTerjeStats().SetInfluenzaVacineValue(vacineTime - deltaTime);
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_INFLUENZA_ENABLED) == false)
		{
			player.GetTerjeStats().SetInfluenzaValue(0);
			return;
		}
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (m_immunityInterval > 0)
		{
			m_immunityInterval = m_immunityInterval - deltaTime;
		}
		
		float influenzaIncPerSec = 0;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_INC_PER_SEC, influenzaIncPerSec);
		
		float influenzaTemperatureDropModifier = 0;
		float influenzaValue = player.GetTerjeStats().GetInfluenzaValue();
		int influenzaIntOrig = (int)influenzaValue;
		
		float vacineModifier = 1.0;
		if (vacineTime > 1)
		{
			vacineModifier = 0.5;
		}
		
		float immunityMod;
		if (player.GetTerjeSkills() && player.GetTerjeSkills().GetSkillModifierValue("immunity", "resdiseasesmod", immunityMod))
		{
			immunityMod = 1.0 - Math.Clamp(immunityMod, 0.0, 0.9);
		}
		else
		{
			immunityMod = 1.0;
		}
		
		float perkColdresMod;
		if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("immunity", "coldres", perkColdresMod))
		{
			perkColdresMod = 1.0 - Math.Clamp(perkColdresMod, 0.0, 1.0);
		}
		else
		{
			perkColdresMod = 1.0;
		}
		
		if (vacineTime < 1 || influenzaValue > 1)
		{
			float currHeatComf = player.GetStatHeatComfort().Get();
			if (currHeatComf < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_EMPTY)
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_TEMPERATURE_EMPTY_MODIFIER, influenzaTemperatureDropModifier);
				influenzaValue = influenzaValue + (influenzaIncPerSec * vacineModifier * immunityMod * perkColdresMod * deltaTime * influenzaTemperatureDropModifier);
			}
			else if (currHeatComf < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_CRITICAL)
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_TEMPERATURE_CRIT_MODIFIER, influenzaTemperatureDropModifier);
				influenzaValue = influenzaValue + (influenzaIncPerSec * vacineModifier * immunityMod * perkColdresMod * deltaTime * influenzaTemperatureDropModifier);
			}
			else if (currHeatComf < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_TEMPERATURE_WARN_MODIFIER, influenzaTemperatureDropModifier);
				influenzaValue = influenzaValue + (influenzaIncPerSec * vacineModifier * immunityMod * perkColdresMod * deltaTime * influenzaTemperatureDropModifier);
			}
		}
		
		int influenzaVanillaAgents = player.GetSingleAgentCount(eAgents.INFLUENZA);
		if (influenzaVanillaAgents > 0)
		{
			if (vacineTime < 1 || influenzaValue > 1)
			{
				float influenzaTransferAgentsModifier = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_TRANSFER_AGENTS_MODIFIER, influenzaTransferAgentsModifier);
				influenzaValue = influenzaValue + (influenzaTransferAgentsModifier * vacineModifier * immunityMod * perkColdresMod * (float)influenzaVanillaAgents);
			}
			
			player.RemoveAgent(eAgents.INFLUENZA);
		}
		
		if (influenzaValue > 0)
		{
			float influenzaDecPerSec = 1;
			float influenzaImmunityHealThreshold = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_DEC_PER_SEC, influenzaDecPerSec);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_IMMUNITY_HEAL_THRESHOLD, influenzaImmunityHealThreshold);

			float perkFtwarmMod;
			if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("immunity", "ftwarm", perkFtwarmMod))
			{
				influenzaImmunityHealThreshold = influenzaImmunityHealThreshold * (1.0 + perkFtwarmMod);
				influenzaDecPerSec = influenzaDecPerSec * (1.0 + perkFtwarmMod);
			}
						
			if (player.GetHeatBufferStage() > 0 && influenzaValue < influenzaImmunityHealThreshold)
			{				
				float influenzaDefaultImmunityStrength = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_DEFAULT_IMMUNITY_STRENGTH, influenzaDefaultImmunityStrength);
				influenzaValue = influenzaValue - (influenzaDefaultImmunityStrength * influenzaDecPerSec * deltaTime);
			}
			else if (influenzaValue > GetInfluenzaVirusAutoReproductionThreshold(player))
			{
				if (vacineTime < 1 || influenzaValue > 1)
				{
					influenzaValue = influenzaValue + (influenzaIncPerSec * vacineModifier * immunityMod * perkColdresMod * deltaTime);
				}
			}
			
			int influenzaLevel = (int)influenzaValue;
			if (antibioticLevel > 0 && antibioticLevel >= influenzaLevel)
			{
				float antibioticStrength = (antibioticLevel - influenzaLevel) + 1;
				influenzaValue = influenzaValue - (antibioticStrength * influenzaDecPerSec * deltaTime);	
			}
			
			if (influenzaValue < 1.0 && vacineTime > 1)
			{
				influenzaValue = 0.0;
			}
			
			player.GetTerjeStats().SetInfluenzaValue(influenzaValue);
			
			if (influenzaLevel == 1)
			{
				float influenzaLightSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_LIGHT_SYMPTOM_CHANCE, influenzaLightSymptomChance);
				if (Math.RandomFloat01() < influenzaLightSymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_SNEEZE);
				}
			}
			else if (influenzaLevel == 2)
			{
				float influenzaHeavySymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_HEAVY_SYMPTOM_CHANCE, influenzaHeavySymptomChance);
				if (Math.RandomFloat01() < influenzaHeavySymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_COUGH);
				}
			}
			else if (influenzaLevel >= 3)
			{
				float influenzaCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_CRITICAL_DMG_MULTIPLIER, influenzaCriticalDmgMultiplier);
				float dmgForce = (influenzaValue - 3.0) * influenzaCriticalDmgMultiplier;
				player.DecreaseHealth("GlobalHealth", "Health", dmgForce * deltaTime);
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
				
				float influenzaCriticalSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_CRITICAL_SYMPTOM_CHANCE, influenzaCriticalSymptomChance);
				if (Math.RandomFloat01() < influenzaCriticalSymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_COUGH);
				}
			}
			
			if (influenzaIntOrig > 0 && influenzaValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_INFLUENZA_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 900;
				}
			}
		}
	}
	
	float GetInfluenzaVirusAutoReproductionThreshold(PlayerBase player)
	{
		return 0.5;
	}
}
