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
	
	ref ScriptInvoker m_eventOnSettingsSync = new ScriptInvoker;
	
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
		
		m_eventOnSettingsSync.Invoke();
	}
	
}

ref PluginTerjeSettings GetTerjeSettingsPlugin()
{
	return PluginTerjeSettings.Cast(GetPlugin(PluginTerjeSettings));
}

string GetTerjeSettingString(int id)
{
	string result;
	if (GetTerjeSettingString(id, result))
	{
		return result;
	}
	
	return "";
}

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
}

int GetTerjeSettingInt(int id)
{
	int result;
	if (GetTerjeSettingInt(id, result))
	{
		return result;
	}
	
	return 0;
}

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
}

float GetTerjeSettingFloat(int id)
{
	float result;
	if (GetTerjeSettingFloat(id, result))
	{
		return result;
	}
	
	return 0;
}

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
}

bool GetTerjeSettingBool(int id)
{
	bool result;
	if (GetTerjeSettingBool(id, result))
	{
		return result;
	}
	
	return false;
}

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
}

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
	static int CORE_SAT_BINARY_TREE_GRID_SIZE;
	static int CORE_WATER_DRAIN_FROM_VOMIT;
	static int CORE_ENERGY_DRAIN_FROM_VOMIT;
	static int CORE_COLORIZED_HUD_BADGES;
	static int CORE_DETAILED_DISEASE_HUD_BADGES;
	static int CORE_DETAILED_HEALING_HUD_BADGES;
	static int CORE_USE_CUSTOM_PROTECTION_CONFIGS;
	
	void OnInit()
	{
		// Override this method in your mod to register new settings.
		CORE_DATABASE_AUTOSAVE_INTERVAL = RegisterSettingFloat("Core.DatabaseAutosaveInterval", "Core", "Once in a specified time, checks all player profiles for changes and, if necessary, saves them to disk. (in seconds)", 300, true);
		CORE_PROFILE_SYNCH_INTERVAL = RegisterSettingFloat("Core.ProfileSynchInterval", "Core", "Once in a specified time, checks all player profiles for changes and, if necessary, send them to client side. (in seconds)", 1, true);
		CORE_STATS_SYNCH_INTERVAL = RegisterSettingFloat("Core.StatsSynchInterval", "Core", "Once in a specified time, checks all player stats for changes and, if necessary, sync them with client side. (in seconds)", 0.2, true);
		CORE_SAT_BINARY_TREE_GRID_SIZE = RegisterSettingInt("Core.SatBinaryTreeGridSize", "Core", "Sets the grid size of the binary search tree binary grid for intersecting scriptable areas. Do not change this value unnecessarily. If there are more than 10k scriptable areas on the server, it is recommended to change this value to 500 or 100 to improve performance. Otherwise it will have no effect or even degrade server performance.", 1000, true);
		CORE_WATER_DRAIN_FROM_VOMIT = RegisterSettingFloat("Core.WaterDrainFromVomit", "Core", "The value of water units that a player will lose when vomiting.", 70, true);
		CORE_ENERGY_DRAIN_FROM_VOMIT = RegisterSettingFloat("Core.EnergyDrainFromVomit", "Core", "The value of energy units that a player will lose when vomiting.", 55, true);
		CORE_COLORIZED_HUD_BADGES = RegisterSettingBool("Core.ColorizedHudBadges", "Core", "Badges on the status bar will have different colors depending on the severity level to make it easier to identify illnesses.", true, false);
		CORE_DETAILED_DISEASE_HUD_BADGES = RegisterSettingBool("Core.DetailedDiseaseHudBadges", "Core", "When this option is enabled, players will see separate detalized icons for each disease that affects them. When this option is disabled, players will see the standard disease icon.", true, false);
		CORE_DETAILED_HEALING_HUD_BADGES = RegisterSettingBool("Core.DetailedHealingHudBadges", "Core", "When this option is enabled, players will see separate icons for each medical drug that affects them (for casual servers). When this option is disabled, players will see the standard pill icon when any medical drug affects their body (for hardcore servers).", false, false);
		CORE_USE_CUSTOM_PROTECTION_CONFIGS = RegisterSettingBool("Core.UseCustomProtectionConfigs", "Core", "Enable this parameter to use additional configuration files are created in the 'TerjeSettings/CustomProtection' folder. Write in these files SteamIDs of players so that they have absolute protection from specific modded effects (radiation, for example).", false, true);
	}
	
	protected void RegisterRegion(string category, string description)
	{
		m_ordered.Insert(new TerjeSettingRegion("[REGION]", category, description, true));
	}
	
	protected int RegisterSettingString(string name, string category, string description, string value, bool serverSideOnly)
	{
		ref TerjeSettingValueString setting = new TerjeSettingValueString(name, category, description, serverSideOnly);
		setting.SetValue(value);
		setting.SetDefault(value);
		m_collection.Insert(name, setting);
		m_categories.Insert(category);
		return m_ordered.Insert(setting);
	}
	
	protected int RegisterSettingFloat(string name, string category, string description, float value, bool serverSideOnly)
	{
		ref TerjeSettingValueFloat setting = new TerjeSettingValueFloat(name, category, description, serverSideOnly);
		setting.SetValue(value);
		setting.SetDefault(value);
		m_collection.Insert(name, setting);
		m_categories.Insert(category);
		return m_ordered.Insert(setting);
	}
	
	protected int RegisterSettingInt(string name, string category, string description, int value, bool serverSideOnly)
	{
		ref TerjeSettingValueInt setting = new TerjeSettingValueInt(name, category, description, serverSideOnly);
		setting.SetValue(value);
		setting.SetDefault(value);
		m_collection.Insert(name, setting);
		m_categories.Insert(category);
		return m_ordered.Insert(setting);
	}
	
	protected int RegisterSettingBool(string name, string category, string description, bool value, bool serverSideOnly)
	{
		ref TerjeSettingValueBool setting = new TerjeSettingValueBool(name, category, description, serverSideOnly);
		setting.SetValue(value);
		setting.SetDefault(value);
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
				if (!setting.IsServerSideOnly() && setting.IsNonDefaultValue())
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

	string GetTypeStr()
	{
		return "NULL";
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
	
	bool IsNonDefaultValue()
	{
		return false;
	}
	
	string GetValueStr()
	{
		return "NULL";
	}
	
	string GetDefaultValueStr()
	{
		return "NULL";
	}
	
	string ToConfigStr()
	{
		string result = GetName() + " = " + GetValueStr() + "; ";
		while (result.Length() < 60)
		{
			result += " ";
		}
		
		return result + "/" + "/ [type: " + GetTypeStr() + "; default: " + GetDefaultValueStr() + "] " + GetDescription();
	}
	
	void FromConfigValue(string value)
	{
	
	}
	
	ref TerjeSettingSynch ToTerjeSettingSynch()
	{
		return new TerjeSettingSynch(GetName(), GetValueStr());
	}
}

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
	
	override string GetDefaultValueStr()
	{
		return "";
	}
	
	override void FromConfigValue(string value)
	{
		
	}
	
	override string GetTypeStr()
	{
		return "region";
	}
}

