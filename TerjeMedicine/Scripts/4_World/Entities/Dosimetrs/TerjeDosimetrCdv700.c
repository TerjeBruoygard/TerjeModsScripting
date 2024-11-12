// <copyright file="TerjeDosimetrCdv700.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeDosimetrCdv700 : TerjeDosimetrBase
{
	override void TerjeEnableDisplayClient()
	{
		SetAnimationPhase("arrow", 0.5);
	}
	
	override void TerjeDisableDisplayClient()
	{
		SetAnimationPhase("arrow", 0);
	}
	
	override void TerjeUpdateDisplayValueClient(int value)
	{
		float arrowPos = Math.Clamp(value / TerjeGeigerMaxLimit(), 0, 1);
		SetAnimationPhase("arrow", arrowPos);
	}
	
	
	override int TerjeGeigerSoundsCount()
	{
		return 4;
	}
	
	override int TerjeGeigerMaxLimit()
	{
		return 5000;
	}
	
	override float TerjeGeigerRadiationModifier()
	{
		return 1000;
	}
	
	override float GetTerjeSensitivityRadius()
	{
		return 10;
	}
	
	override string TerjeGeigerGetSoundSet(int index)
	{
		return "TerjeGeigerClasic" + index + "_SoundSet";
	}
};