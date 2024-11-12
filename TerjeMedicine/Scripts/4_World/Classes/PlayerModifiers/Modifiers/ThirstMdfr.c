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
		float metabolicSpeedWaterModifier = 1;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_METABOLIC_SPEED_WATER_MODIFIER, metabolicSpeedWaterModifier);
		return super.GetTerjeMetabolicSpeedModifier(player, deltaT, water) * metabolicSpeedWaterModifier;
	}
	
	override protected float GetTerjeHealthDammageModifier(PlayerBase player, float deltaT, float water)
	{
		float waterLowDamageModifier = 1;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_WATER_LOW_DAMAGE_MODIFIER, waterLowDamageModifier);
		return super.GetTerjeHealthDammageModifier(player, deltaT, water) * waterLowDamageModifier;
	}
};
