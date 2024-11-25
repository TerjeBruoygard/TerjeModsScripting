// <copyright file="ActionDisinfectHands.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionDisinfectSelf
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.GetItemOnSlot("Gloves"))
			return false;
		
		return true;
	}
	
	override string GetText()
	{
		return "#STR_TERJEMED_DISINFECT_HANDS";
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_Player.SetBloodyHands(false);
		
		float handsDisinfectionTime = 0;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HANDS_DISINFECTION_TIME, handsDisinfectionTime);	
		action_data.m_Player.GetTerjeStats().SetDisinfectedHands(handsDisinfectionTime);
		
		super.OnFinishProgressServer(action_data);
	}
}

modded class ActionDisinfectTarget
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (target && target.GetObject())
		{
			PlayerBase other = PlayerBase.Cast( target.GetObject() );
			if (other.GetItemOnSlot("Gloves"))
			{
				return false;
			}
		}
		
		return true;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());		
		if( target )
		{
			target.SetBloodyHands(false);
			
			float handsDisinfectionTime = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HANDS_DISINFECTION_TIME, handsDisinfectionTime);	
			target.GetTerjeStats().SetDisinfectedHands(handsDisinfectionTime);
		}
		
		super.OnFinishProgressServer(action_data);
	}
}

modded class ActionWashHandsItem
{
	override void OnEndServer( ActionData action_data )
	{
		super.OnEndServer(action_data);
		
		if (action_data.m_State != UA_INTERRUPT)
		{
			PlayerBase target = PlayerBase.Cast(action_data.m_Player);
			if (target && action_data.m_MainItem && action_data.m_MainItem.GetLiquidType() == LIQUID_DISINFECTANT)
			{
				float handsDisinfectionTime = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HANDS_DISINFECTION_TIME, handsDisinfectionTime);	
				target.GetTerjeStats().SetDisinfectedHands(handsDisinfectionTime);
			}
		}
	}
}

modded class ActionWashHandsItemContinuous
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);
		
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (target && action_data.m_MainItem && action_data.m_MainItem.GetLiquidType() == LIQUID_DISINFECTANT)
		{
			float handsDisinfectionTime = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HANDS_DISINFECTION_TIME, handsDisinfectionTime);	
			target.GetTerjeStats().SetDisinfectedHands(handsDisinfectionTime);
		}
	}
}
