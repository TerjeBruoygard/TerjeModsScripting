// <copyright file="TerjeSkillTooltip.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSkillTooltip
{
	private static ref Widget m_skillTooltipInstance = null;
	static ref Widget GetSkillTooltipWidget(ref TerjeSkillCfg skillCfg, int exp, int points)
	{
		if (m_skillTooltipInstance)
		{
			m_skillTooltipInstance.Unlink();
		}
		
		m_skillTooltipInstance = GetGame().GetWorkspace().CreateWidgets("TerjeSkills/Layouts/TerjeSkillTooltip.layout", ItemManager.GetInstance().GetTerjeSkillsRoot() );
		m_skillTooltipInstance.Show(false);
		
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
		
		return m_skillTooltipInstance;
	}
};