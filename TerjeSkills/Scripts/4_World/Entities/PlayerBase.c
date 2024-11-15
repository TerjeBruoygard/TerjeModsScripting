// <copyright file="PlayerBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

enum TerjeSkillsStealthMask
{
	// DO NOT CHANGE THIS ENUM
	// ITS REPRESENT BITMASK FROM 0..31
	// THIS BITMASK IS ALREADY FULL
	TERJE_SKILLS_STEALTH_SHOES = 0,
	TERJE_SKILLS_STEALTH_WEAPON = 7,
	TERJE_SKILLS_STEALTH_CLOTHES = 14,
	TERJE_SKILLS_STEALTH_VOICE = 21,
	TERJE_SKILLS_STEALTH_FEETS = 30,
	TERJE_SKILLS_STEALTH_NINJA = 31
};

modded class PlayerBase
{
	ref array<ItemBase> m_terjeSkillsSpawnEntityOnGroundCache = null;
	private int m_terjeSkillsStealthMask = 0;
	
	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableInt("m_terjeSkillsStealthMask");
	}
	
	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);
		AddAction(ActionTerjeMaskStash, InputActionMap);
	}
	
	override void OnTerjeRegisterModifiers(ref array<ref TerjePlayerModifierBase> modifiers)
	{
		super.OnTerjeRegisterModifiers(modifiers);	
		modifiers.Insert(new TerjePlayerModifierSkillAthletic());
		modifiers.Insert(new TerjePlayerModifierSkillStealth());
		modifiers.Insert(new TerjePlayerModifierPerkStrongHands());
	}
	
	override EntityAI SpawnEntityOnGroundOnCursorDir(string object_name, float distance)
	{
		EntityAI result = super.SpawnEntityOnGroundOnCursorDir(object_name, distance);
		if (m_terjeSkillsSpawnEntityOnGroundCache != null)
		{
			ItemBase resultItem = ItemBase.Cast(result);
			if (resultItem)
			{
				m_terjeSkillsSpawnEntityOnGroundCache.Insert(resultItem);
			}
		}
		return result;
	}
	
	override void OnTerjeRPC(PlayerIdentity sender, string id, ParamsReadContext ctx)
	{
		super.OnTerjeRPC(sender, id, ctx);
		
		if (id == TerjeSkillsConstants.TRPC_PLAYER_PERK_APPLY)
		{
			if (GetGame().IsDedicatedServer())
			{
				Param2<string, string> perkUpgradeParams;
				if (!ctx.Read(perkUpgradeParams))
				{
					return;
				}
				
				GetTerjeSkills().AddPerkLevel(perkUpgradeParams.param1, perkUpgradeParams.param2);
			}
		}
		else if (id == TerjeSkillsConstants.TRPC_PLAYER_PERKS_RESET)
		{
			if (GetGame().IsDedicatedServer())
			{
				Param1<string> perkResetParams;
				if (!ctx.Read(perkResetParams))
				{
					return;		
				}
				
				GetTerjeSkills().ResetSkill(perkResetParams.param1);
			}
		}
	}
	
	override void EEKilled(Object killer)
	{
		if (GetGame().IsDedicatedServer() && GetTerjeSkills() != null)
		{
			ref array<ref TerjeSkillCfg> skills = new array<ref TerjeSkillCfg>;
			GetTerjeSkillsRegistry().GetSkills(skills);
			foreach (ref TerjeSkillCfg skill : skills)
			{
				GetTerjeSkills().AddSkillExperience(skill.GetId(), skill.GetExpLoseOnDeath());
			}
		}
		
		super.EEKilled(killer);
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		TerjeStrongBonesPerkEEHitByHandler(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		TerjeSurvDmgModEEHitByHandler(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		TerjeDamageHandler.GetInstance().EEHitBy(damageResult, damageType, source, this, component, dmgZone, ammo, modelPos, speedCoef);
	}
	
	override bool CanBeTargetedByAI(EntityAI ai)
    {
        bool result = super.CanBeTargetedByAI(ai);
		
        
        return result;
    }
	
	override protected float GetWeightSpecialized(bool forceRecalc = false)
	{
		float result = super.GetWeightSpecialized(forceRecalc);	
		
		
		return Math.Max(0.0, result);
	}
	
	override void OnTerjeCharacterLifetimeUpdated(int secondsSinceRespawn)
	{
		if (GetTerjeSkills() != null)
		{
			int offsetValue;
			if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_SURV_LIFETIME_OFFSET, offsetValue) && (secondsSinceRespawn % offsetValue) == 0)
			{
				float expGain;
				if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_SURV_LIFETIME_GAIN_EXP, expGain))
				{
					GetTerjeSkills().AddSkillExperience("surv", expGain);
				}
			}
		}
	}
	
	private float TerjeCalculateVestAndHelmetWeight()
	{
		float totalWeight = 0;
		ItemBase vest = GetItemOnSlot("Vest");
		if (vest)
		{
			totalWeight += vest.GetConfigWeightModified();
		}
		
		ItemBase helmet = GetItemOnSlot("Headgear");
		if (helmet)
		{
			totalWeight += helmet.GetConfigWeightModified();
		}
		
		return totalWeight;	
	}
	
	private void TerjeStrongBonesPerkEEHitByHandler(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (GetGame().IsDedicatedServer() && GetTerjeSkills() != null && !GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS))
		{
			if (GetHealth("RightLeg", "Health") <= 1 || GetHealth("LeftLeg", "Health") <= 1 || GetHealth("RightFoot", "Health") <= 1 || GetHealth("LeftFoot", "Health") <= 1)
			{
				float strbonesPerkModifier;
				if (GetTerjeSkills().GetPerkValue("athlc", "strbones", strbonesPerkModifier) && Math.RandomFloat01() > Math.Clamp(1.0 + strbonesPerkModifier, 0.0, 1.0))
				{
					// Prevent bones broke
					if (GetHealth("RightLeg", "Health") <= 1)
					{
						SetHealth("RightLeg", "Health", 2);
					}
					
					if (GetHealth("LeftLeg", "Health") <= 1)
					{
						SetHealth("LeftLeg", "Health", 2);
					}
					
					if (GetHealth("RightFoot", "Health") <= 1)
					{
						SetHealth("RightFoot", "Health", 2);
					}
					
					if (GetHealth("LeftFoot", "Health") <= 1)
					{
						SetHealth("LeftFoot", "Health", 2);
					}
				}
			}
		}
	}
	
	private void TerjeSurvDmgModEEHitByHandler(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (source && source.IsZombie())
		{
			float survSkillMod;
			if (GetGame().IsDedicatedServer() && GetTerjeSkills() != null && GetTerjeSkills().GetSkillModifierValue("surv", "survzmbmod", survSkillMod))
			{
				float actualDmg = damageResult.GetDamage(dmgZone, "Health") * Math.Clamp(Math.AbsFloat(survSkillMod), 0, 1);
				if (actualDmg > 0)
				{
					AddHealth(dmgZone, "Health", actualDmg);
				}
			}
		}
	}
	
	void UpdateTerjeSkillsStealthBitmask()
	{
		if (GetGame().IsDedicatedServer() && GetTerjeSkills() != null)
		{
			int bitmask = m_terjeSkillsStealthMask;
			bool setShadowtrc = GetTerjeSkills().GetPerkLevel("stlth", "shadowtrc") > 0;
			bool setNinja = GetGame().GetWorld().IsNight() && (GetTerjeSkills().GetPerkLevel("stlth", "ninja") > 0);

			bitmask = UpdateTerjeSkillsStealthBitmask_Perk(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_SHOES, "qtstep");
			bitmask = UpdateTerjeSkillsStealthBitmask_Perk(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_WEAPON, "qshooter");
			bitmask = UpdateTerjeSkillsStealthBitmask_Perk(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_VOICE, "coldbldd");
			bitmask = UpdateTerjeSkillsStealthBitmask_Perk(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_CLOTHES, "fitequip");
			bitmask = BitmaskHelper.SetBit(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_FEETS, setShadowtrc);
			bitmask = BitmaskHelper.SetBit(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_NINJA, setNinja);

			if (m_terjeSkillsStealthMask != bitmask)
			{
				m_terjeSkillsStealthMask = bitmask;
				SetSynchDirty();
			}
		}
	}
	
	bool GetTerjeSkillsStealthPerkValueFromBitmask(int bitIndex, string perkId, out float result)
	{
		ref TerjeSkillCfg skill;
		if (!GetTerjeSkillsRegistry().FindSkill("stlth", skill))
		{
			result = 0.0;
			return false;
		}
		
		ref TerjePerkCfg perk;
		if (!skill.FindPerk(perkId, perk))
		{
			result = 0.0;
			return false;
		}
		
		if (bitIndex == TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_FEETS || bitIndex == TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_NINJA)
		{
			result = perk.GetValue(0);
			return BitmaskHelper.GetBit(m_terjeSkillsStealthMask, bitIndex);
		}
		else
		{
			for (int index = 0; index < 7; index++)
			{
				bool bitValue = BitmaskHelper.GetBit(m_terjeSkillsStealthMask, bitIndex + index);
				if (bitValue && index < perk.GetStagesCount())
				{
					result = perk.GetValue(index);
					return true;
				}
			}
		}
		
		result = 0.0;
		return false;
	}
	
	private int UpdateTerjeSkillsStealthBitmask_Perk(int bitmask, int offset, string perkId)
	{
		int perkValue;
		if (!GetTerjeSkills() || !GetTerjeSkills().GetPerkValue("stlth", perkId, perkValue))
		{
			perkValue = 0;
		}
		for (int index = 0; index < 7; index++)
		{
			bool bitValue = (perkValue == (index + 1));
			bitmask = BitmaskHelper.SetBit(bitmask, offset + index, bitValue);
		}
		
		return bitmask;
	}
};