// <copyright file="TerjeWidgetHeaderPanel.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetHeaderPanel : TerjeWidgetBase
{
	protected TextWidget m_widgetHeaderText;
	protected Widget m_widgetHeaderBody;
	protected Widget m_widgetContent;
	
	override void OnInit()
	{
		super.OnInit();
		m_widgetHeaderText = TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetHeaderText"));
		m_widgetHeaderBody = GetNativeWidget().FindAnyWidget("TerjeWidgetHeaderBody");
		m_widgetContent = GetNativeWidget().FindAnyWidget("TerjeWidgetContent");
		RecalculateLayout();
	}
	
	void SetHeaderText(string text)
	{
		PushCommand(new TerjeWidgetCommand_Text(text));
	}
	
	void SetHeaderTextImmediately(string text)
	{
		m_widgetHeaderText.SetText(text);
	}
	
	void RecalculateLayout()
	{
		PushPostCommand(new TerjeWidgetCommand_HeaderPanelRecalc());
	}
	
	void RecalculateLayoutImmediately()
	{
		m_widgetContent.Update();
		GetNativeWidget().Update();
	}
	
	TerjeWidgetBase CreateContentWidget(typename name)
	{
		return CreateTerjeWidgetEx(name, m_widgetContent);
	}
	
	TerjeWidgetBase CreateHeaderWidget(typename name)
	{
		return CreateTerjeWidgetEx(name, m_widgetHeaderBody);
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_Text))
		{
			SetHeaderTextImmediately(TerjeWidgetCommand_Text.Cast(command).m_text);
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_HeaderPanelRecalc))
		{
			RecalculateLayoutImmediately();
			return;
		}
	}
}

class TerjeWidgetCommand_HeaderPanelRecalc : TerjeWidgetCommand
{
}

class TerjeWidgetPrimaryHeaderPanel : TerjeWidgetHeaderPanel
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetPrimaryHeaderPanel.layout";
	}
}

class TerjeWidgetSecondaryHeaderPanel : TerjeWidgetHeaderPanel
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetSecondaryHeaderPanel.layout";
	}
}