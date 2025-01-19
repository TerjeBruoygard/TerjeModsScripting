// <copyright file="TerjePlayerModifierHematomas.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierHematomas : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float salveTimer = player.GetTerjeStats().GetSalveValue();
		if (salveTimer > 0)
		{			
			player.GetTerjeStats().SetSalveValue(salveTimer - deltaTime);
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_HEMATOMAS_ENABLED) == false)
		{
			player.GetTerjeStats().SetHematomas(0);
			return;
		}
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		float hematomas = player.GetTerjeStats().GetHematomas();
		if (hematomas > 0)
		{
			int hematomasIntOrig = (int)hematomas;
			float hematomaHealModifier = 1;
			if (salveTimer > 0)
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEMATOMAS_HEAL_MEDS_MODIFIER, hematomaHealModifier);
			}
			else
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEMATOMAS_HEAL_COMMON_MODIFIER, hematomaHealModifier);
			}	
			
			float perkHematomrecMod;
			if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("immunity", "hematomrec", perkHematomrecMod))
			{
				hematomaHealModifier = hematomaHealModifier * (1.0 + perkHematomrecMod);
			}
			
			hematomas = hematomas - (hematomaHealModifier * deltaTime);
			player.GetTerjeStats().SetHematomas(hematomas);
			
			float hematomasCriticalCount = 1;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEMATOMAS_CRITICAL_COUNT, hematomasCriticalCount);
			if (hematomas > hematomasCriticalCount)
			{
				float hematomasCriticalDamage = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEMATOMAS_CRITICAL_DAMAGE, hematomasCriticalDamage);
				
				float dmgForce = (hematomas - hematomasCriticalCount) * hematomasCriticalDamage;
				player.DecreaseHealth("GlobalHealth", "Health", dmgForce * deltaTime);
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
			}
			
			if ((int)hematomas < hematomasIntOrig)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_HEMATOMA_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
				}
			}
		}
	}
}
