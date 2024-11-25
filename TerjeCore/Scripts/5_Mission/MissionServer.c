// <copyright file="MissionServer.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		TerjeSkillsRegistry.GetInstance();
	}
	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		GetTerjeDatabase().OnPlayerConnected(player, identity, identity.GetId());
		GetTerjeSettingsPlugin().SendSettingsToClient(identity);
	}
	
	override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		super.PlayerDisconnected(player, identity, uid);
		GetTerjeDatabase().OnPlayerDisconnected(player, identity, uid);
	}
}