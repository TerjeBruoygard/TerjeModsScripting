// <copyright file="DayZGame.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class DayZGame
{
	protected string m_terjeSelectedCharacterClassname = string.Empty;
	
	void SetSelectedTerjeCharacterClassname(string value)
	{
		m_terjeSelectedCharacterClassname = value;
	}
	
	override string CreateRandomPlayer()
	{
		if (m_terjeSelectedCharacterClassname != string.Empty)
		{
			return m_terjeSelectedCharacterClassname;
		}
		
		return super.CreateRandomPlayer();
	}
}