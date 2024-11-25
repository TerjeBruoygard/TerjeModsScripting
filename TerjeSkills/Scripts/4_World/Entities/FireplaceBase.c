// <copyright file="FireplaceBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class FireplaceBase
{
	private float m_terjeSurvSkillBasedModifier = 1.0;
	
	void SetTerjeSkillSurvFuelModifier(float value)
	{
		m_terjeSurvSkillBasedModifier = value;
	}
	
	override protected float GetFuelBurnRateMP()
	{
		if (m_terjeSurvSkillBasedModifier > 1)
		{
			return super.GetFuelBurnRateMP() / m_terjeSurvSkillBasedModifier;
		}
		
		return super.GetFuelBurnRateMP();
	}
}