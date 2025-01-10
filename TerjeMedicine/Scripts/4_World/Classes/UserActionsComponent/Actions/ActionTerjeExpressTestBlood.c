// <copyright file="ActionTerjeExpressTestBlood.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionTerjeExpressTestVirusZSelf : ActionTestBloodSelf
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		if (action_data.m_MainItem)
		{
			string message;
			if (action_data.m_Player && action_data.m_Player.GetTerjeStats() && action_data.m_Player.GetTerjeStats().GetZVirusValue() > 0.01)
			{
				message = "#STR_TERJEMED_POSITIVE";
			}
			else
			{
				message = "#STR_TERJEMED_NEGATIVE";
			}
			
			NotificationSystem.SendNotificationToPlayerExtended(action_data.m_Player, 10, "#STR_TERJEMED_PIS_ZV", message, "set:TerjeMedicine_icon image:tm_virusz");
			action_data.m_MainItem.Delete();
			OnTerjeFinishApplyMedExperience(action_data);
		}
	}
}

class ActionTerjeExpressTestSepsisSelf : ActionTestBloodSelf
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		if (action_data.m_MainItem)
		{
			string message;
			if (action_data.m_Player && action_data.m_Player.GetTerjeStats() && action_data.m_Player.GetTerjeStats().GetSepsisValue() > 0.01)
			{
				message = "#STR_TERJEMED_POSITIVE";
			}
			else
			{
				message = "#STR_TERJEMED_NEGATIVE";
			}
			
			NotificationSystem.SendNotificationToPlayerExtended(action_data.m_Player, 10, "#STR_TERJEMED_PIS_SEPSIS", message, "set:TerjeMedicine_icon image:tm_sepsis");
			action_data.m_MainItem.Delete();
			OnTerjeFinishApplyMedExperience(action_data);
		}
	}
}

class ActionTerjeExpressTestRabiesSelf : ActionTestBloodSelf
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		if (action_data.m_MainItem)
		{
			string message;
			if (action_data.m_Player && action_data.m_Player.GetTerjeStats() && action_data.m_Player.GetTerjeStats().GetRabiesValue() > 0.01)
			{
				message = "#STR_TERJEMED_POSITIVE";
			}
			else
			{
				message = "#STR_TERJEMED_NEGATIVE";
			}
			
			NotificationSystem.SendNotificationToPlayerExtended(action_data.m_Player, 10, "#STR_TERJEMED_PIS_RABIES", message, "set:TerjeMedicine_icon image:tm_rabies");
			action_data.m_MainItem.Delete();
			OnTerjeFinishApplyMedExperience(action_data);
		}
	}
}

class ActionTerjeExpressTestVirusZTarget : ActionTestBloodTarget
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase ntarget = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (action_data.m_MainItem)
		{
			string message = "#STR_TERJEMED_NEGATIVE";
			if (ntarget && ntarget.GetTerjeStats() && ntarget.GetTerjeStats().GetZVirusValue() > 0.01)
			{
				message = "#STR_TERJEMED_POSITIVE";
			}
			else
			{
				message = "#STR_TERJEMED_NEGATIVE";
			}
			
			NotificationSystem.SendNotificationToPlayerExtended(action_data.m_Player, 10, "#STR_TERJEMED_PIS_ZV", message, "set:TerjeMedicine_icon image:tm_virusz");
			action_data.m_MainItem.Delete();
			OnTerjeFinishApplyMedExperience(action_data);
		}
	}
	
	override void OnFinishProgressClient(ActionData action_data)
	{
	}

	override void OnStartServer(ActionData action_data)
	{			
	}
}

class ActionTerjeExpressTestSepsisTarget : ActionTestBloodTarget
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase ntarget = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (action_data.m_MainItem)
		{
			string message;
			if (ntarget && ntarget.GetTerjeStats() && ntarget.GetTerjeStats().GetSepsisValue() > 0.01)
			{
				message = "#STR_TERJEMED_POSITIVE";
			}
			else
			{
				message = "#STR_TERJEMED_NEGATIVE";
			}
			
			NotificationSystem.SendNotificationToPlayerExtended(action_data.m_Player, 10, "#STR_TERJEMED_PIS_SEPSIS", message, "set:TerjeMedicine_icon image:tm_sepsis");
			action_data.m_MainItem.Delete();
			OnTerjeFinishApplyMedExperience(action_data);
		}
	}
	
	override void OnFinishProgressClient(ActionData action_data)
	{
	}

	override void OnStartServer(ActionData action_data)
	{			
	}
}

class ActionTerjeExpressTestRabiesTarget : ActionTestBloodTarget
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase ntarget = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (action_data.m_MainItem)
		{
			string message;
			if (ntarget && ntarget.GetTerjeStats() && ntarget.GetTerjeStats().GetRabiesValue() > 0.01)
			{
				message = "#STR_TERJEMED_POSITIVE";
			}
			else
			{
				message = "#STR_TERJEMED_NEGATIVE";
			}
			
			NotificationSystem.SendNotificationToPlayerExtended(action_data.m_Player, 10, "#STR_TERJEMED_PIS_RABIES", message, "set:TerjeMedicine_icon image:tm_rabies");
			action_data.m_MainItem.Delete();
			OnTerjeFinishApplyMedExperience(action_data);
		}
	}
	
	override void OnFinishProgressClient(ActionData action_data)
	{
	}

	override void OnStartServer(ActionData action_data)
	{			
	}
}