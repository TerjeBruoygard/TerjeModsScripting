// <copyright file="ActionUseTerjeSleepingBag.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class ActionUseTerjeSleepingBag : ActionInteractBase
{
	void ActionUseTerjeSleepingBag()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "#use";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		bool isActionEnabled;
		TerjeSleepingBag sleepingBag = TerjeSleepingBag.Cast(target.GetObject());
		if (GetGame() && sleepingBag && sleepingBag.CanBePacked())
		{
			if (vector.Distance(player.GetWorldPosition(), sleepingBag.GetWorldPosition()) < 0.65)
			{
				if (player && !player.IsInVehicle() && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_SLEEPINGBAG_ACTION, isActionEnabled) && isActionEnabled)
				{
					if (GetGame().IsDedicatedServer())
					{
						return true;
					}
					
					if (player.GetEmoteManager() && player.GetEmoteManager().CanPlayEmote(EmoteConstants.ID_EMOTE_LYINGDOWN))
					{
						return true;
					}
				}
			}
		}
		
		return false;
	}

	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		TeleportOnSleepingBag(action_data);
	}
	
	override void OnEndClient(ActionData action_data)
	{
		super.OnEndClient(action_data);
		TeleportOnSleepingBag(action_data);
		action_data.m_Player.GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_LYINGDOWN);
	}
	
	private void TeleportOnSleepingBag(ActionData action_data)
	{
		PlayerBase player = action_data.m_Player;
		TerjeSleepingBag sleepingBag = TerjeSleepingBag.Cast(action_data.m_Target.GetObject());
		if (sleepingBag && player)
		{
			player.SetPosition(sleepingBag.ModelToWorld(Vector(0.38, 0.0, 0.16)));
			
			vector playerRotation = player.GetOrientation();
			vector bagRotation = sleepingBag.GetOrientation();
			
			playerRotation[0] = bagRotation[0];
			player.SetOrientation(playerRotation);
		}
	}
}