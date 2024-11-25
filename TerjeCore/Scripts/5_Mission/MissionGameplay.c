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

		PluginTerjeSettings plugin = GetTerjeSettingsPlugin();
		if (plugin)
		{
			plugin.m_eventOnSettingsSync.Insert(OnTerjeSettingsSynch);
		}
	}
	
	override void OnMissionFinish()
	{
		super.OnMissionFinish();
		
		PluginTerjeSettings plugin = GetTerjeSettingsPlugin();
		if (plugin)
		{
			plugin.m_eventOnSettingsSync.Remove(OnTerjeSettingsSynch);
		}
	}
	
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		UIScriptedMenu currentMenu = GetGame().GetUIManager().GetMenu();
		if (currentMenu)
		{
			if (currentMenu.IsInherited(TerjeModalDialog))
			{
				currentMenu.OnKeyPress(null, 0, 0, key);
			}
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (player && player.GetTerjeStats())
		{
			if (m_Hud)
			{
				bool detailedDiseaseHudBadges = false;
				bool detailedHealingHudBadges = false;
				GetTerjeSettingBool(TerjeSettingsCollection.CORE_DETAILED_DISEASE_HUD_BADGES, detailedDiseaseHudBadges);
				GetTerjeSettingBool(TerjeSettingsCollection.CORE_DETAILED_HEALING_HUD_BADGES, detailedHealingHudBadges);
				OnUpdateTerjeCustomBadges(player, detailedDiseaseHudBadges, detailedHealingHudBadges);
			}
			
			OnUpdateTerjeCustomGUI(player, timeslice);
		}
	}
	
	void OnTerjeSettingsSynch()
	{
		if (m_Hud)
		{
			m_Hud.InitConditionalTerjeBadgesAndNotifiers();
		}
	}
	
	void OnUpdateTerjeCustomGUI(PlayerBase player, float deltaTime)
	{
	
	}
	
	void OnUpdateTerjeCustomBadges(PlayerBase player, bool detailedDiseaseHudBadges, bool detailedHealingHudBadges)
	{
	
	}
}