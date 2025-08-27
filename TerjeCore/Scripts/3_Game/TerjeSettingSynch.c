// <copyright file="TerjeSettingSynch.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSettingsSynch
{
	protected ref array<ref TerjeSettingSynch> m_settings = new array<ref TerjeSettingSynch>;
	
	void OnReceiveClientSettings(ParamsReadContext ctx)
	{
		Reset();
		ctx.Read(m_settings);
	}
	
	void Reset()
	{
		m_settings.Clear();
	}
	
	array<ref TerjeSettingSynch> GetData()
	{
		return m_settings;
	}
}

class TerjeSettingSynch
{
	string m_name;
	string m_value;
	
	void TerjeSettingSynch(string name, string value)
	{
		m_name = name;
		m_value = value;
	}
}

TerjeSettingsSynch GetTerjeSettingsSynchContext()
{
	/*
	 This code block is private and was hidden before publishing on github.
	 
	 This repository does not provide full code of our mods need to be fully functional.
	 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
	 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
	 Copyright (c) TerjeMods. All rights reserved.
	*/
}