// <copyright file="TerjePlayerProfile.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjePlayerProfile
{
	private int m_FirstName;
	private int m_LastName;
	private int m_CharacterClassname;
	private int m_SoulsCount;
	private int m_LastLoadoutId;
	private int m_LastLoadoutSelections;
	private int m_SkillsSelectedFlag;
	private int m_LastRespawnId;
	
	override void OnInit()
	{
		super.OnInit();

		m_FirstName = RegisterRecordString("tp.fname", "", true);
		m_LastName = RegisterRecordString("tp.lname", "", true);
		m_CharacterClassname = RegisterRecordString("tp.cname", "", true);
		m_SoulsCount = RegisterRecordInt("tp.slc", -1, false);
		m_LastLoadoutId = RegisterRecordString("tp.llid", "", true);
		m_LastLoadoutSelections = RegisterRecordString("tp.llsel", "", true);
		m_SkillsSelectedFlag = RegisterRecordInt("tp.ssf", 0, true);
		m_LastRespawnId = RegisterRecordString("tp.lrid", "", true);
	}
	
	override void OnNewProfileCreated()
	{
		super.OnNewProfileCreated();
		
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetSkillsSelectedFlag(1);
			SetSoulsCount(GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_INIT_COUNT));
		}
	}
	
	override void OnExistProfileLoaded()
	{
		super.OnExistProfileLoaded();
		
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (GetIntValue(m_SoulsCount) == -1)
			{
				SetSoulsCount(GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_INIT_COUNT));
			}
		}
	}
	
	void SetFirstName(string firstName)
	{
		SetStringValue(m_FirstName, firstName);
	}
	
	string GetFirstName()
	{
		return GetStringValue(m_FirstName);
	}
	
	void SetLastName(string lastName)
	{
		SetStringValue(m_LastName, lastName);
	}
	
	string GetLastName()
	{
		return GetStringValue(m_LastName);
	}
	
	void SetCharacterClassname(string className)
	{
		SetStringValue(m_CharacterClassname, className);
	}
	
	string GetCharacterClassname()
	{
		return GetStringValue(m_CharacterClassname);
	}
	
	void SetSoulsCount(int value)
	{
		SetIntValue(TerjeMathHelper.ClampInt(m_SoulsCount, 0, TerjeStartScreenConstants.SOULS_MAX_LIMIT), value);
	}
	
	int GetSoulsCount()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(m_SoulsCount), 0, TerjeStartScreenConstants.SOULS_MAX_LIMIT);
	}
	
	void SetLastLoadout(string loadoutId, string selections)
	{
		SetStringValue(m_LastLoadoutId, loadoutId);
		SetStringValue(m_LastLoadoutSelections, selections);
	}
	
	void GetLastLoadout(out string loadoutId, out string selections)
	{
		loadoutId = GetStringValue(m_LastLoadoutId);
		selections = GetStringValue(m_LastLoadoutSelections);
	}
	
	void SetSkillsSelectedFlag(int flag)
	{
		SetIntValue(m_SkillsSelectedFlag, flag);
	}
	
	int GetSkillsSelectedFlag()
	{
		return GetIntValue(m_SkillsSelectedFlag);
	}
	
	void SetLastRespawnId(string respawnId)
	{
		SetStringValue(m_LastRespawnId, respawnId);
	}
	
	string GetLastRespawnId()
	{
		return GetStringValue(m_LastRespawnId);
	}
}