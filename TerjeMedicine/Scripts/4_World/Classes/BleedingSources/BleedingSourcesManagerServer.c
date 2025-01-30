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
		return TerjeOverrideProcessHit_FromConfig(damage, source, component, zone, ammo, modelPos, playerTakeDammage);
	}
	
	bool TerjeOverrideProcessHit_Animal(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// Override this function in your mod if you need to override my logic for getting wounds from animal.
		// Retrun "true" by default to call my wounds logic, false to disable it.
		return TerjeOverrideProcessHit_FromConfig(damage, source, component, zone, ammo, modelPos, playerTakeDammage);
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
	
	bool TerjeOverrideProcessHit_FromConfig(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos, inout bool playerTakeDammage)
	{
		// You can configure wounds for modded animals and zombies using the TerjeCustomInjuries class in config.cpp
		/*
			class CfgVehicles
			{
				class AnimalBase;
				class YourCustomAnimal: AnimalBase
				{
					class TerjeCustomInjuries
					{
						// Ignore a player's block and armor when calculating a hit hit. (0 = false, 1 = true)
						ignorePlayerBlock=0;
						
						// Overwrite default TerjeMedicine wounds with wounds from the config or not (0 = false, 1 = true)
						overrideDefaultInjueries=1;
						
						// The chance of bleeding on hit (0.0 = 0%, 1.0 = 100%)
						lightBleedingChance=0.0;
						heavyBleedingChance=0.0;
						internalBleedingChance=0.0;
						
						// The chance of hematoma (bruise) on hit (0.0 = 0%, 1.0 = 100%)
						hematomaChance=0.0;
						
						// Chance of concussion (brain contusion) (0.0 = 0%, 1.0 = 100%)
						lightContussionChance=0.0;
						heavyContussionChance=0.0;
						
						// Biohazard (chemical poision)
						chemicalPoisonChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						chemicalPoisonValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Influenza
						infuenzaInfectionChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						infuenzaInfectionValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Radiation (when you have TerjeRadiation mod)
						radiationChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						radiationValue=0.0; // Value added to the radiation buffer of player
						
						// Zomvie virus
						zombieVirusChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						zombieVirusValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Sepsis (blood poisoning)
						sepsisInfectionChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						sepsisInfectionValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Rabies
						rabiesVirusChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						rabiesVirusValue=0.0; // Value 1.0 for level 1, 2.0 for level 2 etc...
						
						// Mind (mental) damage. For Stalker PSI mutants
						psiDamageChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						psiDamageValue=0.0; // Mind damage per second (10 for example)
						psiDamageTime=0.0; // Time of effect in seconds (5 for example)
						
						// Sleeping damage.
						sleepDamageChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
						sleepDamageValue=0.0; // Sleeping damage per second (10 for example)
						sleepDamageTime=0.0; // Time of effect in seconds (5 for example)
					};
				};
			};
		*/
		if (GetGame() && source && m_Player && m_Player.GetTerjeStats() != null)
		{
			float value;
			string configRoot = "CfgVehicles " + source.GetType() + " TerjeCustomInjuries";
			if (GetGame().ConfigIsExisting(configRoot))
			{
				if (GetGame().ConfigGetInt(configRoot + " ignorePlayerBlock") == 1)
				{
					playerTakeDammage = true;
				}
				
				if (playerTakeDammage)
				{
					value = GetGame().ConfigGetFloat(configRoot + " lightBleedingChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						AttemptAddBleedingSource(component);
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " heavyBleedingChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() + 1);
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " internalBleedingChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetViscera(true);
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " hematomaChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetHematomas(m_Player.GetTerjeStats().GetHematomas() + 1);
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " lightContussionChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_LIGHT);
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " heavyContussionChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_HEAVY);
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " chemicalPoisonChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetBiohazardValue(m_Player.GetTerjeStats().GetBiohazardValue() + GetGame().ConfigGetFloat(configRoot + " chemicalPoisonValue"));
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " infuenzaInfectionChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetInfluenzaValue(m_Player.GetTerjeStats().GetInfluenzaValue() + GetGame().ConfigGetFloat(configRoot + " infuenzaInfectionValue"));
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " radiationChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.AddTerjeRadiation(GetGame().ConfigGetFloat(configRoot + " radiationValue"));
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " zombieVirusChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetZVirusValue(m_Player.GetTerjeStats().GetZVirusValue() + GetGame().ConfigGetFloat(configRoot + " zombieVirusValue"));
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " sepsisInfectionChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetSepsisValue(m_Player.GetTerjeStats().GetSepsisValue() + GetGame().ConfigGetFloat(configRoot + " sepsisInfectionValue"));
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " rabiesVirusChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().SetRabiesValue(m_Player.GetTerjeStats().GetRabiesValue() + GetGame().ConfigGetFloat(configRoot + " rabiesVirusValue"));
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " psiDamageChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().AddMindDegradation(GetGame().ConfigGetFloat(configRoot + " psiDamageValue"), GetGame().ConfigGetFloat(configRoot + " psiDamageTime"));
					}
					
					value = GetGame().ConfigGetFloat(configRoot + " sleepDamageChance");
					if (value > 0 && Math.RandomFloat01() < value)
					{
						m_Player.GetTerjeStats().AddSleepingDecrement(GetGame().ConfigGetFloat(configRoot + " sleepDamageValue"), GetGame().ConfigGetFloat(configRoot + " sleepDamageTime"));
					}
				}
				
				if (GetGame().ConfigGetInt(configRoot + " overrideDefaultInjueries") == 1)
				{
					return false;
				}
			}
		}
		
		return true;
	}
}
