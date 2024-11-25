// <copyright file="ActionSurgeryBullet.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionSurgeryBulletBaseCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float time = m_ActionData.m_MainItem.GetTerjeSurgeryBulletTime(m_ActionData.m_Player);
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(Math.Max(time, 1));
	}
}

class ActionSurgeryBulletSelf : ActionBandageBase
{	
	void ActionSurgeryBulletSelf()
	{
		m_CallbackClass 	= ActionSurgeryBulletBaseCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_STITCHUPSELF;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_SURBULLET_SELF";
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
		return player.HasTerjeBulletWoundsSelf() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (action_data.m_MainItem && target)
		{
			ApplySurgeryBullet(action_data.m_MainItem, target, target);
		}
	}
	
	override void OnStartAnimationLoopServer( ActionData action_data )
	{
		super.OnStartAnimationLoopServer(action_data);
		
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (target && target.GetTerjeStats())
		{
			float pain = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FORCE_SURGERY_PAIN);
			if (target.GetTerjeStats().GetPainValue() < pain)
			{
				target.GetTerjeStats().SetPainValue(pain);
			}
		}
	}
}

class ActionSurgeryBulletTarget : ActionBandageBase
{
	void ActionSurgeryBulletTarget()
	{
		m_CallbackClass 	= ActionSurgeryBulletBaseCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_SURBULLET_TARGET";
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem 	= new CCINonRuined();
		m_ConditionTarget 	= new CCTMan(UAMaxDistances.DEFAULT);
	}

	override int GetStanceMask(PlayerBase player)
	{
		if (player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_PRONE))
		{
			return DayZPlayerConstants.STANCEMASK_CROUCH;
		}
		else
		{
			return DayZPlayerConstants.STANCEMASK_ERECT;
		}
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (otherPlayer)
		{
			return otherPlayer.HasTerjeBulletWounds() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
		}
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase operator = PlayerBase.Cast(action_data.m_Player);
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if (action_data.m_MainItem && target && operator)
		{
			if (CanReceiveAction(action_data.m_Target))
			{
				ApplySurgeryBullet(action_data.m_MainItem, target, operator);
			}
		}
	}
	
	override void OnStartAnimationLoopServer( ActionData action_data )
	{
		super.OnStartAnimationLoopServer(action_data);
		
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (target && target.GetTerjeStats())
		{
			float pain = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FORCE_SURGERY_PAIN);
			if (target.GetTerjeStats().GetPainValue() < pain)
			{
				target.GetTerjeStats().SetPainValue(pain);
			}
		}
	}
}