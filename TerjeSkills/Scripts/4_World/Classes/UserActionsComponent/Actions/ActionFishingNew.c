// <copyright file="ActionFishingNew.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionFishingNew
{
	override protected EntityAI TrySpawnCatch(FishingActionData action_data)
	{
		EntityAI result = super.TrySpawnCatch(action_data);
		
		if (GetGame().IsDedicatedServer())
		{
			int expGainValue;
			if (result)
			{
				expGainValue = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FISHING_SUCCESS_CATCH_EXP_GAIN);
			}
			else
			{
				expGainValue = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FISHING_FAILED_CATCH_EXP_GAIN);
			}
			
			if (action_data.m_Player && action_data.m_Player.GetTerjeSkills())
			{
				action_data.m_Player.GetTerjeSkills().AddSkillExperience("fish", expGainValue);
			}
		}
		
		return result;
	}
};

modded class CatchingContextFishingRodAction
{
	override protected void TryDamageItems()
	{
		if (GetGame().IsDedicatedServer() && m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().IsPerkRegistered("fish", "strgarms"))
		{
			float settingValue;
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("fish", "strgarms", perkValue))
			{
				perkValue = Math.Clamp(1.0 + perkValue, 0, 1);
			}
			else
			{
				perkValue = 1.0;
			}
			
			if (m_Hook && !m_Hook.IsSetForDeletion())
			{
				settingValue = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_HOOK_DAMAGE);
				m_Hook.AddHealth("", "Health", settingValue * perkValue * -1.0);
			}
			
			if (m_Rod && !m_Rod.IsSetForDeletion())
			{
				settingValue = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_ROD_DAMAGE);
				m_Rod.AddHealth("", "Health", settingValue * perkValue * -1.0);
			}
		}
		else
		{
			super.TryDamageItems();
		}
	}
	
	override float GetChanceCoef()
	{
		float perkValue;
		float result = super.GetChanceCoef();
		if (m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().GetPerkValue("fish", "skfishman", perkValue))
		{
			result *= Math.Max(1.0, 1.0 + perkValue);
		}
		
		return result;
	}
	
	override float RandomizeSignalDuration()
	{
		float perkValue;
		float result = super.RandomizeSignalDuration();
		if (m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().GetPerkValue("fish", "skfishman", perkValue))
		{
			result *= Math.Max(1.0, 1.0 + perkValue);
		}
		
		return result;
	}
	
	override float RandomizeSignalStartTime()
	{
		float perkValue;
		float result = super.RandomizeSignalStartTime();
		if (m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().GetPerkValue("fish", "skfishman", perkValue))
		{
			result = result / Math.Max(1.0, 1.0 + perkValue);
		}
		
		return result;
	}
	
	override float GetQualityModifier()
	{
		float perkValue;
		float result = super.GetQualityModifier();
		if (GetGame().IsDedicatedServer() && m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().IsPerkRegistered("fish", "fishmluck"))
		{
			result *= GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_FISH_SIZE_MODIFIER);
			if (m_Player.GetTerjeSkills().GetPerkValue("fish", "fishmluck", perkValue))
			{
				result += Math.Max(0.0, perkValue);
			}
		}
		
		return result;
	}
	
	override float GetHookLossChanceModifierClamped()
	{
		float perkValue;
		float result = super.GetHookLossChanceModifierClamped();
		if (m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().GetPerkValue("fish", "reliabgear", perkValue))
		{
			result *= Math.Clamp(1.0 + perkValue, 0, 1);
		}
		
		return result;
	}
	
	override float GetBaitLossChanceModifierClamped()
	{
		float perkValue;
		float result = super.GetBaitLossChanceModifierClamped();
		if (m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().GetPerkValue("fish", "reliabgear", perkValue))
		{
			result *= Math.Clamp(1.0 + perkValue, 0, 1);
		}
		
		return result;
	}
};