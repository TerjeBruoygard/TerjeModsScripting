// <copyright file="ItemBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ItemBase
{
	float GetTerjeSurgeryVisceraEffectivity(PlayerBase player)
	{
		float result = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " terjeSurgeryVisceraEffectivity");
		if (result <= 0)
		{
			result = 0.01;
		}
		
		float perkValue;
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("med", "surgint", perkValue))
		{
			float perkAffectRange = Math.Clamp(1.0 - result, 0, 1);
			result = result + (perkAffectRange * perkValue);
		}
		
		float settingMod;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_SURGERY_EFF_MOD, settingMod))
		{
			settingMod = 1.0;
		}
		
		return result * settingMod;
	}
	
	float GetTerjeSurgeryVisceraTime(PlayerBase player)
	{
		float result = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " terjeSurgeryVisceraTime");
		if (result < 1)
		{
			result = 60;
		}
		
		float perkValue;
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("med", "surgeon", perkValue))
		{
			result = result * Math.Clamp(1.0 + perkValue, 0, 1);
		}
		
		float settingMod;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_SURGERY_TIME_MOD, settingMod))
		{
			settingMod = 1.0;
		}
		
		return result * settingMod;
	}
	
	float GetTerjeSurgeryBulletEffectivity(PlayerBase player)
	{
		float result = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " terjeSurgeryBulletEffectivity");
		if (result <= 0)
		{
			result = 0.01;
		}
		
		float perkValue;
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("med", "surgbw", perkValue))
		{
			float perkAffectRange = Math.Clamp(1.0 - result, 0, 1);
			result = result + (perkAffectRange * perkValue);
		}
		
		float settingMod;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLET_SURGERY_EFF_MOD, settingMod))
		{
			settingMod = 1.0;
		}
		
		return result * settingMod;
	}
	
	float GetTerjeSurgeryBulletTime(PlayerBase player)
	{
		float result = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " terjeSurgeryBulletTime");
		if (result < 1)
		{
			result = 30;
		}
		
		float perkValue;
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("med", "surgeon", perkValue))
		{
			result = result * Math.Clamp(1.0 + perkValue, 0, 1);
		}
		
		float settingMod;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLET_SURGERY_TIME_MOD, settingMod))
		{
			settingMod = 1.0;
		}
		
		return result * settingMod;
	}
	
	float GetTerjeSurgeryStubEffectivity(PlayerBase player)
	{
		float result = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " terjeSurgeryStubEffectivity");
		if (result <= 0)
		{
			result = 0.01;
		}
		
		float perkValue;
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("med", "surgsw", perkValue))
		{
			float perkAffectRange = Math.Clamp(1.0 - result, 0, 1);
			result = result + (perkAffectRange * perkValue);
		}
		
		float settingMod;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUB_SURGERY_EFF_MOD, settingMod))
		{
			settingMod = 1.0;
		}
		
		return result * settingMod;
	}
	
	float GetTerjeSurgeryStubTime(PlayerBase player)
	{
		float result = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " terjeSurgeryStubTime");
		if (result < 1)
		{
			result = 20;
		}
		
		float perkValue;
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("med", "surgeon", perkValue))
		{
			result = result * Math.Clamp(1.0 + perkValue, 0, 1);
		}
		
		float settingMod;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUB_SURGERY_TIME_MOD, settingMod))
		{
			settingMod = 1.0;
		}
		
		return result * settingMod;
	}
	
	override bool CanBeDisinfected()
	{
		if (super.CanBeDisinfected())
		{
			return true;
		}
		
		if (GetTerjeGameConfig().ConfigGetBool("CfgVehicles " + GetType() + " canBeDisinfected"))
		{
			return true;
		}
		
		return false;
	}
	
	bool IsTerjeEmptyQuantity()
	{
		return GetQuantity() <= GetQuantityMin();
	}
	
	override void AddAction(typename actionName)
	{
		// Change ActionSew to ActionSurgery
		if (actionName == ActionSewSelf)
		{
			super.AddAction(ActionSurgeryVisceraSelf);
			super.AddAction(ActionSurgeryBulletSelf);
			super.AddAction(ActionSurgeryStubSelf);
			return;
		}
		else if (actionName == ActionSewTarget)
		{
			super.AddAction(ActionSurgeryVisceraTarget);
			super.AddAction(ActionSurgeryBulletTarget);
			super.AddAction(ActionSurgeryStubTarget);
			return;
		}
		
		// Default
		super.AddAction(actionName);
		
		// Bind additional actions to support rebandaging
		if (actionName == ActionBandageSelf)
		{
			super.AddAction(ActionRebandageSelf);
		}
		else if (actionName == ActionBandageTarget)
		{
			super.AddAction(ActionRebandageTarget);
		}
		
		// Bind additional actions to support sutures disinfection
		if (actionName == ActionDisinfectSelf)
		{
			super.AddAction(ActionDisinfectSutureSelf);
			super.AddAction(ActionDisinfectBandagedWoundSelf);
		}
		else if (actionName == ActionDisinfectTarget)
		{
			super.AddAction(ActionDisinfectSutureTarget);
			super.AddAction(ActionDisinfectBandagedWoundTarget);
		}
	}
	
	override int TerjeOverrideDescriptionByConsumableEffects()
	{
		if (GetGame().IsClient())
		{
			PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
			if (player && player.GetTerjeSkills())
			{
				if (GetTerjeGameConfig().ConfigGetBool("CfgVehicles " + GetType() + " medicalPillsCategory"))
				{
					if (!player.GetTerjeSkills().IsPerkRegistered("med", "pillrecog") || player.GetTerjeSkills().GetPerkLevel("med", "pillrecog") > 0)
					{
						return 1;
					}
				}
				else if (GetTerjeGameConfig().ConfigGetBool("CfgVehicles " + GetType() + " medicalAmpoulsCategory"))
				{
					if (!player.GetTerjeSkills().IsPerkRegistered("med", "amplrecog") || player.GetTerjeSkills().GetPerkLevel("med", "amplrecog") > 0)
					{
						return 1;
					}
				}
				else if (GetTerjeGameConfig().ConfigGetBool("CfgVehicles " + GetType() + " medicalInjectorsCategory"))
				{
					if (!player.GetTerjeSkills().IsPerkRegistered("med", "injrecog") || player.GetTerjeSkills().GetPerkLevel("med", "injrecog") > 0)
					{
						return 1;
					}
				}
			}
		}
		
		return super.TerjeOverrideDescriptionByConsumableEffects();
	}
}