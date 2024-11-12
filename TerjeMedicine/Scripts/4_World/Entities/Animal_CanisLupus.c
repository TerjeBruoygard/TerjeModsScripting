// <copyright file="Animal_CanisLupus.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Animal_CanisLupus
{
	private bool m_HasTerjeRabies;
	
	override bool HasTerjeRabies()
	{
		return m_HasTerjeRabies;
	}
	
	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame().IsDedicatedServer())
		{
			float rabiesChance;
			if (GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_WOLF_INFECTED_CHANCE, rabiesChance))
			{
				m_HasTerjeRabies = (Math.RandomFloat01() < rabiesChance);
			}
		}
	}
}
