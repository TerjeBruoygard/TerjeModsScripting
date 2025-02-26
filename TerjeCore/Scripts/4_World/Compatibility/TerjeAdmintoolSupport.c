// <copyright file="TerjeAdmintoolSupport.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

ref TerjeAdmintoolSupport GetTerjeAdmintoolSupport()
{
	return TerjeAdmintoolSupport.GetInstance();
}

class TerjeAdmintoolSupport
{
	private static ref TerjeAdmintoolSupport m_instance = null;
	private ref map<string, ref TerjeAdmintoolSupport_PlayerStat> m_playerStats = new map<string, ref TerjeAdmintoolSupport_PlayerStat>;
	private ref array<ref TerjeAdmintoolSupport_PlayerStat> m_orderedPlayerStats = new array<ref TerjeAdmintoolSupport_PlayerStat>;
	
	static ref TerjeAdmintoolSupport GetInstance()
	{
		if (m_instance == null)
		{
			m_instance = new TerjeAdmintoolSupport();
			m_instance.OnInit();
		}
		
		return m_instance;
	}
	
	void OnInit()
	{
	
	}
	
	void OnHeal(PlayerBase player)
	{
	
	}
	
	protected void RegisterPlayerStat(TerjeAdmintoolSupport_PlayerStat stat)
	{
		if (stat == null)
		{
			return;
		}
		
		if (m_playerStats.Contains(stat.GetId()))
		{
			return;
		}
		
		m_playerStats.Insert(stat.GetId(), stat);
		m_orderedPlayerStats.Insert(stat);
	}
	
	void GetPlayerStats(array<ref TerjeAdmintoolSupport_PlayerStat> result)
	{
		foreach (ref TerjeAdmintoolSupport_PlayerStat stats : m_orderedPlayerStats)
		{
			result.Insert(stats);
		}
	}
	
	bool FindPlayerStat(string id, out TerjeAdmintoolSupport_PlayerStat result)
	{
		return m_playerStats.Find(id, result);
	}
}

class TerjeAdmintoolSupport_PlayerStat
{
	private string m_Id;
	private string m_Name;
	private string m_Icon;
	private float m_Min;
	private float m_Max;
	
	void TerjeAdmintoolSupport_PlayerStat(string id, string name, string icon, float min, float max)
	{
		m_Id = id;
		m_Name = name;
		m_Icon = icon;
		m_Min = min;
		m_Max = max;
	}
	
	string GetId()
	{
		return m_Id;
	}
	
	string GetName()
	{
		return m_Name;
	}
	
	string GetIcon()
	{
		return m_Icon;
	}
	
	float GetMin()
	{
		return m_Min;
	}
	
	float GetMax()
	{
		return m_Max;
	}
	
	float GetValue(PlayerBase player) {}
	void SetValue(PlayerBase player, float value) {}
}