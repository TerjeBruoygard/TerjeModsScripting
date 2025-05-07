// <copyright file="TerjeSkillsRegistry.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

ref TerjeSkillsRegistry GetTerjeSkillsRegistry()
{
	return TerjeSkillsRegistry.GetInstance();
}

class TerjeSkillsRegistry
{
	private static ref TerjeSkillsRegistry m_instance = null;
	private ref map<string, ref TerjeSkillCfg> m_skills = new map<string, ref TerjeSkillCfg>;
	private ref array<ref TerjeSkillCfg> m_orderedSkills = new array<ref TerjeSkillCfg>;
	
	static ref TerjeSkillsRegistry GetInstance()
	{
		if (m_instance == null)
		{
			m_instance = new TerjeSkillsRegistry();
			m_instance.OnInit();
		}
		
		return m_instance;
	}
	
	void OnInit()
	{
	
	}
	
	protected void RegisterSkill(TerjeSkillCfg skill)
	{
		if (skill == null)
		{
			return;
		}
		
		if (m_skills.Contains(skill.GetId()))
		{
			return;
		}
		
		m_skills.Insert(skill.GetId(), skill);
		m_orderedSkills.Insert(skill);
	}
	
	protected void DeleteSkill(TerjeSkillCfg skill)
	{
		m_skills.Remove(skill.GetId());
		m_orderedSkills.RemoveItem(skill);
	}
	
	void GetSkills(array<ref TerjeSkillCfg> result)
	{
		foreach (ref TerjeSkillCfg skill : m_orderedSkills)
		{
			if (skill != null)
			{
				result.Insert(skill);
			}
		}
	}
	
	bool FindSkill(string id, out TerjeSkillCfg result)
	{
		return m_skills.Find(id, result);
	}
	
	bool HasSkillsMod()
	{
		return false;
	}
}

class TerjeSkillCfg
{
	private string m_cfgPath;
	private string m_id;
	private string m_displayName;
	private string m_description;
	private string m_icon;
	private int m_perkPointsPerLevel;
	private int m_expLoseOnDeath;
	private ref array<int> m_levels = new array<int>;
	private ref map<string, ref TerjePerkCfg> m_perks = new map<string, ref TerjePerkCfg>;
	private ref array<ref TerjePerkCfg> m_orderedPerks = new array<ref TerjePerkCfg>;
	private ref map<string, ref TerjeSkillModifierCfg> m_modifiers = new map<string, ref TerjeSkillModifierCfg>;
	private ref array<ref TerjeSkillModifierCfg> m_orderedModifiers = new array<ref TerjeSkillModifierCfg>;
	
	void TerjeSkillCfg(string cfgPath)
	{
		m_cfgPath = cfgPath;
		OnInit();
	}
	
	void OnInit()
	{
	
	}
	
	string GetId()
	{
		return m_id;
	}
	
	string GetDisplayName()
	{
		return m_displayName;
	}
	
	string GetDescription()
	{
		return m_description;
	}
	
	int GetPerkPointsPerLevel()
	{
		return m_perkPointsPerLevel;
	}
	
	int GetExpLoseOnDeath()
	{
		return m_expLoseOnDeath;
	}
	
	string GetIcon()
	{
		return m_icon;
	}
	
	int GetMaxLevel()
	{
		return m_levels.Count();
	}
	
	int GetExpForLevel(int level)
	{
		if (level == 0)
		{
			return 0;
		}
		
		if (level > m_levels.Count())
		{
			level = m_levels.Count();
		}
		
		return m_levels.Get(level - 1);
	}
	
	int GetLevelFromExp(int exp)
	{
		for (int i = 0; i < m_levels.Count(); i++)
		{
			if (exp < m_levels.Get(i))
			{
				return i;
			}
		}
		
		return GetMaxLevel();
	}
	
