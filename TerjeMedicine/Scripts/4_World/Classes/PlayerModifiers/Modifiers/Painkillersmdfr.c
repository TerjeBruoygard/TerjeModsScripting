// <copyright file="Painkillersmdfr.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PainKillersMdfr: ModifierBase
{
	override protected bool ActivateCondition(PlayerBase player)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_PAIN_ENABLED) == false)
		{
			return super.ActivateCondition(player);
		}
		
		return false;
	}
	
	override protected bool DeactivateCondition(PlayerBase player)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_PAIN_ENABLED) == false)
		{
			return super.DeactivateCondition(player);
		}
		
		return false;
	}
	
	override protected void OnActivate(PlayerBase player)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_PAIN_ENABLED) == false)
		{
			super.OnActivate(player);
		}
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_PAIN_ENABLED) == false)
		{
			super.OnDeactivate(player);
		}
	}
	
	override void OnTick(PlayerBase player, float deltaT)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_PAIN_ENABLED) == false)
		{
			super.OnTick(player, deltaT);
		}
	}
}