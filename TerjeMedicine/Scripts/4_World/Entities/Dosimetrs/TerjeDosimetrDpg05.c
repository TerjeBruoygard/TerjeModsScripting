// <copyright file="TerjeDosimetrDpg05.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeDosimetrDpg05 : TerjeDosimetrBase
{
	override int TerjeGeigerSoundsCount()
	{
		return 4;
	}
	
	override int TerjeGeigerMaxLimit()
	{
		return 999;
	}
	
	override float TerjeGeigerRadiationModifier()
	{
		return 100;
	}
	
	override float GetTerjeSensitivityRadius()
	{
		return 1.5;
	}
	
	override string TerjeGeigerGetSoundSet(int index)
	{
		return "TerjeGeigerElectro" + index + "_SoundSet";
	}
};