// <copyright file="ThirstMdfr.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ThirstMdfr
{
	override protected float GetTerjeMetabolicSpeedModifier(PlayerBase player, float deltaT, float water)
	{
		float metabolic_speed = super.GetTerjeMetabolicSpeedModifier(player, deltaT, water);
		if (player && player.GetTerjeSkills())
		{
			float skillModifier;
			if (player.GetTerjeSkills().GetSkillModifierValue("mtblsm", "energconsmod", skillModifier))
			{
				metabolic_speed = metabolic_speed * Math.Clamp(1.0 + skillModifier, 0.0, 1.0);
			}
			
			if (m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_IDLE)
			{
				float watrsavePerkValue;
				if (player.GetTerjeSkills().GetPerkValue("mtblsm", "watrsave", watrsavePerkValue))
				{
					metabolic_speed = metabolic_speed * Math.Clamp(1.0 + watrsavePerkValue, 0.0, 1.0);
				}
			}
			else if (m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT)
			{
				float hydrcontrPerkValue;
				if (player.GetTerjeSkills().GetPerkValue("mtblsm", "hydrcontr", hydrcontrPerkValue))
				{
					metabolic_speed = metabolic_speed * Math.Clamp(1.0 + hydrcontrPerkValue, 0.0, 1.0);
				}
			}
			else
			{
				float watrcontaPerkValue;
				if (player.GetTerjeSkills().GetPerkValue("mtblsm", "watrconta", watrcontaPerkValue))
				{
					metabolic_speed = metabolic_speed * Math.Clamp(1.0 + watrcontaPerkValue, 0.0, 1.0);
				}
			}
		}
		
		return metabolic_speed;
	}
	
	override protected float GetTerjeHealthDammageModifier(PlayerBase player, float deltaT, float water)
	{
		float reswaterPerkValue;
		float healthDmg = super.GetTerjeHealthDammageModifier(player, deltaT, water);
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("mtblsm", "reswater", reswaterPerkValue))
		{
			healthDmg = healthDmg * Math.Clamp(1.0 + reswaterPerkValue, 0.0, 1.0);
		}
		
		return healthDmg;
	}
};