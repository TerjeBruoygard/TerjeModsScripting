// <copyright file="ContaminationMdfr.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ContaminationStage1Mdfr
{
	override protected bool ActivateCondition(PlayerBase player)
	{
		return false;
	}
	
	override protected bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}
	
	override protected void OnActivate(PlayerBase player)
	{

	}

	override protected void OnDeactivate(PlayerBase player)
	{

	}
	
	override protected void OnTick(PlayerBase player, float deltaT)
	{
		
	}
}

modded class ContaminationStage2Mdfr
{
	override protected bool ActivateCondition(PlayerBase player)
	{
		return false;
	}
	
	override protected bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}
	
	override protected void OnActivate(PlayerBase player)
	{

	}

	override protected void OnDeactivate(PlayerBase player)
	{

	}
	
	override protected void OnTick(PlayerBase player, float deltaT)
	{
		
	}
}

modded class ContaminationStage3Mdfr
{
	override protected bool ActivateCondition(PlayerBase player)
	{
		return false;
	}
	
	override protected bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}
	
	override protected void OnActivate(PlayerBase player)
	{

	}

	override protected void OnDeactivate(PlayerBase player)
	{

	}
	
	override protected void OnTick(PlayerBase player, float deltaT)
	{
		
	}
}

modded class AreaExposureMdfr
{
	override void BleedingSourceCreateCheck(PlayerBase player)
	{
		bool biohazardSkinIrritation = false;
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_BIOHAZARD_SKIN_IRRITATION, biohazardSkinIrritation) && biohazardSkinIrritation)
		{
			super.BleedingSourceCreateCheck(player);
		}
	}
	
	override void ApplyAgentsToBleedingSources(PlayerBase player, float deltaT)
	{
		super.ApplyAgentsToBleedingSources(player, deltaT);
		
		if (player && player.GetTerjeStats())
		{
			int openWounds = player.GetTerjeStats().GetStubWounds();
			if (openWounds > 0)
			{
				player.InsertAgent(eAgents.CHEMICAL_POISON, openWounds * deltaT);
			}
		}
	}
}

