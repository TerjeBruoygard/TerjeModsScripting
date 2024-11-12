// <copyright file="ActionTerjeMaskStash.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionTerjeMaskStashCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DIG_STASH);
	}
}

class ActionTerjeMaskStash: ActionContinuousBase
{	
	void ActionTerjeMaskStash()
	{
		m_CallbackClass 	= ActionTerjeMaskStashCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight 	= UASoftSkillsWeight.ROUGH_LOW;
		m_Text 				= "#STR_TERJESKILL_MASKSTASH_ACTION";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget	= new CCTObject(UAMaxDistances.DEFAULT);
		m_ConditionItem 	= new CCINotPresent();
	}
	
	override bool Can(PlayerBase player, ActionTarget target, ItemBase item, int condition_mask)
	{
		if (!super.Can(player, target, item, condition_mask))
			return false;
		
		return player.CheckFreeSpace(vector.Forward, 1.0, false);
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		UndergroundStash stash;
		if (Class.CastTo(stash, target.GetObject()) && stash.CanBeDigged() && !stash.GetTerjeStashInvisible())
		{			
			if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkLevel("surv", "stashes") > 0)
			{
				return true;
			}	
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		// Dig out of stash
		UndergroundStash stash;
		if (Class.CastTo(stash, action_data.m_Target.GetObject()))
		{
			stash.SetTerjeStashInvisible(true);
		}
	}
}