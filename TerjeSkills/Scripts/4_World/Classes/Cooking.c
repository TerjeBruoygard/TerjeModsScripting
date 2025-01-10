// <copyright file="Cooking.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Cooking
{
	override int UpdateCookingStateOnStick( Edible_Base item_to_cook, float cook_time_inc )
	{
		int result = super.UpdateCookingStateOnStick(item_to_cook, cook_time_inc);
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (result == 1 && item_to_cook && item_to_cook.GetFoodStageType() != FoodStageType.BURNED)
			{
				PlayerBase hierarhyParent = PlayerBase.Cast(item_to_cook.GetHierarchyRootPlayer());
				if (hierarhyParent && hierarhyParent.GetTerjeSkills())
				{
					int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_SURV_COOKING_ON_STICK_EXP_GAIN);
					if (expGain > 0)
					{
						hierarhyParent.GetTerjeSkills().AddSkillExperience("surv", expGain);
					}
				}
			}
		}
		
		return result;
	}
}