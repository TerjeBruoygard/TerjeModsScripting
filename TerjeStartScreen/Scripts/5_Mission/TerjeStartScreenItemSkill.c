// <copyright file="TerjeStartScreenItemSkill.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenItemSkill : TerjeWidgetBase
{
	protected ImageWidget m_iconWidget;
	protected TextWidget m_nameWidget;
	protected TextWidget m_descWidget;
	protected TextWidget m_levelWidget;
	protected Widget m_buttonPlusWidget;
	protected Widget m_buttonMinusWidget;
	protected string m_skillId;
	protected int m_currentLevel;
	protected int m_maxLevel;
	
	// void ScriptInvoker(TerjeStartScreenItemSkill widget, int diff)
	ref ScriptInvoker OnClickEvent = new ScriptInvoker;
	
	override void OnInit()
	{
		super.OnInit();
		m_iconWidget = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("SkillItemIcon"));
		m_nameWidget = TextWidget.Cast(GetNativeWidget().FindAnyWidget("SkillItemName"));
		m_descWidget = TextWidget.Cast(GetNativeWidget().FindAnyWidget("SkillItemDesc"));
		m_levelWidget = TextWidget.Cast(GetNativeWidget().FindAnyWidget("SkillItemLvl"));
		m_buttonPlusWidget = GetNativeWidget().FindAnyWidget("ButtonPlus");
		m_buttonMinusWidget = GetNativeWidget().FindAnyWidget("ButtonMinus");
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/ItemSkill.layout";
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenItemSkillSet))
		{
			SetSkillCfgImmediately(TerjeWidgetCommand_TerjeStartScreenItemSkillSet.Cast(command).m_skillCfg);
		}
		else if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenItemSkillUdp))
		{
			OnItemSkillChanged(TerjeWidgetCommand_TerjeStartScreenItemSkillUdp.Cast(command).m_diff);
		}
		else if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenItemSkillLvl))
		{
			SetSkillLvlImmediately(TerjeWidgetCommand_TerjeStartScreenItemSkillLvl.Cast(command).m_lvl);
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if ((m_buttonPlusWidget != null) && (w == m_buttonPlusWidget) && (button == 0))
		{
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenItemSkillUdp(1));
			return true;
		}
		else if ((m_buttonMinusWidget != null) && (w == m_buttonMinusWidget) && (button == 0))
		{
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenItemSkillUdp(-1));
			return true;
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	void SetSkillCfg(TerjeSkillCfg skillCfg)
	{
		PushCommand(new TerjeWidgetCommand_TerjeStartScreenItemSkillSet(skillCfg));
	}
	
	void SetSkillCfgImmediately(TerjeSkillCfg skillCfg)
	{
		m_currentLevel = 0;
		m_skillId = skillCfg.GetId();
		m_maxLevel = skillCfg.GetMaxLevel();
		m_iconWidget.LoadImageFile(0, skillCfg.GetIcon());
		m_nameWidget.SetText(skillCfg.GetDisplayName());
		m_descWidget.SetText(skillCfg.GetDescription());
		m_levelWidget.SetText(m_currentLevel.ToString());
	}
	
	void SetSkillLvl(int lvl)
	{
		PushCommand(new TerjeWidgetCommand_TerjeStartScreenItemSkillLvl(lvl));
	}
	
	void SetSkillLvlImmediately(int lvl)
	{
		m_currentLevel = TerjeMathHelper.ClampInt(lvl, 0, m_maxLevel);
		m_levelWidget.SetText(m_currentLevel.ToString());
	}
	
	void OnItemSkillChanged(int diff)
	{
		OnClickEvent.Invoke(this, diff);
	}
	
	string GetSkillId()
	{
		return m_skillId;
	}
	
	int GetCurrentLevel()
	{
		return m_currentLevel;
	}
	
	int GetMaxLevel()
	{
		return m_maxLevel;
	}
}

class TerjeWidgetCommand_TerjeStartScreenItemSkillSet : TerjeWidgetCommand
{
	ref TerjeSkillCfg m_skillCfg;
	
	void TerjeWidgetCommand_TerjeStartScreenItemSkillSet(TerjeSkillCfg skillCfg)
	{
		m_skillCfg = skillCfg;
	}
}

class TerjeWidgetCommand_TerjeStartScreenItemSkillUdp : TerjeWidgetCommand
{
	int m_diff;
	
	void TerjeWidgetCommand_TerjeStartScreenItemSkillUdp(int diff)
	{
		m_diff = diff;
	}
}

class TerjeWidgetCommand_TerjeStartScreenItemSkillLvl : TerjeWidgetCommand
{
	int m_lvl;
	
	void TerjeWidgetCommand_TerjeStartScreenItemSkillLvl(int lvl)
	{
		m_lvl = lvl;
	}
}