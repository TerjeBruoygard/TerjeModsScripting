// <copyright file="ActionTerjeExpressTestAgents.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionTerjeExpressTestAgentsCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DEFAULT);
	}
}

class ActionTerjeExpressTestAgents: ActionContinuousBase
{
	void ActionTerjeExpressTestAgents()
	{
		m_CallbackClass = ActionTerjeExpressTestAgentsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
		m_Text = "#use";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTObject( UAMaxDistances.DEFAULT );
	}
	
	override bool HasTarget()
	{
		return true;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return target && target.GetObject() && target.GetObject().IsItemBase();
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		ItemBase targetItem = ItemBase.Cast(action_data.m_Target.GetObject());
		if (action_data.m_MainItem && targetItem)
		{
			action_data.m_MainItem.AddQuantity(-1);
			
			array<string> strAgents();
			OnTerjeStringifyCollectedAgents(targetItem, OnTerjeCollectAgentsFromTarget(targetItem), strAgents);
			
			string message = "";
			if (strAgents.Count() > 0)
			{
				for (int i = 0; i < strAgents.Count(); i++)
				{
					if (i > 0)
					{
						message += ", ";
					}
					
					message += strAgents.Get(i);
				}
			}
			else
			{
				message = "#STR_TERJEMED_EXPRESS_CLEAN";
			}
			
			NotificationSystem.SendNotificationToPlayerExtended(action_data.m_Player, 10, "#STR_TERJEMED_EXPRESS_RESULT", message, "set:TerjeMedicine_icon image:tm_expresstest");
		}
	}
	
	int OnTerjeCollectAgentsFromTarget(ItemBase target)
	{
		int result = target.GetAgents();
		if (target.IsLiquidContainer() && target.IsLiquidPresent())
		{
			if (target.GetTerjeLiquidType() != 0)
			{
				result |= TerjeCustomLiquids.GetInstance().GetAgents(target.GetTerjeLiquidType());
			}
			else
			{
				result |= Liquid.GetAgents(target.GetLiquidType());
			}
		}
		
		return result;
	}
	
	void OnTerjeStringifyCollectedAgents(ItemBase target, int agents, array<string> result)
	{
		if (agents & eAgents.CHOLERA)
		{
			result.Insert("#STR_TERJEMED_CHOLERA");
		}
		
		if (agents & eAgents.INFLUENZA)
		{
			result.Insert("#STR_TERJEMED_INFLUENZA");
		}
		
		if (agents & eAgents.SALMONELLA)
		{
			result.Insert("#STR_TERJEMED_SALMONELLA");
		}
		
		if (agents & eAgents.BRAIN)
		{
			result.Insert("#STR_TERJEMED_BRAIN");
		}
		
		if (agents & eAgents.FOOD_POISON)
		{
			result.Insert("#STR_TERJEMED_FOOD_POISON");
		}
		
		if (agents & eAgents.CHEMICAL_POISON)
		{
			result.Insert("#STR_TERJEMED_CHEMICAL_POISON");
		}
		
		if (agents & eAgents.HEAVYMETAL)
		{
			result.Insert("#STR_TERJEMED_HEAVYMETAL");
		}
	}
}