// <copyright file="TerjeStartScreenPageSkills.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenPageSkills : TerjeStartScreenPageBase
{
	protected Widget m_nextButton;
	protected TextWidget m_infoText;
	protected Widget m_skillsPanel;
	protected ref map<string, int> m_skillsData;
	
	protected int m_pointsCount;
	
	override void OnInit()
	{
		super.OnInit();
		m_nextButton = GetNativeWidget().FindAnyWidget("ButtonOk");
		m_infoText = TextWidget.Cast(GetNativeWidget().FindAnyWidget("WindowInfo"));
		m_skillsPanel = GetNativeWidget().FindAnyWidget("SkillsPanel");
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/PageSkills.layout";
	}
	
	override void InitInputContext(TerjeStartScreenContextBase context)
	{
		super.InitInputContext(context);
		
		TerjeStartScreenContextSkills skillsContext = TerjeStartScreenContextSkills.Cast(context);
		if (skillsContext != null)
		{
			m_pointsCount = skillsContext.m_inputPoints;
			m_skillsData = new map<string, int>;
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenSkillsRefresh());
		}
	}
	
	override void InitOutputContext(TerjeStartScreenContextBase context)
	{
		super.InitOutputContext(context);
		
		TerjeStartScreenContextSkills skillsContext = TerjeStartScreenContextSkills.Cast(context);
		if (skillsContext != null)
		{
			skillsContext.m_outputPoints.Copy(m_skillsData);
		}
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_Clicked))
		{
			ExecuteNextPage();
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenSkillsRefresh))
		{
			DestroyAllChildren();
			
			m_infoText.SetText("#STR_TERJESTARTSCREEN_PAGE_SKILLS_INFO " + m_pointsCount);
			TerjeWidgetScrollArea scrollArea = TerjeWidgetScrollArea.Cast(CreateTerjeWidgetEx(TerjeWidgetScrollArea, m_skillsPanel));
			
			array<ref TerjeSkillCfg> skills();
			GetTerjeSkillsRegistry().GetSkills(skills);
			foreach (ref TerjeSkillCfg skill : skills)
			{
				CreateSkillItemWidget(scrollArea, skill);
			}
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if ((m_nextButton != null) && (w == m_nextButton) && (button == 0))
		{
			PushCommand(new TerjeWidgetCommand_Clicked(button));
			return true;
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	protected void CreateSkillItemWidget(TerjeWidgetScrollArea scrollArea, TerjeSkillCfg skillCfg)
	{
		TerjeStartScreenItemSkill itemWidget = TerjeStartScreenItemSkill.Cast( scrollArea.CreateChildWidget(TerjeStartScreenItemSkill) );
		itemWidget.SetSkillCfg(skillCfg);
		itemWidget.OnClickEvent.Insert(OnSkillItemChanged);
	}
	
	protected void OnSkillItemChanged(TerjeStartScreenItemSkill item, int diff)
	{
		if (item != null && m_skillsData != null)
		{
			int lvl = item.GetCurrentLevel() + diff;
			int points = m_pointsCount - diff;
			if (lvl >= 0 && lvl <= item.GetMaxLevel() && points >= 0)
			{
				m_pointsCount = points;
				m_skillsData.Set(item.GetSkillId(), lvl);
				m_infoText.SetText("#STR_TERJESTARTSCREEN_PAGE_SKILLS_INFO " + points);
				item.SetSkillLvl(lvl);
			}
		}
	}
}

class TerjeWidgetCommand_TerjeStartScreenSkillsRefresh : TerjeWidgetCommand
{
	void TerjeWidgetCommand_TerjeStartScreenSkillsRefresh()
	{
		
	}
}