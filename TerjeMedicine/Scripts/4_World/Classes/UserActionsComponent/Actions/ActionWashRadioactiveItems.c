// <copyright file="ActionWashRadioactiveItems.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CAContinuousWashRadioactiveItems : CAContinuousBase
{
	protected float 				m_SpentQuantity;
	protected float 				m_SpentQuantity_total;
	protected float 				m_ItemMaxQuantity;
	protected float					m_TimeElpased;
	protected float 				m_QuantityUsedPerSecond;
	protected float 				m_DefaultTimeStep;
	protected ref Param1<float>		m_SpentUnits;
	
	void CAContinuousWashRadioactiveItems(float quantity_used_per_second, float time_to_progress)
	{
		m_QuantityUsedPerSecond = quantity_used_per_second * 0.25;
		m_DefaultTimeStep = time_to_progress;
	}
	
	override void Setup(ActionData action_data)
	{
		m_TimeElpased = 0;
		m_SpentQuantity = 0;
		EntityAI targetEntity = EntityAI.Cast(action_data.m_Target.GetObject());
		
		if (!m_SpentUnits)
		{
			m_SpentUnits = new Param1<float>(0);
		}
		else
		{
			m_SpentUnits.param1 = 0;
		}
		
		m_QuantityUsedPerSecond *= action_data.m_MainItem.GetLiquidThroughputCoef();
		m_ItemMaxQuantity = action_data.m_MainItem.GetQuantity();
	}
	
	
	override int Execute(ActionData action_data )
	{
		if (!action_data.m_Player || !action_data.m_Target)
		{
			return UA_ERROR;
		}
		
		if (action_data.m_MainItem.GetQuantity() <= action_data.m_MainItem.GetQuantityMin())
		{
			CalcAndSetQuantity(action_data);
			OnCompletePogress(action_data);
			return UA_FINISHED;
		}
		
		m_SpentQuantity += m_QuantityUsedPerSecond * action_data.m_Player.GetDeltaT();
		m_TimeElpased += action_data.m_Player.GetDeltaT();
		if (m_TimeElpased >= m_DefaultTimeStep)
		{
			CalcAndSetQuantity(action_data);
			m_TimeElpased = 0;
		}
		
		return UA_PROCESSING;
	}
	
	override int Cancel(ActionData action_data)
	{
		if (!action_data.m_Player || !action_data.m_Target || !action_data.m_Target.GetObject())
		{
			return UA_ERROR;
		}
		
		CalcAndSetQuantity(action_data);
		return UA_CANCEL;
	}	
	
	override float GetProgress()
	{
		return m_SpentQuantity_total / m_ItemMaxQuantity;
	}
	
	void CalcAndSetQuantity(ActionData action_data)
	{
		EntityAI targetEntity = EntityAI.Cast(action_data.m_Target.GetObject());
		m_SpentQuantity_total += m_SpentQuantity;
		
		if (GetGame().IsServer())
		{
			if (m_SpentUnits)
			{
				m_SpentUnits.param1 = m_SpentQuantity;
				SetACData(m_SpentUnits);
			}
			
			if (action_data.m_MainItem)
			{
				action_data.m_MainItem.AddQuantity(-m_SpentQuantity);
			}
			
			if (targetEntity)
			{
				float cleanupForce = ActionWashRadioactiveItems.GetTerjeRadiationCleanupForce(action_data.m_MainItem);
				GetTerjeScriptableAreas().AddTerjeRadiationToEntity(targetEntity, -1 * cleanupForce * m_TimeElpased);
				targetEntity.AddWet(targetEntity.GetWetMax() * 0.1);
			}
		}
		
		m_SpentQuantity = 0;
	}
};

class ActionWashRadioactiveItemsCB : ActionContinuousBaseCB
{
	private const float TIME_TO_REPEAT = 0.25;
	
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousWashRadioactiveItems(UAQuantityConsumed.DRAIN_LIQUID, TIME_TO_REPEAT);
	}
};

class ActionWashRadioactiveItems: ActionContinuousBase
{
	void ActionWashRadioactiveItems()
	{
		m_CallbackClass = ActionWashRadioactiveItemsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_EMPTY_VESSEL;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_EMPTY_VESSEL;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_Text = "#STR_TERJEMED_WASH_RADIATION";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
	}
	
	override bool HasProneException()
	{
		return true;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		EntityAI targetEntity = EntityAI.Cast(target.GetObject());
		if ( targetEntity && item && !targetEntity.IsMan() )
		{
			if (item.IsLiquidContainer() && item.GetQuantity() > item.GetQuantityMin())
			{
				if (GetTerjeRadiationCleanupForce(item) > 0 && GetTerjeScriptableAreas().IsTerjeRadiationSupportedForEntity(targetEntity))
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	
	override void OnStartAnimationLoop( ActionData action_data )
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsServer() )
		{
			Bottle_Base vesselInHands = Bottle_Base.Cast( action_data.m_MainItem );
			Param1<bool> play = new Param1<bool>( true );

			GetGame().RPCSingleParam( vesselInHands, SoundTypeBottle.EMPTYING, play, true );
		}
	}
	
	override void OnEndAnimationLoop( ActionData action_data )
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsServer() )
		{
			Bottle_Base vesselInHands = Bottle_Base.Cast( action_data.m_MainItem );
			Param1<bool> play = new Param1<bool>( false );
			GetGame().RPCSingleParam( vesselInHands, SoundTypeBottle.EMPTYING, play, true );
		}
	}
	
	override void OnEnd( ActionData action_data )
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsServer() )
		{
			Bottle_Base vesselInHands = Bottle_Base.Cast( action_data.m_MainItem );
			Param1<bool> play = new Param1<bool>( false );
			GetGame().RPCSingleParam( vesselInHands, SoundTypeBottle.EMPTYING, play, true );
		}
	}
	
	static float GetTerjeRadiationCleanupForce(ItemBase item)
	{
		string liquidClass = item.GetTerjeLiquidClassname();
		if (liquidClass != "")
		{
			return GetGame().ConfigGetFloat("CfgTerjeCustomLiquids " + liquidClass + " terjeRadiationCleanupForce");
		}
		else if (item.GetLiquidType() != LIQUID_NONE)
		{
			liquidClass = Liquid.GetLiquidClassname(item.GetLiquidType());
			if (liquidClass != "")
			{
				return GetGame().ConfigGetFloat("cfgLiquidDefinitions " + liquidClass + " terjeRadiationCleanupForce");
			}
		}
		
		return 0;
	}
};