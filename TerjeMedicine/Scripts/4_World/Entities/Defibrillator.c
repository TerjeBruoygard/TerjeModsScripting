// <copyright file="Defibrillator.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Defibrillator
{
	override void DischargeServer(PlayerBase victim)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_KNOCKOUT_REVIVE_BY_DEF))
		{
			PlayerBase operator = PlayerBase.Cast(this.GetHierarchyRootPlayer());
			if (TerjeDefibrilateKnockoutServer(victim, operator))
			{
				return;
			}
		}
		
		super.DischargeServer(victim);
	}
	
	bool TerjeDefibrilateKnockoutServer(PlayerBase victim, PlayerBase operator)
	{
		if (victim && victim.GetTerjeHealth() && victim.GetTerjeStats() && victim.GetTerjeStats().IsInKnockout())
		{
			if (victim.GetTerjeHealth().GetHealth() < PlayerConstants.SL_HEALTH_LOW)
			{
				victim.GetTerjeHealth().SetHealth(PlayerConstants.SL_HEALTH_LOW, TerjeDamageSource.COMA);
			}
			
			if (victim.GetTerjeHealth().GetBlood() < PlayerConstants.SL_BLOOD_LOW)
			{
				victim.GetTerjeHealth().SetBlood(PlayerConstants.SL_BLOOD_LOW, TerjeDamageSource.COMA);
			}
			
			victim.GiveShock(100);
			return true;
		}
		
		return false;
	}
}