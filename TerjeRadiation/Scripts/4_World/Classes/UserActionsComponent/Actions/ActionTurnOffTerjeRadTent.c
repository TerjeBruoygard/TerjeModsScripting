// <copyright file="ActionTurnOffTerjeRadTent.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionTurnOffTerjeRadTent : ActionInteractBase
{
	void ActionTurnOffTerjeRadTent()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text = "#switch_off";
	}
	
	override bool IsUsingProxies()
	{
		return true;
	}
	
	override bool UseMainItem()
	{
		return false;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursorParent(UAMaxDistances.DEFAULT);
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		Object targetParent = target.GetParent();
		
		TentBase inventory_tent = TentBase.Cast(targetObject);
		if (inventory_tent && inventory_tent.GetHierarchyRootPlayer())
		{
			return false; //tent is somewhere in player's inventory
		}
		
		if ( player && targetObject && targetParent )
		{
			TerjeRadTent tent = TerjeRadTent.Cast( targetParent );
			if ( tent.IsValidTerjeRadTentToWork() )
			{
				array<string> selections = new array<string>;
				targetObject.GetActionComponentNameList(target.GetComponentIndex(), selections);
				
				for ( int s = 0; s < selections.Count(); s++ )
				{
					string selectionName = selections[s];
					if ( selectionName == "body" )
					{
						return (tent.HasEnergyManager() && tent.GetCompEM().CanSwitchOff());
					}
				}
			}
		}
		
		return false;
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		EntityAI target_entity = EntityAI.Cast( action_data.m_Target.GetParent() );
		
		if ( target_entity.GetCompEM().CanSwitchOff() )
		{
			target_entity.GetCompEM().SwitchOff();
			
			InformPlayers( action_data.m_Player, action_data.m_Target, UA_FINISHED );
		}
		else
		{
			InformPlayers( action_data.m_Player, action_data.m_Target, UA_FAILED );
		}
	}
}