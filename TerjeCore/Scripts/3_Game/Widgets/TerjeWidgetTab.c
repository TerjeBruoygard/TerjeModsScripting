// <copyright file="TerjeWidgetTab.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetTab : TerjeWidgetBase
{
	private string m_tabName;
	private int m_tabId;
	
	void SetTabMetadata(string name, int id)
	{
		m_tabName = name;
		m_tabId = id;
	}
	
	string GetTabName()
	{
		return m_tabName;
	}
	
	int GetTabId()
	{
		return m_tabId;
	}
	
	TerjeWidgetBase CreateContentWidget(typename name)
	{
		return CreateTerjeWidget(name);
	}
}