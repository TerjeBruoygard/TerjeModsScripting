// <copyright file="HungerMdfr.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class HungerMdfr
{
	override protected float GetTerjeMetabolicSpeedModifier(PlayerBase player, float deltaT, float energy)
	{
		float metabolic_speed = super.GetTerjeMetabolicSpeedModifier(player, deltaT, energy);
		if (player && player.GetTerjeSkills())
		{
			float skillModifier;
			if (player.GetTerjeSkills().GetSkillModifierValue("mtblsm", "energconsmod", skillModifier))
			{
				metabolic_speed = metabolic_speed * Math.Clamp(1.0 + skillModifier, 0.0, 1.0);
			}
			
			if (m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_IDLE)
			{
				float enrgsavePerkValue;
				if (player.GetTerjeSkills().GetPerkValue("mtblsm", "enrgsave", enrgsavePerkValue))
				{
					metabolic_speed = metabolic_speed * Math.Clamp(1.0 + enrgsavePerkValue, 0.0, 1.0);
				}
			}
			else if (m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT)
			{
				float enrgcontrPerkValue;
				if (player.GetTerjeSkills().GetPerkValue("mtblsm", "enrgcontr", enrgcontrPerkValue))
				{
					metabolic_speed = metabolic_speed * Math.Clamp(1.0 + enrgcontrPerkValue, 0.0, 1.0);
				}
			}
			else
			{
				float enrgcontaPerkValue;
				if (player.GetTerjeSkills().GetPerkValue("mtblsm", "enrgconta", enrgcontaPerkValue))
				{
					metabolic_speed = metabolic_speed * Math.Clamp(1.0 + enrgcontaPerkValue, 0.0, 1.0);
				}
			}
		}
		
		return metabolic_speed;
	}
	
	override protected float GetTerjeHealthDammageModifier(PlayerBase player, float deltaT, float energy)
	{
		float reshungerPerkValue;
		float healthDmg = super.GetTerjeHealthDammageModifier(player, deltaT, energy);
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("mtblsm", "reshunger", reshungerPerkValue))
		{
			healthDmg = healthDmg * Math.Clamp(1.0 + reshungerPerkValue, 0.0, 1.0);
		}
		
		return healthDmg;
	}
};