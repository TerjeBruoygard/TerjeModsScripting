// <copyright file="TerjePlayerInspectableStats.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerInspectableStats
{
	private int m_Count;
	private ref array<string> m_Titles;
	private ref array<string> m_Icons;
	private ref array<string> m_Descriptions;
	
	void TerjePlayerInspectableStats(PlayerBase player, int level)
	{
		m_Count = 0;
		m_Titles = new array<string>;
		m_Icons = new array<string>;
		m_Descriptions = new array<string>;
		OnInit(player, level);
	}
	
	void OnInit(PlayerBase player, int level)
	{
		if (player && player.IsAlive())
		{
			float playerHealth = player.GetHealth("GlobalHealth", "Health");
			if (playerHealth < PlayerConstants.SL_HEALTH_CRITICAL)
			{
				AddInspectableStat("#STR_TERJECORE_PIS_HEALTH", "set:dayz_gui image:iconHealth4", "#STR_TERJECORE_PIS_HEALTH_CRIT");
			}
			else if (playerHealth < PlayerConstants.SL_HEALTH_LOW)
			{
				AddInspectableStat("#STR_TERJECORE_PIS_HEALTH", "set:dayz_gui image:iconHealth3", "#STR_TERJECORE_PIS_HEALTH_LOW");
			}
			else if (playerHealth < PlayerConstants.SL_HEALTH_NORMAL)
			{
				AddInspectableStat("#STR_TERJECORE_PIS_HEALTH", "set:dayz_gui image:iconHealth2", "#STR_TERJECORE_PIS_HEALTH_WARN");
			}
			
			float playerBlood = player.GetHealth("GlobalHealth", "Blood");
			if (playerBlood < PlayerConstants.SL_BLOOD_CRITICAL)
			{
				AddInspectableStat("#STR_TERJECORE_PIS_BLOOD", "set:dayz_gui image:iconBlood4", "#STR_TERJECORE_PIS_BLOOD_CRIT");
			}
			else if (playerBlood < PlayerConstants.SL_BLOOD_LOW)
			{
				AddInspectableStat("#STR_TERJECORE_PIS_BLOOD", "set:dayz_gui image:iconBlood3", "#STR_TERJECORE_PIS_BLOOD_LOW");
			}
			else if (playerBlood < PlayerConstants.SL_BLOOD_NORMAL)
			{
				AddInspectableStat("#STR_TERJECORE_PIS_BLOOD", "set:dayz_gui image:iconBlood2", "#STR_TERJECORE_PIS_BLOOD_WARN");
			}
			
			if (player.GetBrokenLegs() != eBrokenLegs.NO_BROKEN_LEGS)
			{
				AddInspectableStat("#STR_TERJECORE_PIS_BBONES", "set:dayz_gui image:iconBone", "#STR_TERJECORE_PIS_BBONES_LEGS");
			}
		}
	}
	
	int GetCount()
	{
		return m_Count;
	}
	
	bool GetStat(int index, out string title, out string icon, out string desc)
	{
		if (index >= 0 && index < m_Titles.Count() && index < m_Icons.Count() && index < m_Descriptions.Count())
		{
			title = m_Titles.Get(index);
			icon = m_Icons.Get(index);
			desc = m_Descriptions.Get(index);
			return true;
		}
		
		title = "";
		icon = "";
		desc = "";
		return false;
	}
	
	protected void AddInspectableStat(string title, string icon, string desc)
	{
		m_Titles.Insert(title);
		m_Icons.Insert(icon);
		m_Descriptions.Insert(desc);
		m_Count++;
	}
}