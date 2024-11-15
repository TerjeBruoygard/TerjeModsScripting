// <copyright file="ActionSkinning.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionSkinning
{
	private EntityAI m_terjeSkinnedBodyCache = null;
	
	override void OnFinishProgressServer(ActionData action_data)
	{
		m_terjeSkinnedBodyCache = EntityAI.Cast(action_data.m_Target.GetObject());
		super.OnFinishProgressServer(action_data);
		m_terjeSkinnedBodyCache = null;
	}
	
	ItemBase CreateOrgan(PlayerBase player, vector body_pos, string item_to_spawn, string cfg_skinning_organ_class, ItemBase tool)
	{
		ItemBase result = super.CreateOrgan(player, body_pos, item_to_spawn, cfg_skinning_organ_class, tool);
		PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
		if (result && m_terjeSkinnedBodyCache && plugin)
		{
			plugin.TransferTerjeRadiation(m_terjeSkinnedBodyCache, result, 1.0);
		}
		
		return result;
	}
};