// <copyright file="TerjePlayerModifierPerkStrongHands.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierPerkStrongHands : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1.0;
	};
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		ItemBase itemInHands = player.GetItemInHands();
		if (itemInHands && player.GetIdentity() && IsHeavyItemSkillCheck(itemInHands) && player.CanDropEntity(itemInHands) && player.GetTerjeSkills())
		{
			if (player.GetTerjeSkills().GetPerkLevel("strng", "strhands") == 0)
			{
				player.GetInventory().DropEntity(InventoryMode.SERVER, player, itemInHands);
				NotificationSystem.SendNotificationToPlayerIdentityExtended(player.GetIdentity(), 5, "#STR_TERJEPERK_REQUIRED_MSG", "#STR_TERJEPERK_STRONGHANDS_MSG", "set:TerjePerk_icon image:tp_stronghands");
			}
		}
	}
	
	bool IsHeavyItemSkillCheck(ItemBase itemInHands)
	{
		if (!itemInHands)
		{
			return false;
		}
		
		if (itemInHands.IsInherited(MediumTent))
		{
			return false;
		}
		
		if (itemInHands.IsInherited(LargeTent))
		{
			return false;
		}
		
		return itemInHands.IsHeavyBehaviour();
	}
};