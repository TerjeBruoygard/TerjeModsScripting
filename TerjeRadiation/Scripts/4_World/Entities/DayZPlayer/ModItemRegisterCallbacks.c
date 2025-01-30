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
		pType.AddItemInHandsProfileIK("TerjeAntiradInjector", "dz/anims/workspaces/player/player_main/props/player_main_1h_morphine.asi", pBehavior, "dz/anims/anm/player/ik/gear/morphine.anm");
		pType.AddItemInHandsProfileIK("TerjeDosimetrPripyat", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeRadiation/Anm/Pripyat.anm");
		pType.AddItemInHandsProfileIK("TerjeDosimetrMkc01A", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeRadiation/Anm/Pripyat.anm");
		pType.AddItemInHandsProfileIK("TerjeDosimetrDpg05", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeRadiation/Anm/Pripyat.anm");
		pType.AddItemInHandsProfileIK("TerjeDosimetrCdv700", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeRadiation/Anm/cdv700.anm");
		pType.AddItemInHandsProfileIK("TerjeSoap", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior, "dz/anims/anm/player/ik/gear/PersonalRadio.anm");
		pType.AddItemInHandsProfileIK("TerjeShower", "dz/anims/workspaces/player/player_main/player_main_1h.asi",	pBehavior, "dz/anims/anm/player/ik/gear/PersonalRadio.anm");
		pType.AddItemInHandsProfileIK("TerjeCanisterChemical", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "TerjeRadiation/Anm/canistre.anm");
	}

	override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterTwoHanded(pType, pBehavior);

		pType.AddItemInHandsProfileIK("TerjeCaseRadSpecial", "dz/anims/workspaces/player/player_main/player_main_2h.asi", pBehavior, "dz/anims/anm/player/ik/two_handed/ScientificCase.anm");
		pType.AddItemInHandsProfileIK("TerjePump",	"dz/anims/workspaces/player/player_main/player_main_2h.asi", pBehavior,	"dz/anims/anm/player/ik/two_handed/BatteryCar.anm");
	}

	override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterHeavy(pType, pBehavior);
		
		pType.AddItemInHandsProfileIK("TerjeCaseRadMilitary", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/heavy/wooden_crate.anm");
		pType.AddItemInHandsProfileIK("TerjeRadTent", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/heavy/car_tent_packed.anm");
	}
}
