// <copyright file="MissionGameplay.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class MissionGameplay
{
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		UIScriptedMenu currentMenu = GetGame().GetUIManager().GetMenu();
		if (currentMenu)
		{
			if (currentMenu.IsInherited(TerjeModalDialog))
			{
				currentMenu.OnKeyPress(null, 0, 0, key);
			}
		}
	}
};