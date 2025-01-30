// <copyright file="ActionConstructor.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		
		actions.Insert(ActionUseSalveTarget);
		actions.Insert(ActionUseSalveSelf);
		
		actions.Insert(ActionInjectSyringeTarget);
		actions.Insert(ActionInjectSyringeSelf);
		actions.Insert(ActionEmptySyringe);
		
		actions.Insert(ActionRebandageSelf);
		actions.Insert(ActionRebandageTarget);
		
		actions.Insert(ActionSurgeryVisceraSelf);
		actions.Insert(ActionSurgeryVisceraTarget);
		
		actions.Insert(ActionSurgeryBulletSelf);
		actions.Insert(ActionSurgeryBulletTarget);
		
		actions.Insert(ActionSurgeryStubSelf);
		actions.Insert(ActionSurgeryStubTarget);
		
		actions.Insert(ActionDisinfectSutureSelf);
		actions.Insert(ActionDisinfectSutureTarget);
		
		actions.Insert(ActionDisinfectBandagedWoundSelf);
		actions.Insert(ActionDisinfectBandagedWoundTarget);
		
		actions.Insert(ActionStethoscopeInspect);
		actions.Insert(ActionPackTerjeSleepingBag);
		actions.Insert(ActionTerjeExpressTestAgents);
		
		actions.Insert(ActionTerjeExpressTestVirusZSelf);
		actions.Insert(ActionTerjeExpressTestSepsisSelf);
		actions.Insert(ActionTerjeExpressTestRabiesSelf);
		actions.Insert(ActionTerjeExpressTestVirusZTarget);
		actions.Insert(ActionTerjeExpressTestSepsisTarget);
		actions.Insert(ActionTerjeExpressTestRabiesTarget);
	}
}