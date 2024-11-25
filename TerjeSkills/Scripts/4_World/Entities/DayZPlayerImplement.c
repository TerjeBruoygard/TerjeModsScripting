// <copyright file="DayZPlayerImplement.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class DayZPlayerImplement
{
	override void OnStepEvent(string pEventType, string pUserString, int pUserInt)
	{
		if (GetGame().IsClient())
		{
			float perkValue;
			PlayerBase player = PlayerBase.Cast(this);
			if (player)
			{
				AnimBootsType bootsType = GetBootsType();
				if (bootsType != AnimBootsType.Boots)
				{
					if (player.GetTerjeSkillsStealthPerkValueFromBitmask(TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_FEETS, "shadowtrc", perkValue))
					{
						HumanMovementState state = new HumanMovementState();
						GetMovementState(state);
						if (state.m_iMovement != DayZPlayerConstants.MOVEMENTIDX_SPRINT)
						{
							ModifyTerjeWaveMasterVolume(perkValue);
						}
					}
				}
				
				if (player.GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_SHOES, "qtstep", perkValue))
				{
					ModifyTerjeWaveMasterVolume(Math.Clamp(1.0 + perkValue, 0, 1));
				}
			}
		}
		
		super.OnStepEvent(pEventType, pUserString, pUserInt);
		ResetTerjeWaveMasterVolume();
	}
	
	override void OnSoundEvent(string pEventType, string pUserString, int pUserInt)
	{
		if (GetGame().IsClient())
		{
			float perkValue;
			PlayerBase player = PlayerBase.Cast(this);
			if (player)
			{
				if (player.GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_NINJA, "ninja", perkValue))
				{
					ModifyTerjeWaveMasterVolume(Math.Clamp(1.0 + perkValue, 0, 1));
				}
				
				if (pEventType == "SoundVoice")
				{
					if (player.GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_VOICE, "coldbldd", perkValue))
					{
						ModifyTerjeWaveMasterVolume(Math.Clamp(1.0 + perkValue, 0, 1));
					}
				}
				else if (pEventType == "SoundWeapon")
				{
					if (player.GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_WEAPON, "qshooter", perkValue))
					{
						ModifyTerjeWaveMasterVolume(Math.Clamp(1.0 + perkValue, 0, 1));
					}
				}
				else if (pEventType == "Sound")
				{
					if ( pUserInt >= 400 && pUserInt <= 405 )
					{
						if (player.GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_WEAPON, "qshooter", perkValue))
						{
							ModifyTerjeWaveMasterVolume(Math.Clamp(1.0 + perkValue, 0, 1));
						}
					}
					if ( pUserInt >= 321 && pUserInt <= 334 )
					{
						if (player.GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_WEAPON, "qshooter", perkValue))
						{
							ModifyTerjeWaveMasterVolume(Math.Clamp(1.0 + perkValue, 0, 1));
						}
					}
					else if ( pUserInt >= 250 && pUserInt < 270 )
					{
						if (player.GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_WEAPON, "qshooter", perkValue))
						{
							ModifyTerjeWaveMasterVolume(Math.Clamp(1.0 + perkValue, 0, 1));
						}
					}
					else if ( pUserInt == 893 || pUserInt == 1201 || pUserInt == 798 || pUserInt == 1200 )
					{
						if (player.GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_WEAPON, "qshooter", perkValue))
						{
							ModifyTerjeWaveMasterVolume(Math.Clamp(1.0 + perkValue, 0, 1));
						}
					}
				}
				else if (pEventType == "SoundAttachment")
				{
					if (player.GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_CLOTHES, "fitequip", perkValue))
					{
						ModifyTerjeWaveMasterVolume(Math.Clamp(1.0 + perkValue, 0, 1));
					}
				}
			}
		}
		
		super.OnSoundEvent(pEventType, pUserString, pUserInt);		
		ResetTerjeWaveMasterVolume();
	}
}