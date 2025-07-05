// <copyright file="TerjePlayerConditionPerk.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditionPerk : TerjePlayerConditionBase
{
	override bool Validate(PlayerBase player, TerjeXmlObject condition)
	{
		string skillId;
		string perkId;
		string requiredLevel;
		if (condition.FindAttribute("skillId", skillId) && condition.FindAttribute("perkId", perkId) && condition.FindAttribute("requiredLevel", requiredLevel))
		{
			if (player && (player.GetTerjeSkills() != null) && (player.GetTerjeSkills().GetPerkLevel(skillId, perkId) >= requiredLevel.ToInt()))
			{
				return true;
			}
		}
		
		return false;
	}
	
	override string GetText(PlayerBase player, TerjeXmlObject condition)
	{
		string skillId;
		string perkId;
		string requiredLevel;
		TerjeSkillCfg skillCfg;
		TerjePerkCfg perkCfg;
		if (condition.FindAttribute("skillId", skillId) && GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			if (condition.FindAttribute("perkId", perkId) && skillCfg.FindPerk(perkId, perkCfg) && condition.FindAttribute("requiredLevel", requiredLevel))
			{
				return "#STR_TERJECORE_COND_REQ '" + perkCfg.GetDisplayName() + "' #STR_TERJECORE_COND_PERK " + requiredLevel;
			}
		}
		
		return string.Empty;
	}
}