// <copyright file="TerjeScriptableProtection.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeScriptableProtection
{
	private static ref TerjeScriptableProtection instance = null;
	
	static ref TerjeScriptableProtection GetInstance()
	{
		if (instance == null)
		{
			instance = new TerjeScriptableProtection();
			instance.OnInit();
		}
		
		return instance;
	}
	
	private ref map<string, ref map<string, ref TerjeScriptableProtectionEntry>> m_data;
	
	void OnInit()
	{
		m_data = new map<string, ref map<string, ref TerjeScriptableProtectionEntry>>;
		if (GetGame().ConfigIsExisting("CfgTerjeScriptableProtection"))
		{
			int protectionCount = GetGame().ConfigGetChildrenCount("CfgTerjeScriptableProtection");
			for (int protectionIndex = 0; protectionIndex < protectionCount; protectionIndex++)
			{
				string protectionClassName = "";
				if (GetGame().ConfigGetChildName("CfgTerjeScriptableProtection", protectionIndex, protectionClassName))
				{
					ref map<string, ref TerjeScriptableProtectionEntry> protectionParts;
					if (!m_data.Find(protectionClassName, protectionParts))
					{
						protectionParts = new map<string, ref TerjeScriptableProtectionEntry>;
						m_data.Set(protectionClassName, protectionParts);
					}
					
					string cfgProtectionPath = "CfgTerjeScriptableProtection " + protectionClassName;
					int partsCount = GetGame().ConfigGetChildrenCount(cfgProtectionPath);
					for (int partsIndex = 0; partsIndex < partsCount; partsIndex++)
					{
						string partClassName = "";
						if (GetGame().ConfigGetChildName(cfgProtectionPath, partsIndex, partClassName))
						{
							ref TerjeScriptableProtectionEntry entry = new TerjeScriptableProtectionEntry;
							entry.OnInit(cfgProtectionPath + " " + partClassName);
							protectionParts.Set(partClassName, entry);
						}
					}
				}
			}
		}
	}
	
	ref TerjeScriptableProtectionEntry GetEntry(string protection, string part)
	{
		ref TerjeScriptableProtectionEntry entry;
		ref map<string, ref TerjeScriptableProtectionEntry> parts;
		if (m_data.Find(protection, parts) && parts.Find(part, entry))
		{
			return entry;
		}
		
		return null;
	}
	
	float GetWeight(string protection, string part)
	{
		ref TerjeScriptableProtectionEntry entry = GetEntry(protection, part);
		if (entry != null)
		{
			return entry.GetWeight();
		}
		
		return 1;
	}
	
	float GetBodyProtection(string protection, string part, float power)
	{
		if (power < 0)
		{
			return 0;
		}
		
		ref TerjeScriptableProtectionEntry entry = GetEntry(protection, part);
		if (entry != null)
		{
			return entry.GetBodyProtection(power);
		}
		
		return 0;
	}
}

class TerjeScriptableProtectionEntry
{
	float m_weight = 1.0;
	ref array<float> m_protectionBodyValues = new array<float>;
	ref array<float> m_protectionBodyThresholds = new array<float>;
	
	void OnInit(string cfgPath)
	{
		m_weight = GetGame().ConfigGetFloat(cfgPath + " weight");
		GetGame().ConfigGetFloatArray(cfgPath + " protectionBodyValues", m_protectionBodyValues);
		GetGame().ConfigGetFloatArray(cfgPath + " protectionBodyThresholds", m_protectionBodyThresholds);
	}
	
	float GetWeight()
	{
		return m_weight;
	}
	
	float GetBodyProtection(float power)
	{
		for (int i = 0; i < m_protectionBodyThresholds.Count(); i++)
		{
			if (power < m_protectionBodyThresholds.Get(i))
			{
				return m_protectionBodyValues.Get(i);
			}
		}
		
		return 0;
	}
}