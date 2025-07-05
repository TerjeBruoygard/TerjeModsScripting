// <copyright file="TerjePlayerConditionTimeout.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditionTimeout : TerjePlayerConditionBase
{
	override bool Validate(PlayerBase player, TerjeXmlObject condition)
	{
		string id;
		if (condition.FindAttribute("id", id) && (id != string.Empty))
		{
			PluginTerjeServertime serverTimePlugin = GetTerjeServertime();
			if (player && (player.GetTerjeProfile() != null) && (serverTimePlugin != null))
			{
				int playerTimestamp;
				if (player.GetTerjeProfile().GetExpirableTimestamp("@" + id, playerTimestamp))
				{
					return playerTimestamp < serverTimePlugin.GetTimestamp();
				}
				else
				{
					return true;
				}
			}
		}
		else
		{
			TerjeLog_Warning("Attribute 'id' is required for 'Timeout' condition.");
		}
		
		return false;
	}
	
	override void Apply(PlayerBase player, TerjeXmlObject condition)
	{
		string id;
		if (condition.FindAttribute("id", id) && (id != string.Empty))
		{
			PluginTerjeServertime serverTimePlugin = GetTerjeServertime();
			if (player && (player.GetTerjeProfile() != null) && (serverTimePlugin != null))
			{
				int timespan = TerjeMathHelper.ParseTimespanFromXml(condition);
				int timestamp = serverTimePlugin.GetTimestamp();
				player.GetTerjeProfile().SetExpirableTimestamp("@" + id, timestamp + timespan);
			}
		}
	}
	
	override string GetText(PlayerBase player, TerjeXmlObject condition)
	{
		string id;
		string timeoutStr = string.Empty;
		if (condition.FindAttribute("id", id) && (id != string.Empty))
		{
			PluginTerjeServertime serverTimePlugin = GetTerjeServertime();
			if (player && (player.GetTerjeProfile() != null) && (serverTimePlugin != null))
			{
				int playerTimestamp;
				if (player.GetTerjeProfile().GetExpirableTimestamp("@" + id, playerTimestamp))
				{
					int timeout = playerTimestamp - serverTimePlugin.GetTimestamp();
					timeoutStr = TerjeStringHelper.SecondsToHM(timeout);
					if (timeoutStr != string.Empty)
					{
						return "#STR_TERJECORE_COND_TM " + timeoutStr;
					}
				}
			}
		}
		
		timeoutStr = TerjeStringHelper.SecondsToHM(TerjeMathHelper.ParseTimespanFromXml(condition));
		if (timeoutStr != string.Empty)
		{
			return "#STR_TERJECORE_COND_TM2 " + timeoutStr;
		}
		
		return string.Empty;
	}
}