// <copyright file="TerjeCustomLiquids.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class LiquidInfo
{
	void InitCustomTerjeLiquid(string className)
	{
		string path = "CfgTerjeCustomLiquids " + className;
		GetGame().ConfigGetTextRaw(string.Format("%1 displayName", path), m_LiquidDisplayName);
		GetGame().FormatRawConfigStringKeys(m_LiquidDisplayName);
		m_LiquidType = GetGame().ConfigGetInt(string.Format("%1 type", path));
		if (GetGame().ConfigIsExisting(string.Format("%1 liquidFreezeThreshold", path)))
			m_TemperatureLiquidFreezeThreshold = GetGame().ConfigGetFloat(string.Format("%1 liquidFreezeThreshold", path));
		if (GetGame().ConfigIsExisting(string.Format("%1 liquidThawThreshold", path)))
			m_TemperatureLiquidThawThreshold = GetGame().ConfigGetFloat(string.Format("%1 liquidThawThreshold", path));
		if (GetGame().ConfigIsExisting(string.Format("%1 liquidBoilingThreshold", path)))
			m_TemperatureLiquidBoilThreshold = GetGame().ConfigGetFloat(string.Format("%1 liquidBoilingThreshold", path));
		m_Flammability = GetGame().ConfigGetFloat(string.Format("%1 flammability", path));
	}
};

class TerjeCustomLiquids
{
	private static ref TerjeCustomLiquids m_Instance = null;
	static ref TerjeCustomLiquids GetInstance()
	{
		if (m_Instance == null)
		{
			m_Instance = new TerjeCustomLiquids;
			m_Instance.Init();
		}
		
		return m_Instance;
	}
	
	ref array<ref LiquidInfo> m_AllCustomLiquids = new array<ref LiquidInfo>;
	ref map<string, int> m_LiquidIdByType = new map<string, int>;
	ref map<int, ref LiquidInfo> m_LiquidInfosByType = new map<int, ref LiquidInfo>;
	ref map<string, ref LiquidInfo> m_LiquidInfosByName = new map<string, ref LiquidInfo>;
	
	void Init()
	{
		string cfgRootClassname = "CfgTerjeCustomLiquids";
		int cfgItemsCount = GetGame().ConfigGetChildrenCount(cfgRootClassname);

		for (int i = 0; i < cfgItemsCount; i++)
		{
			string liquidClassName;
			GetGame().ConfigGetChildName(cfgRootClassname, i, liquidClassName);
			
			ref NutritionalProfile profile = BuildNutritionalProfile(cfgRootClassname + " " + liquidClassName);
			ref LiquidInfo info = new LiquidInfo(liquidClassName, profile);
			info.InitCustomTerjeLiquid(liquidClassName);
			int index = m_AllCustomLiquids.Insert(info) + 1;
			m_LiquidInfosByType.Insert(index, info);
			m_LiquidInfosByName.Insert(liquidClassName, info);
			m_LiquidIdByType.Insert(liquidClassName, index);
		}
	}
	
	ref NutritionalProfile BuildNutritionalProfile(string liquidFullPath)
	{
		float energy = GetGame().ConfigGetFloat(liquidFullPath + " Nutrition energy");
		float nutritional_index = GetGame().ConfigGetFloat(liquidFullPath + " Nutrition nutritionalIndex");
		float volume = GetGame().ConfigGetFloat(liquidFullPath + " Nutrition fullnessIndex");
		float water_content = GetGame().ConfigGetFloat(liquidFullPath + " Nutrition water");
		float toxicity = GetGame().ConfigGetFloat(liquidFullPath + " Nutrition toxicity");
		int agents = GetGame().ConfigGetInt(liquidFullPath + " Nutrition agents");
		float digest = GetGame().ConfigGetFloat(liquidFullPath + " Nutrition digestibility");
		return new NutritionalProfile(energy, water_content, nutritional_index, volume, toxicity, agents, digest);
	}
	
	ref NutritionalProfile GetNutritionalProfileByType(int liquid_type)
	{
		LiquidInfo info = m_LiquidInfosByType.Get(liquid_type);
		if (info && info.m_NutriProfile)
			return info.m_NutriProfile;
		
		return null;
	}
	
	ref NutritionalProfile GetNutritionalProfileByName(string class_name)
	{
		LiquidInfo info = m_LiquidInfosByName.Get(class_name);
		if (info && info.m_NutriProfile)
			return info.m_NutriProfile;
		
		return null;
	}
	
	bool FindLiquidIndexByType(string class_name, out int index)
	{
		return m_LiquidIdByType.Find(class_name, index);
	}
	
	int GetLiquidIndexByType(string class_name)
	{
		int result;
		if (FindLiquidIndexByType(class_name, result))
		{
			return result;
		}
		
		return 0;
	}
	
	string GetLiquidClassname(int liquid_type)
	{
		ref LiquidInfo info;
		if (m_LiquidInfosByType.Find(liquid_type, info))
		{
			return info.m_LiquidClassName;
		}
		
		return "";
	}
	
	int GetAgents(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_NutriProfile.GetAgents();
	}
	
	float GetToxicity(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_NutriProfile.GetToxicity();
	}
	
	float GetWaterContent(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_NutriProfile.GetWaterContent();
	}
	
	float GetEnergy(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_NutriProfile.GetEnergy();
	}
	
	float GetNutritionalIndex(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_NutriProfile.GetNutritionalIndex();
	}
	
	string GetDisplayName(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_LiquidDisplayName;
	}
	
	float GetFlammability(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_Flammability;
	}
	
	float GetFullness(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_NutriProfile.GetFullnessIndex();
	}
	
	float GetDigestibility(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_NutriProfile.GetDigestibility();
	}
	
	float GetFreezeThreshold(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_TemperatureLiquidFreezeThreshold;
	}
	
	float GetThawThreshold(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_TemperatureLiquidThawThreshold;
	}
	
	float GetBoilThreshold(int liquid_type)
	{
		return m_LiquidInfosByType.Get(liquid_type).m_TemperatureLiquidBoilThreshold;
	}
	
	void FixVanillaTransfer(ItemBase source_ent, ItemBase target_ent, float quantity = -1)
	{
		if (source_ent.GetLiquidType() == LIQUID_TERJE_CUSTOM && target_ent.GetLiquidType() == LIQUID_TERJE_CUSTOM)
		{
			target_ent.SetTerjeLiquidType(source_ent.GetTerjeLiquidType());
		}
	}
	
	void Transfer(ItemBase source_ent, ItemBase target_ent, float quantity = -1)
	{
		if (!CanTransfer(source_ent, target_ent))
		{
			return;
		}
		
		Liquid.Transfer(source_ent, target_ent, quantity);
		FixVanillaTransfer(source_ent, target_ent, quantity);
	}
	
	bool CanTransfer(ItemBase source_ent, ItemBase target_ent)
	{
		if (!Liquid.CanTransfer(source_ent, target_ent))
		{
			return false;
		}
		
		if (target_ent.GetQuantity() > 0 && target_ent.GetTerjeLiquidType() != source_ent.GetTerjeLiquidType())
		{
			return false;
		}
		
		return true;
	}
};