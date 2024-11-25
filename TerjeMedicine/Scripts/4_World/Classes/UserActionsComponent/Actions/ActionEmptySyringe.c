// <copyright file="ActionEmptySyringe.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionEmptySyringe: ActionSingleUseBase
{
	void ActionEmptySyringe()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		m_FullBody = false;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "#empty";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if ( GetGame().IsDedicatedServer() )
		{
			return true;
		}
		
		return player.IsCurrentCameraAimedAtGround();
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		TerjeSyringeFull syringe = TerjeSyringeFull.Cast(action_data.m_MainItem);
		if (syringe)
		{
			action_data.m_Player.ServerReplaceItemWithNew(new TerjeSyringeReplaceLambda(syringe, syringe.GetTerjeSyringeClassnameEmpty(), action_data.m_Player));
		}
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		TerjeSyringeFull syringe = TerjeSyringeFull.Cast(action_data.m_MainItem);
		if (syringe)
		{
			action_data.m_Player.LocalReplaceItemWithNew(new TerjeSyringeReplaceLambda(syringe, syringe.GetTerjeSyringeClassnameEmpty(), action_data.m_Player));
		}
	}
}