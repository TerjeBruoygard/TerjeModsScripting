// <copyright file="TerjeStartScreenPageRules.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenPageRules : TerjeStartScreenPageBase
{
	protected Widget m_nextButtonPanel;
	protected Widget m_contentPanel;
	protected TerjeWidgetScrollArea m_scrollArea = null;
	protected TerjeWidgetButton m_nextButton = null;
	protected float m_timeCounter = 0;
	protected float m_timeLimit = 5;
	protected bool m_readToEndRequired = true;
	
	override void OnInit()
	{
		super.OnInit();
		m_nextButtonPanel = GetNativeWidget().FindAnyWidget("NextButtonPanel");
		m_contentPanel = GetNativeWidget().FindAnyWidget("ContentPanel");
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/PageRules.layout";
	}
	
	override void InitInputContext(TerjeStartScreenContextBase context)
	{
		super.InitInputContext(context);
		
		TerjeStartScreenContextRules rulesContext = TerjeStartScreenContextRules.Cast(context);
		if (rulesContext != null)
		{
			m_readToEndRequired = rulesContext.m_readToEndRequired;
			m_timeLimit = rulesContext.m_nextTimeout;
			
			m_timeCounter = 0;
			DestroyAllChildren();
			
			m_nextButton = TerjeWidgetButton.Cast(CreateTerjeWidgetEx(TerjeWidgetButton, m_nextButtonPanel));
			m_nextButton.SetText("#STR_USRACT_NEXT_ACTION");
			m_nextButton.SetEnabled(false);
			m_nextButton.OnClickEvent.Insert(OnClickNextButton);
			
			m_scrollArea = TerjeWidgetScrollArea.Cast(CreateTerjeWidgetEx(TerjeWidgetScrollArea, m_contentPanel));
			SetRulesContent(m_scrollArea, rulesContext);
		}
	}
	
	override void InitOutputContext(TerjeStartScreenContextBase context)
	{
		super.InitOutputContext(context);
		
		TerjeStartScreenContextRules rulesContext = TerjeStartScreenContextRules.Cast(context);
		if (rulesContext != null)
		{
			rulesContext.m_rulesMarkdownContent.Clear();
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		if (m_scrollArea != null && m_nextButton != null)
		{
			if (m_timeCounter > m_timeLimit)
			{
				if ((!m_readToEndRequired) || (!m_scrollArea.IsScrollVisible()) || (m_scrollArea.GetScrollPos() == 1))
				{
					if (!m_nextButton.IsEnabled())
					{
						m_nextButton.SetEnabled(true);
					}
				}
			}
			
			m_timeCounter = m_timeCounter + timeslice;
		}
	}
	
	protected void OnClickNextButton(TerjeWidgetButton widget)
	{
		ExecuteNextPage();
	}
	
	protected void SetRulesContent(TerjeWidgetScrollArea scrollArea, TerjeStartScreenContextRules rulesContext)
	{
		TerjeWidgetMarkdown.Cast(scrollArea.CreateChildWidget(TerjeWidgetMarkdown)).SetContent(rulesContext.m_rulesMarkdownContent);
	}
}