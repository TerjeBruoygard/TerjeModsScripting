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
	
	void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
	
	}
	
	float GetPlayerImmunity(PlayerBase player)
	{
		return 0;
	}
	
	float GetPlayerHealth(PlayerBase player)
	{
		return player.GetTerjeHealth().GetHealth();
	}
	
	float GetPlayerHealth01(PlayerBase player)
	{
		return player.GetTerjeHealth().GetHealth01();
	}
	
	void AddPlayerHealth(PlayerBase player, float value)
	{
		player.GetTerjeHealth().AddHealth(value);
	}
	
	void SetPlayerHealth(PlayerBase player, TerjeDamageSource dmgSource, float value)
	{
		player.GetTerjeHealth().SetHealth(value, dmgSource);
	}
	
	void DecreasePlayerHealth(PlayerBase player, TerjeDamageSource dmgSource, float value)
	{
		player.GetTerjeHealth().DecreaseHealth(value, dmgSource);
	}
	
	
	float GetPlayerBlood(PlayerBase player)
	{
		return player.GetTerjeHealth().GetBlood();
	}
	
	float GetPlayerBlood01(PlayerBase player)
	{
		return player.GetTerjeHealth().GetBlood01();
	}
	
	void AddPlayerBlood(PlayerBase player, float value)
	{
		player.GetTerjeHealth().AddBlood(value);
	}
	
	void SetPlayerBlood(PlayerBase player, TerjeDamageSource dmgSource, float value)
	{
		player.GetTerjeHealth().SetBlood(value, dmgSource);
	}
	
	void DecreasePlayerBlood(PlayerBase player, TerjeDamageSource dmgSource, float value)
	{
		player.GetTerjeHealth().DecreaseBlood(value, dmgSource);
	}
	
	
	float GetPlayerShock(PlayerBase player)
	{
		return player.GetTerjeHealth().GetShock();
	}
	
	float GetPlayerShock01(PlayerBase player)
	{
		return player.GetTerjeHealth().GetShock01();
	}
	
	void AddPlayerShock(PlayerBase player, float value)
	{
		player.GetTerjeHealth().AddShock(value);
	}
	
	void SetPlayerShock(PlayerBase player, TerjeDamageSource dmgSource, float value)
	{
		player.GetTerjeHealth().SetShock(value, dmgSource);
	}
	
	void DecreasePlayerShock(PlayerBase player, TerjeDamageSource dmgSource, float value)
	{
		player.GetTerjeHealth().DecreaseShock(value, dmgSource);
	}
}