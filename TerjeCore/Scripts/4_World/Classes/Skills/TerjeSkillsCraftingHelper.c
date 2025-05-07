// <copyright file="TerjeSkillsCraftingHelper.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSkillsCraftingHelper
{
	private static ref TerjeSkillsCraftingHelper m_Instance = null;
	
	static ref TerjeSkillsCraftingHelper GetInstance()
	{
		if (m_Instance == null)
		{
			m_Instance = new TerjeSkillsCraftingHelper;
		}
		
		return m_Instance;
	}
	
	bool CanDoCraftPerkRequired(RecipeBase recipe, PlayerBase player, string skillId, string perkId, int requiredLevel = 1)
	{
		return true;
	}
	
	void DoCraftPerkRequired(RecipeBase recipe, PlayerBase player, array<ItemBase> results, string skillId, string perkId, bool gainExperience)
	{
	
	}
}