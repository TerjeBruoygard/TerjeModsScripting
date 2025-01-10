// <copyright file="CraftSurvivalSkill.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class CraftHandDrillKit
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "anctech");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "anctech", true);
	}
}

modded class CraftArrow
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftArrowBone
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftBaseBallBatBarbed
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftBaseBallBatNailed
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftBoneKnife
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftBow
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftStoneKnife
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftSpearStone
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftCamoNetShelter
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftGhillieAttachment
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftGhillieBushrag
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftGhillieHood
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftGhillieSuit
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftGhillieTop
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftGutsRope
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftImprovisedLeatherBag
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftLeatherCourierBag
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftLeatherSack
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftSpearBone
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}

modded class CraftTannedLeather
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
}