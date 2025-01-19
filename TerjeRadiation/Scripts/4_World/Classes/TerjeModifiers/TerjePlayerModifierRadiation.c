// <copyright file="TerjePlayerModifierRadiation.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierRadiation : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		
		int antiradLevel = 0;
		float antiradTime = 0;
		if (player.GetTerjeStats().GetAntirad(antiradLevel, antiradTime))
		{
			if (antiradTime > 0)
			{
				player.GetTerjeStats().SetAntirad(antiradLevel, antiradTime - deltaTime);
			}
			else if (antiradLevel > 0)
			{
				player.GetTerjeStats().SetAntirad(0, 0);
			}
		}
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (m_immunityInterval > 0)
		{
			m_immunityInterval = m_immunityInterval - deltaTime;
		}
		
		float radiationValue = player.GetTerjeStats().GetRadiationValue();
		float radiationAccumulator = player.GetTerjeStats().GetRadiationAccumulated();
		if (radiationAccumulator > 0)
		{
			if (antiradLevel > 0)
			{
				float bufferMedDecPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_MEDS_DEC_PER_SEC) * antiradLevel * deltaTime;
				if (bufferMedDecPerSec > 0)
				{
					radiationAccumulator -= bufferMedDecPerSec;
				}
			}
			else
			{
				float bufferCommonDecPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_COMMON_DEC_PER_SEC) * deltaTime;
				if (bufferCommonDecPerSec > 0)
				{
					radiationAccumulator -= bufferCommonDecPerSec;
				}
			}
			
			if (radiationAccumulator > GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_CRITICAL_DISEASE_THRESHOLD))
			{
				radiationValue += GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_CRITICAL_DISEASE_INCREMENT) * deltaTime;
			}
			else if (radiationAccumulator > GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_HEAVY_DISEASE_THRESHOLD))
			{
				if (radiationValue < 2.5)
				{
					radiationValue += GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_HEAVY_DISEASE_INCREMENT) * deltaTime;
				}
			}
			else if (radiationAccumulator > GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_LIGHT_DISEASE_THRESHOLD))
			{
				if (radiationValue < 1.5)
				{
					radiationValue += GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_LIGHT_DISEASE_INCREMENT) * deltaTime;
				}
			}

			player.GetTerjeStats().SetRadiationAccumulated(radiationAccumulator);
		}
		
		if (radiationValue > 0)
		{
			int radiationLevel = (int)radiationValue;
			float radiationDecPerSec = 0;
			if (antiradLevel > 0)
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_MEDS_DEC_PER_SEC, radiationDecPerSec);
				radiationDecPerSec = radiationDecPerSec * ((antiradLevel - radiationLevel) + 1);
			}
			else
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_COMMON_DEC_PER_SEC, radiationDecPerSec);	
			}
			
			float immunityMod;
			if (player.GetTerjeSkills() && player.GetTerjeSkills().GetSkillModifierValue("immunity", "resdiseasesmod", immunityMod))
			{
				immunityMod = 1.0 + immunityMod;
			}
			else
			{
				immunityMod = 1.0;
			}
			
			float perkRadgenMod;
			if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("immunity", "radregen", perkRadgenMod))
			{
				perkRadgenMod = 1.0 + perkRadgenMod;
			}
			else
			{
				perkRadgenMod = 1.0;
			}
			
			radiationValue = radiationValue - (radiationDecPerSec * immunityMod * perkRadgenMod * deltaTime);
			player.GetTerjeStats().SetRadiationValue(radiationValue);
			
			if (radiationValue > 1)
			{
				float radiationLightSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_LIGHT_SYMPTOM_CHANCE, radiationLightSymptomChance);
				if (Math.RandomFloat01() < radiationLightSymptomChance * deltaTime)
				{
					float radiationVomitForceModifier = 1;
					GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_VOMIT_FORCE_MODIFIER, radiationVomitForceModifier);					
					player.CallTerjeVomitSymptom(Math.RandomIntInclusive(3, 5), radiationVomitForceModifier);
				}
			}
			
			if (radiationValue > 2)
			{
				float radiationHeavySymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_HEAVY_SYMPTOM_CHANCE, radiationHeavySymptomChance);
				if (Math.RandomFloat01() < radiationHeavySymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
					player.GetBleedingManagerServer().AttemptAddBleedingSource( Math.RandomIntInclusive(0, 5) );
				}
				
				float radiationCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_CRITICAL_DMG_MULTIPLIER, radiationCriticalDmgMultiplier);
				float dmgForce = (radiationValue - 3.0) * radiationCriticalDmgMultiplier;
				player.DecreaseHealth("GlobalHealth", "Health", dmgForce * deltaTime);
				
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
			}
			
			if (radiationLevel > 0 && radiationValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.RADIATION_IMMUNITY_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 900;
				}
			}
		}
		
		player.UpdateTerjeRadiationAccumulated();
	}
}
