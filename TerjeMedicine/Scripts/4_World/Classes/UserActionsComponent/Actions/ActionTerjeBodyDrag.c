// <copyright file="ActionTerjeBodyDrag.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionTerjeBodyDragCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(0.1);
	}
}

class ActionTerjeBodyDrag : ActionContinuousBase
{
	void ActionTerjeBodyDrag()
	{
		m_CallbackClass = ActionTerjeBodyDragCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DEPLOY_HEAVY;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text = "#STR_TERJEMED_BODY_DRAG";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player && target && !player.GetItemInHands())
		{
			PlayerBase ntarget = PlayerBase.Cast(target.GetObject());
			if(player && ntarget && (!ntarget.IsAlive() || ntarget.IsUnconscious()) && !player.GetParent() && !ntarget.GetParent())
			{
				bool isEnabled = false;
				if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_BODY_DRAG_ACTION, isEnabled))
				{
					return isEnabled;
				}
			}
		}
		
		return false;
	}
	
	override bool HasProgress()
	{
		return false;
	}
	
	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT, false);
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		if (action_data.m_Target && action_data.m_Player)
		{
			PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
			if (targetPlayer && (!targetPlayer.IsAlive() || targetPlayer.IsUnconscious()))
			{
				vector fromPos = targetPlayer.GetWorldPosition();
				vector toPos = action_data.m_Player.GetWorldPosition();
				targetPlayer.OnTerjeBodyDragProgress(fromPos, toPos, 0);
				targetPlayer.TerjeRPCSingleParam("tm.body.drag", new Param2<vector, vector>(fromPos, toPos), true);
			}
		}
	}
}