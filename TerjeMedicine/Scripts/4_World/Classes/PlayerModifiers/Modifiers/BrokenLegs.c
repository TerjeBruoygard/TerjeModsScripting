// <copyright file="BrokenLegs.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class BrokenLegsMdfr
{
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			float immunityExpGain = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_FIX_LEGS_EXP_GAIN);
			if (immunityExpGain > 0 && player && player.GetTerjeSkills())
			{
				player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
			}
		}
	}
}