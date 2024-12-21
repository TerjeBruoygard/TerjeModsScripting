// <copyright file="TerjePlayerInspectableStats.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjePlayerInspectableStats
{
	override void OnInit(PlayerBase player)
	{
		super.OnInit(player);
		
		if (player && player.IsAlive() && player.GetTerjeStats())
		{
			if (player.GetTerjeStats().GetViscera())
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_viscera", "#STR_TERJEMED_PIS_VISCERA");
			}
			
			int stubWoundsCount = player.GetTerjeStats().GetStubWounds();
			if (stubWoundsCount > 0)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_wound", "#STR_TERJEMED_PIS_STUB (" + stubWoundsCount + ")");
			}
			
			int bulletWoundsCount = player.GetTerjeStats().GetBulletWounds();
			if (bulletWoundsCount > 0)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_wound", "#STR_TERJEMED_PIS_BULLET (" + bulletWoundsCount + ")");
			}
			
			if (player.GetTerjeStats().GetSleepingLevel() >= 4)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_SLEEP", "set:TerjeMedicine_icon image:tm_sleeping_4", "#STR_TERJEMED_PIS_SLEEP_DESC");
			}
			
			int mindLevel = player.GetTerjeStats().GetMindLevel();
			if (mindLevel == 5)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_MIND", "set:TerjeMedicine_icon image:tm_mind_4", "#STR_TERJEMED_PIS_MIND_HARD");
			}
			else if (mindLevel == 4)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_MIND", "set:TerjeMedicine_icon image:tm_mind_3", "#STR_TERJEMED_PIS_MIND_LOW");
			}
			
			if (player.GetTerjeStats().GetBandagesClean() > 0)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_bandagedclean_2", "#STR_TERJEMED_PIS_BC");
			}
			
			if (player.GetTerjeStats().GetBandagesDirty() > 0)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_bandageddirty_2", "#STR_TERJEMED_PIS_BD");
			}
			
			if (player.GetTerjeStats().GetSuturesBandagedClean() > 0)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_bandagedclean_2", "#STR_TERJEMED_PIS_SBC");
			}
			
			if (player.GetTerjeStats().GetSuturesBandagedDirty() > 0)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_bandageddirty_2", "#STR_TERJEMED_PIS_SBD");
			}
			
			if (player.GetTerjeStats().GetSuturesClean() > 0)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_protectingwound", "#STR_TERJEMED_PIS_SC");
			}
			
			if (player.GetTerjeStats().GetSuturesDirty() > 0)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_protectingwoundseps", "#STR_TERJEMED_PIS_SD");
			}
			
			int hematomasCount = player.GetTerjeStats().GetHematomas();
			if (hematomasCount > TerjeMedicineConstants.HEMATOMAS_CRITICAL_COUNT)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_hematoma", "#STR_TERJEMED_PIS_HEM_CRIT (" + hematomasCount + ")");
			}
			else if (hematomasCount > TerjeMedicineConstants.HEMATOMAS_BAD_COUNT)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_hematoma", "#STR_TERJEMED_PIS_HEM_BAD (" + hematomasCount + ")");
			}
			else if (hematomasCount > TerjeMedicineConstants.HEMATOMAS_PAIN_COUNT)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_WOUND", "set:TerjeMedicine_icon image:tm_hematoma", "#STR_TERJEMED_PIS_HEM_LOW (" + hematomasCount + ")");
			}
			
			int zombieVirus = player.GetTerjeStats().GetZVirusLevel();
			if (zombieVirus == 1)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_ZV", "set:TerjeMedicine_icon image:tm_virusz", "#STR_TERJEMED_PIS_L1");
			}
			else if (zombieVirus == 2)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_ZV", "set:TerjeMedicine_icon image:tm_virusz", "#STR_TERJEMED_PIS_L2");
			}
			else if (zombieVirus == 3)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_ZV", "set:TerjeMedicine_icon image:tm_virusz", "#STR_TERJEMED_PIS_L3");
			}
			
			int sepsis = player.GetTerjeStats().GetSepsisLevel();
			if (sepsis == 1)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_SEPSIS", "set:TerjeMedicine_icon image:tm_sepsis", "#STR_TERJEMED_PIS_L1");
			}
			else if (sepsis == 2)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_SEPSIS", "set:TerjeMedicine_icon image:tm_sepsis", "#STR_TERJEMED_PIS_L2");
			}
			else if (sepsis == 3)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_SEPSIS", "set:TerjeMedicine_icon image:tm_sepsis", "#STR_TERJEMED_PIS_L3");
			}
			
			int rabies = player.GetTerjeStats().GetRabiesLevel();
			if (rabies == 1)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_RABIES", "set:TerjeMedicine_icon image:tm_rabies", "#STR_TERJEMED_PIS_L1");
			}
			else if (rabies == 2)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_RABIES", "set:TerjeMedicine_icon image:tm_rabies", "#STR_TERJEMED_PIS_L2");
			}
			else if (rabies == 3)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_RABIES", "set:TerjeMedicine_icon image:tm_rabies", "#STR_TERJEMED_PIS_L3");
			}
			
			int pain = player.GetTerjeStats().GetPainLevel();
			if (pain == 1)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_PAIN", "set:TerjeMedicine_icon image:tm_pain", "#STR_TERJEMED_PIS_PAIN_L1");
			}
			else if (pain == 2)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_PAIN", "set:TerjeMedicine_icon image:tm_pain", "#STR_TERJEMED_PIS_PAIN_L2");
			}
			else if (pain == 3)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_PAIN", "set:TerjeMedicine_icon image:tm_pain", "#STR_TERJEMED_PIS_PAIN_L3");
			}
			
			int influenza = player.GetTerjeStats().GetInfluenzaLevel();
			if (influenza == 1)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_INFLUENZA", "set:TerjeMedicine_icon image:tm_influenza", "#STR_TERJEMED_PIS_INF_L1");
			}
			else if (influenza == 2)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_INFLUENZA", "set:TerjeMedicine_icon image:tm_influenza", "#STR_TERJEMED_PIS_INF_L2");
			}
			else if (influenza == 3)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_INFLUENZA", "set:TerjeMedicine_icon image:tm_influenza", "#STR_TERJEMED_PIS_INF_L3");
			}
			
			int overdose = player.GetTerjeStats().GetOverdoseLevel();
			if (overdose == 1)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_OVERDOSE", "set:TerjeMedicine_icon image:tm_overdosed", "#STR_TERJEMED_PIS_OVERD_L1");
			}
			else if (overdose == 2)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_OVERDOSE", "set:TerjeMedicine_icon image:tm_overdosed", "#STR_TERJEMED_PIS_OVERD_L2");
			}
			else if (overdose == 3)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_OVERDOSE", "set:TerjeMedicine_icon image:tm_overdosed", "#STR_TERJEMED_PIS_OVERD_L3");
			}
			
			int poison = player.GetTerjeStats().GetPoisonLevel();
			if (poison == 1)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_POISON", "set:TerjeMedicine_icon image:tm_poison", "#STR_TERJEMED_PIS_PL1");
			}
			else if (poison == 2)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_POISON", "set:TerjeMedicine_icon image:tm_poison", "#STR_TERJEMED_PIS_PL2");
			}
			else if (poison == 3)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_POISON", "set:TerjeMedicine_icon image:tm_poison", "#STR_TERJEMED_PIS_PL3");
			}
			
			int biohazard = player.GetTerjeStats().GetBiohazardLevel();
			if (biohazard == 1)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_BIOHAZARD", "set:TerjeMedicine_icon image:tm_biohazard", "#STR_TERJEMED_PIS_PL1");
			}
			else if (biohazard == 2)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_BIOHAZARD", "set:TerjeMedicine_icon image:tm_biohazard", "#STR_TERJEMED_PIS_PL2");
			}
			else if (biohazard == 3)
			{
				AddInspectableStat("#STR_TERJEMED_PIS_BIOHAZARD", "set:TerjeMedicine_icon image:tm_biohazard", "#STR_TERJEMED_PIS_PL3");
			}
			
			if (player.GetTerjeStats().GetContusion())
			{
				AddInspectableStat("#STR_TERJEMED_PIS_CONTUSION", "set:TerjeMedicine_icon image:tm_concussion", "#STR_TERJEMED_PIS_CONTUSION_DESC");
			}
		}
	}
}