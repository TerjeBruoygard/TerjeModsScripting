// <copyright file="TerjePlayerModifierBloodRegen.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierBloodRegen : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float bloodRegenValue = 0;
		float bloodRegenTimer = 0;
		if (player.GetTerjeStats().GetBloodRegen(bloodRegenValue, bloodRegenTimer))
		{			
			if (bloodRegenTimer > 0)
			{
				player.GetTerjeStats().SetBloodRegen(bloodRegenValue, bloodRegenTimer - deltaTime);
			}
			else if (bloodRegenValue > 0)
			{
				player.GetTerjeStats().SetBloodRegen(0, 0);
			}
		}
		
		if (bloodRegenValue > 0)
		{
			float bloodRegenMedsModifier = 1;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BLOOD_REGEN_MEDS_MODIFIER, bloodRegenMedsModifier);
			player.AddHealth("GlobalHealth", "Blood", bloodRegenValue * bloodRegenMedsModifier * deltaTime);
		}
	}
}
