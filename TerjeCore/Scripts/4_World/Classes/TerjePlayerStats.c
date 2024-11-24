// <copyright file="TerjePlayerStats.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerStats : TerjePlayerRecordsBase
{
	private int m_LifetimeStat;
	
	override void OnInit()
	{
		super.OnInit();
		m_LifetimeStat = RegisterRecordInt("lifetime", 0, true);
	};
	
	int IncrementLifetime()
	{
		int result = GetIntValue(m_LifetimeStat) + 1;
		SetIntValue(m_LifetimeStat, result);
		return result;
	};
	
	int GetLifetime()
	{
		return GetIntValue(m_LifetimeStat);
	};
};