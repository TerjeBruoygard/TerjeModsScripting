// <copyright file="ActionTerjeReadSkillbook.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class UATimeSpent
{
	const float TERJE_READ_SKILLBOOK = 15;
}

class ActionTerjeReadSkillbookCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.TERJE_READ_SKILLBOOK);
	}
}

class ActionTerjeReadSkillbook: ActionContinuousBase
{
	void ActionTerjeReadSkillbook()
	{
		m_CallbackClass 	= ActionTerjeReadSkillbookCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_VIEWNOTE;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_FullBody 			= true;
		m_Text 				= "#STR_TERJESKILL_READ_BOOK";
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
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return item && item.IsInherited(TerjeBookBase) && item.ConfigIsExisting("terjeSkillId");
	}
	
	override bool ActionConditionContinue(ActionData action_data)
	{
		return true;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		ItemBase bookItem = action_data.m_MainItem;
		if (!bookItem)
		{
			return;
		}
		
		ref TerjeSkillCfg skillCfg;
		string skillId = bookItem.ConfigGetStringRaw("terjeSkillId");
		int skillExpGain = bookItem.ConfigGetInt("terjeSkillExpGain");
		int skillMinLevel = bookItem.ConfigGetInt("terjeSkillMinLevel");
		int skillMaxLevel = bookItem.ConfigGetInt("terjeSkillMaxLevel");
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg) || skillCfg == null)
		{
			return;
		}
		
		if (skillExpGain <= 0)
		{
			return;
		}
		
		if (skillMinLevel > skillMaxLevel)
		{
			return;
		}
		
		if (skillMaxLevel <= 0)
		{
			return;
		}
		
		PlayerBase player = action_data.m_Player;
		if (!player || !player.IsAlive() || player.GetTerjeProfile() == null || player.GetTerjeSkills() == null)
		{
			return;
		}
		
		bool isKnownBook = false;
		int skillLevel = player.GetTerjeSkills().GetSkillLevel(skillId);
		if (GetTerjeSettingBool(TerjeSettingsCollection.SKILLS_SINGLE_SKILLBOOK_READING))
		{
			isKnownBook = player.GetTerjeProfile().HasKnownSkillBook(skillId, bookItem.GetType());
		}
		
		if (isKnownBook)
		{
			NotificationSystem.SendNotificationToPlayerExtended(player, 10, "#STR_TERJESKILL_NOTHING_NEW", "#STR_TERJESKILL_NOTHING_NEW_DESC", skillCfg.GetIcon());
		}
		else if (skillLevel < skillMinLevel)
		{
			NotificationSystem.SendNotificationToPlayerExtended(player, 10, "#STR_TERJESKILL_TOO_HARD", "#STR_TERJESKILL_TOO_HARD_DESC", skillCfg.GetIcon());
		}
		else if (skillLevel > skillMaxLevel)
		{
			NotificationSystem.SendNotificationToPlayerExtended(player, 10, "#STR_TERJESKILL_TOO_EASY", "#STR_TERJESKILL_TOO_EASY_DESC", skillCfg.GetIcon());
		}
		else
		{
			player.GetTerjeSkills().AddSkillExperience(skillId, skillExpGain, false, true);
			player.GetTerjeProfile().AddKnownSkillBook(skillId, bookItem.GetType());
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.SKILLS_DELETE_SKILLBOOK_READING))
			{
				bookItem.DeleteSafe();
			}
		}
	}
}