class TerjeSettingValueString extends TerjeSettingValueBase
{
	private string m_value;
	private string m_default;
	
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
	
	void SetDefault(string value)
	{
		m_default = value;
	}
	
	override string GetDefaultValueStr()
	{
		return "\"" + m_default + "\"";
	}
	
	override bool IsNonDefaultValue()
	{
		return m_default != m_value;
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
	
	override string GetTypeStr()
	{
		return "string";
	}
}

class TerjeSettingValueInt extends TerjeSettingValueBase
{
	private int m_value;
	private int m_default;
	
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
	
	void SetDefault(int value)
	{
		m_default = value;
	}
	
	override string GetDefaultValueStr()
	{
		return m_default.ToString();
	}
	
	override bool IsNonDefaultValue()
	{
		return m_default != m_value;
	}
	
	override void FromConfigValue(string value)
	{
		SetValue(value.Trim().ToInt());
	}
	
	override string GetTypeStr()
	{
		return "int";
	}
}

class TerjeSettingValueFloat extends TerjeSettingValueBase
{
	private float m_value;
	private float m_default;
	
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
	
	void SetDefault(float value)
	{
		m_default = value;
	}
	
	override string GetDefaultValueStr()
	{
		return m_default.ToString();
	}
	
	override bool IsNonDefaultValue()
	{
		return m_default != m_value;
	}
	
	override void FromConfigValue(string value)
	{
		SetValue(value.Trim().ToFloat());
	}
	
	override string GetTypeStr()
	{
		return "float";
	}
}

class TerjeSettingValueBool extends TerjeSettingValueBase
{
	private bool m_value;
	private bool m_default;
	
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
	
	void SetDefault(bool value)
	{
		m_default = value;
	}
	
	override string GetDefaultValueStr()
	{
		if (m_default)
		{
			return "true";
		}
		
		return "false";
	}
	
	override bool IsNonDefaultValue()
	{
		return m_default != m_value;
	}
	
	override void FromConfigValue(string value)
	{
		value = value.Trim();
		value.ToLower();
		SetValue(value == "true");
	}
	
	override string GetTypeStr()
	{
		return "bool";
	}
}
