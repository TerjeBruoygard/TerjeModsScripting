// <copyright file="TerjeCustomConditionHandler.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeCustomConditionHandler
{
	// Calls on the server to check condition
	bool CheckCondition(PlayerBase player, TerjeXmlObject condition)
	{
		return false;
	}
	
	// Calls on the server after the player selects loadout, spawn point, etc... with this condition
	void ApplyCondition(PlayerBase player, TerjeXmlObject condition)
	{
	
	}
	
	// Calls on the server to define the condition text that will be displayed to the player in the UI
	string GetConditionText(PlayerBase player, TerjeXmlObject condition)
	{
		return string.Empty;
	}
}