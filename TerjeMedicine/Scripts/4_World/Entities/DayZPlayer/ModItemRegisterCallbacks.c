// <copyright file="ModItemRegisterCallbacks.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ModItemRegisterCallbacks
{
	override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterOneHanded(pType, pBehavior);
		
		pType.AddItemInHandsProfileIK("TerjePillsBase", "dz/anims/workspaces/player/player_main/props/player_main_1h_tablets.asi", pBehavior, "dz/anims/anm/player/ik/gear/cassette.anm");
		pType.AddItemInHandsProfileIK("TerjeAmpouleBase", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/InjectionVial.anm");
		pType.AddItemInHandsProfileIK("TerjeSyringeNew", "dz/anims/workspaces/player/player_main/props/player_main_1h_syringe.asi", pBehavior, "dz/anims/anm/player/ik/gear/VitaminBottle.anm");
		pType.AddItemInHandsProfileIK("TerjeSyringeEmpty", "dz/anims/workspaces/player/player_main/props/player_main_1h_syringe.asi", pBehavior, "dz/anims/anm/player/ik/gear/Syringe_Empty.anm");
		pType.AddItemInHandsProfileIK("TerjeSyringeFull", "dz/anims/workspaces/player/player_main/props/player_main_1h_syringe.asi", pBehavior, "dz/anims/anm/player/ik/gear/Syringe_Full.anm");
		pType.AddItemInHandsProfileIK("TerjeInjectorBase", "dz/anims/workspaces/player/player_main/props/player_main_1h_morphine.asi", pBehavior, "dz/anims/anm/player/ik/gear/morphine.anm");
		pType.AddItemInHandsProfileIK("TerjeBandageHemostatic", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/StartKit.anm");
		pType.AddItemInHandsProfileIK("TerjeSurgicalKit",  "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/electronic_repair_kit.anm");
		pType.AddItemInHandsProfileIK("TerjeSalveBase", "dz/anims/workspaces/player/player_main/props/player_main_1h_pills.asi", pBehavior, "dz/anims/anm/player/ik/gear/VitaminBottle.anm");
		pType.AddItemInHandsProfileIK("TerjeStethoscope", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "dz/anims/anm/player/ik/gear/steak_knife.anm");
		pType.AddItemInHandsProfileIK("TerjeFirstAidKitMedium", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "dz/anims/anm/player/ik/gear/screwdriver.anm");
		pType.AddItemInHandsProfileIK("TerjeFirstAidKitLarge", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "dz/anims/anm/player/ik/gear/screwdriver.anm");
		pType.AddItemInHandsProfileIK("TerjeFirstAidKitIndividualBase", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeMedicine/Anm/IFAK.anm");
		pType.AddItemInHandsProfileIK("TerjeFirstAidKitAdvancedBase", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "TerjeMedicine/Anm/AFAK.anm");
		pType.AddItemInHandsProfileIK("TerjeSurgicalTool_White", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "TerjeMedicine/Anm/surgical_tool.anm");
		pType.AddItemInHandsProfileIK("TerjeSurgicalTool_Ceramic", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "TerjeMedicine/Anm/surgical_tool.anm");
		pType.AddItemInHandsProfileIK("TerjePlaster", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior,	"dz/anims/anm/player/ik/gear/tetracycline_tablets.anm");
		pType.AddItemInHandsProfileIK("TerjeHeadgearPsiHelm", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior, "dz/anims/anm/player/ik/gear/ballistic_helmet.anm");
		pType.AddItemInHandsProfileIK("TerjeStethoscope", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "dz/anims/anm/player/ik/gear/steak_knife.anm");
		pType.AddItemInHandsProfileIK("TerjeExpressTestAgents", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior,	"dz/anims/anm/player/ik/gear/tetracycline_tablets.anm");
		pType.AddItemInHandsProfileIK("TerjeExpressTestVirusZ", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior,	"dz/anims/anm/player/ik/gear/BloodTest_Kit.anm");
		pType.AddItemInHandsProfileIK("TerjeExpressTestSepsis", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior,	"dz/anims/anm/player/ik/gear/BloodTest_Kit.anm");
		pType.AddItemInHandsProfileIK("TerjeExpressTestRabies", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior,	"dz/anims/anm/player/ik/gear/BloodTest_Kit.anm");
		pType.AddItemInHandsProfileIK("TerjeExpressTestVirusZPack", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior,	"dz/anims/anm/player/ik/gear/tetracycline_tablets.anm");
		pType.AddItemInHandsProfileIK("TerjeExpressTestSepsisPack", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior,	"dz/anims/anm/player/ik/gear/tetracycline_tablets.anm");
		pType.AddItemInHandsProfileIK("TerjeExpressTestRabiesPack", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior,	"dz/anims/anm/player/ik/gear/tetracycline_tablets.anm");
		
		pType.AddItemInHandsProfileIK("CharcoalTablets", "dz/anims/workspaces/player/player_main/props/player_main_1h_tablets.asi", pBehavior, "dz/anims/anm/player/ik/gear/cassette.anm");
		pType.AddItemInHandsProfileIK("ChelatingTablets", "dz/anims/workspaces/player/player_main/props/player_main_1h_tablets.asi", pBehavior, "dz/anims/anm/player/ik/gear/cassette.anm");
		pType.AddItemInHandsProfileIK("PainkillerTablets", "dz/anims/workspaces/player/player_main/props/player_main_1h_tablets.asi", pBehavior, "dz/anims/anm/player/ik/gear/cassette.anm");
		pType.AddItemInHandsProfileIK("TetracyclineAntibiotics", "dz/anims/workspaces/player/player_main/props/player_main_1h_tablets.asi", pBehavior, "dz/anims/anm/player/ik/gear/cassette.anm");
	}

	override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterTwoHanded(pType, pBehavior);

		pType.AddItemInHandsProfileIK("TerjeSleepingBag", "dz/anims/workspaces/player/player_main/weapons/player_main_2h_extinguisher.asi", pBehavior, "dz/anims/anm/player/ik/two_handed/WaterproofBag.anm");	
	}
	
}
