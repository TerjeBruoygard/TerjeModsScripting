// <copyright file="DayZGame.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class DayZGame
{
	ref set<int> m_terjePressedKeys = new set<int>;
	ref ScriptInvoker TerjeKeyPressedEvent = new ScriptInvoker;
	
	protected void OnTerjeSynchSettingsFromServer(ParamsReadContext ctx)
	{
		GetTerjeGameConfig().OnReceiveClientSettings(ctx);
		GetTerjeSettingsSynchContext().OnReceiveClientSettings(ctx);
	}
	
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		if (m_terjePressedKeys.Find(key) == -1)
		{
			m_terjePressedKeys.Insert(key);
		}
	}
	
	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
	
		int keyIndex = m_terjePressedKeys.Find(key);
		if (keyIndex != -1)
		{
			m_terjePressedKeys.Remove(keyIndex);
			TerjeKeyPressedEvent.Invoke(key);
		}
	}
	
	bool IsTerjeKeyPressed(int key)
	{
		return (m_terjePressedKeys.Find(key) != -1);
	}
}