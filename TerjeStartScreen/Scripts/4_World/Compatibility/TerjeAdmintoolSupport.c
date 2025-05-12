// <copyright file="TerjeAdmintoolSupport.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeAdmintoolSupport
{
	override void OnInit()
	{
		super.OnInit();
		
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Souls("terjeSouls", "Souls", "set:TerjeStartScreen_icons image:tss_soul", 0, TerjeStartScreenConstants.SOULS_MAX_LIMIT));
	}
}

class TerjeAdmintoolSupport_PlayerStat_Souls : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeSouls() != null)
		{
			return player.GetTerjeSouls().GetCount();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeSouls())
		{
			player.GetTerjeSouls().SetCount((int)Math.Round(value));
		}
	}
}