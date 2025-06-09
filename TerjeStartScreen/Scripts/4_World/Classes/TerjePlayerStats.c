// <copyright file="TerjePlayerStats.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjePlayerStats
{
	private int m_TerjeStartScreen_Progress;
	private int m_TerjeStartScreen_SurvSoulsCounter;
	
	override void OnInit()
	{
		super.OnInit();
		
		m_TerjeStartScreen_Progress = RegisterRecordBool("tp.prgss", false, true);
		m_TerjeStartScreen_SurvSoulsCounter = RegisterRecordInt("tp.survsc", 0, true);
	}
	
	bool IsStartScreenInProgress()
	{
		return GetBoolValue(this.m_TerjeStartScreen_Progress);
	}
	void SetStartScreenInProgress(bool value)
	{
		SetBoolValue(this.m_TerjeStartScreen_Progress, value);
	}
	
	int GetSurvSoulsCounter()
	{
		return TerjeMathHelper.MaxInt(0, GetIntValue(this.m_TerjeStartScreen_SurvSoulsCounter));
	}
	void IncrementSurvSoulsCounter()
	{
		SetIntValue(this.m_TerjeStartScreen_SurvSoulsCounter, GetSurvSoulsCounter() + 1);
	}
}
