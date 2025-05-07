// <copyright file="TerjeWidgetButtonHold.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetButtonHold : TerjeWidgetBase
{
	protected Widget m_buttonActor;
	protected TextWidget m_buttonText; 
	protected ProgressBarWidget m_buttonBar;
	
	protected bool m_hold = false;
	protected float m_timer = 0;
	protected float m_holdTime = 5;
	
	// void ScriptInvoker(TerjeWidgetButtonHold widget)
	ref ScriptInvoker OnClickEvent = new ScriptInvoker;
	
	override void OnInit()
	{
		super.OnInit();
		m_buttonActor = GetNativeWidget().FindAnyWidget("TerjeWidgetBtn");
		m_buttonText = TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetTxt"));
		m_buttonBar = ProgressBarWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetBar"));
	}
	
	void SetHoldTime(float value)
	{
		m_holdTime = value;
	}
	
	void SetEnabled(bool enabled)
	{
		PushCommand(new TerjeWidgetCommand_Enabled(enabled));
	}
	
	void SetEnabledImmediately(bool enabled)
	{
		if (enabled)
		{
			GetNativeWidget().SetColor(ARGB(60, 255, 0, 0));
			m_buttonActor.Show(true);
		}
		else
		{
			GetNativeWidget().SetColor(ARGB(60, 80, 80, 80));
			m_buttonActor.Show(false);
		}
	}
	
	void SetText(string text)
	{
		PushCommand(new TerjeWidgetCommand_Text(text));
	}
	
	void SetTextImmediately(string text)
	{
		m_buttonText.SetText(text);
	}

	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetButtonHold.layout";
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_Text))
		{
			SetTextImmediately(TerjeWidgetCommand_Text.Cast(command).m_text);
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_Clicked))
		{
			OnClickEvent.Invoke(this);
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_Enabled))
		{
			SetEnabledImmediately(TerjeWidgetCommand_Enabled.Cast(command).m_enabled);
			return;
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
	
		if (m_hold)
		{
			m_timer = m_timer + timeslice;
			
			float process = m_timer / m_holdTime;
			if (process >= 1)
			{
				m_hold = false;
				m_timer = 0;
				m_buttonBar.SetCurrent(0);
				OnClickEvent.Invoke(this);
			}
			else
			{
				m_buttonBar.Show(true);
				m_buttonBar.SetCurrent(Math.Clamp(process, m_buttonBar.GetMin(), m_buttonBar.GetMax()));
			}
		}
		else
		{
			m_buttonBar.Show(false);
		}
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		if ((w == m_buttonActor) && (button == MouseState.LEFT))
		{
			m_hold = true;
			m_timer = 0;
			return true;
		}
		
		return super.OnMouseButtonDown(w, x, y, button);
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		m_hold = false;
		m_timer = 0;
		return true;
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		m_hold = false;
		m_timer = 0;
		return true;
	}
	
	override bool OnMouseLeave( Widget w, Widget enterW, int x, int y )
	{
		m_hold = false;
		m_timer = 0;
		return true;
	}
}