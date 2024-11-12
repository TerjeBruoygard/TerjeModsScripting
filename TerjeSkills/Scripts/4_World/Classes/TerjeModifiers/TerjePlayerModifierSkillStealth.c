// <copyright file="TerjePlayerModifierSkillStealth.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierSkillStealth : TerjePlayerModifierBase
{
	private vector m_skillsCrouchLastPos;
	private float m_distanceCounter = -1;
	
	override float GetTimeout()
	{
		return 3.0;
	};
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		player.UpdateTerjeSkillsStealthBitmask();
		
		if (player.IsInVehicle())
		{
			m_distanceCounter = -1;
			return;
		}
		
		if (m_distanceCounter < 0)
		{
			m_distanceCounter = 0;
			m_skillsCrouchLastPos = player.GetPosition();
		}
		else
		{
			if (player.m_MovementState.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_CROUCH || player.m_MovementState.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_RAISEDCROUCH)
			{
				float currentDistance = vector.Distance(m_skillsCrouchLastPos, player.GetPosition());
				if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT)
				{
					m_distanceCounter += Math.Clamp(currentDistance, 0, 15);
				}
				else if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_RUN)
				{
					m_distanceCounter += Math.Clamp(currentDistance, 0, 10);
				}
				else if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_WALK)
				{
					m_distanceCounter += Math.Clamp(currentDistance, 0, 5);
				}
			}
			else
			{
				m_distanceCounter = 0;
			}
			
			int athleticCheckDistance;
			if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_STEALTH_CHECK_DISTANCE, athleticCheckDistance) && m_distanceCounter > athleticCheckDistance)
			{
				m_distanceCounter = 0;
				
				int stealthExpGain;
				if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_STEALTH_EXP_GAIN, stealthExpGain))
				{
					player.GetTerjeSkills().AddSkillExperience("stlth", stealthExpGain);
				}
			}
			
			m_skillsCrouchLastPos = player.GetPosition();
		}
	}
};
