// <copyright file="ActionCPR.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionCPR
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (!super.ActionCondition(player, target, item))
		{
			return false;
		}
		
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().IsPerkRegistered("med", "brnlife"))
		{
			return player.GetTerjeSkills().GetPerkLevel("med", "brnlife") > 0;
		}
		
		return true;
	}
}