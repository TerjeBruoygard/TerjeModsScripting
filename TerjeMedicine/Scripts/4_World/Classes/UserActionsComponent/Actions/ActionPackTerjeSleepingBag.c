// <copyright file="ActionPackTerjeSleepingBag.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionPackTerjeSleepingBag : ActionPackTent
{
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor(UAMaxDistances.DEFAULT);
	}

	override bool IsUsingProxies()
	{
		return false;
	}
	
	override bool ActionConditionContinue( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		TerjeSleepingBag sleepingBag = TerjeSleepingBag.Cast( targetObject );
		return sleepingBag && sleepingBag.CanBePacked();
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object targetObject = target.GetObject();
		TerjeSleepingBag sleepingBag = TerjeSleepingBag.Cast( targetObject );
		return player && sleepingBag && sleepingBag.CanBePacked();
	}
	
	override void OnExecute( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		TerjeSleepingBag sleepingBag = TerjeSleepingBag.Cast( targetObject );
		sleepingBag.SetIsBeingPacked(true);
	}
	
	override void OnEnd( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		TerjeSleepingBag sleepingBag = TerjeSleepingBag.Cast( targetObject );
		sleepingBag.SetIsBeingPacked(false);
		if ( action_data.m_Player ) 
		{
			action_data.m_Player.TryHideItemInHands(false);
		}
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		TerjeSleepingBag sleepingBag = TerjeSleepingBag.Cast( targetObject );
		if (sleepingBag.CanBePacked())
		{
			sleepingBag.Pack( true );
			sleepingBag.SetPosition( action_data.m_Player.GetPosition() );
			sleepingBag.SetOrientation( action_data.m_Player.GetOrientation() );
			sleepingBag.PlaceOnSurface();
		}
	}
	
	override string GetAdminLogMessage(ActionData action_data)
	{
		if ((action_data != null) && (action_data.m_Target != null) && (action_data.m_Target.GetObject()))
		{
			return " packed " + action_data.m_Target.GetObject().GetDisplayName() + " with Hands ";
		}
		
		return string.Empty;
	}
}