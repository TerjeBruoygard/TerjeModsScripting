// <copyright file="BleedingSource.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class BleedingSource
{
	override void CreateParticle() {}
	override void RemoveParticle() {}
	
	override void OnUpdateServer(float deltatime, float blood_scale, bool no_blood_loss )
	{
		float perkWhealingMod;
		if (m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().GetPerkValue("immunity", "whealing", perkWhealingMod))
		{
			m_ActiveTime += deltatime * perkWhealingMod;
		}
		
		super.OnUpdateServer(deltatime, blood_scale, true);
				
		if ( !no_blood_loss )
		{
			float flow = m_FlowModifier;
			float lightBleedModifier = 1;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_LIGHT_BLEED_MODIFIER, lightBleedModifier);
			
			float hemostaticModifier = 1;
			float hemostaticValue = 0;
			float hemostaticTimer = 0;
			if (m_Player && m_Player.IsAlive() && m_Player.GetTerjeStats() && m_Player.GetTerjeStats().GetHemostatic(hemostaticValue, hemostaticTimer) && hemostaticValue > 0)
			{
				hemostaticModifier = hemostaticModifier / (hemostaticValue + 1);
			}
			
			float totalBloodLose = PlayerConstants.BLEEDING_SOURCE_BLOODLOSS_PER_SEC * lightBleedModifier * hemostaticModifier * blood_scale * deltatime * flow;
			m_Player.AddHealth("GlobalHealth","Blood", totalBloodLose);
		}
	}
}
