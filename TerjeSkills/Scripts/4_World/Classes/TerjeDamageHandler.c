// <copyright file="TerjeDamageHandler.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeDamageHandler
{
	private static ref TerjeDamageHandler m_Instance = null;
	static ref TerjeDamageHandler GetInstance()
	{
		if (m_Instance == null)
		{
			m_Instance = new TerjeDamageHandler;
		}
		
		return m_Instance;
	}
	
	bool IsStrengthExperienceRequired(string ammo, string ammoType)
	{
		if (ammo.IndexOf("FlashLight") == 0)
		{
			return false; // Compatibility
		}
		
		if (GetTerjeGameConfig().ConfigGetBool( "CfgAmmo " + ammo + " terjeIgnoreExpStrength" ))
		{
			return false;
		}
		
		return true;
	}
	
	void TerjeCommitAdditionalPerkDamage(EntityAI source, EntityAI target, string dmgZone, string ammoName, vector modelPos, float damageCoef, int delay)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, EntityAI target, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void EEHitBy_MasterStrikePerk(TotalDamageResult damageResult, int damageType, PlayerBase sourcePlayer, EntityAI target, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if ((dmgZone == "Head") && (sourcePlayer.GetTerjeSkills() != null) && (sourcePlayer.GetTerjeSkills().GetPerkLevel("strng", "mrstroke") > 0))
		{
			if (target.IsMan())
			{
				TerjeCommitAdditionalPerkDamage(sourcePlayer, target, dmgZone, "Dummy_TerjeStrengthMStroke", modelPos, 1.0, 200);
			}
			else if (target.IsAnimal() || target.IsZombie())
			{
				TerjeCommitAdditionalPerkDamage(sourcePlayer, target, dmgZone, "Dummy_TerjeStrengthMStrokeAlt", modelPos, 1.0, 200);
			}
		}
	}
}
