// <copyright file="TerjeSkillsRegistry.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeSkillsRegistry
{
	private bool m_readyToDisplay = false;
	
	override void OnInit()
	{
		super.OnInit();
		if (GetGame().ConfigIsExisting("CfgTerjeSkills"))
		{
			int skillsCount = GetGame().ConfigGetChildrenCount("CfgTerjeSkills");
			for (int i = 0; i < skillsCount; i++)
			{
				string skillClassName = "";
				if (GetGame().ConfigGetChildName("CfgTerjeSkills", i, skillClassName))
				{
					if (GetGame().ConfigGetInt("CfgTerjeSkills " + skillClassName + " enabled") == 1)
					{
						RegisterSkill(new TerjeSkillCfg("CfgTerjeSkills " + skillClassName));
					}
				}
			}
		}
	}
	
	void OnTerjeSettingsLoaded()
	{
		int settingKey;
		bool settingValue;
		array<ref TerjeSkillCfg> registeredSkills();
		GetSkills(registeredSkills);
		foreach (ref TerjeSkillCfg skill : registeredSkills)
		{
			if (TerjeSettingsCollection.SKILLS_ACTIVE_SKILLS.Find(skill.GetId(), settingKey) && GetTerjeSettingBool(settingKey, settingValue) && !settingValue)
			{
				DeleteSkill(skill);
			}
			else
			{
				skill.OnTerjeSettingsLoaded();
			}
		}
		
		m_readyToDisplay = true;
	}
	
	bool IsReadyToDisplay()
	{
		return m_readyToDisplay;
	}
}

modded class TerjeSkillCfg
{
	override void OnInit()
	{
		super.OnInit();
		
		m_id = GetGame().ConfigGetTextOut(m_cfgPath + " id");
		m_displayName = GetGame().ConfigGetTextOut(m_cfgPath + " displayName");
		m_description = GetGame().ConfigGetTextOut(m_cfgPath + " description");
		m_icon = GetGame().ConfigGetTextOut(m_cfgPath + " icon");
		m_perkPointsPerLevel = GetGame().ConfigGetInt(m_cfgPath + " perkPointsPerLevel");
		m_expLoseOnDeath = GetGame().ConfigGetInt(m_cfgPath + " expLoseOnDeath");
		GetGame().ConfigGetIntArray(m_cfgPath + " levels", m_levels);
		
		int perksCount = 0;
		int requiredPerkPoints = 0;
		int totalPerkPoints = m_perkPointsPerLevel * m_levels.Count();
		if (GetGame().ConfigIsExisting(m_cfgPath + " Perks"))
		{
			perksCount = GetGame().ConfigGetChildrenCount(m_cfgPath + " Perks");
			for (int i = 0; i < perksCount; i++)
			{
				string perkClassName = "";
				if (GetGame().ConfigGetChildName(m_cfgPath + " Perks", i, perkClassName))
				{
					if (GetGame().ConfigGetInt(m_cfgPath + " Perks " + perkClassName + " enabled") == 1)
					{
						ref TerjePerkCfg perkCfg = new TerjePerkCfg(m_cfgPath + " Perks " + perkClassName);
						RegisterPerk(perkCfg);
						for (int s = 0; s < perkCfg.GetStagesCount(); s++)
						{
							requiredPerkPoints += perkCfg.GetRequiredPerkPoints(s);
						}
					}
				}
			}
		}
		
		if (GetGame().ConfigIsExisting(m_cfgPath + " Modifiers"))
		{
			int modifiersCount = GetGame().ConfigGetChildrenCount(m_cfgPath + " Modifiers");
			for (int q = 0; q < modifiersCount; q++)
			{
				string modifierClassName = "";
				if (GetGame().ConfigGetChildName(m_cfgPath + " Modifiers", q, modifierClassName))
				{
					if (GetGame().ConfigGetInt(m_cfgPath + " Modifiers " + modifierClassName + " enabled") == 1)
					{
						RegisterModifier(new TerjeSkillModifierCfg(m_cfgPath + " Modifiers " + modifierClassName));
					}
				}
			}
		}
		
		int perkPointsDelta = totalPerkPoints - requiredPerkPoints;
		TerjeLog_Info("Registered skill '" + m_cfgPath + "' with " + perksCount + " perks. Perk points delta is " + perkPointsDelta);
	}
	
	void OnTerjeSettingsLoaded()
	{
		int settingKey;
		bool settingValue;
		array<ref TerjePerkCfg> registeredPerks();
		GetPerks(registeredPerks);
		foreach (ref TerjePerkCfg perk : registeredPerks)
		{
			if (TerjeSettingsCollection.SKILLS_ACTIVE_PERKS.Find(this.GetId() + ":" + perk.GetId(), settingKey) && GetTerjeSettingBool(settingKey, settingValue) && !settingValue)
			{
				DeletePerk(perk);
			}
		}
	}
}

modded class TerjePerkCfg
{
	override void OnInit()
	{
		super.OnInit();
		
		m_id = GetGame().ConfigGetTextOut(m_cfgPath + " id");
		m_displayName = GetGame().ConfigGetTextOut(m_cfgPath + " displayName");
		m_description = GetGame().ConfigGetTextOut(m_cfgPath + " description");
		m_stagesCount = GetGame().ConfigGetInt(m_cfgPath + " stagesCount");
		m_disabledIcon = GetGame().ConfigGetTextOut(m_cfgPath + " disabledIcon");
		m_enabledIcon = GetGame().ConfigGetTextOut(m_cfgPath + " enabledIcon");
		m_hidden = (GetGame().ConfigGetInt(m_cfgPath + " hidden") == 1);
		GetGame().ConfigGetIntArray(m_cfgPath + " requiredSkillLevels", m_requiredSkillLevels);
		if (m_requiredSkillLevels.Count() != m_stagesCount)
		{
			TerjeLog_Error("Perk '" + m_cfgPath + "' stagesCount and requiredSkillLevels count missmatch!!!");
		}
		
		GetGame().ConfigGetIntArray(m_cfgPath + " requiredPerkPoints", m_requiredPerkPoints);
		if (m_requiredPerkPoints.Count() != m_stagesCount)
		{
			TerjeLog_Error("Perk '" + m_cfgPath + "' stagesCount and requiredPerkPoints count missmatch!!!");
		}
		
		GetGame().ConfigGetFloatArray(m_cfgPath + " values", m_values);
		if (m_values.Count() != m_stagesCount)
		{
			TerjeLog_Error("Perk '" + m_cfgPath + "' stagesCount and values count missmatch!!!");
		}
		
		if (!GetGame().ConfigGetText(m_cfgPath + " specialMetric", m_metricSymbol))
		{
			m_metricSymbol = "%";
		}
		
		if (GetGame().ConfigIsExisting(m_cfgPath + " hints"))
		{
			GetGame().ConfigGetTextArrayRaw(m_cfgPath + " hints", m_hints);
			if (m_hints.Count() != m_stagesCount)
			{
				TerjeLog_Error("Perk '" + m_cfgPath + "' stagesCount and hints count missmatch!!!");
			}
		}
	}
}

modded class TerjeSkillModifierCfg
{
	override void OnInit()
	{
		super.OnInit();
		
		m_id = GetGame().ConfigGetTextOut(m_cfgPath + " id");
		m_text = GetGame().ConfigGetTextOut(m_cfgPath + " text");
		m_value = GetGame().ConfigGetFloat(m_cfgPath + " value");
	}
}