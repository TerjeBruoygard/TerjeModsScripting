// <copyright file="ActionTargetsCursor.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionTargetsCursor
{
	override string GetItemDesc(ActionBase action)
	{
		int nameDisplayMode = -1;
		if (GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_DISPLAY_PLAYER_NAMES_MODE, nameDisplayMode) && (nameDisplayMode >= 0))
		{
			Object tgObject = m_DisplayInteractTarget;
			if (!tgObject && m_Target)
			{
				tgObject = m_Target.GetObject();
			}
			
			PlayerBase tgPlayer = PlayerBase.Cast(tgObject);
			if (tgPlayer)
			{
				string characterName = tgPlayer.GetTerjeCharacterName();
				if (characterName != string.Empty)
				{
					if (nameDisplayMode == 0)
					{
						return characterName;
					}
					else if (nameDisplayMode == 1)
					{
						if (!tgPlayer.IsAlive())
						{
							return characterName;
						}
					}
					else if (nameDisplayMode == 2)
					{
						if (tgPlayer.GetTerjeFaceVisible())
						{
							return characterName;
						}
					}
					else if (nameDisplayMode == 3)
					{
						if ((!tgPlayer.IsAlive()) && (tgPlayer.GetTerjeFaceVisible()))
						{
							return characterName;
						}
					}
				}
			}
		}
		
		return super.GetItemDesc(action);;
	}
}