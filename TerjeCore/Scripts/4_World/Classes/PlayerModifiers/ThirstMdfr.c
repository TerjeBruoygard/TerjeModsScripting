// <copyright file="ThirstMdfr.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ThirstMdfr
{
	override void OnTick(PlayerBase player, float deltaT)
	{
		player.GetMovementState(m_MovementState);
		float water = player.GetStatWater().Get();
		float metabolic_speed = MiscGameplayFunctions.GetWaterMetabolicSpeed(m_MovementState.m_iMovement);
		float modifier = GetTerjeMetabolicSpeedModifier(player, deltaT, water);
		float healthDmg = 0;
		
		player.GetStatWater().Add( (-metabolic_speed * modifier * deltaT) );
		if ( water <= PlayerConstants.LOW_WATER_THRESHOLD )
		{
			player.SetMixedSoundState( eMixedSoundStates.THIRSTY );
			if ((player.GetStomach().GetDigestingType() & PlayerStomach.DIGESTING_WATER) == 0)
			{
				float healthModifier = GetTerjeHealthDammageModifier(player, deltaT, water);
				healthDmg = -PlayerConstants.LOW_WATER_DAMAGE_PER_SEC * healthModifier * deltaT;
				player.AddHealth("GlobalHealth", "Health", healthDmg);
			}
		}
		else
		{
			player.UnsetMixedSoundState( eMixedSoundStates.THIRSTY );
		}
		
		OnTerjeTickResult(player, deltaT, water, healthDmg);
	}
	
	protected float GetTerjeMetabolicSpeedModifier(PlayerBase player, float deltaT, float water)
	{
		return (water / PlayerConstants.SL_WATER_MAX) + PlayerConstants.CONSUMPTION_MULTIPLIER_BASE;
	}
	
	protected float GetTerjeHealthDammageModifier(PlayerBase player, float deltaT, float water)
	{
		return 1.0;
	}
	
	protected void OnTerjeTickResult(PlayerBase player, float deltaT, float water, float healthDmg)
	{
		// Override this function instead of OnTick when you need an access to water and damage results.
	}
};