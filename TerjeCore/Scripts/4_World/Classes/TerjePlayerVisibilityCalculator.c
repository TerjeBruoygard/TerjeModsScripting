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
		switch (hms.m_iMovement)
		{
			case DayZPlayerConstants.MOVEMENTIDX_SPRINT:
				return 2.5;
			case DayZPlayerConstants.MOVEMENTIDX_WALK:
				return 0.75;
			case DayZPlayerConstants.MOVEMENTIDX_IDLE:
				return 0.50;
		}
		
		return 1.0;
	}
	
	float GetMovementStanceVisualCoef(PlayerBase player)
	{
		HumanMovementState hms = new HumanMovementState();
		player.GetMovementState(hms);
		switch (hms.m_iStanceIdx)
		{
			case DayZPlayerConstants.STANCEIDX_CROUCH:
			case DayZPlayerConstants.STANCEIDX_RAISEDCROUCH:
				return 0.75;
				
			case DayZPlayerConstants.STANCEIDX_PRONE:
			case DayZPlayerConstants.STANCEIDX_RAISEDPRONE:
				return 0.50;
		}
		
		return 1.0;
	}

}