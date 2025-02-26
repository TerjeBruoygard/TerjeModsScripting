// <copyright file="MissionGameplay.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class MissionGameplay
{
	override void OnTerjeSettingsSynch()
	{
		super.OnTerjeSettingsSynch();

		GetTerjeSkillsRegistry().OnTerjeSettingsLoaded();
	}
	
	override void OnMissionStart()
	{
		super.OnMissionStart();
		
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJESKILLS_CATEYES).Start();
	}
	
	override void OnMissionFinish()
	{
		super.OnMissionFinish();
		
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJESKILLS_CATEYES).Stop();
	}
	
	override void OnUpdateTerjeCustomGUI(PlayerBase player, float deltaTime)
	{
		super.OnUpdateTerjeCustomGUI(player, deltaTime);

		float cateyesValue = 0.0;
		float settingModifier;
		float perkValue;
		
		DayZPlayerCameraBase camera = DayZPlayerCameraBase.Cast(player.GetCurrentPlayerCamera());
		if ((camera != null) && (camera.GetTerjeNVType() == 0) && (player.GetTerjeSkills() != null) && player.GetTerjeSkills().GetPerkValue("stlth", "catvis", perkValue))
		{
			if (!GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STEALTH_CAT_VISION_POWER, settingModifier))
			{
				settingModifier = 1.0;
			}
			
			bool isNight = GetGame() && GetGame().GetWorld() && GetGame().GetWorld().IsNight();
			bool isUnderground = player.GetUndergroundHandler() && player.GetUndergroundHandler().IsTerjeClientUnderground();
			if (isNight || isUnderground)
			{
				cateyesValue = perkValue * settingModifier;
			}
		}
		
		PPERequester_CatEyes cateyesRequester = PPERequester_CatEyes.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJESKILLS_CATEYES));
		if (cateyesRequester)
		{
			cateyesRequester.OnTerjeUpdate(cateyesValue, deltaTime);
			cateyesRequester.SetRequesterUpdating(true);
		}
	}
}
