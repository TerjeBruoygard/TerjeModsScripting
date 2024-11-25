// <copyright file="TerjePerkTooltip.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePerkTooltip
{
	private static ref Widget m_perkTooltipInstance = null;
	static ref Widget GetPerkTooltipWidget(ref TerjePerkCfg perkCfg, int perkLevel, int perkActiveLevel, bool canBeUpgraded)
	{
		if (m_perkTooltipInstance)
		{
			m_perkTooltipInstance.Unlink();
		}
		
		m_perkTooltipInstance = GetGame().GetWorkspace().CreateWidgets("TerjeSkills/Layouts/TerjePerkTooltip.layout", ItemManager.GetInstance().GetTerjeSkillsRoot() );
		m_perkTooltipInstance.Show(false);
		
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
		
		return m_perkTooltipInstance;
	}
}