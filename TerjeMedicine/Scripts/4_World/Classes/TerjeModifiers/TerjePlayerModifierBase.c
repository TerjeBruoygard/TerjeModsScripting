// <copyright file="TerjePlayerModifierBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjePlayerModifierBase
{
	override float GetPlayerImmunity(PlayerBase player)
	{
		if (player.GetTerjeSkills() && player.GetTerjeSkills().IsPerkRegistered("immunity", "resdiseasesmod"))
		{
			float immunityMod;
			if (player.GetTerjeSkills().GetSkillModifierValue("immunity", "resdiseasesmod", immunityMod))
			{
				return Math.Clamp(immunityMod, 0.0, 1.0);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return player.GetTerjeStats().GetInternalImmunity();
		}
	}
}