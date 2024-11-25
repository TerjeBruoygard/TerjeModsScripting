// <copyright file="TerjePlayerStats.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjePlayerStats
{
	private int m_TerjeMed_RadiationAccumutaled;
	private int m_TerjeMed_RadiationLevel;
	private int m_TerjeMed_RadiationValue;
	private int m_TerjeMed_AntiradLevel;
	private int m_TerjeMed_AntiradValue;
	
	override void OnInit()
	{
		super.OnInit();
		
		m_TerjeMed_RadiationLevel = RegisterRecordInt("tm.rad_l", 0, false); // Radiation sickness level
		m_TerjeMed_RadiationValue = RegisterRecordFloat("tm.rad_v", 0, true); // Radiation sickness value
		m_TerjeMed_RadiationAccumutaled = RegisterRecordFloat("tm.rad_acc", 0, true); // Radiation accumulated in the body
		
		m_TerjeMed_AntiradLevel = RegisterRecordInt("tm.rad+hl", 0, false); // Antirad level
		m_TerjeMed_AntiradValue = RegisterRecordFloat("tm.rad+ht", 0, true); // Antirad timer
	}
	
	// Radiation
	int GetRadiationLevel()
	{
		return ClampInt(GetIntValue(this.m_TerjeMed_RadiationLevel), 0, 3);
	}
	float GetRadiationValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_RadiationValue), 0, TerjeRadiationConstants.RADIATION_MAX_VALUE);
	}
	void SetRadiationValue(float value)
	{
		value = Math.Clamp(value, 0, TerjeRadiationConstants.RADIATION_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_RadiationValue, value);
		SetIntValue(this.m_TerjeMed_RadiationLevel, ClampInt((int)value, 0, 3));
	}
	void SetRadiationAccumulated(float value)
	{
		value = Math.Clamp(value, 0, TerjeRadiationConstants.RADIATION_PLAYER_ACCUMULATOR_SERVER_MAX);
		SetFloatValue(this.m_TerjeMed_RadiationAccumutaled, value);
	}
	float GetRadiationAccumulated()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_RadiationAccumutaled), 0, TerjeRadiationConstants.RADIATION_PLAYER_ACCUMULATOR_SERVER_MAX);
	}
	
	// Antirad
	int GetAntiradLevel()
	{
		return ClampInt(GetIntValue(this.m_TerjeMed_AntiradLevel), 0, 3);
	}
	bool GetAntirad(out int level, out float timer)
	{
		level = GetIntValue(this.m_TerjeMed_AntiradLevel);
		timer = GetFloatValue(this.m_TerjeMed_AntiradValue);
		return true;
	}
	void SetAntirad(int level, float timer)
	{
		SetIntValue(this.m_TerjeMed_AntiradLevel, ClampInt(level, 0, 3));
		SetFloatValue(this.m_TerjeMed_AntiradValue, Math.Max(timer, 0));
	}
}
