// <copyright file="CAContinuousMineWood.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class CAContinuousMineWood
{
	override void CreatePrimaryItems(ActionData action_data)
	{
		if (GetGame().IsDedicatedServer() && action_data.m_Player && action_data.m_Player.GetTerjeSkills() && action_data.m_MainItem)
		{
			float gainChance;
			if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STRENGTH_ITEMS_USE_GAIN_CHANCE, gainChance) && Math.RandomFloat01() < gainChance)
			{
				int gainExp;
				if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_STRENGTH_ITEMS_USE_GAIN_EXP, gainExp))
				{
					action_data.m_Player.GetTerjeSkills().AddSkillExperience("strng", gainExp);
				}
			}
		}
		
		super.CreatePrimaryItems(action_data);
	}
};
