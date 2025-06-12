// <copyright file="TerjeToSaveLootOnDeathCompatibility.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

/* DO NOT OBFUSCATE */
#ifdef SATORU_SAVE_LOOT_ON_DEATH_MOD
modded class MissionServer
{
	override void SL_EquipCharacter(PlayerBase player)
	{
		// SAVED LOOT WILL BE CREATER AFTER START SCREEN WILL CLOSED
	}
}
#endif