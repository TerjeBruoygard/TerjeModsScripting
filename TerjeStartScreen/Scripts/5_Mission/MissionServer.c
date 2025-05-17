// <copyright file="MissionServer.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class MissionServer
{
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		GetPluginTerjeRespawnObjects().SendToClient(identity);
		
		if ((player.GetTerjeStats() != null) && (player.GetTerjeStats().IsStartScreenInProgress()))
		{
			if (player.m_terjeStartScreenParams == null)
			{
				string uid = string.Empty;
				if (identity)
				{
					uid = identity.GetId();
				}
				
				TerjeLog_Warning("Player '" + uid + "' killed and deleted from database because connected with unfinished start screen processing state.");
				player.SetTerjeServerStartScreenImmunity(false);
				player.ClearInventory();
				player.SetTerjeMaintenanceMode(true);
				player.SetHealth("", "", 0);
			}
		}
	}
	
	override void InvokeOnDisconnect(PlayerBase player)
	{
		super.InvokeOnDisconnect(player);
		
		if (player && player.m_terjeStartScreenParams != null)
		{
			string uid = string.Empty;
			if (player.GetIdentity())
			{
				uid = player.GetIdentity().GetId();
			}
			
			TerjeLog_Warning("Player '" + uid + "' killed and deleted from database because disconnected with active start screen processing.");
			player.m_terjeStartScreenParams = null;
			player.SetTerjeServerStartScreenImmunity(false);
			player.ClearInventory();
			player.SetTerjeMaintenanceMode(true);
			player.SetHealth("", "", 0);
		}
	}
	
	override void OnGameplayDataHandlerLoad()
	{
		super.OnGameplayDataHandlerLoad();
		m_RespawnMode = GameConstants.RESPAWN_MODE_RANDOM;
	}
	
	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		TerjePlayerProfile profile;
		if (GetTerjeDatabase().GetPlayerProfile(identity.GetId(), profile))
		{
			GetDayZGame().SetSelectedTerjeCharacterClassname(profile.GetCharacterClassname());
		}
		
		PlayerBase result = super.OnClientNewEvent(identity, pos, ctx);
		GetDayZGame().SetSelectedTerjeCharacterClassname(string.Empty);
		return result;
	}
}