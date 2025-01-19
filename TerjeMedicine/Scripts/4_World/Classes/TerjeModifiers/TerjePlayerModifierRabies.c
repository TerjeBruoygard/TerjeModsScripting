// <copyright file="TerjePlayerModifierRabies.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierRabies : TerjePlayerModifierBase
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
		if (player.GetTerjeStats().GetRabiesCure(antibioticLevel, antibioticTime))
		{
			if (antibioticTime > 0)
			{
				player.GetTerjeStats().SetRabiesCure(antibioticLevel, antibioticTime - deltaTime);
			}
			else if (antibioticLevel > 0)
			{
				player.GetTerjeStats().SetRabiesCure(0, 0);
			}
		}
		
		float vacineTime = player.GetTerjeStats().GetRabiesVacineValue();
		if (vacineTime > 0)
		{
			player.GetTerjeStats().SetRabiesVacineValue(vacineTime - deltaTime);
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_RABIES_ENABLED) == false)
		{
			player.GetTerjeStats().SetRabiesValue(0);
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
		
		float rabiesValue = player.GetTerjeStats().GetRabiesValue();
		int rabiesIntOrig = (int)rabiesValue;
		
		float vacineModifier = 1.0;
		if (vacineTime > 1)
		{
			vacineModifier = 0.5;
		}
		
		float immunityMod;
		if (player.GetTerjeSkills() && player.GetTerjeSkills().GetSkillModifierValue("immunity", "resdiseasesmod", immunityMod))
		{
			immunityMod = Math.Clamp(1.5 - immunityMod, 0.5, 1.0);
		}
		else
		{
			immunityMod = 1.0;
		}
		
		float perkRabResist;
		if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("immunity", "rabres", perkRabResist))
		{
			perkRabResist = 1.0 - Math.Clamp(perkRabResist, 0.0, 1.0);
		}
		else
		{
			perkRabResist = 1.0;
		}
		
		if (rabiesValue > 0)
		{			
			if (rabiesValue > 0.1)
			{
				float rabiesIncPerSec = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_INC_PER_SEC, rabiesIncPerSec);
				rabiesValue = rabiesValue + (rabiesIncPerSec * vacineModifier * immunityMod * perkRabResist * deltaTime);
			}
			
			int rabiesLevel = (int)rabiesValue;
			if (antibioticLevel > 0 && antibioticLevel >= rabiesLevel)
			{
				float rabiesDecPerSec = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_DEC_PER_SEC, rabiesDecPerSec);
				float antibioticStrength = (antibioticLevel - rabiesLevel) + 1;
				rabiesValue = rabiesValue - (antibioticStrength * rabiesDecPerSec * deltaTime);	
			}
			
			if (rabiesValue < 1.0 && vacineTime > 1)
			{
				rabiesValue = 0;
			}
			
			player.GetTerjeStats().SetRabiesValue(rabiesValue);
			
			if (rabiesLevel >= 1)
			{
				float rabiesLightSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_LIGHT_SYMPTOM_CHANCE, rabiesLightSymptomChance);
				if (Math.RandomFloat01() < rabiesLightSymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_HOT);
				}
			}
			
			if (rabiesLevel >= 2)
			{
				float rabiesHeavySymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_HEAVY_SYMPTOM_CHANCE, rabiesHeavySymptomChance);
				if (Math.RandomFloat01() < rabiesHeavySymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_HAND_SHIVER);
				}
			}
			
			if (rabiesLevel >= 3)
			{
				float rabiesCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_CRITICAL_DMG_MULTIPLIER, rabiesCriticalDmgMultiplier);
				float dmgForce = (rabiesValue - 3.0) * rabiesCriticalDmgMultiplier;
				player.DecreaseHealth("GlobalHealth", "Health", dmgForce * deltaTime);
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
				
				float rabiesCriticalSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_CRITICAL_SYMPTOM_CHANCE, rabiesCriticalSymptomChance);
				if (Math.RandomFloat01() < rabiesCriticalSymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_GASP);
				}
			}
			
			if (rabiesIntOrig > 0 && rabiesValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_RABIES_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 1200;
				}
			}
		}
	}
}
