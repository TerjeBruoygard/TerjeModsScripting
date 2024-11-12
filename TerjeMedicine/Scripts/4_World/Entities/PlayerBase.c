// <copyright file="PlayerBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

enum TerjeMedicineWoundsMask
{
	TERJE_MED_WOUNDS_MASK_STUB = 0,
	TERJE_MED_WOUNDS_MASK_BULLET,
	TERJE_MED_WOUNDS_MASK_VISCERA,
	TERJE_MED_WOUNDS_MASK_SUTURE,
	TERJE_MED_WOUNDS_MASK_SUTURE_DIRTY,
	TERJE_MED_WOUNDS_MASK_DIRTYBANDAGE,
	TERJE_MED_WOUNDS_MASK_STUB_SURGERY
};

modded class PlayerBase
{
	private int m_terjeMedWoundsMask = 0;
	private int m_terjeRadiationSynch = 0;
	
	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableInt("m_terjeMedWoundsMask");
		RegisterNetSyncVariableInt("m_terjeRadiationSynch", 0, TerjeMedicineConstants.RADIATION_PLAYER_ACCUMULATOR_SYNCH_MAX);
	}
	
	override void OnTerjeRegisterModifiers(ref array<ref TerjePlayerModifierBase> modifiers)
	{
		super.OnTerjeRegisterModifiers(modifiers);
		
		modifiers.Insert(new TerjePlayerModifierScriptableAreas());
		modifiers.Insert(new TerjePlayerModifierSleeping());
		modifiers.Insert(new TerjePlayerModifierMind());
		modifiers.Insert(new TerjePlayerModifierPain());
		modifiers.Insert(new TerjePlayerModifierSepsis());
		modifiers.Insert(new TerjePlayerModifierZVirus());
		modifiers.Insert(new TerjePlayerModifierPoison());
		modifiers.Insert(new TerjePlayerModifierInfluenza());
		modifiers.Insert(new TerjePlayerModifierOverdose());
		modifiers.Insert(new TerjePlayerModifierContusion());
		modifiers.Insert(new TerjePlayerModifierHemostatic());
		modifiers.Insert(new TerjePlayerModifierBloodRegen());
		modifiers.Insert(new TerjePlayerModifierHematomas());
		modifiers.Insert(new TerjePlayerModifierAdrenalin());
		modifiers.Insert(new TerjePlayerModifierRadiation());
		modifiers.Insert(new TerjePlayerModifierDisinfected());
		modifiers.Insert(new TerjePlayerModifierComa());
		modifiers.Insert(new TerjePlayerModifierWounds());
		modifiers.Insert(new TerjePlayerModifierBiohazard());
		modifiers.Insert(new TerjePlayerModifierRabies());
	}
	
	override void OnTerjeRPC(PlayerIdentity sender, string id, ParamsReadContext ctx)
	{
		super.OnTerjeRPC(sender, id, ctx);
		
		if (id == TerjeMedicineConstants.TRPC_PLAYER_ZED_VOICE)
		{
			if (!GetGame().IsDedicatedServer())
			{
				Param1<int> zvSoundSet;
				if (!ctx.Read(zvSoundSet))
				{
					return;		
				}
				
				string zvSoundName = "";
				int zvId = zvSoundSet.param1;
				if (IsMale())
				{
					if (zvId == 0) zvSoundName = "ZmbM_HunterOld_Base_DisturbedIdle_Soundset";
					else zvSoundName = "ZmbM_HunterOld_Base_CalmMove_Soundset";
				}
				else
				{
					if (zvId == 0) zvSoundName = "ZmbF_CitizenANormal_Base_DisturbedIdle_Soundset";
					else zvSoundName = "ZmbF_CitizenANormal_Base_CalmMove_Soundset";
				}
				
				EffectSound sound = SEffectManager.PlaySoundOnObject(zvSoundName, this);
				sound.SetAutodestroy(true);
			}
		}
	}
	
	override void IncreaseDiseaseCount()
	{
		m_DiseaseCount = 0;
	}
	
	override void DecreaseDiseaseCount()
	{
		m_DiseaseCount = 0;
	}
	
	override bool HasDisease()
	{
		return false;
	}
	
	override bool IsBleeding()
	{
		return super.IsBleeding() || HasTerjeStubWounds() || HasTerjeSutures();
	}
	
	override bool AddTerjeRadiation(float rAmount)
	{
		if (GetGame().IsDedicatedServer() && GetTerjeStats())
		{
			if (rAmount > 0)
			{
				rAmount *= (1.0 - Math.Clamp(GetTerjeRadiationProtection(), 0, 1));
			}
			
			if (rAmount != 0)
			{
				GetTerjeStats().SetRadiationAccumulated(GetTerjeStats().GetRadiationAccumulated() + rAmount);
			}
			
			return true;
		}
		
		return super.AddTerjeRadiation(rAmount);
	};
	
	override float GetTerjeRadiation()
	{
		if (GetTerjeStats())
		{
			if (GetGame().IsDedicatedServer())
			{
				return GetTerjeStats().GetRadiationAccumulated();
			}
			else
			{
				return m_terjeRadiationSynch * TerjeMedicineConstants.RADIATION_PLAYER_ACCUMULATOR_SYNCH_DIVIDER;
			}
		}
		
		return super.GetTerjeRadiation();
	};
	
	override float GetTerjeRadiationAdvanced(bool body, bool itemInHands, bool equipment)
	{
		float result = 0;
		if (body)
		{
			result += GetTerjeRadiation();
		}
		
		if (itemInHands)
		{
			ItemBase inHands = GetItemInHands();
			if (inHands)
			{
				result += inHands.GetTerjeRadiation();
			}
		}
		
		if (equipment)
		{
			ItemBase attachment;
			int attCount = GetInventory().AttachmentCount();
			for ( int attIdx = 0; attIdx < attCount; attIdx++ )
			{
				if (ItemBase.CastTo(attachment, GetInventory().GetAttachmentFromIndex( attIdx )) && attachment)
				{
					result += attachment.GetTerjeRadiation();
				}
			}
		}
		
		return result;
	};
	
	override float GetTerjeRadiationProtection()
	{
		float protection = GetTerjeScriptableAreas().CalculatePlayerBodyProtection(this, "radiation");
		float perkRadresMod;
		if (GetTerjeSkills() && GetTerjeSkills().GetPerkValue("immunity", "radres", perkRadresMod))
		{
			protection = protection + ((1.0 - protection) * perkRadresMod);
		}
		
		return Math.Clamp(protection, 0, 1);
	};
	
	override float GetHealthRegenSpeed()
	{
		float healthRegenCommonModifier = 1;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEALTH_REGEN_COMMON_MODIFIER, healthRegenCommonModifier);
		
		float perkQhealingMod;
		if (GetTerjeSkills() && GetTerjeSkills().GetPerkValue("immunity", "qhealing", perkQhealingMod))
		{
			perkQhealingMod = 1.0 + perkQhealingMod;
		}
		else
		{
			perkQhealingMod = 1.0;
		}
		
		return super.GetHealthRegenSpeed() * healthRegenCommonModifier * perkQhealingMod;
	}
	
	bool HasTerjeBleedingSelf()
	{
		return super.IsBleeding() || HasTerjeStubWoundsSelf() || HasTerjeSuturesSelf();
	}
	
	bool HasTerjeDirtyBandages()
	{
		return BitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_DIRTYBANDAGE);
	}
	
	bool HasTerjeDirtyBandagesSelf()
	{
		return (GetTerjeStats().GetBandagesDirty() > 0) || (GetTerjeStats().GetSuturesBandagedDirty() > 0);
	}
	
	bool HasTerjeSutures()
	{
		return BitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_SUTURE);
	}
	
	bool HasTerjeSuturesSelf()
	{
		return GetTerjeStats().GetSuturesTotal() > 0;
	}
	
	bool HasTerjeSuturesDirty()
	{
		return BitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_SUTURE_DIRTY);
	}
	
	bool HasTerjeSuturesDirtySelf()
	{
		return GetTerjeStats().GetSuturesDirty() > 0;
	}
	
	bool HasTerjeStubWounds()
	{
		return BitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_STUB);
	}
	
	bool HasTerjeStubWoundsSelf()
	{
		return GetTerjeStats().GetStubWounds() > 0;
	}
	
	bool HasTerjeBulletWounds()
	{
		return BitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_BULLET);
	}
	
	bool HasTerjeBulletWoundsSelf()
	{
		return GetTerjeStats().GetBulletWounds() > 0;
	}
	
	bool HasTerjeViscera()
	{
		return BitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_VISCERA);
	}
	
	bool HasTerjeVisceraSelf()
	{
		return GetTerjeStats().GetViscera();
	}
	
	bool HasTerjeStubReadyToSurgery()
	{
		return BitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_STUB_SURGERY);
	}
	
	bool HasTerjeStubReadyToSurgerySelf()
	{
		return (GetTerjeStats().GetBandagesTotal() > 0) || (GetTerjeStats().GetStubWounds() > 0);
	}
	
	override bool HasTerjeSicknesOrInjures()
	{
		if (super.HasTerjeSicknesOrInjures()) return true;
		if (GetTerjeStats().GetBulletWounds() > 3) return true;
		if (GetTerjeStats().GetStubWounds() > 3) return true;
		if (GetTerjeStats().GetViscera()) return true;
		if (GetTerjeStats().GetPainLevel() > 1) return true;
		if (GetTerjeStats().GetSepsisLevel() > 1) return true;
		if (GetTerjeStats().GetZVirusLevel() > 1) return true;
		if (GetTerjeStats().GetInfluenzaLevel() > 2) return true;
		if (GetTerjeStats().GetOverdoseLevel() > 2) return true;
		if (GetTerjeStats().GetRadiationLevel() > 0) return true;
		if (GetTerjeStats().GetMindLevel() > 3) return true;
		return false;
	}
	
	bool IsStayingInBlock()
	{
		if (m_MeleeFightLogic)
		{
			return m_MeleeFightLogic.IsInBlock();
		}
		
		return false;
	}
	
	bool IsFaceBlocked(bool mouthOnly)
	{
		ref ItemBase itemCheck = GetItemOnSlot("Mask");
		if (itemCheck)
		{
			if (mouthOnly)
			{
				bool skipMaskCondition = false;
				string itemMaskType = itemCheck.GetType();
				if (itemMaskType.IndexOf("Balaclava3Holes_") == 0)
				{
					skipMaskCondition = true;
				}
				
				if (!skipMaskCondition)
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		
		itemCheck = GetItemOnSlot("Headgear");
		if (itemCheck)
		{
			string configPathNoMask = "CfgVehicles " + itemCheck.GetType() +  " noMask";
			if (GetGame().ConfigIsExisting(configPathNoMask))
			{
				if (GetGame().ConfigGetInt(configPathNoMask) == 1)
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	void UpdateTerjeWoundsBitmask()
	{
		if (GetGame().IsDedicatedServer())
		{
			int bitmask = m_terjeMedWoundsMask;
			bitmask = BitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_STUB, HasTerjeStubWoundsSelf());
			bitmask = BitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_BULLET, HasTerjeBulletWoundsSelf());
			bitmask = BitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_VISCERA, HasTerjeVisceraSelf());
			bitmask = BitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_SUTURE, HasTerjeSuturesSelf());
			bitmask = BitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_SUTURE_DIRTY, HasTerjeSuturesDirtySelf());
			bitmask = BitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_DIRTYBANDAGE, HasTerjeDirtyBandagesSelf());
			bitmask = BitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_STUB_SURGERY, HasTerjeStubReadyToSurgerySelf());
			
			if (m_terjeMedWoundsMask != bitmask)
			{
				m_terjeMedWoundsMask = bitmask;
				SetSynchDirty();
			}
		}
	}
	
	void UpdateTerjeRadiationAccumulated()
	{
		if (GetGame().IsDedicatedServer())
		{
			int newValue = (int)Math.Round(GetTerjeStats().GetRadiationAccumulated() / TerjeMedicineConstants.RADIATION_PLAYER_ACCUMULATOR_SYNCH_DIVIDER);
			if (m_terjeRadiationSynch != newValue)
			{
				m_terjeRadiationSynch = newValue;
				SetSynchDirty();
			}
		}
	}
	
	void CallTerjeVomitSymptom(float duration, float drainForce)
	{
		SymptomBase symptom = GetSymptomManager().QueueUpPrimarySymptom( SymptomIDs.SYMPTOM_VOMIT );			
		if( symptom )
		{
			symptom.SetDuration( duration );

			float waterDrainFromVomit = 70;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_WATER_DRAIN_FROM_VOMIT, waterDrainFromVomit);	
			
			float energyDrainFromVomit = 55;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ENERGY_DRAIN_FROM_VOMIT, energyDrainFromVomit);	
			
			if ( GetStatWater().Get() > drainForce * waterDrainFromVomit )
			{
				GetStatWater().Add( -1.0 * drainForce * waterDrainFromVomit );
			}
			
			if ( GetStatEnergy().Get() > drainForce * energyDrainFromVomit )
			{
				GetStatEnergy().Add( -1.0 * drainForce * energyDrainFromVomit );
			}
		}

	}
};
