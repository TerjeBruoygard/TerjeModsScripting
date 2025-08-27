// <copyright file="TerjeSoundEmitter.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSoundEmitter extends House
{
	SoundOnVehicle m_soundEffect;
	
	void TerjeSoundEmitter()
	{
		if ( GetGame().IsDedicatedServer() )
		{
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater(AutoDeleteIntenalCall, GetLifeTime(), false);
		}
		
		if ( !GetGame().IsDedicatedServer() )
		{
			PlaySoundInternal();
		}
	}
	
	void ~TerjeSoundEmitter() 
	{
		if ( !GetGame().IsDedicatedServer() )
		{
			if ( m_soundEffect )
			{
				GetGame().ObjectDelete( m_soundEffect );
				m_soundEffect = null;
			}
		}
	}
	
	private void AutoDeleteIntenalCall()
	{
		if ( GetGame().IsDedicatedServer() )
		{
			GetGame().ObjectDelete( this );
		}
	}
	
	private void PlaySoundInternal()
	{
		if ( !GetGame().IsDedicatedServer() )
		{
			m_soundEffect = PlaySound(GetSound(), GetRange(), true);	
		}
	}
	
	protected int GetLifeTime()
	{
		float sec = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " emitterLifetime");
		return (int)(sec * 1000);
	}
	
	protected float GetRange()
	{
		return GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " emitterRange");
	}
	
	protected string GetSound()
	{
		return GetTerjeGameConfig().ConfigGetTextOut("CfgVehicles " + GetType() + " emitterSound");
	}
}