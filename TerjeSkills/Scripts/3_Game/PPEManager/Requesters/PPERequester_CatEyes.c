// <copyright file="PPERequester_CatEyes.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PPERequester_CatEyes extends PPERequester_GameplayBase
{
	static const int L_0_CAT_EYES = 266;
	
	float m_terjeLastValue = 0;
	
	void OnTerjeUpdate(float value, float dt)
	{
		if (value > m_terjeLastValue)
		{
			value = Math.Lerp(m_terjeLastValue, value, Math.Clamp(dt, 0, 1)); 
		}
		else if (value < m_terjeLastValue)
		{
			value = Math.Lerp(value, m_terjeLastValue, 1.0 - Math.Clamp(dt, 0, 1)); 
		}
		
		SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,value,PPERequester_CatEyes.L_0_CAT_EYES,PPOperators.HIGHEST);
		m_terjeLastValue = value;
	}
}