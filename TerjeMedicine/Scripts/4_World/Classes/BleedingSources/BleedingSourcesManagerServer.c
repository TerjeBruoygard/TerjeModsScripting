// <copyright file="BleedingSourcesManagerServer.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class BleedingSourcesManagerServer
{	
	bool TerjeAttemptRemoveBleedingSource(int component)
	{
		int bit = GetBitFromSelectionID(component);
		
		if ( bit == 0 )
		{
			return false;
		}
		
		return RemoveBleedingSource(bit);
	}
	
	override void RemoveMostSignificantBleedingSource()
	{
		if (m_Player.GetTerjeStats())
		{
			if (m_Player.GetTerjeStats().GetStubWounds() > 0)
			{
				m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() - 1);
				m_Player.GetTerjeStats().SetBandagesClean(m_Player.GetTerjeStats().GetBandagesClean() + 1);
			}
			else if (m_Player.GetTerjeStats().GetSuturesClean() > 0)
			{
				m_Player.GetTerjeStats().SetSuturesClean(m_Player.GetTerjeStats().GetSuturesClean() - 1);
				m_Player.GetTerjeStats().SetSuturesBandagedClean(m_Player.GetTerjeStats().GetSuturesBandagedClean() + 1);
			}
			else if (m_Player.GetTerjeStats().GetSuturesDirty() > 0)
			{
				m_Player.GetTerjeStats().SetSuturesDirty(m_Player.GetTerjeStats().GetSuturesDirty() - 1);
				m_Player.GetTerjeStats().SetSuturesBandagedClean(m_Player.GetTerjeStats().GetSuturesBandagedClean() + 1);
			}
			else
			{
				super.RemoveMostSignificantBleedingSource();
			}
		}
		else
		{
			super.RemoveMostSignificantBleedingSource();
		}
	}
	
	float TerjeCalculateZoneProtection(string zone, string protection)
	{
		if (zone == "")
		{
			return 0;
		}
		
		if (zone == "Torso")
		{
			return TerjeCalculateAttachmentProtection("Vest", protection) + TerjeCalculateAttachmentProtection("Body", protection);
		}
		
		if (zone == "Head" || zone == "Brain")
		{
			return TerjeCalculateAttachmentProtection("Headgear", protection) + TerjeCalculateAttachmentProtection("Mask", protection);
		}
		
		if (zone == "LeftArm" || zone == "RightArm")
		{
			return TerjeCalculateAttachmentProtection("Body", protection);
		}
		
		if (zone == "LeftHand" || zone == "RightHand")
		{
			return TerjeCalculateAttachmentProtection("Gloves", protection);
		}
		
		if (zone == "LeftLeg" || zone == "RightLeg")
		{
			return TerjeCalculateAttachmentProtection("Legs", protection);
		}
		
		if (zone == "LeftFoot" || zone == "RightFoot")
		{
			return TerjeCalculateAttachmentProtection("Feet", protection);
		}
		
		return 0;
	}
	
	float TerjeCalculateAttachmentProtection(string slotName, string protection)
	{
		ItemBase attachment = m_Player.GetItemOnSlot(slotName);
		if (attachment && !attachment.IsRuined())
		{
			return GetGame().ConfigGetFloat("CfgVehicles " + attachment.GetType() + " Protection " + protection);
		}
		
		return 0;
	}
	
	float TerjeBallisticCalculatorProcess(EntityAI source, string ammo)
	{
		float firearmArmorModifier = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_ARMOR_MODIFIER);
		float firearmBalliscticCalculatorSpeedMod = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_BALLISCTIC_CALCULATOR_SPEED_MOD);
		float firearmBalliscticCalculatorCaliberMod = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_BALLISCTIC_CALCULATOR_CALIBER_MOD);
		float firearmBalliscticCalculatorWeightMod = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_BALLISCTIC_CALCULATOR_WEIGHT_MOD);
		float firearmBalliscticCalculatorAPMod = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_FIREARM_BALLISCTIC_CALCULATOR_A_P_MOD);
		float distanceMod = Math.Clamp(1300 - vector.Distance(source.GetPosition(), m_Player.GetPosition()), 100, 1000) * 0.001;
		float bulletSpeed = GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " typicalSpeed" ) * 0.1 * firearmBalliscticCalculatorSpeedMod;
		float bulletCaliber = GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " caliber" ) * firearmBalliscticCalculatorCaliberMod;
		float bulletWeight = GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " weight" ) * firearmBalliscticCalculatorWeightMod;
		float armorDamage = Math.Max(GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " DamageApplied Health armorDamage" ), 1) * firearmBalliscticCalculatorAPMod;
		float penetrationCalcModifier = bulletSpeed * bulletCaliber * distanceMod * bulletWeight * armorDamage * firearmArmorModifier;
		
		// Divide damage for crossbow bolts
		if (ammo.LastIndexOf("Bolt") != -1)
		{
			penetrationCalcModifier *= 0.1;
		}
		
		return penetrationCalcModifier;
	}
	
	override void ProcessHit(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
		// Call super.ProcessHit to compatibility with other mods
		super.ProcessHit(damage, source, component, zone, ammo, modelPos);
		
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	bool TerjeCustomProcessHit_Zombie(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from zombies.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_Animal(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from animal.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_Melee(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from melee weapon.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_Projectile(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from projectile (firearm).
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_FragGrenade(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from explosions (grenades).
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_Nonlethal(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from nonlethal ammo (rubber bullets by example).
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_BearTrap(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from bear trap.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
	
	bool TerjeOverrideProcessHit_BarbedWire(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from bear trap.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return true;
	}
}
