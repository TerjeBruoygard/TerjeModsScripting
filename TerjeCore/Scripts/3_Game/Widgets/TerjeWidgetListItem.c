// <copyright file="TerjeWidgetListItem.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetListItem : TerjeWidgetBase
{
	protected Widget m_widgetBackground;
	protected Widget m_widgetContent;
	protected Widget m_widgetActor;
	protected string m_itemId;
	protected bool m_selected;
	
	// void ScriptInvoker(TerjeWidgetListItem)
	ref ScriptInvoker OnClickEvent = new ScriptInvoker;
	
	override void OnInit()
	{
		super.OnInit();
		m_widgetBackground = GetNativeWidget().FindAnyWidget("TerjeListItemBac");
		m_widgetContent = GetNativeWidget().FindAnyWidget("TerjeListItemContent");
		m_widgetActor = GetNativeWidget().FindAnyWidget("TerjeListItemBtn");
		m_selected = false;
	}

	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetListItem.layout";
	}
	
	TerjeWidgetBase CreateChildWidget(typename name)
	{
		return CreateTerjeWidgetEx(name, m_widgetContent);
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_ListItemSelect))
		{
			SetSelectedImmediately(TerjeWidgetCommand_ListItemSelect.Cast(command).m_state);
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_Clicked))
		{
			OnClickEvent.Invoke(this);
			return;
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if ((m_widgetActor != null) && (w == m_widgetActor) && (button == 0))
		{
			PushCommand(new TerjeWidgetCommand_Clicked(button));
			return true;
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	void SetSelected(bool state)
	{
		m_selected = state;
		PushCommand(new TerjeWidgetCommand_ListItemSelect(state));
	}
	
	void SetSelectedImmediately(bool state)
	{
		m_selected = state;
		
		if (state)
		{
			m_widgetBackground.SetColor(ARGB(255, 145, 18, 18));
			m_widgetActor.SetColor(ARGB(80, 0, 0, 0));
		}
		else
		{
			m_widgetBackground.SetColor(ARGB(255, 10, 10, 10));
			m_widgetActor.SetColor(ARGB(80, 0, 0, 0));
		}
	}
	
	bool IsSelected()
	{
		return m_selected;
	}
	
	void SetItemId(string id)
	{
		m_itemId = id;
	}
	
	string GetItemId()
	{
		return m_itemId;
	}
	
	void ForceItemResizeImmediately()
	{
		float dummy;
		float contentWidth;
		float contentHeight;
		GetNativeWidget().GetSize(contentWidth, dummy);
		m_widgetContent.Update();
		m_widgetContent.GetScreenSize(dummy, contentHeight);
		GetNativeWidget().SetSize(contentWidth, contentHeight);
	}
}

class TerjeWidgetCommand_ListItemSelect : TerjeWidgetCommand
{
	bool m_state;
	
	void TerjeWidgetCommand_ListItemSelect(bool state)
	{
		m_state = state;
	}
}