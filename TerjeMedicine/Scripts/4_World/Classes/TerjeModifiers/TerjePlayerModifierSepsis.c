// <copyright file="TerjePlayerModifierSepsis.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierSepsis : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	
	override float GetTimeout()
	{
		return 0.5;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
				
		float antisepsisTime = player.GetTerjeStats().GetAntisepsisValue();
		if (antisepsisTime > 0)
		{	
			player.GetTerjeStats().SetAntisepsisValue(antisepsisTime - deltaTime);
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SEPSIS_ENABLED) == false)
		{
			player.GetTerjeStats().SetSepsisValue(0);
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

		float sepsisValue = player.GetTerjeStats().GetSepsisValue();
		if (sepsisValue > 0)
		{
			int sepsisIntOrig = (int)sepsisValue;
			
			float immunityMod;
			if (player.GetTerjeSkills() && player.GetTerjeSkills().GetSkillModifierValue("immunity", "resdiseasesmod", immunityMod))
			{
				immunityMod = 1.0 - Math.Clamp(immunityMod, 0.0, 0.9);
			}
			else
			{
				immunityMod = 1.0;
			}
			
			float sepsisIncPerSec = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_INC_PER_SEC, sepsisIncPerSec);	
			sepsisValue = sepsisValue + (sepsisIncPerSec * immunityMod * deltaTime);
			
			if (antisepsisTime > 0)
			{
				float sepsisDecPerSec = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_DEC_PER_SEC, sepsisDecPerSec);
				sepsisValue = sepsisValue - (sepsisDecPerSec * deltaTime);	
			}
			
			player.GetTerjeStats().SetSepsisValue(sepsisValue);
			
			if (sepsisValue > 1)
			{
				float sepsisLightSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_LIGHT_SYMPTOM_CHANCE, sepsisLightSymptomChance);
				if (Math.RandomFloat01() < sepsisLightSymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
				}
			}
			
			if (sepsisValue > 2)
			{
				float sepsisHeavySymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_HEAVY_SYMPTOM_CHANCE, sepsisHeavySymptomChance);
				if (Math.RandomFloat01() < sepsisHeavySymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_HOT);
				}
			}
			
			if (sepsisValue > 3)
			{
				float sepsisCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_CRITICAL_DMG_MULTIPLIER, sepsisCriticalDmgMultiplier);
				float dmgForce = (sepsisValue - 3.0) * sepsisCriticalDmgMultiplier;
				player.DecreaseHealth("GlobalHealth", "Health", dmgForce * deltaTime);
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
				
				float sepsisCriticalSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_CRITICAL_SYMPTOM_CHANCE, sepsisCriticalSymptomChance);
				if (Math.RandomFloat01() < sepsisCriticalSymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
				}
			}
			
			if (sepsisIntOrig > 0 && sepsisValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_SEPSIS_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 900;
				}
			}
		}
	}
}
