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
		float metabolicSpeedEnergyModifier = 1;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_METABOLIC_SPEED_ENERGY_MODIFIER, metabolicSpeedEnergyModifier);
		return super.GetTerjeMetabolicSpeedModifier(player, deltaT, energy) * metabolicSpeedEnergyModifier;
	}
	
	override protected float GetTerjeHealthDammageModifier(PlayerBase player, float deltaT, float energy)
	{
		float energyLowDamageModifier = 1;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ENERGY_LOW_DAMAGE_MODIFIER, energyLowDamageModifier);
		return super.GetTerjeHealthDammageModifier(player, deltaT, energy) * energyLowDamageModifier;
	}
};
