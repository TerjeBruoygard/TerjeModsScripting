// <copyright file="TerjeSkillWidget.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSkillWidget: Container
{	
	private ref Header m_Header;
	private ref TerjeSkillCfg m_Skill;
	private PlayerBase m_Player;
	private ref map<string, ref Widget> m_perkWidgets;
	private ref TerjeModalDialog m_resetSkillModalDialog;
	private int m_CurrentLevel;
	private int m_CurrentExp;
	private int m_CurrentPerkPoints;
	
	void TerjeSkillWidget(LayoutHolder parent) 
	{
		m_perkWidgets = new map<string, ref Widget>;
		
		Widget headerWidget = GetMainWidget().FindAnyWidget("terje_skill_header");
		if (headerWidget)
		{
			WidgetEventHandler.GetInstance().RegisterOnMouseEnter(headerWidget, this, "OnHeaderMouseEnter");
			WidgetEventHandler.GetInstance().RegisterOnMouseLeave(headerWidget, this, "OnHeaderMouseLeave");
		}
		
		Widget resetPerksWidget = GetMainWidget().FindAnyWidget("terje_skill_header_reset_hover");
		if (resetPerksWidget)
		{
			WidgetEventHandler.GetInstance().RegisterOnMouseEnter(resetPerksWidget, this, "OnResetMouseEnter");
			WidgetEventHandler.GetInstance().RegisterOnMouseLeave(resetPerksWidget, this, "OnResetMouseLeave");
			WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(resetPerksWidget, this, "OnResetMouseDown");
			WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp(resetPerksWidget, this, "OnResetMouseUp");
		}
	}
	
	void ~TerjeSkillWidget() 
	{
		m_perkWidgets.Clear();
		
		ref ItemManager itemManager = ItemManager.GetInstance();
		if (itemManager != null)
		{
			itemManager.HideTooltip();
		}
	}
	
	void InitializeSkill(ref TerjeSkillCfg skill, PlayerBase player)
	{
		m_Skill = skill;
		m_Player = player;
	}
	
	override void SetLayoutName()
	{
		m_LayoutName = "TerjeSkills/Layouts/TerjeSkillLayout.layout";
	}
	
	override void SetHeader(Header header)
	{
		m_Header = header;
	}
	
	override Header GetHeader()
	{
		return m_Header;
	}
	
	bool OnHeaderMouseEnter(Widget w, int x, int y)
	{
		ref ItemManager itemManager = ItemManager.GetInstance();
		if (itemManager != null)
		{
			itemManager.TerjeSkillsSetupTooltipWidget(TerjeSkillTooltip.GetSkillTooltipWidget(m_Skill, m_CurrentExp, m_CurrentPerkPoints), x, y);
		}
		
		return false;
	}
	
	bool OnHeaderMouseLeave( Widget w, Widget s, int x, int y )
	{
		ref ItemManager itemManager = ItemManager.GetInstance();
		if (itemManager != null)
		{
			itemManager.HideTooltip();
		}
		
		return false;
	}
	
	bool OnResetMouseEnter(Widget w, int x, int y)
	{
		if (w)
		{
			w.SetColor(ARGB(60, 0, 0, 0));
			return true;
		}
		
		return false;
	}
	
	bool OnResetMouseLeave( Widget w, Widget s, int x, int y	)
	{
		if (w)
		{
			w.SetColor(ARGB(0, 0, 0, 0));
			return true;
		}
		
		return false;
	}
	
	void OnResetMouseDown( Widget w, int x, int y, int button )
	{
		if (w)
		{
			w.SetColor(ARGB(120, 0, 0, 0));
		}
	}
	
	void OnResetMouseUp( Widget w, int x, int y, int button )
	{
		if (w && w.IsVisible() && m_Player && m_Player.GetIdentity() && m_Player.IsAlive() && m_Player.GetTerjeSkills() && m_Skill != null)
		{
			float experienceLoseOnResetPerks;
			GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_EXPERIENCE_LOSE_ON_RESET_PERKS, experienceLoseOnResetPerks);
			
			int expbackPercent = (int)(experienceLoseOnResetPerks * 100.0);
			string title = "#STR_TERJESKILL_MISC13";
			string message = "#STR_TERJESKILL_MISC14 " + expbackPercent + "% #STR_TERJESKILL_MISC15";			
			GetGame().GetUIManager().ShowScriptedMenu(TerjeModalDialog.GetInstance(title, message, this, "OnResetSkillModalDialogResult"), GetGame().GetUIManager().GetMenu());
		}
	}
	
	void OnResetSkillModalDialogResult(bool result)
	{
		if (result)
		{
			string skillId = m_Skill.GetId();
			
			// Apply on client
			m_Player.GetTerjeSkills().ResetSkill(skillId);
			Refresh();
					
			// Apply on server
			m_Player.TerjeRPCSingleParam(TerjeSkillsConstants.TRPC_PLAYER_PERKS_RESET, new Param1<string>(skillId), true, null);
		}
	}
	
	bool OnPerkMouseEnter(Widget w, int x, int y)
	{
		if (w && m_Skill && m_Player && m_Player.GetTerjeSkills())
		{
			Widget highlightWidget = w.FindAnyWidget("terje_perk_highlight");
			if (highlightWidget)
			{
				highlightWidget.SetColor(ARGB(60, 0, 0, 0));
				
				ref TerjePerkCfg perkCfg;
				if (m_Skill.FindPerk(w.GetName(), perkCfg))
				{
					bool canBeUpgraded;
					int perkLevel;
					int perkActiveLevel;
					m_Player.GetTerjeSkills().GetPerkStatus(m_Skill.GetId(), perkCfg.GetId(), perkLevel, perkActiveLevel, canBeUpgraded);
					ref ItemManager itemManager = ItemManager.GetInstance();
					if (itemManager != null)
					{
						itemManager.TerjeSkillsSetupTooltipWidget(TerjePerkTooltip.GetPerkTooltipWidget(perkCfg, perkLevel, perkActiveLevel, canBeUpgraded), x, y);
					}
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	bool OnPerkMouseLeave( Widget w, Widget s, int x, int y	)
	{
		if (w)
		{
			Widget highlightWidget = w.FindAnyWidget("terje_perk_highlight");
			if (highlightWidget)
			{
				highlightWidget.SetColor(ARGB(0, 0, 0, 0));
				return true;
			}
		}
		
		ref ItemManager itemManager = ItemManager.GetInstance();
		if (itemManager != null)
		{
			itemManager.HideTooltip();
		}
		
		return false;
	}
	
	void OnPerkMouseDown( Widget w, int x, int y, int button )
	{
		if (w)
		{
			Widget highlightWidget = w.FindAnyWidget("terje_perk_highlight");
			if (highlightWidget)
			{
				highlightWidget.SetColor(ARGB(120, 0, 0, 0));
				
				ref ItemManager itemManager = ItemManager.GetInstance();
				if (itemManager != null)
				{
					itemManager.HideTooltip();
				}
			}
		}
	}
	
	void OnPerkMouseUp( Widget w, int x, int y, int button )
	{
		if (w)
		{
			Widget highlightWidget = w.FindAnyWidget("terje_perk_highlight");
			if (highlightWidget)
			{
				highlightWidget.SetColor(ARGB(0, 0, 0, 0));
				
				if (highlightWidget.IsVisible() && m_Player && m_Player.GetIdentity() && m_Player.IsAlive() && m_Player.GetTerjeSkills() && m_Skill != null)
				{
					string skillId = m_Skill.GetId();
					string perkId = w.GetName();
					
					// Apply on client
					m_Player.GetTerjeSkills().AddPerkLevel(skillId, perkId);
					Refresh();
					
					// Apply on server
					m_Player.TerjeRPCSingleParam(TerjeSkillsConstants.TRPC_PLAYER_PERK_APPLY, new Param2<string, string>(skillId, perkId), true, null);
				}
			}
		}
	}
	
	override void Refresh()
	{
		super.Refresh();

		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
};
