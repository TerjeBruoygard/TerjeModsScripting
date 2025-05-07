// <copyright file="TerjePlayerModifierComa.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierComa : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 3;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		bool hasAdrenalin = false;
		if (player.GetTerjeStats() != null && player.GetTerjeStats().GetAdrenalinValue() > 0)
		{
			hasAdrenalin = true;
		}
		
		if (!hasAdrenalin)
		{
			float immunityMod = Math.Clamp(1.0 - GetPlayerImmunity(player), 0, 1);
			bool criticalBlood = player.GetHealth("GlobalHealth", "Blood") < (PlayerConstants.SL_BLOOD_CRITICAL * immunityMod);
			bool criticalHealth = player.GetHealth("GlobalHealth", "Health") < (PlayerConstants.SL_HEALTH_CRITICAL * immunityMod);
			if (criticalBlood || criticalHealth)
			{
				bool enableMedicalComa = false;
				if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_MEDICAL_COMA, enableMedicalComa) && enableMedicalComa)
				{
					SetPlayerShock(player, TerjeDamageSource.COMA, 0);
				}
			}
		}
	}
}
