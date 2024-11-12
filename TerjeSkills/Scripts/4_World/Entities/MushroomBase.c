// <copyright file="MushroomBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class MushroomBase
{
	private Particle m_terjeHighlightParticle;
	
	override bool IsTerjeClientUpdateRequired()
	{
		return true;
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (GetGame().IsClient() && m_terjeHighlightParticle)
		{
			m_terjeHighlightParticle.Stop();
		}
	}
	
	override void OnTerjeClientUpdate(float deltaTime)
	{
		super.OnTerjeClientUpdate(deltaTime);
		
		if (GetGame().IsClient())
		{
			bool showParticles = false;
			if (GetFoodStage() && GetHierarchyParent() == null)
			{
				FoodStageType foodStageType = GetFoodStageType();
				if (foodStageType == FoodStageType.RAW || foodStageType == FoodStageType.ROTTEN || foodStageType == FoodStageType.DRIED)
				{
					PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
					if (localPlayer && localPlayer.GetTerjeSkills() && localPlayer.GetTerjeSkills().GetPerkLevel("surv", "mushprem") > 0)
					{
						showParticles = true;
					}
				}
			}
			
			if (showParticles)
			{
				if (!m_terjeHighlightParticle)
				{
					m_terjeHighlightParticle = ParticleManager.GetInstance().PlayOnObject(ParticleList.TERJE_SKILLS_MUSHROOMS_HIGHLIGHT, this);
				}
			}
			else
			{
				if (m_terjeHighlightParticle)
				{
					m_terjeHighlightParticle.Stop();
					m_terjeHighlightParticle = null;
				}
			}
		}
	}
}