// <copyright file="TerjeScriptedWidget.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeScriptedWidget : ScriptedWidgetEventHandler
{	
	protected Widget m_Root;
	protected ref array<ref TerjeWidgetBase> m_terjeWidgets = new array<ref TerjeWidgetBase>;

	void TerjeScriptedWidget(Widget parent)
	{
		OnCreate(parent);
		OnInit();
		OnUpdate(0);
	}
	
	protected void OnCreate(Widget parent)
	{
		m_Root = GetGame().GetWorkspace().CreateWidgets(GetNativeLayout(), parent);
		if (m_Root != null)
		{
			string backgroundImage = GetBackgroundImage();
			if (backgroundImage != string.Empty)
			{
				ImageWidget.Cast(m_Root).LoadImageFile(0, backgroundImage);
			}
			
			m_Root.SetColor(GetBackgroundColor());
			m_Root.SetHandler(this);
		}
	}
	
	protected void OnInit()
	{
	
	}
	
	string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeScriptedMenu.layout";
	}
	
	Widget GetNativeWidget()
	{
		return m_Root;
	}
	
	protected int GetBackgroundColor()
	{
		return ARGB(0, 0, 0, 0);
	}
	
	protected string GetBackgroundImage()
	{
		return "";
	}
	
	protected TerjeWidgetBase CreateTerjeWidget(typename name)
	{
		ref TerjeWidgetBase widget = TerjeWidgetBase.Cast(name.Spawn());
		if (widget)
		{
			widget.OnCreate(GetNativeWidget());
			widget.OnInit();
			m_terjeWidgets.Insert(widget);
			return widget;
		}
		
		TerjeLog_Error("Failed to crate terje widget: " + name.ToString());
		return null;
	}
	
	protected void DestroyAllChildren()
	{
		foreach (TerjeWidgetBase child : m_terjeWidgets)
		{
			if (child && child.GetNativeWidget())
			{
				child.GetNativeWidget().Unlink();
			}
		}
		
		m_terjeWidgets.Clear();
	}
	
	protected void DestroyTerjeWidget(TerjeWidgetBase widget)
	{
		if (widget)
		{
			int index = m_terjeWidgets.Find(widget);
			if (index != -1)
			{
				m_terjeWidgets.Remove(index);
				if (widget.GetNativeWidget())
				{
					widget.GetNativeWidget().Unlink();
				}
			}
		}
	}
	
	void OnUpdate(float timeslice)
	{
		foreach (ref TerjeWidgetBase tw : m_terjeWidgets)
		{
			if (tw != null)
			{
				tw.OnUpdate(timeslice);
			}
		}
	}
}