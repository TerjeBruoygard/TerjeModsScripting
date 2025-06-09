// <copyright file="ActionTerjePassportOpen.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionTerjePassportOpen: ActionSingleUseBase
{
	void ActionTerjePassportOpen()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM_ONCE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_OPENITEM_ONCE;
		m_Text = "#open";
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

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		TerjePassport passport = TerjePassport.Cast(action_data.m_MainItem);
		if (passport)
		{
			passport.OpenTerjePassportServer(action_data.m_Player);
		}
	}
}