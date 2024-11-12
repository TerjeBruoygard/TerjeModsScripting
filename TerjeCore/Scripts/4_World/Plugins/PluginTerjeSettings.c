// <copyright file="PluginTerjeSettings.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeSettings extends PluginBase
{	
	private const string SETTINGS_DIR = "$profile:TerjeSettings";
	private ref TerjeSettingsCollection m_settingsCollection = new TerjeSettingsCollection;
	
	ref TerjeSettingsCollection GetSettingsCollection()
	{
		return m_settingsCollection;
	}
	
	override void OnInit()
	{
		m_settingsCollection.OnInit();
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void SendSettingsToClient(PlayerIdentity identity)
	{
		GetTerjeRPC().SendToClient("core.settings", identity, new Param1<ref array<ref TerjeSettingSynch>>(GetSettingsCollection().GetSynchSettings()));
	}
	
	private void OnReceiveClientSettings(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param1<ref array<ref TerjeSettingSynch>> clientData;
		if (!ctx.Read(clientData ))
		{
			return;
		}
		
		GetSettingsCollection().ApplySynchSettings(clientData.param1);
	}
	
};

ref PluginTerjeSettings GetTerjeSettingsPlugin()
{
	return PluginTerjeSettings.Cast(GetPlugin(PluginTerjeSettings));
};

string GetTerjeSettingString(int id)
{
	string result;
	if (GetTerjeSettingString(id, result))
	{
		return result;
	}
	
	return "";
};

bool GetTerjeSettingString(int id, out string result)
{
	ref TerjeSettingValueBase setting = GetTerjeSettingsPlugin().GetSettingsCollection().Get(id);
	if (setting != null)
	{
		TerjeSettingValueString strSetting = TerjeSettingValueString.Cast(setting);
		if (strSetting != null)
		{
			if (GetGame().IsDedicatedServer() || !strSetting.IsServerSideOnly())
			{
				result = strSetting.GetValue();
				return true;
			}
		}
	}
	
	result = "";
	return false;
};

int GetTerjeSettingInt(int id)
{
	int result;
	if (GetTerjeSettingInt(id, result))
	{
		return result;
	}
	
	return 0;
};

bool GetTerjeSettingInt(int id, out int result)
{
	ref TerjeSettingValueBase setting = GetTerjeSettingsPlugin().GetSettingsCollection().Get(id);
	if (setting != null)
	{
		TerjeSettingValueInt intSetting = TerjeSettingValueInt.Cast(setting);
		if (intSetting != null)
		{
			if (GetGame().IsDedicatedServer() || !intSetting.IsServerSideOnly())
			{
				result = intSetting.GetValue();
				return true;
			}
		}
	}
	
	result = 0;
	return false;
};

float GetTerjeSettingFloat(int id)
{
	float result;
	if (GetTerjeSettingFloat(id, result))
	{
		return result;
	}
	
	return 0;
};

bool GetTerjeSettingFloat(int id, out float result)
{
	ref TerjeSettingValueBase setting = GetTerjeSettingsPlugin().GetSettingsCollection().Get(id);
	if (setting != null)
	{
		TerjeSettingValueFloat floatSetting = TerjeSettingValueFloat.Cast(setting);
		if (floatSetting != null)
		{
			if (GetGame().IsDedicatedServer() || !floatSetting.IsServerSideOnly())
			{
				result = floatSetting.GetValue();
				return true;
			}
		}
	}
	
	result = 0;
	return false;
};

bool GetTerjeSettingBool(int id)
{
	bool result;
	if (GetTerjeSettingBool(id, result))
	{
		return result;
	}
	
	return false;
};

bool GetTerjeSettingBool(int id, out bool result)
{
	ref TerjeSettingValueBase setting = GetTerjeSettingsPlugin().GetSettingsCollection().Get(id);
	if (setting != null)
	{
		TerjeSettingValueBool boolSetting = TerjeSettingValueBool.Cast(setting);
		if (boolSetting != null)
		{
			if (GetGame().IsDedicatedServer() || !boolSetting.IsServerSideOnly())
			{
				result = boolSetting.GetValue();
				return true;
			}
		}
	}
	
	result = false;
	return false;
};

class TerjeSettingsCollection
{
	private ref array<ref TerjeSettingValueBase> m_ordered = new array<ref TerjeSettingValueBase>;
	private ref map<string, ref TerjeSettingValueBase> m_collection = new map<string, ref TerjeSettingValueBase>;
	private ref set<string> m_categories = new set<string>;
	private ref array<ref TerjeSettingSynch> m_synch = null;
	private bool m_ready = false;
	
	static int CORE_DATABASE_AUTOSAVE_INTERVAL;
	static int CORE_PROFILE_SYNCH_INTERVAL;
	static int CORE_STATS_SYNCH_INTERVAL;
	
	void OnInit()
	{
		// Override this method in your mod to register new settings.
		CORE_DATABASE_AUTOSAVE_INTERVAL = RegisterSettingFloat("Core.DatabaseAutosaveInterval", "Core", "Once in a specified time, checks all player profiles for changes and, if necessary, saves them to disk. (in seconds)", 300, true);
		CORE_PROFILE_SYNCH_INTERVAL = RegisterSettingFloat("Core.ProfileSynchInterval", "Core", "Once in a specified time, checks all player profiles for changes and, if necessary, send them to client side. (in seconds)", 1, true);
		CORE_STATS_SYNCH_INTERVAL = RegisterSettingFloat("Core.StatsSynchInterval", "Core", "Once in a specified time, checks all player stats for changes and, if necessary, sync them with client side. (in seconds)", 0.2, true);
	}
	
	protected void RegisterRegion(string category, string description)
	{
		m_ordered.Insert(new TerjeSettingRegion("[REGION]", category, description, true));
	}
	
	protected int RegisterSettingString(string name, string category, string description, string value, bool serverSideOnly)
	{
		ref TerjeSettingValueString setting = new TerjeSettingValueString(name, category, description, serverSideOnly);
		setting.SetValue(value);
		m_collection.Insert(name, setting);
		m_categories.Insert(category);
		return m_ordered.Insert(setting);
	}
	
	protected int RegisterSettingFloat(string name, string category, string description, float value, bool serverSideOnly)
	{
		ref TerjeSettingValueFloat setting = new TerjeSettingValueFloat(name, category, description, serverSideOnly);
		setting.SetValue(value);
		m_collection.Insert(name, setting);
		m_categories.Insert(category);
		return m_ordered.Insert(setting);
	}
	
	protected int RegisterSettingInt(string name, string category, string description, int value, bool serverSideOnly)
	{
		ref TerjeSettingValueInt setting = new TerjeSettingValueInt(name, category, description, serverSideOnly);
		setting.SetValue(value);
		m_collection.Insert(name, setting);
		m_categories.Insert(category);
		return m_ordered.Insert(setting);
	}
	
	protected int RegisterSettingBool(string name, string category, string description, bool value, bool serverSideOnly)
	{
		ref TerjeSettingValueBool setting = new TerjeSettingValueBool(name, category, description, serverSideOnly);
		setting.SetValue(value);
		m_collection.Insert(name, setting);
		m_categories.Insert(category);
		return m_ordered.Insert(setting);
	}
	
	void GetCategories(set<string> categories)
	{
		categories.Copy(m_categories);
	}
	
	void GetSettings(array<ref TerjeSettingValueBase> settings)
	{
		foreach (ref TerjeSettingValueBase setting : m_ordered)
		{
			settings.Insert(setting);
		}
	}
	
	ref array<ref TerjeSettingSynch> GetSynchSettings()
	{
		if (m_synch == null)
		{
			m_synch = new array<ref TerjeSettingSynch>;
			foreach (ref TerjeSettingValueBase setting : m_ordered)
			{
				if (!setting.IsServerSideOnly())
				{
					m_synch.Insert(setting.ToTerjeSettingSynch());
				}
			}
		}
		
		return m_synch;
	}
	
	void ApplySynchSettings(ref array<ref TerjeSettingSynch> settings)
	{
		ref TerjeSettingValueBase settingValue;
		foreach (ref TerjeSettingSynch synchData : settings)
		{
			if (m_collection.Find(synchData.m_name, settingValue))
			{
				settingValue.FromConfigValue(synchData.m_value);
			}
		}
		
		m_ready = true;
		TerjeLog_Info("All settings successfully syncronized with client (" + settings.Count() + ")");
	}
	
	bool Find(string name, out TerjeSettingValueBase result)
	{
		if (!GetGame().IsDedicatedServer() && !m_ready)
		{
			return false;
		}
		
		if (!m_collection.Find(name, result))
		{
			return false;
		}
		
		if (!GetGame().IsDedicatedServer() && result.IsServerSideOnly())
		{
			return false;
		}
		
		return true;
	}
	
	ref TerjeSettingValueBase Get(int id)
	{
		if (!GetGame().IsDedicatedServer() && !m_ready)
		{
			return null;
		}
		
		ref TerjeSettingValueBase result = m_ordered.Get(id);
		if (!GetGame().IsDedicatedServer() && result.IsServerSideOnly())
		{
			return null;
		}
		
		return result;
	}
};

class TerjeSettingSynch
{
	string m_name;
	string m_value;
	
	void TerjeSettingSynch(string name, string value)
	{
		m_name = name;
		m_value = value;
	}
};

class TerjeSettingValueBase
{
	private string m_name;
	private string m_category;
	private string m_description;
	private bool m_serverSideOnly;
	
	void TerjeSettingValueBase(string name, string category, string description, bool serverSideOnly)
	{
		m_name = name;
		m_category = category;
		m_description = description;
		m_serverSideOnly = serverSideOnly;
	}

	string GetName()
	{
		return m_name;
	}
	
	string GetCategory()
	{
		return m_category;
	}
	
	string GetDescription()
	{
		return m_description;
	}
	
	bool IsServerSideOnly()
	{
		return m_serverSideOnly;
	}
	
	string GetValueStr()
	{
		return "NULL";
	}
	
	string ToConfigStr()
	{
		return GetName() + " = " + GetValueStr() + "; // " + GetDescription();
	}
	
	void FromConfigValue(string value)
	{
	
	}
	
	ref TerjeSettingSynch ToTerjeSettingSynch()
	{
		return new TerjeSettingSynch(GetName(), GetValueStr());
	}
};

class TerjeSettingRegion extends TerjeSettingValueBase
{
	void SetValue(string value)
	{

	}
	
	string GetValue()
	{
		return "";
	}
	
	override string GetValueStr()
	{
		return "";
	}
	
	override void FromConfigValue(string value)
	{
		
	}
};

class TerjeSettingValueString extends TerjeSettingValueBase
{
	private string m_value;
	
	void SetValue(string value)
	{
		m_value = value;
	}
	
	string GetValue()
	{
		return m_value;
	}
	
	override string GetValueStr()
	{
		return "\"" + GetValue() + "\"";
	}
	
	override void FromConfigValue(string value)
	{
		value = value.Trim();
		if (value.Length() < 2 || value.Get(0) != "\"" || value.Get(value.Length() - 1) != "\"")
		{
			TerjeLog_Error("Failed to parse setting '" + GetName() + "'.");
			return;
		}
		
		SetValue(value.Substring(1, value.Length() - 2));
	}
};

class TerjeSettingValueInt extends TerjeSettingValueBase
{
	private int m_value;
	
	void SetValue(int value)
	{
		m_value = value;
	}
	
	int GetValue()
	{
		return m_value;
	}
	
	override string GetValueStr()
	{
		return GetValue().ToString();
	}
	
	override void FromConfigValue(string value)
	{
		SetValue(value.Trim().ToInt());
	}
};

class TerjeSettingValueFloat extends TerjeSettingValueBase
{
	private float m_value;
	
	void SetValue(float value)
	{
		m_value = value;
	}
	
	float GetValue()
	{
		return m_value;
	}
	
	override string GetValueStr()
	{
		return GetValue().ToString();
	}
	
	override void FromConfigValue(string value)
	{
		SetValue(value.Trim().ToFloat());
	}
};

class TerjeSettingValueBool extends TerjeSettingValueBase
{
	private bool m_value;
	
	void SetValue(bool value)
	{
		m_value = value;
	}
	
	bool GetValue()
	{
		return m_value;
	}
	
	override string GetValueStr()
	{
		if (GetValue())
		{
			return "true";
		}
		
		return "false";
	}
	
	override void FromConfigValue(string value)
	{
		value = value.Trim();
		value.ToLower();
		SetValue(value == "true");
	}
};
