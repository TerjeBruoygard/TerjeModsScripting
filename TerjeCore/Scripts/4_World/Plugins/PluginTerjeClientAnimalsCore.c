// <copyright file="PluginTerjeClientAnimalsCore.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeClientAnimalsCore : PluginBase 
{
	private int m_currentIndex = int.MIN;
	private float m_currentUpdateTimer = 0;
	private ref map<int, AnimalBase> m_updatableClientAnimals;
	
	override void OnInit()
	{
		super.OnInit();
		m_updatableClientAnimals = new map<int, AnimalBase>;
	}
	
	override void OnUpdate(float delta_time)
	{
		super.OnUpdate(delta_time);
		
		m_currentUpdateTimer += delta_time;
		if (m_currentUpdateTimer >= 1)
		{
			foreach (int index, AnimalBase animal : m_updatableClientAnimals)
			{
				animal.OnTerjeClientUpdate(m_currentUpdateTimer);
			}
			
			m_currentUpdateTimer = 0;
		}
	}
	
	override void OnDestroy()
	{
		super.OnDestroy();
		m_updatableClientAnimals.Clear();
	}
	
	int RegisterAnimal(AnimalBase animal)
	{
		m_currentIndex = m_currentIndex + 1;
		m_updatableClientAnimals.Insert(m_currentIndex, animal);
		return m_currentIndex;
	}
	
	void UnregisterAnimal(int index)
	{
		m_updatableClientAnimals.Remove(index);
	}
}

PluginTerjeClientAnimalsCore GetTerjeClientAnimalsCore() 
{
	return PluginTerjeClientAnimalsCore.Cast(GetPlugin(PluginTerjeClientAnimalsCore));
}