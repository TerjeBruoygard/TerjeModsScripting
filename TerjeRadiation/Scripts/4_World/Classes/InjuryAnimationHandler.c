// <copyright file="InjuryAnimationHandler.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class InjuryAnimationHandler
{
	override eInjuryHandlerLevels GetInjuryLevel(float health)
	{
		eInjuryHandlerLevels result = super.GetInjuryLevel(health);
		
		if (m_Player && m_Player.GetTerjeStats())
		{
			eInjuryHandlerLevels radiationSickness = CalculateRadiationState();
			if (TerjeInjuryLevelToValue(result) < TerjeInjuryLevelToValue(radiationSickness))
			{
				result = radiationSickness;
			}
		}
		
		return result;
	}
	
	private eInjuryHandlerLevels CalculateRadiationState()
	{
		int radLevel = m_Player.GetTerjeStats().GetRadiationLevel();
		if (radLevel == 1)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		if (radLevel == 2)
		{
			return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		
		if (radLevel == 3)
		{
			return eInjuryHandlerLevels.RUINED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
};