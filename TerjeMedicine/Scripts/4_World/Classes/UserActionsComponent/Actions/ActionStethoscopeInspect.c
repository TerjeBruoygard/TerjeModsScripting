// <copyright file="ActionStethoscopeInspect.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CAContinuousRepeatStethoscopeInspect : CAContinuousRepeat
{
	const float TERJE_NOTIFICATION_HIDE_TIME = 2;
	int m_terjeCurrentIndex;
	float m_terjeNotificationTime;
	
	void CAContinuousRepeatStethoscopeInspect( float time_to_complete_action )
	{
		m_terjeCurrentIndex = -1;
		m_terjeNotificationTime = Math.Max(1, time_to_complete_action - TERJE_NOTIFICATION_HIDE_TIME);
		m_DefaultTimeToComplete = time_to_complete_action;
	}
	
	override int Execute( ActionData action_data )
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
}

class ActionStethoscopeInspectCB : ActionContinuousBaseCB
{
	const float TERJE_STETHOSCOPE_LOOP_TIME = 5;
	
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeatStethoscopeInspect(TERJE_STETHOSCOPE_LOOP_TIME);
	}
}

class TerjeStethoscopeActionData : ActionData
{
	ref TerjePlayerInspectableStats m_terjeInspectableStats = null;
	
	void FillTerjeInspectableStats(PlayerBase player, int level)
	{
		m_terjeInspectableStats = new TerjePlayerInspectableStats(player, level);
	}
}

class ActionStethoscopeInspect: ActionContinuousBase
{
	void ActionStethoscopeInspect()
	{
		m_CallbackClass 	= ActionStethoscopeInspectCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_SALINEBLOODBAGTARGET;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT;

		m_Text = "#STR_TERJEMED_STETHOSCOPE_USE";
	}
	
	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}
	
	override ActionData CreateActionData()
	{
		return new TerjeStethoscopeActionData;
	}
	
	override bool SetupAction(PlayerBase player, ActionTarget target, ItemBase item, out ActionData action_data, Param extra_data = null)
	{
		if (super.SetupAction(player, target, item, action_data, extra_data))
		{
			TerjeStethoscopeActionData terjeActionData;
			if (Class.CastTo(terjeActionData, action_data))
			{
				PlayerBase targetPlayer = PlayerBase.Cast( action_data.m_Target.GetObject() );
				if (targetPlayer)
				{
					if (GetGame().IsDedicatedServer() && player && player.GetTerjeSkills())
					{
						if (player.GetTerjeSkills().IsPerkRegistered("med", "stethscp"))
						{
							int perkLevel = player.GetTerjeSkills().GetPerkLevel("med", "stethscp");
							if (perkLevel > 0)
							{
								terjeActionData.FillTerjeInspectableStats(targetPlayer, perkLevel);
							}
						}
						else
						{
							terjeActionData.FillTerjeInspectableStats(targetPlayer, 3);
						}
					}
					
					return true;
				}
			}
		}
		
		return false;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.GetItemInHands())
		{
			return false;
		}

		TerjeStethoscope itemStatoschope = TerjeStethoscope.Cast(player.GetItemOnSlot("Eyewear"));
		if (!itemStatoschope || itemStatoschope.IsRuined())
		{
			return false;
		}

		PlayerBase targetPlayer = PlayerBase.Cast( target.GetObject() );
		if (!targetPlayer)
		{
			return false;
		}
		
		if (!targetPlayer.IsAlive())
		{
			return false;
		}
		
		return true;
	}
}