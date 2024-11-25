// <copyright file="TerjePlayerModifierPsionicScriptableAreas.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierPsionicScriptableAreas : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 5.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
		if (!plugin)
		{
			return;
		}
		
		// Calculate psionic zones
		float psionicEffectPower = plugin.CalculateTerjeEffectValue(player, "psi");
		if (psionicEffectPower > 0)
		{
			float psionicGlobalModifier = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PSIONIC_AREAS_POWER_MOD);
			player.GetTerjeStats().AddMindDegradation(psionicEffectPower * psionicGlobalModifier, deltaTime);
			player.GetTerjeStats().SetMindLastPsionicPower(psionicEffectPower);
		}
	}
}