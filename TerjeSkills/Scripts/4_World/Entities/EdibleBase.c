// <copyright file="EdibleBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Edible_Base
{
	override int TerjeOverrideDescriptionByConsumableEffects()
	{
		if (GetGame().IsClient())
		{
			PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
			if (player && player.GetTerjeSkills())
			{
				if ((!GetTerjeGameConfig().ConfigGetBool("CfgVehicles " + GetType() + " medicalPillsCategory")) && player.GetTerjeSkills().GetPerkLevel("surv", "expert") > 0)
				{
					return 2;
				}
			}
		}
		
		return super.TerjeOverrideDescriptionByConsumableEffects();
	}
}