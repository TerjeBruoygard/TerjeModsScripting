// <copyright file="HungerMdfr.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class HungerMdfr
{
	override void OnTick(PlayerBase player, float deltaT)
	{
		player.GetMovementState(m_MovementState);
		float energy = player.GetStatEnergy().Get();
		float metabolic_speed = MiscGameplayFunctions.GetEnergyMetabolicSpeed(m_MovementState.m_iMovement);
		float modifier = GetTerjeMetabolicSpeedModifier(player, deltaT, energy);
		float healthDmg = 0;
		
		player.GetStatEnergy().Add( -metabolic_speed * modifier * deltaT );
		if ( energy <= PlayerConstants.LOW_ENERGY_THRESHOLD )
		{
			player.SetMixedSoundState( eMixedSoundStates.HUNGRY );
			if ((player.GetStomach().GetDigestingType() & PlayerStomach.DIGESTING_ENERGY) == 0)
			{
				float healthModifier = GetTerjeHealthDammageModifier(player, deltaT, energy);
				healthDmg = PlayerConstants.LOW_ENERGY_DAMAGE_PER_SEC * healthModifier * deltaT;
				player.GetTerjeHealth().DecreaseHealth(healthDmg, TerjeDamageSource.HUNGER);
			}
		}
		else
		{
			player.UnsetMixedSoundState( eMixedSoundStates.HUNGRY );
		}
		
		OnTerjeTickResult(player, deltaT, energy, healthDmg);
	}
	
	protected float GetTerjeMetabolicSpeedModifier(PlayerBase player, float deltaT, float energy)
	{
		return (energy / PlayerConstants.SL_ENERGY_MAX) + PlayerConstants.CONSUMPTION_MULTIPLIER_BASE;
	}
	
	protected float GetTerjeHealthDammageModifier(PlayerBase player, float deltaT, float energy)
	{
		return 1.0;
	}
	
	protected void OnTerjeTickResult(PlayerBase player, float deltaT, float energy, float healthDmg)
	{
		// Override this function instead of OnTick when you need an access to energy and damage results.
	}
}