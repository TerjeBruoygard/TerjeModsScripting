// <copyright file="TerjePlayerConditionSkill.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditionSkill : TerjePlayerConditionBase
{
	override bool Validate(PlayerBase player, TerjeXmlObject condition)
	{
		string skillId;
		string requiredLevel;
		if (condition.FindAttribute("skillId", skillId) && condition.FindAttribute("requiredLevel", requiredLevel))
		{
			if (player && (player.GetTerjeSkills() != null) && (player.GetTerjeSkills().GetSkillLevel(skillId) >= requiredLevel.ToInt()))
			{
				return true;
			}
		}
		
		return false;
	}
	
	override string GetText(PlayerBase player, TerjeXmlObject condition)
	{
		string skillId;
		string requiredLevel;
		TerjeSkillCfg skillCfg;
		if (condition.FindAttribute("skillId", skillId) && GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg) && condition.FindAttribute("requiredLevel", requiredLevel))
		{
			return "#STR_TERJECORE_COND_REQ '" + skillCfg.GetDisplayName() + "' #STR_TERJECORE_COND_SKILL " + requiredLevel;
		}
		
		return string.Empty;
	}
}