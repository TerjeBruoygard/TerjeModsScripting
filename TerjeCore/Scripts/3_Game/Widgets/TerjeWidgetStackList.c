// <copyright file="TerjeWidgetStackList.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetStackList : TerjeWidgetBase
{
	protected bool m_allowMultipleSelection;
	
	// void ScriptInvoker(TerjeWidgetStackList, TerjeWidgetListItem, bool)
	ref ScriptInvoker OnItemSelectedEvent = new ScriptInvoker;
	
	override void OnCreate(Widget parent)
	{
		super.OnCreate(parent);
		m_allowMultipleSelection = false;
	}
	
	override void OnInit()
	{
		super.OnInit();
		RecalculateLayout();
	}
	
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetStackArea.layout";
	}
	
	void RecalculateLayout()
	{
		PushPostCommand(new TerjeWidgetCommand_ListRecalc());
	}
	
	void AllowMultipleSelections(bool value)
	{
		m_allowMultipleSelection = value;
	}
	
	void RecalculateLayoutImmediately()
	{
		for (int i = 0; i < GetChildrenCount(); i++)
		{
			TerjeWidgetListItem iterWidget = TerjeWidgetListItem.Cast(GetChild(i));
			if (iterWidget != null)
			{
				iterWidget.ForceItemResizeImmediately();
			}
		}
		
		GetNativeWidget().Update();
	}
	
	TerjeWidgetListItem CreateItemWidget(string id, bool selected = false)
	{
		TerjeWidgetListItem itemWidget = TerjeWidgetListItem.Cast(CreateTerjeWidget(TerjeWidgetListItem));
		itemWidget.SetItemId(id);
		itemWidget.SetSelected(false);
		itemWidget.OnClickEvent.Insert(OnListItemClick);
		
		if (selected)
		{
			OnListItemClick(itemWidget);
		}
		
		return itemWidget;
	}
	
	void SelectItem(string id)
	{
		for (int i = 0; i < GetChildrenCount(); i++)
		{
			TerjeWidgetListItem iterWidget = TerjeWidgetListItem.Cast(GetChild(i));
			if (iterWidget != null && iterWidget.GetItemId() == id)
			{
				OnListItemClick(iterWidget);
				return;
			}
		}
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_ListRecalc))
		{
			RecalculateLayoutImmediately();
			return;
		}
	}
	
	protected void OnListItemClick(TerjeWidgetListItem w)
	{
		bool state;
		if (m_allowMultipleSelection)
		{
			state = !w.IsSelected();
			w.SetSelected(state);
			OnItemSelectedEvent.Invoke(this, w, state);
		}
		else
		{
			for (int i = 0; i < GetChildrenCount(); i++)
			{
				TerjeWidgetListItem iterWidget = TerjeWidgetListItem.Cast(GetChild(i));
				if (iterWidget != null)
				{
					state = (iterWidget == w);
					if (state != iterWidget.IsSelected())
					{
						iterWidget.SetSelected(state);
						OnItemSelectedEvent.Invoke(this, iterWidget, state);
					}
				}
			}
		}
	}
}