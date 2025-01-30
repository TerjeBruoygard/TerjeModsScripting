// <copyright file="ItemBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ItemBase
{
	private float m_terjeSkillsDamageModifier = 1.0;
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && IsClothing())
		{
			float perkValue;
			float actualHP = GetHealth("", "Health");
			if (actualHP > 0)
			{
				PlayerBase ownerPlayer = PlayerBase.Cast(this.GetHierarchyRootPlayer());
				if (ownerPlayer && ownerPlayer.IsAlive() && ownerPlayer.GetTerjeSkills() != null && ownerPlayer.GetTerjeSkills().GetPerkValue("surv", "durequip", perkValue))
				{
					m_terjeSkillsDamageModifier = Math.Clamp(1.0 + perkValue, 0, 1);
				
					float addHealth = damageResult.GetDamage("", "Health") * Math.Clamp(Math.AbsFloat(perkValue), 0, 1);
					if (addHealth > 0)
					{
						AddHealth("", "Health", addHealth);
					}
				}
			}
		}
		
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		m_terjeSkillsDamageModifier = 1.0;
	}
	
	override bool DamageItemInCargo(float damage)
	{
		return super.DamageItemInCargo(damage * m_terjeSkillsDamageModifier);
	}
	
	override bool DamageItemAttachments(float damage)
	{
		return super.DamageItemAttachments(damage * m_terjeSkillsDamageModifier);
	}
}