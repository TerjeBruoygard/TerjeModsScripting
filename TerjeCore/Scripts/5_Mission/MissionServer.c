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
	
	override void OnEvent(EventType eventTypeId, Param params) 
	{
		if (eventTypeId == ClientPrepareEventTypeID)
		{
			ClientPrepareEventParams clientPrepareParams = ClientPrepareEventParams.Cast(params);
			if (clientPrepareParams != null)
			{
				GetTerjeDatabase().OnPlayerPreloading(clientPrepareParams.param1);
			}
		}
		else if (eventTypeId == ClientRespawnEventTypeID)
		{
			ClientRespawnEventParams respawnParams = ClientRespawnEventParams.Cast(params);
			if (respawnParams != null)
			{
				PlayerBase respawnPlayer = PlayerBase.Cast(respawnParams.param2);
				if (respawnPlayer)
				{
					respawnPlayer.SetTerjeGodMode(false);
					respawnPlayer.SetTerjeIndestructible(false);
					respawnPlayer.SetTerjeIgnoreDamage(false);
				}
			}
		}
		else if (eventTypeId == ClientDisconnectedEventTypeID)
		{
			ClientDisconnectedEventParams disconnectParams = ClientDisconnectedEventParams.Cast(params);
			if (disconnectParams != null)
			{
				PlayerBase disconnectPlayer = PlayerBase.Cast(disconnectParams.param2);
				if (disconnectPlayer)
				{
					disconnectPlayer.SetTerjeGodMode(false);
					disconnectPlayer.SetTerjeIndestructible(false);
					disconnectPlayer.SetTerjeIgnoreDamage(false);
				}
			}
		}
		
		super.OnEvent(eventTypeId, params);
	}
	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		GetTerjeDatabase().OnPlayerConnected(player, identity, identity.GetId());
		GetTerjeSettingsPlugin().SendSettingsToClient(identity);
		GetTerjeCustomRecipesPlugin().SendTerjeCustomRecipesToClient(identity);
	}
	
	override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		super.PlayerDisconnected(player, identity, uid);
		GetTerjeDatabase().OnPlayerDisconnected(player, identity, uid);
	}
}