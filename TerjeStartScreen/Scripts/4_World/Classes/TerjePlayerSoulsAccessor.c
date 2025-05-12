// <copyright file="TerjePlayerSoulsAccessor.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjePlayerSoulsAccessor
{
	const string SOULS_ICON = "set:TerjeStartScreen_icons image:tss_soul";
	const string SOULS_BADGE = "set:TerjeStartScreen_icons image:tss_soul_badge";
	
	override bool IsEnabled()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_SOULS_ENABLED);
	}
	
	override int GetCount()
	{
		int result = 0;
		if (m_Player && (m_Player.GetIdentity() != null) && (m_Player.GetTerjeProfile() != null))
		{
			result = m_Player.GetTerjeProfile().GetSoulsCount();
		}
		
		return result;
	}
	
	override void SetCount(int count, bool showNotification = true)
	{
		if (IsLocked())
		{
			return;
		}
		
		if (GetGame() && GetGame().IsDedicatedServer() && IsEnabled())
		{
			if (m_Player && (m_Player.GetIdentity() != null) && (m_Player.GetTerjeProfile() != null))
			{
				int newSouls = TerjeMathHelper.ClampInt(count, 0, TerjeStartScreenConstants.SOULS_MAX_LIMIT);
				int oldSouls = m_Player.GetTerjeProfile().GetSoulsCount();
				if (oldSouls != newSouls)
				{
					m_Player.GetTerjeProfile().SetSoulsCount(newSouls);
					
					if (showNotification && GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_SOULS_NOTIFY))
					{
						string title = "#STR_TERJESTARTSCREEN_SOUL_TITLE";
						string message = "#STR_TERJESTARTSCREEN_SOUL_ADD " + newSouls;
						if (newSouls < oldSouls)
						{
							message = "#STR_TERJESTARTSCREEN_SOUL_REM " + newSouls;
						}
						
						if (newSouls == 0)
						{
							message = message + "<br/>#STR_TERJESTARTSCREEN_SOUL_ZERO";
						}
						
						NotificationSystem.SendNotificationToPlayerIdentityExtended(m_Player.GetIdentity(), 8, title, message, SOULS_ICON);
					}
				}
			}
		}
	}
	
	override void AddCount(int count, bool showNotification = true)
	{
		SetCount(GetCount() + count, showNotification);
	}
}