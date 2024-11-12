// <copyright file="TerjePlayerModifierDisinfected.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierDisinfected : TerjePlayerModifierBase
{
	private float m_glovesUndisinfectedTimer = 0;
	private ItemBase m_lastGloves = null;
	
	override float GetTimeout()
	{
		return 0.3;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
				
		float m_disinfectedHands = player.GetTerjeStats().GetDisinfectedHands();
		if (m_disinfectedHands > 0)
		{
			if (player.HasBloodyHands())
			{
				m_disinfectedHands = 0;
			}
			
			player.GetTerjeStats().SetDisinfectedHands(m_disinfectedHands - deltaTime);
		}
		
		bool disinfectedIndicator = false;
		ItemBase gloves = player.GetItemOnSlot("Gloves");
		if (m_lastGloves == gloves)
		{
			if (gloves)
			{
				if (gloves.IsRuined() && gloves.IsDisinfected())
				{
					gloves.SetCleanness(0);
					m_glovesUndisinfectedTimer = 0;
				}
				
				if (gloves.IsDisinfected())
				{
					m_glovesUndisinfectedTimer = m_glovesUndisinfectedTimer - deltaTime;
					if (m_glovesUndisinfectedTimer < 0)
					{
						m_glovesUndisinfectedTimer = 0;
						gloves.SetCleanness(0);
					}
				}
			}
			else
			{
				m_glovesUndisinfectedTimer = 0;
			}
		}
		else
		{			
			m_lastGloves = gloves;
			
			if (gloves && gloves.IsDisinfected())
			{
				float glovesDisinfectionTime = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_GLOVES_DISINFECTION_TIME, glovesDisinfectionTime);
				m_glovesUndisinfectedTimer = glovesDisinfectionTime;
			}
			else
			{
				m_glovesUndisinfectedTimer = 0;
			}
		}
		
		if (gloves)
		{
			if (gloves.IsDisinfected())
			{
				disinfectedIndicator = true;
			}
		}
		else if (m_disinfectedHands > 0)
		{
			disinfectedIndicator = true;
		}
		
		player.GetTerjeStats().SetDisinfected(disinfectedIndicator);
	}
};
