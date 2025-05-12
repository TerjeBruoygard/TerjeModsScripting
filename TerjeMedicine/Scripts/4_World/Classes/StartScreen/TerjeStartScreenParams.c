// <copyright file="TerjeStartScreenParams.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeStartScreenParams
{
	// Server only
	float m_sleep = -1;
	float m_mind = -1;
	
	override void Build(PlayerBase player)
	{
		super.Build(player);
		
		if (player.GetTerjeStats() != null)
		{
			m_sleep = player.GetTerjeStats().GetSleepingValue();
			m_mind = player.GetTerjeStats().GetMindValue();
		}
	}
	
	override void OnServerTick(PlayerBase player, float deltaTime)
	{
		super.OnServerTick(player, deltaTime);
		
		if (GetGame() && GetGame().IsDedicatedServer() && (player.GetTerjeStats() != null))
		{
			player.GetTerjeStats().SetSleepingValue(m_sleep);
			player.GetTerjeStats().SetMindValue(m_mind);
		}
	}
	
	override void SetPlayerStats(TerjeXmlObject xmlNode)
	{
		super.SetPlayerStats(xmlNode);
		
		string attrValue;
		
		if (xmlNode.FindAttribute("sleep", attrValue))
		{
			m_sleep = attrValue.ToFloat();
		}
		
		if (xmlNode.FindAttribute("mind", attrValue))
		{
			m_mind = attrValue.ToFloat();
		}
	}
	
	override void OnServerDone(PlayerBase player)
	{
		super.OnServerDone(player);
		
		if (player.IsAlive() && (player.GetTerjeStats() != null))
		{
			if (m_sleep > 0)
			{
				player.GetTerjeStats().SetSleepingValue(m_sleep);
			}
			
			if (m_mind > 0)
			{
				player.GetTerjeStats().SetMindValue(m_mind);
			}
		}
	}
}