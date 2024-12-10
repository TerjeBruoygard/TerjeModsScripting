// <copyright file="TerjePlayerVisibilityCalculator.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

ref TerjePlayerVisibilityCalculator GetTerjePlayerVisibilityCalculator()
{
	return TerjePlayerVisibilityCalculator.GetInstance();
}

class TerjePlayerVisibilityCalculator
{
	private static ref TerjePlayerVisibilityCalculator m_instance = null;
	
	static ref TerjePlayerVisibilityCalculator GetInstance()
	{
		if (m_instance == null)
		{
			m_instance = new TerjePlayerVisibilityCalculator();
			m_instance.OnInit();
		}
		
		return m_instance;
	}
	
	void OnInit()
	{
	
	}
	
	float GetVisualCoef(PlayerBase player)
	{
		return GetMovementSpeedVisualCoef(player) * GetMovementStanceVisualCoef(player);
	}
	
	float GetMovementSpeedVisualCoef(PlayerBase player)
	{
		HumanMovementState hms = new HumanMovementState();
		player.GetMovementState(hms);
		if (hms.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT)
		{
			return 2.5;
		}
		else if (hms.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_WALK)
		{
			return 0.75;
		}
		else if (hms.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_IDLE)
		{
			return 0.50;
		}
		
		return 1.0;
	}
	
	float GetMovementStanceVisualCoef(PlayerBase player)
	{
		HumanMovementState hms = new HumanMovementState();
		player.GetMovementState(hms);
		if (hms.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_CROUCH || hms.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_RAISEDCROUCH)
		{
			return 0.75;
		}
		else if (hms.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_PRONE || hms.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_RAISEDPRONE)
		{
			return 0.50;
		}
		
		return 1.0;
	}

}