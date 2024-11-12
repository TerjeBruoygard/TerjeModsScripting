// <copyright file="ItemManager.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ItemManager
{
	private ref Widget m_terjeSkillsTooltip = null;
	private ref Timer m_terjeSkillsToolTipTimer = null;
	
	override void HideTooltip()
	{
		super.HideTooltip();
		
		if (m_terjeSkillsToolTipTimer != null)
		{
			delete m_terjeSkillsToolTipTimer;
			m_terjeSkillsToolTipTimer = null;
		}
		
		if (m_terjeSkillsTooltip != null)
		{
			m_terjeSkillsTooltip.Unlink();
			m_terjeSkillsTooltip = null;
		}
	}
	
	ref Widget GetTerjeSkillsRoot()
	{
		return m_RootWidget;
	}
	
	void TerjeSkillsSetupTooltipWidget(ref Widget tooltipWidget, int x, int y)
	{
		HideTooltip();
		
		int screen_w, screen_h;
		float width, height;
		GetScreenSize(screen_w, screen_h);
		tooltipWidget.GetScreenSize(width,height);
		GetMousePos(x,y);
		
		screen_w -= 10;
		screen_h -= 10;
		
		int rightEdge = x + width;
		if (rightEdge > screen_w)
		{
			x = screen_w - width;
		}
		
		int bottomEdge = y + height;
		if (bottomEdge > screen_h)
		{
			y = screen_h - height;
		}
		
		tooltipWidget.SetPos(x, y);
		
		m_terjeSkillsToolTipTimer = new Timer();
		m_terjeSkillsToolTipTimer.Run( TOOLTIP_DELAY, this, "ShowTerjeSkillsTooltip" );
		m_terjeSkillsTooltip = tooltipWidget;
	}
	
	void ShowTerjeSkillsTooltip()
	{
		if (m_terjeSkillsTooltip != null)
		{
			m_terjeSkillsTooltip.Show(true);
			m_terjeSkillsTooltip.Update();
		}
	}
};