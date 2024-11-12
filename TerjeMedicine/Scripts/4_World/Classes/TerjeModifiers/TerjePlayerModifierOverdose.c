// <copyright file="TerjePlayerModifierOverdose.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierOverdose : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 0.5;
	};
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_OVERDOSE_ENABLED) == false)
		{
			return;
		}
		
		float overdoseValue = player.GetTerjeStats().GetOverdoseValue();
		if (overdoseValue > 0)
		{
			float perkIntoxicresMod;
			if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("immunity", "intoxicres", perkIntoxicresMod))
			{
				perkIntoxicresMod = 1.0 + perkIntoxicresMod;
			}
			else
			{
				perkIntoxicresMod = 1.0;
			}
			
			float overdoseDecPerSec = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_OVERDOSE_DEC_PER_SEC, overdoseDecPerSec);	
			overdoseValue = overdoseValue - (overdoseDecPerSec * perkIntoxicresMod * deltaTime);		
			player.GetTerjeStats().SetOverdoseValue(overdoseValue);
			
			if (overdoseValue > 2)
			{
				if (player.GetHealth("", "Shock") > 50)
				{
					float overdoseUnconsciousChance = 0;
					if (GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_OVERDOSE_UNCONSCIOUS_CHANCE, overdoseUnconsciousChance) && Math.RandomFloat01() < overdoseUnconsciousChance * deltaTime)
					{
						player.SetHealth("","Shock",0);
					}
				}
			}
			
			
			if (overdoseValue > 3)
			{
				float overdoseCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_OVERDOSE_CRITICAL_DMG_MULTIPLIER, overdoseCriticalDmgMultiplier);
				player.DecreaseHealth("GlobalHealth","Health", overdoseCriticalDmgMultiplier * (overdoseValue - 3) * deltaTime);
			}
		}
	}
};
