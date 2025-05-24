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
	private int m_RespawnObjectsClassname;
	private int m_RespawnObjectsPosition;
	private int m_RespawnObjectsMetadata;
	private int m_RespawnObjectsPlayerPos;
	private int m_RespawnObjectsPlayerOri;
	private int m_ServerRulesAccepted;
	
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
		m_RespawnObjectsClassname = RegisterRecordStringMap("tp.rsoc", true);
		m_RespawnObjectsPosition = RegisterRecordStringMap("tp.rsop", true);
		m_RespawnObjectsMetadata = RegisterRecordStringMap("tp.rsom", true);
		m_RespawnObjectsPlayerPos = RegisterRecordStringMap("tp.rspp", true);
		m_RespawnObjectsPlayerOri = RegisterRecordStringMap("tp.rspo", true);
		m_ServerRulesAccepted = RegisterRecordBool("tp.sra", false, true);
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
		int max = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_MAXCOUNT);
		if (max < 1)
		{
			max = 1;
		}
		
		SetIntValue(m_SoulsCount, TerjeMathHelper.ClampInt(value, 0, max));
	}
	
	int GetSoulsCount()
	{
		int max = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_MAXCOUNT);
		if (max < 1)
		{
			max = 1;
		}
		
		return TerjeMathHelper.ClampInt(GetIntValue(m_SoulsCount), 0, max);
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
	
	bool HasRespawnObjectData(string respawnId)
	{
		return ContainsMapKey(m_RespawnObjectsClassname, respawnId);
	}
	
	void SetRespawnObjectData(string respawnId, string classname, string metadata, vector objectPos, vector playerPos, vector playerOri)
	{
		SetStringMapValue(m_RespawnObjectsClassname, respawnId, classname);
		SetStringMapValue(m_RespawnObjectsMetadata, respawnId, metadata);
		SetStringMapValue(m_RespawnObjectsPosition, respawnId, objectPos.ToString(false));
		SetStringMapValue(m_RespawnObjectsPlayerPos, respawnId, playerPos.ToString(false));
		SetStringMapValue(m_RespawnObjectsPlayerOri, respawnId, playerOri.ToString(false));
	}
	
	bool FindRespawnObjectData(string respawnId, out string classname, out string metadata, out vector objectPos, out vector playerPos, out vector playerOri)
	{
		string value;
		if (!FindStringMapValue(m_RespawnObjectsClassname, respawnId, value))
			return false;
		
		classname = value;
		if (!FindStringMapValue(m_RespawnObjectsMetadata, respawnId, value))
			return false;
		
		metadata = value;
		if (!FindStringMapValue(m_RespawnObjectsPosition, respawnId, value))
			return false;
		
		objectPos = value.ToVector();
		if (!FindStringMapValue(m_RespawnObjectsPlayerPos, respawnId, value))
			return false;
		
		playerPos = value.ToVector();
		if (!FindStringMapValue(m_RespawnObjectsPlayerOri, respawnId, value))
			return false;
		
		playerOri = value.ToVector();
		return true;
	}
	
	void DeleteRespawnObjectData(string respawnId)
	{
		RemoveMapValue(m_RespawnObjectsClassname, respawnId);
		RemoveMapValue(m_RespawnObjectsMetadata, respawnId);
		RemoveMapValue(m_RespawnObjectsPosition, respawnId);
		RemoveMapValue(m_RespawnObjectsPlayerPos, respawnId);
		RemoveMapValue(m_RespawnObjectsPlayerOri, respawnId);
	}
	
	void SetServerRulesAccepted(bool value)
	{
		SetBoolValue(m_ServerRulesAccepted, value);
	}
	
	bool GetServerRulesAccepted()
	{
		return GetBoolValue(m_ServerRulesAccepted);
	}
}