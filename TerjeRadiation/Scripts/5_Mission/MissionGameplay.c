// <copyright file="MissionGameplay.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class MissionGameplay
{
	override void OnMissionStart()
	{
		super.OnMissionStart();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_RADIATION).Start();
	}
	
	override void OnMissionFinish()
	{
		super.OnMissionFinish();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_RADIATION).Stop();
	}
	
	override void OnUpdateTerjeCustomBadges(PlayerBase player, bool detailedDiseaseHudBadges, bool detailedHealingHudBadges)
	{
		super.OnUpdateTerjeCustomBadges(player, detailedDiseaseHudBadges, detailedHealingHudBadges);

		if (detailedDiseaseHudBadges)
		{
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_RADIATION, player.GetTerjeStats().GetRadiationLevel());
		}
		
		if (detailedHealingHudBadges)
		{
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_ANTIRAD, player.GetTerjeStats().GetAntiradLevel());
		}
	}
	
	override void OnUpdateTerjeCustomGUI(PlayerBase player, float deltaTime)
	{
		super.OnUpdateTerjeCustomGUI(player, deltaTime);
		PPERequester_TerjeMedRadiation.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_RADIATION)).SetRadiationEffect(player.GetTerjeStats().GetRadiationLevel());
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_RADIATION).SetRequesterUpdating(true);
	}
}
