// <copyright file="ActionCraftKnifeEnv.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionCraftStoneKnifeEnv
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		return super.ActionCondition(player, target, item) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(null, player, "surv", "bushcraft");
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_Player.m_terjeSkillsSpawnEntityOnGroundCache = new array<ItemBase>;
		super.OnFinishProgressServer(action_data);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(null, action_data.m_Player, action_data.m_Player.m_terjeSkillsSpawnEntityOnGroundCache, "surv", "bushcraft", true);
		action_data.m_Player.m_terjeSkillsSpawnEntityOnGroundCache = null;
	}
}

modded class ActionCraftBoneKnifeEnv
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		return super.ActionCondition(player, target, item) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(null, player, "surv", "bushcraft");
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_Player.m_terjeSkillsSpawnEntityOnGroundCache = new array<ItemBase>;
		super.OnFinishProgressServer(action_data);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(null, action_data.m_Player, action_data.m_Player.m_terjeSkillsSpawnEntityOnGroundCache, "surv", "bushcraft", true);
		action_data.m_Player.m_terjeSkillsSpawnEntityOnGroundCache = null;
	}
}