// <copyright file="TerjeBookBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeBookBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionTerjeReadSkillbook);
	}
	
	override bool DescriptionOverride(out string output)
	{
		if (ConfigIsExisting("terjeSkillId"))
		{
			ref TerjeSkillCfg skillCfg;
			string skillId = ConfigGetStringRaw("terjeSkillId");
			int skillExpGain = ConfigGetInt("terjeSkillExpGain");
			int skillMinLevel = ConfigGetInt("terjeSkillMinLevel");
			int skillMaxLevel = ConfigGetInt("terjeSkillMaxLevel");
			if (GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg) && skillExpGain > 0 && skillMaxLevel > 0)
			{
				output = skillCfg.GetDisplayName() + ": <color rgba='97,215,124,255'>+" + skillExpGain + "</color> #STR_TERJESKILL_MISC2 (#STR_TERJESKILL_MISC1: <color rgba='0,148,255,255'>" + skillMinLevel + "-" + skillMaxLevel + "</color>)";
				return true;
			}
		}
		
		return super.DescriptionOverride(output);
	}
}