// <copyright file="Environment.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Environment
{
	override void ProcessHeatComfort()
	{
		if (m_Player && m_Player.GetTerjeDisableHeatComfort())
		{
			m_HeatComfort = 0.0;
 			SetTargetHeatComfort(0.0);
 			m_Player.GetStatHeatComfort().Set(0.0);
			return;
		}
		
		super.ProcessHeatComfort();
	}
	
	override void SetHeatcomfortDirectly()
	{
		if (m_Player && m_Player.GetTerjeDisableHeatComfort())
		{
			m_HeatComfort = 0.0;
 			SetTargetHeatComfort(0.0);
 			m_Player.GetStatHeatComfort().Set(0.0);
			return;
		}
		
		super.SetHeatcomfortDirectly();
	}
}