// <copyright file="TerjeAmpouleBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeAmpouleBase : Inventory_Base
{
	override void InitItemVariables()
	{
		super.InitItemVariables();
		can_this_be_combined = true;
	}
};

class TerjeAmpouleAlcohol : TerjeAmpouleBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionDisinfectTarget);
		AddAction(ActionDisinfectSelf);
		AddAction(ActionWashHandsItemContinuous);
	}
	
	override float GetDisinfectQuantity(int system = 0, Param param1 = null)
	{
		return 1;
	}
	
	override int GetLiquidType()
	{
		return LIQUID_DISINFECTANT;
	}
};