// <copyright file="DayZPlayerImplementFallDamage.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class DayZPlayerImplementFallDamage
{
	override void HandleFallDamage(FallDamageData pData)
	{
		PlayerBase player;
		if (PlayerBase.CastTo(player, m_Player) && player && player.GetTerjeSkills())
		{
			float stuntmanPerkModifier;
			if (player.GetTerjeSkills().GetPerkValue("athlc", "stuntman", stuntmanPerkModifier))
			{
				pData.m_Height = pData.m_Height * Math.Clamp(1.0 - stuntmanPerkModifier, 0.0, 1.0);
			}
		}
		
		super.HandleFallDamage(pData);
	}
}