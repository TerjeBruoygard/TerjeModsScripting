// <copyright file="TerjeToDogTagsCompatibility.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

/* DO NOT OBFUSCATE */
#ifdef WRDG_DOGTAGS
#ifdef SERVER
modded class PluginTerjeStartScreen
{
	override void DeleteLoadoutItemEquip(ItemBase item)
	{
		if (item.IsInherited(Dogtag_Base))
		{
			return;
		}
		
		super.DeleteLoadoutItemEquip(item);
	}
}

modded class TerjeStartScreenParams
{
	override void OnServerDone(PlayerBase player)
	{
		super.OnServerDone(player);
		if (player)
		{
			Dogtag_Base dogTag = Dogtag_Base.Cast(player.GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("Dogtag")));
			if (dogTag)
			{
				dogTag.SetNickName(player.GetTerjeCharacterName());
			}
		}
	}
}
#endif
#endif