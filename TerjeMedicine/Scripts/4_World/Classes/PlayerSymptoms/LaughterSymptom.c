// <copyright file="LaughterSymptom.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class LaughterSymptom
{
	override void OnGetActivatedServer(PlayerBase player)
	{
		bool mindUseLaughterSymptom = true;
		GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_MIND_USE_LAUGHTER_SYMPTOM, mindUseLaughterSymptom);
		if (mindUseLaughterSymptom)
		{
			super.OnGetActivatedServer(player);
		}
	}
}
