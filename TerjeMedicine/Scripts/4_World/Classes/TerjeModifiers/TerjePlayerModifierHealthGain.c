// <copyright file="TerjePlayerModifierHealthGain.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierHealthGain : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float healthGainTimer = player.GetTerjeStats().GetHealthExtraRegenTimer();
		if (healthGainTimer > 0)
		{
			float gainPower = Math.Clamp(1.0 - GetPlayerHealth01(player), 0, 1);
			float gainPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEALTH_REGEN_MEDS_PER_SEC);
			if (gainPower > 0 && gainPerSec > 0)
			{
				AddPlayerHealth(player, gainPerSec * gainPower * deltaTime);
			}
			
			player.GetTerjeStats().SetHealthExtraRegenTimer(healthGainTimer - deltaTime);
		}
	}
}
