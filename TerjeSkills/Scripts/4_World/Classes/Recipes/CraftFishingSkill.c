// <copyright file="CraftFishingSkill.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class CraftFishingRod
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		bool result = super.CanDo(ingredients, player);	
		if (result && player && player.GetTerjeSkills() && player.GetTerjeSkills().IsPerkRegistered("fish", "craftsman"))
		{
			return player.GetTerjeSkills().GetPerkLevel("fish", "craftsman") > 0;
		}
		
		return result;
	}
};

modded class CraftFishNetTrap
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		bool result = super.CanDo(ingredients, player);	
		if (result && player && player.GetTerjeSkills() && player.GetTerjeSkills().IsPerkRegistered("fish", "craftsman"))
		{
			return player.GetTerjeSkills().GetPerkLevel("fish", "craftsman") > 0;
		}
		
		return result;
	}
};

modded class CraftBoneHook
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		bool result = super.CanDo(ingredients, player);	
		if (result && player && player.GetTerjeSkills() && player.GetTerjeSkills().IsPerkRegistered("fish", "craftsman"))
		{
			return player.GetTerjeSkills().GetPerkLevel("fish", "craftsman") > 0;
		}
		
		return result;
	}
};

modded class CraftWoodenHook
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		bool result = super.CanDo(ingredients, player);	
		if (result && player && player.GetTerjeSkills() && player.GetTerjeSkills().IsPerkRegistered("fish", "craftsman"))
		{
			return player.GetTerjeSkills().GetPerkLevel("fish", "craftsman") > 0;
		}
		
		return result;
	}
};