// <copyright file="RedefineInjectors.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Morphine
{
	override void OnApply(PlayerBase player)
	{
		super.OnApply(player);
		ApplyTerjeConsumableEffects(player, 1);
	}
};

modded class Epinephrine
{
	override void OnApply(PlayerBase player)
	{
		super.OnApply(player);
		ApplyTerjeConsumableEffects(player, 1);
	}
};

modded class AntiChemInjector
{
	override void OnApply(PlayerBase player)
	{
		super.OnApply(player);
		ApplyTerjeConsumableEffects(player, 1);
	}
};