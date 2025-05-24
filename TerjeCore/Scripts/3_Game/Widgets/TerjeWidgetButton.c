// <copyright file="TerjeWidgetButton.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetButton : TerjeWidgetBase
{
	protected bool m_enabled;
	protected Widget m_buttonActor;
	protected TextWidget m_buttonText; 
	
	// void ScriptInvoker(TerjeWidgetButton widget)
	ref ScriptInvoker OnClickEvent = new ScriptInvoker;
	
	override void OnInit()
	{
		super.OnInit();
		m_enabled = true;
		m_buttonActor = GetNativeWidget().FindAnyWidget("TerjeWidgetBtn");
		m_buttonText = TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetTxt"));
	}
	
	void SetEnabled(bool enabled)
	{
		m_enabled = enabled;
		PushCommand(new TerjeWidgetCommand_Enabled(enabled));
	}
	
	void SetEnabledImmediately(bool enabled)
	{
		m_enabled = enabled;
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
	
	bool IsEnabled()
	{
		return m_enabled;
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
		return "TerjeCore/Layouts/TerjeWidgetButton.layout";
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
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if ((m_buttonActor != null) && (w == m_buttonActor) && (button == 0))
		{
			PushCommand(new TerjeWidgetCommand_Clicked(button));
			return true;
		}
		
		return super.OnClick(w, x, y, button);
	}
}

class TerjeWidgetCommand_Clicked : TerjeWidgetCommand
{
	int m_button;
	
	void TerjeWidgetCommand_Clicked(int button)
	{
		m_button = button;
	}
}

class TerjeWidgetCommand_Enabled : TerjeWidgetCommand
{
	bool m_enabled;
	
	void TerjeWidgetCommand_Enabled(bool enabled)
	{
		m_enabled = enabled;
	}
}