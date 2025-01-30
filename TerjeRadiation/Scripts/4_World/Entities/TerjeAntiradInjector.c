// <copyright file="TerjeAntiradInjector.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeAntiradInjector: Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectTarget);
		AddAction(ActionInjectSelf);
	}
	
	override void OnApply(PlayerBase player)
	{
		if (!player)
			return;
		
		ApplyTerjeConsumableEffects(player, 1);
	}
	
	override bool DescriptionOverride(out string output)
	{
		if (super.DescriptionOverride(output))
		{
			return true;
		}
		
		if (ConfigGetString("descriptionShort") == "...")
		{
			// Hack for compatibility with TerjeMedicine
			output = "#STR_TERJERAD_RADIOPROTECTOR_DESC";
			return true;
		}
		
		return false;
	}
}