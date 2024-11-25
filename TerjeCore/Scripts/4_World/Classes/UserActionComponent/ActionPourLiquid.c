// <copyright file="ActionPourLiquid.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionPourLiquid
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		bool result = super.ActionCondition(player, target, item);
		if (result)
		{
			ItemBase target_item = ItemBase.Cast(target.GetObject());
			if ( target_item && item )
			{
				result = TerjeCustomLiquids.GetInstance().CanTransfer(item, target_item);
			}
		}
		
		return result;
	}
}