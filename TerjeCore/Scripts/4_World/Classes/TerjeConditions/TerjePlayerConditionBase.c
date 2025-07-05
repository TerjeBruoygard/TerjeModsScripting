// <copyright file="TerjePlayerConditionBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditionBase
{
	bool Validate(PlayerBase player, TerjeXmlObject condition)
	{
		return false;
	}
	
	void Apply(PlayerBase player, TerjeXmlObject condition)
	{
	
	}
	
	string GetText(PlayerBase player, TerjeXmlObject condition)
	{
		return string.Empty;
	}
}