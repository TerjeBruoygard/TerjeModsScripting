// <copyright file="TerjePlayerModifierBiohazard.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierBiohazard : TerjePlayerModifierBase
{
	private float m_biohazardImmunityInterval = 0;
	private float m_firstSymptomTime = 0;
	private int m_lastBiohazardLevel = -1;
	
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		int antibiohazardLevel = 0;
		float antibiohazardTime = 0;
		if (player.GetTerjeStats().GetAntibiohazard(antibiohazardLevel, antibiohazardTime))
		{
			if (antibiohazardTime > 0)
			{
				player.GetTerjeStats().SetAntibiohazard(antibiohazardLevel, antibiohazardTime - deltaTime);
			}
			else if (antibiohazardLevel > 0)
			{
				player.GetTerjeStats().SetAntibiohazard(0, 0);
			}
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_BIOHAZARD_ENABLED) == false)
		{
			player.GetTerjeStats().SetBiohazardValue(0);
			return;
		}
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (m_firstSymptomTime > 0)
		{
			m_firstSymptomTime = m_firstSymptomTime + deltaTime;
		}
		
		if (m_biohazardImmunityInterval > 0)
		{
			m_biohazardImmunityInterval = m_biohazardImmunityInterval - deltaTime;
		}
		
		float biohazardValue = player.GetTerjeStats().GetBiohazardValue();
		int biohazardIntOrig = (int)biohazardValue;
		int biohazardVanillaAgents = player.GetSingleAgentCount(eAgents.CHEMICAL_POISON);
		if (biohazardVanillaAgents > 0)
		{
			float biohazardTransferAgentsModifier = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BIOHAZARD_TRANSFER_AGENTS_MODIFIER, biohazardTransferAgentsModifier);
			biohazardValue = biohazardValue + (biohazardTransferAgentsModifier * (float)biohazardVanillaAgents);
			
			player.RemoveAgent(eAgents.CHEMICAL_POISON);
		}
		
		int biohazardLevel = TerjeMathHelper.ClampInt((int)biohazardValue, 0, 3);
		if (m_lastBiohazardLevel == 0 && biohazardLevel > 0)
		{
			m_firstSymptomTime = deltaTime;
		}
		
		m_lastBiohazardLevel = biohazardLevel;
		
		if (biohazardValue > 0)
		{
			float perkResistMod;
			if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("immunity", "biohzres", perkResistMod))
			{
				perkResistMod = 1.0 + perkResistMod;
			}
			else
			{
				perkResistMod = 1.0;
			}
			
			float biohazardDecPerSec = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BIOHAZARD_DEC_PER_SEC, biohazardDecPerSec);	
			biohazardValue = biohazardValue - (perkResistMod * biohazardDecPerSec * deltaTime);

			if (antibiohazardLevel > 0)
			{
				float biohazardAntidoteHealMultiplier = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BIOHAZARD_ANTIDOTE_HEAL_MULTIPLIER);
				biohazardValue = biohazardValue - (perkResistMod * antibiohazardLevel * biohazardDecPerSec * biohazardAntidoteHealMultiplier * deltaTime);	
			}
			
			player.GetTerjeStats().SetBiohazardValue(biohazardValue);

			if (biohazardLevel >= 2)
			{
				float biohazardSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BIOHAZARD_SYMPTOM_CHANCE, biohazardSymptomChance);
				if (Math.RandomFloat01() < biohazardSymptomChance * deltaTime || m_firstSymptomTime > 5)
				{
					float biohazardVomitForceModifier = 1.0;
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BIOHAZARD_VOMIT_FORCE_MODIFIER, biohazardVomitForceModifier);
					player.CallTerjeVomitSymptom(Math.RandomIntInclusive(4, 8), biohazardVomitForceModifier);
					m_firstSymptomTime = 0;
				}
			}
			
			if (biohazardLevel >= 3)
			{
				float biohazardCriticalDmgMultiplier = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BIOHAZARD_CRITICAL_DMG_MULTIPLIER);
				float dmgForce = (biohazardValue - 3.0) * biohazardCriticalDmgMultiplier;
				DecreasePlayerHealth(player, TerjeDamageSource.BIOHAZARD, dmgForce * deltaTime);
				
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
			}
			
			if (biohazardIntOrig > 0 && biohazardValue < 1 && m_biohazardImmunityInterval <= 0)
			{
				float immunityBiohazardExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_BIOHAZARD_EXP_GAIN, immunityBiohazardExpGain);
				if (immunityBiohazardExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityBiohazardExpGain);
					m_biohazardImmunityInterval = 600;
				}
			}
		}
	}
}
