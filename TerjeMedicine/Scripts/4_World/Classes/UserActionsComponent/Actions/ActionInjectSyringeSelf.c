// <copyright file="ActionInjectSyringeSelf.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionInjectSyringeSelf: ActionSingleUseBase
{
	void ActionInjectSyringeSelf()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INJECTION;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_MEDIUM;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "#inject";
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		if (action_data.m_MainItem && action_data.m_Player)
		{
			action_data.m_MainItem.OnApply(action_data.m_Player);
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

class TerjeSyringeReplaceLambda : ReplaceItemWithNewLambda
{
	override void CopyOldPropertiesToNew(notnull EntityAI old_item, EntityAI new_item)
	{
		super.CopyOldPropertiesToNew(old_item, new_item);
		new_item.SetHealth01("", "", old_item.GetHealth01());
	}
}