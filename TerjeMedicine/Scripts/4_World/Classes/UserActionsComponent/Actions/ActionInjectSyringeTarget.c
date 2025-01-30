// <copyright file="ActionInjectSyringeTarget.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionInjectSyringeTarget: ActionSingleUseBase
{
	void ActionInjectSyringeTarget()
	{
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_MEDIUM;
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INJECTIONTARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}
		
	override string GetText()
	{
		return "#inject_target";
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		if (action_data.m_MainItem && action_data.m_Target.GetObject())
		{
			PlayerBase targetPlayer = PlayerBase.Cast( action_data.m_Target.GetObject() );
			if (targetPlayer)
			{
				action_data.m_MainItem.OnApply(targetPlayer);
			}
		}
		
		action_data.m_MainItem.SetCleanness(0);
		
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