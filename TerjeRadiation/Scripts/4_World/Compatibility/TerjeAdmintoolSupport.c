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
		
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_RadiationAccum("terjeRadiationAccum", "Rad-buffer", "set:TerjeRadiation_icon image:tr_rad_sickness", 0, TerjeRadiationConstants.RADIATION_PLAYER_ACCUMULATOR_SERVER_MAX));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_RadiationSick("terjeRadiationSick", "Rad-sickness", "set:TerjeRadiation_icon image:tr_rad_sickness", 0, TerjeRadiationConstants.RADIATION_MAX_VALUE));
	}
	
	override void OnHeal(PlayerBase player)
	{
		super.OnHeal(player);
		
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetRadiationAccumulated(0);
			player.GetTerjeStats().SetRadiationValue(0);
		}
	}
};

class TerjeAdmintoolSupport_PlayerStat_RadiationAccum : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetRadiationAccumulated();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetRadiationAccumulated(value);
		}
	}
};

class TerjeAdmintoolSupport_PlayerStat_RadiationSick : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetRadiationValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetRadiationValue(value);
		}
	}
};