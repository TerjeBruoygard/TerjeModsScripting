// <copyright file="RightArea.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class RightArea
{
	protected ref TerjeSkillsContainer m_terjeSkillsContainer = null;
	
	override void Refresh()
	{
		super.Refresh();
		
		if (m_terjeSkillsContainer != null)
		{
			m_terjeSkillsContainer.Refresh();
		}
	}
	
	override void UpdateInterval()
	{
		super.UpdateInterval();
		
		if (m_terjeSkillsContainer != null)
		{
			m_terjeSkillsContainer.UpdateInterval();
		}
		else if (m_terjeSkillsContainer == null && GetTerjeSkillsRegistry().IsReadyToDisplay())
		{
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			if (player)
			{
				m_terjeSkillsContainer = new TerjeSkillsContainer(this);
				m_terjeSkillsContainer.InitializeSkills(player);
				m_Body.Insert( m_terjeSkillsContainer );
				RecomputeOpenedContainers();
			}
		}
	}
}