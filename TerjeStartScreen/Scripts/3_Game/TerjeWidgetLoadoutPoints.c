// <copyright file="TerjeWidgetLoadoutPoints.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetLoadoutPoints : TerjeWidgetBase
{
	protected ImageWidget m_iconWidget;
	protected TextWidget m_textWidget;
	
	override void OnInit()
	{
		super.OnInit();
		m_iconWidget = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetPointsImage"));
		m_textWidget = TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetPointsText"));
	}
	
	void SetPointsData(string icon, int count)
	{
		PushCommand(new TerjeWidgetCommand_SetLoadoutItemPoints(icon, count));
	}
	
	void SetPointsDataImmediately(string icon, int count)
	{
		if (icon != string.Empty)
		{
			m_iconWidget.LoadImageFile(0, icon);
		}
		
		int color = ARGB(255, 255, 255, 255);
		if (count <= 0)
		{
			color = ARGB(255, 255, 0, 0);
		}
		
		m_iconWidget.SetColor(color);
		m_textWidget.SetColor(color);
		m_textWidget.SetText(count.ToString());
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/ItemLoadoutPoints.layout";
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_SetLoadoutItemPoints))
		{
			TerjeWidgetCommand_SetLoadoutItemPoints pointsCmd = TerjeWidgetCommand_SetLoadoutItemPoints.Cast(command);
			SetPointsDataImmediately(pointsCmd.m_icon, pointsCmd.m_count);
			return;
		}
	}
}

class TerjeWidgetCommand_SetLoadoutItemPoints : TerjeWidgetCommand
{
	string m_icon;
	int m_count;
	
	void TerjeWidgetCommand_SetLoadoutItemPoints(string icon, int count)
	{
		m_icon = icon;
		m_count = count;
	}
}