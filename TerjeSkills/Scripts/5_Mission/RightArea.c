// <copyright file="RightArea.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class RightArea
{
	protected ref TerjeSkillsContainer m_terjeSkillsContainer;
	
	void RightArea(LayoutHolder parent)
	{
		m_terjeSkillsContainer = new TerjeSkillsContainer(this);
		m_terjeSkillsContainer.InitializeSkills(PlayerBase.Cast(GetGame().GetPlayer()));
		m_Body.Insert( m_terjeSkillsContainer );
	}
	
	override void Refresh()
	{
		super.Refresh();
		if (m_terjeSkillsContainer)
		{
			m_terjeSkillsContainer.Refresh();
		}
	}
	
	override void UpdateInterval()
	{
		super.UpdateInterval();
		if (m_terjeSkillsContainer)
		{
			m_terjeSkillsContainer.UpdateInterval();
		}
	}
};