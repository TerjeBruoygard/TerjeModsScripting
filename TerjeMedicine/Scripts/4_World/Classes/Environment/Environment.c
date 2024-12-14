// <copyright file="Environment.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Environment
{
	override protected float GetPlayerHeat()
	{
		float result = super.GetPlayerHeat();
		
		if (m_Player && m_Player.IsAlive() && m_Player.GetTerjeStats())
		{
			int influenzaLevel = m_Player.GetTerjeStats().GetInfluenzaLevel();
			if (influenzaLevel > 0)
			{
				float influenzaBodyTemperatureModifier = 0;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INFLUENZA_BODY_TEMPERATURE_MODIFIER, influenzaBodyTemperatureModifier))
				{
					result = result + (influenzaLevel * influenzaBodyTemperatureModifier);
				}
			}
			
			int rabiesLevel = m_Player.GetTerjeStats().GetRabiesLevel();
			if (rabiesLevel > 0)
			{
				float rabiesBodyTemperatureModifier = 0;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_BODY_TEMPERATURE_MODIFIER, rabiesBodyTemperatureModifier))
				{
					result = result + (rabiesLevel * rabiesBodyTemperatureModifier);
				}
			}
		}
		
		return result;
	}
}
