// <copyright file="ActionDisinfectBandagedWound.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionDisinfectBandagedWoundSelf: ActionDisinfectBase
{
	void ActionDisinfectBandagedWoundSelf()
	{
		m_CallbackClass = ActionDisinfectSelfCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_STITCHUPSELF;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "#STR_TERJEMED_DISINFECTBANDAGE";
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
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return player.HasTerjeDirtyBandagesSelf();
	}
	

	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (action_data.m_MainItem && target)
		{
			if (target.GetTerjeStats().GetBandagesDirty() > 0)
			{
				target.GetTerjeStats().SetBandagesDirty(target.GetTerjeStats().GetBandagesDirty() - 1);
				target.GetTerjeStats().SetBandagesClean(target.GetTerjeStats().GetBandagesClean() + 1);
			}
			else if (target.GetTerjeStats().GetSuturesBandagedDirty() > 0)
			{
				target.GetTerjeStats().SetSuturesBandagedDirty(target.GetTerjeStats().GetSuturesBandagedDirty() - 1);
				target.GetTerjeStats().SetSuturesBandagedClean(target.GetTerjeStats().GetSuturesBandagedClean() + 1);
			}
		}
		
		Apply(action_data);
	}
}

class ActionDisinfectBandagedWoundTarget: ActionDisinfectBase
{	
	void ActionDisinfectBandagedWoundTarget()
	{
		m_CallbackClass = ActionDisinfectSelfCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "#STR_TERJEMED_DISINFECTBANDAGE";
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (target)
		{
			PlayerBase target_player = PlayerBase.Cast(target.GetObject());
			if (target_player)
			{
				return target_player.HasTerjeDirtyBandages();
			}
			
		}
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if ( target )
		{
			if (CanReceiveAction(action_data.m_Target))
			{
				if (target.GetTerjeStats().GetBandagesDirty() > 0)
				{
					target.GetTerjeStats().SetBandagesDirty(target.GetTerjeStats().GetBandagesDirty() - 1);
					target.GetTerjeStats().SetBandagesClean(target.GetTerjeStats().GetBandagesClean() + 1);
				}
				else if (target.GetTerjeStats().GetSuturesBandagedDirty() > 0)
				{
					target.GetTerjeStats().SetSuturesBandagedDirty(target.GetTerjeStats().GetSuturesBandagedDirty() - 1);
					target.GetTerjeStats().SetSuturesBandagedClean(target.GetTerjeStats().GetSuturesBandagedClean() + 1);
				}
				
				Apply(action_data);
			}
		}
	}
}