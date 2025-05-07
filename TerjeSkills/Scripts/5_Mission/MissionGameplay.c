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
	
	override void OnMissionFinish()
	{
		super.OnMissionFinish();
		
		PPERequester_CatEyes cateyesRequester = PPERequester_CatEyes.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJESKILLS_CATEYES));
		if ((cateyesRequester != null) && (cateyesRequester.IsRequesterRunning()))
		{
			cateyesRequester.Stop();
		}
	}
	
	override void OnUpdateTerjeCustomGUI(PlayerBase player, float deltaTime)
	{
		super.OnUpdateTerjeCustomGUI(player, deltaTime);

		float cateyesValue = -1;
		DayZPlayerCameraBase camera = DayZPlayerCameraBase.Cast(player.GetCurrentPlayerCamera());
		if ((camera != null) && (camera.GetTerjeNVType() == 0) && (player.GetTerjeSkills() != null))
		{
			float perkValue;
			if ((player.GetTerjeSkills().IsPerkRegistered("stlth", "catvis")) && (player.GetTerjeSkills().GetPerkValue("stlth", "catvis", perkValue)))
			{
				float settingModifier;
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
		}
		
		PPERequester_CatEyes cateyesRequester = PPERequester_CatEyes.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJESKILLS_CATEYES));
		if (cateyesRequester != null)
		{
			if (cateyesValue > 0)
			{
				if (!cateyesRequester.IsRequesterRunning())
				{
					cateyesRequester.Start();
				}
				
				cateyesRequester.OnTerjeUpdate(cateyesValue, deltaTime);
				cateyesRequester.SetRequesterUpdating(true);
			}
			else
			{
				if (cateyesRequester.IsRequesterRunning())
				{
					cateyesRequester.Stop();
				}
			}
		}
	}
}
