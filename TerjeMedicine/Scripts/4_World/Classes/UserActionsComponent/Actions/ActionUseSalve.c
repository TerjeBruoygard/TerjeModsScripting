// <copyright file="ActionUseSalve.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionUseSalveBase: ActionContinuousBase
{
	void ApplyUseSalve( ItemBase item, PlayerBase player)
	{
		if (item)
		{
			item.ApplyTerjeConsumableEffects(player, 1);
			
			if (item.HasQuantity())
			{
				item.AddQuantity(-1,true);
			}
			else
			{
				item.Delete();
			}
		}
	}
}

class ActionUseSalveCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
}

class ActionUseSalveSelf: ActionUseSalveBase
{	
	void ActionUseSalveSelf()
	{
		m_CallbackClass = ActionUseSalveCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
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
		return "#STR_TERJEMED_SALVE_USE_SELF";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if(action_data.m_MainItem && target)
		{
			ApplyUseSalve( action_data.m_MainItem, target );
		}
	}
}

class ActionUseSalveTarget: ActionUseSalveBase
{	
	void ActionUseSalveTarget()
	{
		m_CallbackClass = ActionUseSalveCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}

	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override bool HasTarget()
	{
		return true;
	}
		
	override string GetText()
	{
		return "#STR_TERJEMED_SALVE_USE_TARGET";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		return targetPlayer && targetPlayer.IsAlive();		
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		if(action_data.m_MainItem && target)
		{
			ApplyUseSalve( action_data.m_MainItem, target );
		}
	}
}