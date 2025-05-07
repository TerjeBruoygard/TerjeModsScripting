// <copyright file="TerjeWidgetMultitab.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetMultitab : TerjeWidgetBase
{
	private ref map<string, int> m_terjeTabs = new map<string, int>;
	
	int GetTabsCount()
	{
		return m_terjeTabs.Count();
	}
	
	TerjeWidgetTab CreateTabWidget(string name)
	{
		int id = GetChildrenCount();
		TerjeWidgetTab tab = TerjeWidgetTab.Cast(CreateTerjeWidget(TerjeWidgetTab));
		if (tab != null)
		{
			if (id == 0)
			{
				tab.Show(true);
			}
			else
			{
				tab.Show(false);
			}
			
			tab.SetTabMetadata(name, id);
			m_terjeTabs.Insert(name, id);
		}
		
		return tab;
	}
	
	TerjeWidgetBase CreateTabWidgetEx(string name, typename content)
	{
		return CreateTabWidget(name).CreateContentWidget(content);
	}
	
	void SelectTabByName(string name)
	{
		foreach (string tabName, int tabId : m_terjeTabs)
		{
			TerjeWidgetTab tab = TerjeWidgetTab.Cast(GetChild(tabId));
			if (tab != null)
			{
				if (tabName == name)
				{
					tab.Show(true);
				}
				else
				{
					tab.Show(false);
				}
			}
		}
	}
	
	void SelectTabById(int id)
	{
		for (int i = 0; i < GetChildrenCount(); i++)
		{
			TerjeWidgetTab tab = TerjeWidgetTab.Cast(GetChild(i));
			if (tab != null)
			{
				if (i == id)
				{
					tab.Show(true);
				}
				else
				{
					tab.Show(false);
				}
			}
		}
	}
	
	TerjeWidgetTab GetTabById(int id)
	{
		return TerjeWidgetTab.Cast(GetChild(id));
	}
	
	TerjeWidgetTab GetTabByName(string name)
	{
		int tabId;
		if (m_terjeTabs.Find(name, tabId))
		{
			return TerjeWidgetTab.Cast(GetChild(tabId));
		}
		
		return null;
	}
	
	TerjeWidgetBase GetContentByName(string name)
	{
		int tabId;
		if (m_terjeTabs.Find(name, tabId))
		{
			TerjeWidgetTab tabWidget = TerjeWidgetTab.Cast(GetChild(tabId));
			if (tabWidget.GetChildrenCount() > 0)
			{
				return tabWidget.GetChild(0);
			}
		}
		
		return null;
	}
	
	override void DestroyAllChildren()
	{
		m_terjeTabs.Clear();
		super.DestroyAllChildren();
	}
}