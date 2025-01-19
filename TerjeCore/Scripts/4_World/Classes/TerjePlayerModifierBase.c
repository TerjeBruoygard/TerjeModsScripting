// <copyright file="TerjePlayerModifierBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierBase
{
	private float m_Timer = 0;
	
	float GetTimeout()
	{
		return 1;
	}
	
	void CallServerTimerIncrement(float deltaTime)
	{
		m_Timer = m_Timer + deltaTime;
	}
	
	void CallServerTick(PlayerBase player)
	{
		if (m_Timer >= GetTimeout())
		{
			OnServerFixedTick(player, m_Timer);
			m_Timer = 0;
		}
	}
	
	void OnServerFixedTick(PlayerBase player, float deltaTime) {}
}