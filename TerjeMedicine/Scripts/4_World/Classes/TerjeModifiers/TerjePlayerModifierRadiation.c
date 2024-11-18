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
	};
	
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
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_RADIATION_ENABLED) == false)
		{
			player.GetTerjeStats().SetRadiationValue(0);
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
				float bufferDecPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIATION_BUFFER_DRUGS_DEC_PER_SEC) * antiradLevel * deltaTime;
				if (bufferDecPerSec > 0)
				{
					radiationAccumulator -= bufferDecPerSec;
				}
			}
			
			float transferPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIATION_TRANSFER_PER_SEC) * deltaTime;
			float transferMod = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIATION_TRANSFER_MOD) * deltaTime;
			if (transferPerSec > 0 && transferMod > 0)
			{
				if (radiationAccumulator > transferPerSec)
				{
					radiationAccumulator -= transferPerSec;
					radiationValue = radiationValue + transferMod;
				}
				else if (radiationAccumulator > 0)
				{
					radiationValue = radiationValue + (transferMod * (radiationAccumulator / transferPerSec));
					radiationAccumulator = 0;
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
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIATION_MEDS_DEC_PER_SEC, radiationDecPerSec);
				radiationDecPerSec = radiationDecPerSec * ((antiradLevel - radiationLevel) + 1);
			}
			else
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIATION_COMMON_DEC_PER_SEC, radiationDecPerSec);	
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
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIATION_LIGHT_SYMPTOM_CHANCE, radiationLightSymptomChance);
				if (Math.RandomFloat01() < radiationLightSymptomChance * deltaTime)
				{
					float radiationVomitForceModifier = 1;
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIATION_VOMIT_FORCE_MODIFIER, radiationVomitForceModifier);					
					player.CallTerjeVomitSymptom(Math.RandomIntInclusive(3, 5), radiationVomitForceModifier);
				}
			}
			
			if (radiationValue > 2)
			{
				float radiationHeavySymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIATION_HEAVY_SYMPTOM_CHANCE, radiationHeavySymptomChance);
				if (Math.RandomFloat01() < radiationHeavySymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
					player.GetBleedingManagerServer().AttemptAddBleedingSource( Math.RandomIntInclusive(0, 5) );
				}
				
				float radiationCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RADIATION_CRITICAL_DMG_MULTIPLIER, radiationCriticalDmgMultiplier);
				float dmgForce = (radiationValue - 3.0) * radiationCriticalDmgMultiplier;
				player.DecreaseHealth("GlobalHealth", "Health", dmgForce * deltaTime);
			}
			
			if (radiationLevel > 0 && radiationValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_RADIATION_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 900;
				}
			}
		}
		
		player.UpdateTerjeRadiationAccumulated();
	}
};
