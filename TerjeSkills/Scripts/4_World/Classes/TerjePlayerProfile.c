// <copyright file="TerjePlayerProfile.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjePlayerProfile
{
	private ref map<string, int> m_TerjeSkills_KnownBooks = new map<string, int>;
	private ref map<string, int> m_TerjeSkills_Experience = new map<string, int>;
	private ref map<string, int> m_TerjeSkills_PerkPoints = new map<string, int>;
	private ref map<string, int> m_TerjeSkills_HighLevels = new map<string, int>;
	private ref map<string, ref map<string, int>> m_TerjeSkills_Perks = new map<string, ref map<string, int>>;
	
	override void OnInit()
	{
		super.OnInit();

		ref array<ref TerjePerkCfg> perks = new array<ref TerjePerkCfg>;
		ref array<ref TerjeSkillCfg> skills = new array<ref TerjeSkillCfg>;
		GetTerjeSkillsRegistry().GetSkills(skills);
		foreach (ref TerjeSkillCfg skill : skills)
		{
			m_TerjeSkills_KnownBooks.Insert(skill.GetId(), RegisterRecordString("ts.knb_" + skill.GetId(), "", true));
			m_TerjeSkills_Experience.Insert(skill.GetId(), RegisterRecordInt("ts.exp_" + skill.GetId(), 0, false));
			m_TerjeSkills_PerkPoints.Insert(skill.GetId(), RegisterRecordInt("ts.pps_" + skill.GetId(), 0, false));
			m_TerjeSkills_HighLevels.Insert(skill.GetId(), RegisterRecordInt("ts.max_" + skill.GetId(), 0, false));
			m_TerjeSkills_Perks.Insert(skill.GetId(), new map<string, int>);
			
			perks.Clear();
			skill.GetPerks(perks);
			foreach (ref TerjePerkCfg perk : perks)
			{
				m_TerjeSkills_Perks.Get(skill.GetId()).Insert(perk.GetId(), RegisterRecordInt("ts.perk_" + skill.GetId() + "+" + perk.GetId(), 0, false));
			}
		}
	}
	
	bool HasKnownSkillBook(string skillId, string bookClassname)
	{
		int recordId;
		if (m_TerjeSkills_KnownBooks.Find(skillId, recordId))
		{
			string result = GetStringValue(recordId);
			string entry = "<" + bookClassname + ">";
			if (result.IndexOf(entry) != -1)
			{
				return true;
			}
		}
		
		return false;
	}
	
	void AddKnownSkillBook(string skillId, string bookClassname)
	{
		int recordId;
		if (m_TerjeSkills_KnownBooks.Find(skillId, recordId))
		{
			string result = GetStringValue(recordId);
			string entry = "<" + bookClassname + ">";
			if (result.IndexOf(entry) == -1)
			{
				SetStringValue(recordId, result + entry);
			}
		}
	}
	
	int GetSkillExperience(string skillId)
	{
		int recordId;
		if (m_TerjeSkills_Experience.Find(skillId, recordId))
		{
			int result = GetIntValue(recordId);
			if (result < 0)
			{
				result = 0;
			}
			
			return result;
		}
		
		return 0;
	}
	
	void SetSkillExperience(string skillId, int value)
	{		
		int recordId;
		if (m_TerjeSkills_Experience.Find(skillId, recordId))
		{
			if (value < 0)
			{
				value = 0;
			}
			
			SetIntValue(recordId, value);
		}
	}
	
	int GetSkillPerkPoints(string skillId)
	{
		int recordId;
		if (m_TerjeSkills_PerkPoints.Find(skillId, recordId))
		{
			int result = GetIntValue(recordId);
			if (result < 0)
			{
				result = 0;
			}
			
			return result;
		}
		
		return 0;
	}
	
	void SetSkillPerkPoints(string skillId, int value)
	{
		int recordId;
		if (m_TerjeSkills_PerkPoints.Find(skillId, recordId))
		{
			if (value < 0)
			{
				value = 0;
			}
			
			SetIntValue(recordId, value);
		}
	}
	
	int GetSkillHighRangeLevel(string skillId)
	{
		int recordId;
		if (m_TerjeSkills_HighLevels.Find(skillId, recordId))
		{
			int result = GetIntValue(recordId);
			if (result < 0)
			{
				result = 0;
			}
			
			return result;
		}
		
		return 0;
	}
	
	void SetSkillHighRangeLevel(string skillId, int value)
	{
		int recordId;
		if (m_TerjeSkills_HighLevels.Find(skillId, recordId))
		{
			if (value < 0)
			{
				value = 0;
			}
			
			SetIntValue(recordId, value);
		}
	}
	
	int GetSkillPerk(string skillId, string perkId)
	{
		int recordId;
		ref map<string, int> perksMap;
		if (m_TerjeSkills_Perks.Find(skillId, perksMap) && perksMap.Find(perkId, recordId))
		{
			int result = GetIntValue(recordId);
			if (result < 0)
			{
				result = 0;
			}
			
			return result;
		}
		
		return 0;
	}
	
	void SetSkillPerk(string skillId, string perkId, int value)
	{
		int recordId;
		ref map<string, int> perksMap;
		if (m_TerjeSkills_Perks.Find(skillId, perksMap) && perksMap.Find(perkId, recordId))
		{
			if (value < 0)
			{
				value = 0;
			}
			
			SetIntValue(recordId, value);
		}
	}
}