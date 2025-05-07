// <copyright file="TerjeWidgetScrollArea.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetScrollArea : TerjeWidgetBase
{
	protected Widget m_contentWidget;
	
	override void OnCreate(Widget parent)
	{
		super.OnCreate(parent);
		m_contentWidget = GetNativeWidget().FindAnyWidget("TerjeWidgetGrid");
	}
	
	override void OnInit()
	{
		super.OnInit();
		RecalculateLayout();
	}
	
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetScrollArea.layout";
	}
	
	float GetContentAreaWidth()
	{
		return ScrollWidget.Cast(GetNativeWidget()).GetContentWidth();
	}
	
	void RecalculateLayout()
	{
		PushPostCommand(new TerjeWidgetCommand_ScrollAreaRecalc());
	}
	
	void RecalculateLayoutImmediately()
	{
		m_contentWidget.Update();
	}
	
	void Clear()
	{
		DestroyAllChildren();
	}
	
	TerjeWidgetBase CreateChildWidget(typename name)
	{
		return CreateTerjeWidgetEx(name, m_contentWidget);
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_ScrollAreaRecalc))
		{
			RecalculateLayoutImmediately();
			return;
		}
	}
}

class TerjeWidgetCommand_ScrollAreaRecalc : TerjeWidgetCommand
{
}