// <copyright file="TerjePlayerSkillsAccessor.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerSkillsAccessor
{
	protected PlayerBase m_Player;
	
	void TerjePlayerSkillsAccessor(PlayerBase player)
	{
		m_Player = player;
	}
	
	int GetSkillLevel(string skillId)
	{
		return 0;
	}
	
	int GetSkillExperience(string skillId)
	{
		return 0;
	}
	
	void SetSkillLevel(string skillId, int level)
	{
	
	}
	
	void AddSkillExperience(string skillId, int value, bool affectModifiers = true, bool showNotification = true)
	{
	
	}
	
	int GetSkillPerkPoints(string skillId)
	{
		return 0;
	}
	
	void ResetAllSkillPerks(string skillId)
	{
	
	}
	
	void ResetSkill(string skillId)
	{
	
	}
	
	void SetPerkLevel(string skillId, string perkId, int level)
	{
	
	}
	
	void AddPerkLevel(string skillId, string perkId)
	{
	
	}
	
	int GetPerkLevel(string skillId, string perkId)
	{
		return 0;
	}
	
	bool GetPerkValue(string skillId, string perkId, out float result)
	{
		result = 0;
		return false;
	}
	
	void GetPerkStatus(string skillId, string perkId, out int perkLevel, out int activePerkLevel, out bool canBeUpgraded)
	{
		perkLevel = 0;
		activePerkLevel = 0;
		canBeUpgraded = false;
	}
	
	bool GetSkillModifierValue(string skillId, string modifierId, out float result)
	{
		result = 0;
		return false;
	}
	
	bool IsPerkRegistered(string skillId, string perkId)
	{
		return false;
	}
}