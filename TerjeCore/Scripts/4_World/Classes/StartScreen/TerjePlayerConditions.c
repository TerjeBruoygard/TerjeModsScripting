// <copyright file="TerjePlayerConditions.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditions
{
	bool ProcessCondition(PlayerBase player, TerjeXmlObject condition)
	{
		string attrValue;
		if (condition.GetName() == "Fail")
		{
			return false;
		}
		else if (condition.GetName() == "SpecificPlayers")
		{
			if (player && player.GetIdentity())
			{
				string playerSteamId = player.GetIdentity().GetId();
				string playerPlainId = player.GetIdentity().GetPlainId();
				for (int specificPlayerId = 0; specificPlayerId < condition.GetChildrenCount(); specificPlayerId++)
				{
					TerjeXmlObject specificPlayerNode = condition.GetChild(specificPlayerId);
					if (specificPlayerNode.IsObjectNode() && (specificPlayerNode.GetName() == "SpecificPlayer"))
					{
						string steamGUID;
						if (specificPlayerNode.FindAttribute("steamGUID", steamGUID))
						{
							if ((playerSteamId == steamGUID) || (playerPlainId == steamGUID))
							{
								return true;
							}
						}
					}
				}
			}
		}
		else if (condition.GetName() == "Timeout")
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
		}
		else if (condition.GetName() == "CustomCondition")
		{
			string classname;
			if (condition.FindAttribute("classname", classname) && (classname != string.Empty))
			{
				typename type = classname.ToType();
				if (type && type.IsInherited(TerjeCustomConditionHandler))
				{
					TerjeCustomConditionHandler customCondition = TerjeCustomConditionHandler.Cast(type.Spawn());
					if (customCondition != null)
					{
						return customCondition.CheckCondition(player, condition);
					}
				}
				else
				{
					TerjeLog_Warning("Class '" + classname + "' not found or not inherited TerjeCustomConditionHandler.");
				}
			}
			else
			{
				TerjeLog_Warning("Attribute 'classname' is required for 'CustomCondition'.");
			}
		}
		
		return false;
	}
	
	void ApplyCondition(PlayerBase player, TerjeXmlObject condition)
	{
		if (condition.GetName() == "Timeout")
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
		else if (condition.GetName() == "CustomCondition")
		{
			string classname;
			if (condition.FindAttribute("classname", classname) && (classname != string.Empty))
			{
				typename type = classname.ToType();
				if (type && type.IsInherited(TerjeCustomConditionHandler))
				{
					TerjeCustomConditionHandler customCondition = TerjeCustomConditionHandler.Cast(type.Spawn());
					if (customCondition != null)
					{
						customCondition.ApplyCondition(player, condition);
					}
				}
			}
		}
	}
	
	void SanitizeCondition(PlayerBase player, TerjeXmlObject condition)
	{
		if (condition.GetName() == "SpecificPlayers")
		{
			// Hide steam GUIDs before send to client
			condition.ClearChildren();
		}
		else if (condition.GetName() == "Timeout")
		{
			// Set actual timer to display on client
			string id;
			if (condition.FindAttribute("id", id) && (id != string.Empty))
			{
				PluginTerjeServertime serverTimePlugin = GetTerjeServertime();
				if (player && (player.GetTerjeProfile() != null) && (serverTimePlugin != null))
				{
					int playerTimestamp;
					if (player.GetTerjeProfile().GetExpirableTimestamp("@" + id, playerTimestamp))
					{
						int timeout = playerTimestamp - serverTimePlugin.GetTimestamp();
						condition.SetAttribute("$timeout", timeout.ToString());
					}
				}
			}
		}
		else if (condition.GetName() == "CustomCondition")
		{
			string classname;
			if (condition.FindAttribute("classname", classname) && (classname != string.Empty))
			{
				typename type = classname.ToType();
				if (type && type.IsInherited(TerjeCustomConditionHandler))
				{
					TerjeCustomConditionHandler customCondition = TerjeCustomConditionHandler.Cast(type.Spawn());
					if (customCondition != null)
					{
						condition.SetAttribute("$client_text", customCondition.GetConditionText(player, condition));
					}
				}
			}
		}
	}
	
	string StringifyCondition(TerjeXmlObject condition)
	{
		if (condition.GetName() == "Fail")
		{
			string message;
			if (!condition.FindAttribute("message", message))
			{
				message = "CONDITION FAILED";
			}
			
			return message;
		}
		else if (condition.GetName() == "SpecificPlayers")
		{
			return "#STR_TERJECORE_COND_SP";
		}
		else if (condition.GetName() == "Timeout")
		{
			string timeoutStr;
			if (condition.FindAttribute("$timeout", timeoutStr))
			{
				timeoutStr = TerjeStringHelper.SecondsToHM(timeoutStr.ToInt());
				if (timeoutStr != string.Empty)
				{
					return string.Format(Widget.TranslateString("#STR_TERJECORE_COND_TM"), timeoutStr);
				}
			}
			
			timeoutStr = TerjeStringHelper.SecondsToHM(TerjeMathHelper.ParseTimespanFromXml(condition));
			if (timeoutStr != string.Empty)
			{
				return "#STR_TERJECORE_COND_TM2 " + timeoutStr;
			}
			
			return string.Empty;
		}
		else if (condition.GetName() == "CustomCondition")
		{
			string clientText;
			if (condition.FindAttribute("$client_text", clientText))
			{
				return clientText;
			}
		}
		
		return "Unknown condition '" + condition.GetName() + "'";
	}
}