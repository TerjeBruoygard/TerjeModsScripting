// <copyright file="TerjeToDogTagsCompatibility.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

/* DO NOT OBFUSCATE */
#ifdef WRDG_DOGTAGS
#ifdef SERVER
modded class MissionServer
{
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(this.TerjeToDogtagCompatibilityUpdateName, player);
	}
	
	void TerjeToDogtagCompatibilityUpdateName(PlayerBase player)
	{
		if (player && player.GetDogtag())
		{
			player.GetDogtag().SetNickName(player.GetTerjeCharacterName()); // updates player's name
		}
	}
}
#endif
#endif