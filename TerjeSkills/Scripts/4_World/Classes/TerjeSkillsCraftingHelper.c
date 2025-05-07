// <copyright file="TerjeSkillsCraftingHelper.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeSkillsCraftingHelper
{
	override bool CanDoCraftPerkRequired(RecipeBase recipe, PlayerBase player, string skillId, string perkId, int requiredLevel = 1)
	{
		bool result = super.CanDoCraftPerkRequired(recipe, player, skillId, perkId);
		if (result && player && player.GetTerjeSkills() && player.GetTerjeSkills().IsPerkRegistered(skillId, perkId))
		{
			if (GetTerjeSettingBool(TerjeSettingsCollection.SKILLS_ALLOW_CRAFTING_WITHOUT_PERKS))
			{
				return true;
			}
			
			if (player.GetTerjeSkills().GetPerkLevel(skillId, perkId) >= requiredLevel)
			{
				return true;
			}
			
			return false;
		}
		
		return result;
	}
	
	override void DoCraftPerkRequired(RecipeBase recipe, PlayerBase player, array<ItemBase> results, string skillId, string perkId, bool gainExperience)
	{
		super.DoCraftPerkRequired(recipe, player, results, skillId, perkId, gainExperience);
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().IsPerkRegistered(skillId, perkId))
		{
			float perkValue;
			if (!player.GetTerjeSkills().GetPerkValue(skillId, perkId, perkValue))
			{
				perkValue = 0.1;
			}
			
			foreach (ItemBase itemResult : results)
			{
				if (itemResult)
				{
					itemResult.SetHealth01("", "", Math.Clamp(perkValue, 0.1, 1.0));
				}
			}
			
			if (gainExperience)
			{
				int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_CRAFTING_EXPERIENCE_GAIN);
				if (expGain > 0)
				{
					player.GetTerjeSkills().AddSkillExperience(skillId, expGain);
				}
			}
		}
	}
}