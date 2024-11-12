// <copyright file="PPERequester_CatEyes.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PPERequester_CatEyes extends PPERequester_GameplayBase
{
	static const int L_0_CAT_EYES = 250;
	
	void SetValue(float value)
	{
		SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,value,PPERequester_CatEyes.L_0_CAT_EYES,PPOperators.HIGHEST);
	}
}