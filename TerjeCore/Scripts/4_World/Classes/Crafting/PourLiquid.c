// <copyright file="PourLiquid.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PourLiquid
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		bool result = super.CanDo(ingredients, player);
		if (result)
		{
			ItemBase entity_in_hands = ItemBase.Cast(player.GetHumanInventory().GetEntityInHands());
			if( entity_in_hands == ingredients[0] )
			{
				result = TerjeCustomLiquids.GetInstance().CanTransfer(ingredients[0],ingredients[1]);
			}
			else
			{
				result = TerjeCustomLiquids.GetInstance().CanTransfer(ingredients[1],ingredients[0]);
			}
		}
		
		return result;
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)
	{
		super.Do(ingredients, player, results, specialty_weight);

		ItemBase entity_in_hands = ItemBase.Cast(player.GetHumanInventory().GetEntityInHands());
		if( entity_in_hands == ingredients[0] )
		{
			TerjeCustomLiquids.GetInstance().FixVanillaTransfer(ingredients[0],ingredients[1]);
		}
		else
		{
			TerjeCustomLiquids.GetInstance().FixVanillaTransfer(ingredients[1],ingredients[0]);
		}
	}
}