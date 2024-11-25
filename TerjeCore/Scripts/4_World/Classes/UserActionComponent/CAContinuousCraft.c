// <copyright file="CAContinuousCraft.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class CAContinuousCraft
{
	override void Setup( ActionData action_data  )
	{
		super.Setup(action_data);
		
		WorldCraftActionData action_data_wc = WorldCraftActionData.Cast(action_data);	
		PluginRecipesManager module_recipes_manager;
		Class.CastTo(module_recipes_manager, GetPlugin(PluginRecipesManager));
		if (module_recipes_manager && action_data.m_Player)
		{
			m_AdjustedTimeToComplete *= module_recipes_manager.GetTerjeRecipeTimeModifier(action_data.m_Player, action_data_wc.m_RecipeID);
		}
	}
}