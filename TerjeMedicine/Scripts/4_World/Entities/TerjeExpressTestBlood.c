// <copyright file="TerjeExpressTestBlood.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeExpressTestVirusZ extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionTerjeExpressTestVirusZSelf);
		AddAction(ActionTerjeExpressTestVirusZTarget);
	}
}

class TerjeExpressTestSepsis extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionTerjeExpressTestSepsisSelf);
		AddAction(ActionTerjeExpressTestSepsisTarget);
	}
}

class TerjeExpressTestRabies extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionTerjeExpressTestRabiesSelf);
		AddAction(ActionTerjeExpressTestRabiesTarget);
	}
}