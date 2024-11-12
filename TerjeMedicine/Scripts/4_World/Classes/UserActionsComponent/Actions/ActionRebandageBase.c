// <copyright file="ActionRebandageBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionRebandageSelf : ActionBandageBase
{	
	void ActionRebandageSelf()
	{
		m_CallbackClass 	= ActionBandageSelfCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_CHANGE_BANDAGE";
	}

	override void CreateConditionComponents()  
	{		
		m_ConditionItem 	= new CCINonRuined();
		m_ConditionTarget 	= new CCTSelf();
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return player.HasTerjeDirtyBandagesSelf() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (action_data.m_MainItem && target)
		{
			ChangeBandage(action_data.m_MainItem, target);
		}
	}
};

class ActionRebandageTarget : ActionBandageBase
{
	void ActionRebandageTarget()
	{
		m_CallbackClass 	= ActionBandageTargetCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_CHANGE_BANDAGE";
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem 	= new CCINonRuined();
		m_ConditionTarget 	= new CCTMan(UAMaxDistances.DEFAULT);
	}

	override int GetStanceMask(PlayerBase player)
	{
		if (player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_PRONE))
			return DayZPlayerConstants.STANCEMASK_CROUCH;
		else
			return DayZPlayerConstants.STANCEMASK_ERECT;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (otherPlayer)
			return otherPlayer.HasTerjeDirtyBandages() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if (action_data.m_MainItem && target)
		{
			if (CanReceiveAction(action_data.m_Target))
				ChangeBandage(action_data.m_MainItem, target);
		}
	}
};