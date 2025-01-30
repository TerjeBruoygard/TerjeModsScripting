// <copyright file="VomitSymptom.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class VomitSymptom
{
	override void OnGetActivatedServer(PlayerBase player)
	{
		super.OnGetActivatedServer(player);
		
		if (player)
		{
			if (player.IsFaceBlocked(true))
			{
				ref ItemBase itemCheck = player.GetItemOnSlot("Mask");
				if (!itemCheck)
				{
					itemCheck = player.GetItemOnSlot("Headgear");
				}
				
				if (itemCheck)
				{
					player.GetInventory().DropEntity(InventoryMode.SERVER, player, itemCheck);
				}
			}
		}
	}
}