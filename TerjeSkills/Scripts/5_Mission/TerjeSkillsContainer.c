// <copyright file="TerjeSkillsContainer.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSkillsContainer : CollapsibleContainer
{
	void TerjeSkillsContainer( LayoutHolder parent, int sort = -1 )
	{
		m_CollapsibleHeader.SetName( "#STR_TERJESKILL_HEADER" );
	}
	
	void InitializeSkills(PlayerBase player)
	{
		// Insert spacer
		Insert(new TerjeSkillBlankSpacer(this));
		
		// Insert skills
		ref array<ref TerjeSkillCfg> skills = new array<ref TerjeSkillCfg>;
		GetTerjeSkillsRegistry().GetSkills(skills);
		foreach (ref TerjeSkillCfg skill : skills)
		{
			TerjeSkillWidget widget = new TerjeSkillWidget(this);
			widget.InitializeSkill(skill, player);
			Insert(widget);
		}
	}
};

class TerjeSkillBlankSpacer : Container
{
	override void SetLayoutName()
	{
		m_LayoutName = "TerjeSkills/Layouts/TerjeBlankLayout.layout";
	}
};