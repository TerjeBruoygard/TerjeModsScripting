// <copyright file="TerjePlayerInspectableStats.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjePlayerInspectableStats
{
	override void OnInit(PlayerBase player)
	{
		super.OnInit(player);
		
		if (player && player.IsAlive() && player.GetTerjeStats())
		{
			int radSickness = player.GetTerjeStats().GetRadiationLevel();
			if (radSickness == 1)
			{
				AddInspectableStat("#STR_TERJERAD_PIS_RADSICK", "set:TerjeRadiation_icon image:tr_rad_sickness", "#STR_TERJERAD_PIS_RADSICK_L1");
			}
			else if (radSickness == 2)
			{
				AddInspectableStat("#STR_TERJERAD_PIS_RADSICK", "set:TerjeRadiation_icon image:tr_rad_sickness", "#STR_TERJERAD_PIS_RADSICK_L2");
			}
			else if (radSickness == 3)
			{
				AddInspectableStat("#STR_TERJERAD_PIS_RADSICK", "set:TerjeRadiation_icon image:tr_rad_sickness", "#STR_TERJERAD_PIS_RADSICK_L3");
			}
		}
	}
}