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
		pType.AddItemInHandsProfileIK("TerjeDosimetrPripyat", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeMedicine/Anm/Pripyat.anm");
		pType.AddItemInHandsProfileIK("TerjeDosimetrMkc01A", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeMedicine/Anm/Pripyat.anm");
		pType.AddItemInHandsProfileIK("TerjeDosimetrDpg05", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeMedicine/Anm/Pripyat.anm");
		pType.AddItemInHandsProfileIK("TerjeDosimetrCdv700", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeMedicine/Anm/cdv700.anm");
		pType.AddItemInHandsProfileIK("TerjeSoap", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior, "dz/anims/anm/player/ik/gear/PersonalRadio.anm");
		pType.AddItemInHandsProfileIK("TerjePlaster", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior,	"dz/anims/anm/player/ik/gear/tetracycline_tablets.anm");
		pType.AddItemInHandsProfileIK("TerjeCanisterChemical", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeMedicine/Anm/canistre.anm");
	}

	override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterTwoHanded(pType, pBehavior);

		pType.AddItemInHandsProfileIK("TerjeCaseRadSpecial", "dz/anims/workspaces/player/player_main/player_main_2h.asi", pBehavior, "dz/anims/anm/player/ik/two_handed/ScientificCase.anm");
	};

	override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterHeavy(pType, pBehavior);
       
		pType.AddItemInHandsProfileIK("TerjeCaseRadMilitary", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/heavy/wooden_crate.anm");
    };
};
