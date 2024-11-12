// <copyright file="StaminaHandler.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class StaminaConsumers
{
	private float m_terjeMaxStaminaModifier = 1.0;
	
	void SetTerjeMaxStaminaModifier(float value)
	{
		m_terjeMaxStaminaModifier = value;
	}
	
	override bool HasEnoughStaminaFor(EStaminaConsumers consumer, float curStamina, bool isDepleted, float cap)
	{
		return super.HasEnoughStaminaFor(consumer, curStamina * m_terjeMaxStaminaModifier, isDepleted, cap * m_terjeMaxStaminaModifier);
	}
	
	override bool HasEnoughStaminaToStart(EStaminaConsumers consumer, float curStamina, bool isDepleted, float cap)
	{
		return super.HasEnoughStaminaToStart(consumer, curStamina * m_terjeMaxStaminaModifier, isDepleted, cap * m_terjeMaxStaminaModifier);
	}
};

modded class StaminaModifier
{
	private float m_terjeModifier = 1.0;
	
	void SetTerjeModifier(float value)
	{
		m_terjeModifier = Math.Clamp(1.0 + value, 0.0, 1.0);
	}
	
	override float GetMinValue()
	{
		return super.GetMinValue() * m_terjeModifier;
	}
	
	override float GetMaxValue()
	{
		return super.GetMaxValue() * m_terjeModifier;
	}
};

modded class StaminaHandler
{
	private float m_terjeMaxStaminaModifier = 1.0;
	private float m_terjeUpdateTimer = 10.0;
	
	override void Update(float deltaT, int pCurrentCommandID)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
		super.Update(deltaT, pCurrentCommandID);
	}
	
	override void SetDepletionMultiplier(float val)
	{
		super.SetDepletionMultiplier(val / m_terjeMaxStaminaModifier);
	}

	override void SetRecoveryMultiplier(float val)
	{
		super.SetRecoveryMultiplier(val / m_terjeMaxStaminaModifier);
	}
	
	override protected void StaminaProcessor_Move(HumanMovementState pHumanMovementState)
	{
		super.StaminaProcessor_Move(pHumanMovementState);
		
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (pHumanMovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT)
			{
				if (m_StaminaDelta < 0 && m_Player.GetTerjeSkills().GetPerkValue("athlc", "quickf", perkValue))
				{
					m_StaminaDelta = m_StaminaDelta * Math.Clamp(1.0 + perkValue, 0.0, 1.0);
				}
			}
			else if (pHumanMovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_RUN || pHumanMovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_WALK)
			{
				if (m_StaminaDelta > 0 && m_Player.GetTerjeSkills().GetPerkValue("athlc", "marathon", perkValue))
				{
					m_StaminaDelta = m_StaminaDelta * Math.Max(1.0 + perkValue, 1.0);
				}
			}
			else if (pHumanMovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_IDLE)
			{
				if (m_StaminaDelta > 0 && m_Player.GetTerjeSkills().GetPerkValue("athlc", "pbreath", perkValue))
				{
					m_StaminaDelta = m_StaminaDelta * Math.Max(1.0 + perkValue, 1.0);
				}
			}		
		}
	}
	
	override protected void StaminaProcessor_Ladder(HumanMovementState pHumanMovementState)
	{
		super.StaminaProcessor_Ladder(pHumanMovementState);
		
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("athlc", "ladder", perkValue))
			{
				if (m_StaminaDelta < 0)
				{
					m_StaminaDelta = m_StaminaDelta * Math.Clamp(1.0 - perkValue, 0.0, 1.0);
				}
				else if (m_StaminaDelta > 0)
				{
					m_StaminaDelta = m_StaminaDelta * Math.Max(1.0 + perkValue, 1.0);
				}
			}
		}
	}
	
	override protected void StaminaProcessor_Swimming(HumanMovementState pHumanMovementState)
	{
		super.StaminaProcessor_Swimming(pHumanMovementState);
		
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("athlc", "swimmer", perkValue))
			{
				if (m_StaminaDelta < 0)
				{
					m_StaminaDelta = m_StaminaDelta * Math.Clamp(1.0 - perkValue, 0.0, 1.0);
				}
				else if (m_StaminaDelta > 0)
				{
					m_StaminaDelta = m_StaminaDelta * Math.Max(1.0 + perkValue, 1.0);
				}
			}
		}
	}
	
	override protected void SetCooldown(float time, int modifier = -1)
	{
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("athlc", "npant", perkValue))
			{
				time = time * Math.Clamp(1.0 + perkValue, 0.0, 1.0);
			}
		}
		
		super.SetCooldown(time, modifier);	
	}
};