// <copyright file="PluginTerjeClientItemsCore.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeClientItemsCore : PluginBase 
{
	private int m_currentIndex = int.MIN;
	private float m_currentUpdateTimer = 0;
	private ref map<int, ItemBase> m_updatableClientItems;
	
	override void OnInit()
	{
		super.OnInit();
		m_updatableClientItems = new map<int, ItemBase>;
	}
	
	override void OnUpdate(float delta_time)
	{
		super.OnUpdate(delta_time);
		
		m_currentUpdateTimer += delta_time;
		if (m_currentUpdateTimer >= 1)
		{
			foreach (int index, ItemBase item : m_updatableClientItems)
			{
				item.OnTerjeClientUpdate(m_currentUpdateTimer);
			}
			
			m_currentUpdateTimer = 0;
		}
	}
	
	override void OnDestroy()
	{
		super.OnDestroy();
		m_updatableClientItems.Clear();
	}
	
	int RegisterItem(ItemBase item)
	{
		m_currentIndex = m_currentIndex + 1;
		m_updatableClientItems.Insert(m_currentIndex, item);
		return m_currentIndex;
	}
	
	void UnregisterItem(int index)
	{
		m_updatableClientItems.Remove(index);
	}
}

PluginTerjeClientItemsCore GetTerjeClientItemsCore() 
{
	return PluginTerjeClientItemsCore.Cast(GetPlugin(PluginTerjeClientItemsCore));
}