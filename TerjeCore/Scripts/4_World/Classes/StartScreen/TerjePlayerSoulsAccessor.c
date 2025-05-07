// <copyright file="TerjePlayerSoulsAccessor.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerSoulsAccessor
{
	protected PlayerBase m_Player;
	protected bool m_locked;
	
	void TerjePlayerSoulsAccessor(PlayerBase player)
	{
		m_Player = player;
		m_locked = false;
	}
	
	bool IsLocked()
	{
		return m_locked;
	}
	
	void SetLocked(bool locked)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			m_locked = locked;
		}
	}
	
	bool IsEnabled()
	{
		return false;
	}
	
	int GetCount()
	{
		return 0;
	}
	
	void SetCount(int count, bool showNotification = true)
	{
	
	}
	
	void AddCount(int count, bool showNotification = true)
	{
	
	}
}