// <copyright file="TerjePlayerHealthAccessor.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerHealthAccessor
{
	protected PlayerBase m_Player;
	protected ref TerjeDamageSource m_LastHealthDamageSource;
	protected ref TerjeDamageSource m_LastBloodDamageSource;
	protected ref TerjeDamageSource m_LastShockDamageSource;
	
	void TerjePlayerHealthAccessor(PlayerBase player)
	{
		m_Player = player;
		m_LastHealthDamageSource = null;
		m_LastBloodDamageSource = null;
		m_LastShockDamageSource = null;
	}
	
	// HEALTH
	float GetHealth()
	{
		if (m_Player)
		{
			return m_Player.GetHealth("GlobalHealth", "Health");
		}
		
		return 0;
	}
	
	float GetHealth01()
	{
		if (m_Player)
		{
			return m_Player.GetHealth01("GlobalHealth", "Health");
		}
		
		return 0;
	}
	
	void AddHealth(float value)
	{
		if (m_Player && (value > 0))
		{
			m_Player.AddHealth("GlobalHealth", "Health", value);
		}
	}
	
	void SetHealth(float value, TerjeDamageSource dmgSource)
	{
		if (m_Player && m_Player.GetAllowDamage())
		{
			if (dmgSource != null)
			{
				m_LastHealthDamageSource = dmgSource;
			}
			
			m_Player.SetHealth("GlobalHealth", "Health", value);
		}
	}
	
	void DecreaseHealth(float value, TerjeDamageSource dmgSource)
	{
		if (m_Player && m_Player.GetAllowDamage() && (value > 0))
		{
			if (dmgSource != null)
			{
				m_LastHealthDamageSource = dmgSource;
			}
			
			m_Player.DecreaseHealth("GlobalHealth", "Health", value);
		}
	}
	
	TerjeDamageSource GetLastHealthDamageSource()
	{
		return m_LastHealthDamageSource;
	}
	
	// BLOOD
	float GetBlood()
	{
		if (m_Player)
		{
			return m_Player.GetHealth("GlobalHealth", "Blood");
		}
		
		return 0;
	}
	
	float GetBlood01()
	{
		if (m_Player)
		{
			return m_Player.GetHealth01("GlobalHealth", "Blood");
		}
		
		return 0;
	}
	
	void AddBlood(float value)
	{
		if (m_Player && (value > 0))
		{
			m_Player.AddHealth("GlobalHealth", "Blood", value);
		}
	}
	
	void SetBlood(float value, TerjeDamageSource dmgSource)
	{
		if (m_Player && m_Player.GetAllowDamage())
		{
			if (dmgSource != null)
			{
				m_LastBloodDamageSource = dmgSource;
			}
			
			m_Player.SetHealth("GlobalHealth", "Blood", value);
		}
	}
	
	void DecreaseBlood(float value, TerjeDamageSource dmgSource)
	{
		if (m_Player && m_Player.GetAllowDamage() && (value > 0))
		{
			if (dmgSource != null)
			{
				m_LastBloodDamageSource = dmgSource;
			}
			
			m_Player.DecreaseHealth("GlobalHealth", "Blood", value);
		}
	}
	
	TerjeDamageSource GetLastBloodDamageSource()
	{
		return m_LastBloodDamageSource;
	}
	
	// SHOCK
	float GetShock()
	{
		if (m_Player)
		{
			return m_Player.GetHealth("", "Shock");
		}
		
		return 0;
	}
	
	float GetShock01()
	{
		if (m_Player)
		{
			return m_Player.GetHealth01("", "Shock");
		}
		
		return 0;
	}
	
	void AddShock(float value)
	{
		if (m_Player && (value > 0))
		{
			m_Player.AddHealth("", "Shock", value);
		}
	}
	
	void SetShock(float value, TerjeDamageSource dmgSource)
	{
		if (m_Player && m_Player.GetAllowDamage())
		{
			if (dmgSource != null)
			{
				m_LastShockDamageSource = dmgSource;
			}
			
			m_Player.SetHealth("", "Shock", value);
		}
	}
	
	void DecreaseShock(float value, TerjeDamageSource dmgSource)
	{
		if (m_Player && m_Player.GetAllowDamage() && (value > 0))
		{
			if (dmgSource != null)
			{
				m_LastShockDamageSource = dmgSource;
			}
			
			m_Player.DecreaseHealth("", "Shock", value);
		}
	}
	
	TerjeDamageSource GetLastShockDamageSource()
	{
		return m_LastShockDamageSource;
	}
}