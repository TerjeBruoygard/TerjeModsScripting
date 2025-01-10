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
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "fish", "craftsman");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "fish", "craftsman", true);
	}
}

modded class CraftFishNetTrap
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "fish", "craftsman");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "fish", "craftsman", true);
	}
}

modded class CraftBoneHook
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "fish", "craftsman");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "fish", "craftsman", true);
	}
}

modded class CraftWoodenHook
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "fish", "craftsman");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "fish", "craftsman", true);
	}
}