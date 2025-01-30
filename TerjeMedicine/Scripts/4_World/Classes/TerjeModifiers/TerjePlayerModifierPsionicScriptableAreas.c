// <copyright file="TerjePlayerModifierPsionicScriptableAreas.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierPsionicScriptableAreas : TerjePlayerModifierBase
{
	private int m_hasAbsoluteCustomProtection = -1;
	
	override float GetTimeout()
	{
		return 1.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
		if (!plugin)
		{
			return;
		}
		
		if (m_hasAbsoluteCustomProtection == -1)
		{
			if (plugin.HasAbsoluteCustomProtectionOfType(player, "psionic"))
			{
				m_hasAbsoluteCustomProtection = 1;
			}
			else
			{
				m_hasAbsoluteCustomProtection = 0;
			}
		}
		
		if (m_hasAbsoluteCustomProtection == 1)
		{
			return;
		}
		
		// Calculate psionic zones
		float psionicEffectPower = plugin.CalculateTerjeEffectValue(player, "psionic");
		if (psionicEffectPower > 0)
		{
			float psionicGlobalModifier = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PSIONIC_AREAS_POWER_MOD);
			float protectionMod = 1.0 - GetTerjeScriptableAreas().CalculatePlayerBodyProtection(player, "psionic", psionicEffectPower);
			player.GetTerjeStats().AddMindDegradation(psionicEffectPower * psionicGlobalModifier * protectionMod, deltaTime);
		}
	}
}