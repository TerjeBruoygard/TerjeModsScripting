// <copyright file="BloodRegenMdfr.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class BloodRegenMdfr
{
	override float GetRegenModifierEnergy(float energy)
	{
		float result = super.GetRegenModifierEnergy(energy);
		
		float bloodRegenCommonModifier = 1;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BLOOD_REGEN_COMMON_MODIFIER, bloodRegenCommonModifier))
		{
			result = result * bloodRegenCommonModifier;
		}
		
		float perkBloodregMod;
		if (m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().GetPerkValue("immunity", "bloodreg", perkBloodregMod))
		{
			result = result * (1.0 + perkBloodregMod);
		}
		
		return result;
	}
}
