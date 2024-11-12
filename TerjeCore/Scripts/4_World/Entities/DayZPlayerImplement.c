// <copyright file="DayZPlayerImplement.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class DayZPlayerImplement
{
	private float m_terjeWaveMasterVolume = 1.0;
	
	private void ModifyTerjeWaveMasterVolume(float value)
	{
		m_terjeWaveMasterVolume *= value;
	}
	
	private void ResetTerjeWaveMasterVolume()
	{
		m_terjeWaveMasterVolume = 1.0;
	}
	
	override AbstractWave PlaySound(SoundObject so, SoundObjectBuilder sob)
	{
		AbstractWave wave = super.PlaySound(so, sob);
		if (wave != null)
		{
			wave.SetVolume(wave.GetVolume() * m_terjeWaveMasterVolume);
		}
		
		return wave;
	}
};