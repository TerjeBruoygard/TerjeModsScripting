// <copyright file="DayZPlayerImplementMeleeCombat.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class DayZPlayerImplementMeleeCombat
{
	override protected int TrySelectFinisherType(InventoryItem weapon, EntityAI target)
	{
		PlayerBase player = PlayerBase.Cast(m_DZPlayer);
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().IsPerkRegistered("stlth", "silentkilr") && player.GetTerjeSkills().GetPerkLevel("stlth", "silentkilr") == 0)
		{
			return -1;
		}
		
		return super.TrySelectFinisherType(weapon, target);
	}
};