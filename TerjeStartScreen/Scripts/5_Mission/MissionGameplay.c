// <copyright file="MissionGameplay.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class MissionGameplay
{
	override void OnInit()
	{
		super.OnInit();
		GetTerjeRPC().RegisterHandler("startscreen.ctx", this, "OnTerjeStartScreenParamsReceived");
		GetTerjeRPC().RegisterHandler("startscreen.close", this, "OnTerjeStartScreenCloseReceived");
		GetTerjeRPC().RegisterHandler("startscreen.ready", this, "OnTerjeStartScreenReadyReceived");
	}
	
	override void OnUpdateTerjeCustomBadges(PlayerBase player, bool detailedDiseaseHudBadges, bool detailedHealingHudBadges)
	{
		super.OnUpdateTerjeCustomBadges(player, detailedDiseaseHudBadges, detailedHealingHudBadges);

		if ((m_Hud != null) && (m_Hud.TERJE_BADGE_SOULS != -1))
		{
			if (player && (player.GetTerjeSouls() != null) && (player.GetTerjeSouls().IsEnabled()) && (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_SOULS_BADGE)))
			{
				m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_SOULS, player.GetTerjeSouls().GetCount());
			}
			else
			{
				m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_SOULS, 0);
			}
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player && (player.m_terjeStartScreenClientReady == false))
		{
			if (player.IsAlive())
			{
				TerjeStartScreenMenu startScreenMenu = TerjeStartScreenMenu.Cast(GetUIManager().GetMenu());
				if (startScreenMenu == null)
				{
					GetUIManager().CloseAll();
					startScreenMenu = TerjeStartScreenMenu.Cast(TerjeUiManager.GetInstance().ShowScriptedMenu(TerjeStartScreenMenu));
				}
				
				if ((startScreenMenu != null) && (startScreenMenu.HasTerjeParams() == false) && (player.m_terjeStartScreenParams != null))
				{
					startScreenMenu.SetTerjeParams(player.m_terjeStartScreenParams);
				}
			}
			else
			{
				player.m_terjeStartScreenClientReady = true;
				player.m_terjeStartScreenParams = null;
				GetUIManager().CloseAll();
				InGameMenu inGameMenu = InGameMenu.Cast(GetUIManager().EnterScriptedMenu( MENU_INGAME, null ));
				if (inGameMenu != null)
				{
					inGameMenu.TerjeGameRespawn();
				}
			}
		}
	}
	
	override int GetRespawnModeClient()
	{
		return GameConstants.RESPAWN_MODE_RANDOM;
	}
	
	private void OnTerjeStartScreenParamsReceived(ParamsReadContext ctx, PlayerIdentity sender)
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player)
		{
			player.m_terjeStartScreenParams = new TerjeStartScreenParams;
			if(!player.m_terjeStartScreenParams.Deserialize(ctx)) 
			{
				player.m_terjeStartScreenParams = null;
				return;
			}
		}
	}
	
	private void OnTerjeStartScreenReadyReceived(ParamsReadContext ctx, PlayerIdentity sender)
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player)
		{
			player.m_terjeStartScreenParams = null;
			player.m_terjeStartScreenClientReady = true;
		}
		
		TerjeStartScreenMenu menu = TerjeStartScreenMenu.Cast(GetUIManager().GetMenu());
		if (menu != null)
		{
			menu.PushCommandClose();
		}
	}
	
	private void OnTerjeStartScreenCloseReceived(ParamsReadContext ctx, PlayerIdentity sender)
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player)
		{
			player.m_terjeStartScreenParams = null;
			player.m_terjeStartScreenClientReady = true;
			OnTerjeStartScreenCloseApply(player, ctx);
		}
		
		TerjeStartScreenMenu menu = TerjeStartScreenMenu.Cast(GetUIManager().GetMenu());
		if (menu != null)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLaterByName(menu, "PushCommandClose", 1500);
		}
	}
	
	private void OnTerjeStartScreenCloseApply(PlayerBase player, ParamsReadContext ctx)
	{
		vector pos;
		if (!ctx.Read(pos))
			return;
		
		vector rot;
		if (!ctx.Read(rot))
			return;
		
		player.SetPosition(pos);
		player.SetOrientation(rot);
	}
}