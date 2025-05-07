// <copyright file="TerjeArtifactBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeArtifactBase extends ItemBase
{
	protected PointLightBase m_terjeArtIdleLight = null;
	protected Particle m_terjeArtEffectIdle = null;
	
	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame() && GetGame().IsClient())
		{
			InventoryLocation location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation(location);
			if(location.GetType() == InventoryLocationType.GROUND || location.GetType() == InventoryLocationType.HANDS)
			{
				StartEffects();
			}
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if(GetGame() && GetGame().IsClient())
		{
			StopEffects();
		}
	}
	
	
	override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
	{
		super.EEItemLocationChanged(oldLoc, newLoc);
		
		if(GetGame() && GetGame().IsClient())
		{
			if(newLoc.GetType() == InventoryLocationType.GROUND || newLoc.GetType() == InventoryLocationType.HANDS)
			{
				StartEffects();
			}
			else
			{
				StopEffects();
			}
		}
	}
	
	protected void StartEffects()
	{
		
	}
	
	protected void StopEffects()
	{
		if (m_terjeArtIdleLight != null)
		{
			m_terjeArtIdleLight.FadeOut();
			m_terjeArtIdleLight = null;
		}
		
		if (m_terjeArtEffectIdle != null)
		{
			m_terjeArtEffectIdle.StopParticle();
			m_terjeArtEffectIdle = null;
		}
	}
};