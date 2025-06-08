// <copyright file="TerjeCustomPointsHandler.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeCustomPointsHandler
{
	// DEPRECATED, use GetPointsEx instead
	int GetPoints(PlayerBase player, string loadoutId, int selectionId)
	{
		return -1;
	}
	
	int GetPointsEx(PlayerBase player, string loadoutId, int selectionId, TerjeXmlObject selectorRoot)
	{
		return -1;
	}
}