	protected void RegisterPerk(TerjePerkCfg perk)
	{
		if (perk == null)
		{
			return;
		}
		
		if (m_perks.Contains(perk.GetId()))
		{
			return;
		}
		
		m_perks.Insert(perk.GetId(), perk);
		m_orderedPerks.Insert(perk);
	}
	
	protected void DeletePerk(TerjePerkCfg perk)
	{
		m_perks.Remove(perk.GetId());
		m_orderedPerks.RemoveItem(perk);
	}
	
	void GetPerks(array<ref TerjePerkCfg> result)
	{
		foreach (ref TerjePerkCfg perk : m_orderedPerks)
		{
			if (perk != null)
			{
				result.Insert(perk);
			}
		}
	}
	
	bool FindPerk(string id, out TerjePerkCfg result)
	{
		return m_perks.Find(id, result);
	}
	
	
	protected void RegisterModifier(TerjeSkillModifierCfg modifier)
	{
		if (modifier == null)
		{
			return;
		}
		
		if (m_modifiers.Contains(modifier.GetId()))
		{
			return;
		}
		
		m_modifiers.Insert(modifier.GetId(), modifier);
		m_orderedModifiers.Insert(modifier);
	}
	
	protected void DeleteModifier(TerjeSkillModifierCfg modifier)
	{
		m_modifiers.Remove(modifier.GetId());
		m_orderedModifiers.RemoveItem(modifier);
	}
	
	void GetModifiers(array<ref TerjeSkillModifierCfg> result)
	{
		foreach (ref TerjeSkillModifierCfg modifier : m_orderedModifiers)
		{
			if (modifier != null)
			{
				result.Insert(modifier);
			}
		}
	}
	
	bool FindModifier(string id, out TerjeSkillModifierCfg result)
	{
		return m_modifiers.Find(id, result);
	}
}

class TerjePerkCfg
{
	private string m_cfgPath;
	private string m_id;
	private string m_displayName;
	private string m_description;
	private string m_disabledIcon;
	private string m_enabledIcon;
	private string m_metricSymbol; 
	private int m_stagesCount;
	private ref array<int> m_requiredSkillLevels = new array<int>;
	private ref array<int> m_requiredPerkPoints = new array<int>;
	private ref array<float> m_values = new array<float>;
	private ref array<string> m_hints = new array<string>;
	private bool m_hidden;
	
	void TerjePerkCfg(string cfgPath)
	{
		m_cfgPath = cfgPath;
		OnInit();
	}
	
	void OnInit()
	{
		
	}
	
	string GetId()
	{
		return m_id;
	}
	
	string GetDisplayName()
	{
		return m_displayName;
	}
	
	string GetDescription()
	{
		return m_description;
	}
	
	int GetStagesCount()
	{
		return m_stagesCount;
	}
	
	string GetDisabledIcon()
	{
		return m_disabledIcon;
	}
	
	string GetEnabledIcon()
	{
		return m_enabledIcon;
	}
	
	int GetRequiredSkillLevel(int stage)
	{
		return m_requiredSkillLevels.Get(stage);
	}
	
	int GetRequiredPerkPoints(int stage)
	{
		return m_requiredPerkPoints.Get(stage);
	}
	
	float GetValue(int stage)
	{
		return m_values.Get(stage);
	}
	
	string GetMetricSymbol()
	{
		return m_metricSymbol;
	}
	
	bool IsHidden()
	{
		return m_hidden;
	}
	
	bool HasHints()
	{
		return m_hints.Count() > 0;
	}
	
	string GetHint(int stage)
	{
		return m_hints.Get(stage);
	}
}

class TerjeSkillModifierCfg
{
	private string m_cfgPath;
	private string m_id;
	private string m_text;
	private float m_value;
	
	void TerjeSkillModifierCfg(string cfgPath)
	{
		m_cfgPath = cfgPath;
		OnInit();
	}
	
	void OnInit()
	{
		
	}
	
	string GetId()
	{
		return m_id;
	}
	
	string GetText()
	{
		return m_text;
	}
	
	float GetValue()
	{
		return m_value;
	}
}