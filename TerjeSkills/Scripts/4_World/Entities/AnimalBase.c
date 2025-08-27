// <copyright file="AnimalBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class AnimalBase
{
	private Particle m_terjeHighlightParticle;
	private bool m_terjeHasReceivedDamage = false;
	private bool m_terjeHasHeadshotDamage = false;
	private bool m_terjeIsExperienceProcessed = false;
	private EntityAI m_terjeLastDamageSource = null;
	private vector m_terjeLastAnimalPos = vector.Zero;
	
	bool HasTerjeReceivedDamage()
	{
		return m_terjeHasReceivedDamage;
	}
	
	bool HasTerjeHeadshotDamage()
	{
		return m_terjeHasHeadshotDamage;
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		m_terjeLastDamageSource = source;
		m_terjeHasReceivedDamage = true;
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (dmgZone == "Zone_Head")
		{
			m_terjeHasHeadshotDamage = true;
		}
		else
		{
			m_terjeHasHeadshotDamage = false;
		}
		
		TerjeHuntingExperienceProcessing(source);
		TerjeHuntingDamageProcessing(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
	
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
		
		EntityAI killerEntity = EntityAI.Cast(killer);
		if (killerEntity != null)
		{
			TerjeHuntingExperienceProcessing(killerEntity);
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (GetGame().IsClient() && m_terjeHighlightParticle)
		{
			m_terjeHighlightParticle.Stop();
		}
	}
	
	override bool IsTerjeClientUpdateRequired()
	{
		return true;
	}
	
	override void OnTerjeClientUpdate(float deltaTime)
	{
		super.OnTerjeClientUpdate(deltaTime);
		
		if (GetGame().IsClient())
		{
			bool showParticles = false;
			if (IsAlive() && GetTerjeGameConfig().ConfigGetBool("CfgVehicles " + GetType() + " terjeHighlightWithPathfinder"))
			{
				if (m_terjeLastAnimalPos != vector.Zero)
				{
					float distance = vector.Distance(m_terjeLastAnimalPos, GetWorldPosition());
					if (distance >= 2.5)
					{
						PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
						if (localPlayer && localPlayer.GetTerjeSkills() && localPlayer.GetTerjeSkills().GetPerkLevel("hunt", "pathfindr") > 0)
						{
							showParticles = true;
						}
					}
				}
			}
			
			if (showParticles)
			{
				if (!m_terjeHighlightParticle)
				{
					m_terjeHighlightParticle = ParticleManager.GetInstance().PlayOnObject(ParticleList.TERJE_SKILLS_ANIMALS_HIGHLIGHT, this);
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
			
			m_terjeLastAnimalPos = GetWorldPosition();
		}
	}
	
	// We use additional logic to process killer player, because EEKilled method has a bug and from time to time returns self animal as a killer.
	void TerjeHuntingExperienceProcessing(EntityAI killer)
	{
		if (m_terjeIsExperienceProcessed)
		{
			return;
		}
		
		if (IsAlive())
		{
			return;
		}
		
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void TerjeHuntingDamageProcessing(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{		
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
}
