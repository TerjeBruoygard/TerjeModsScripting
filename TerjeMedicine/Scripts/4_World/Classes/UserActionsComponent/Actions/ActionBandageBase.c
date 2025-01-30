// <copyright file="ActionBandageBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionBandageSelfCB
{
	override void CreateActionComponent()
	{
		float perkModifier;
		if (m_ActionData.m_Player && m_ActionData.m_Player.GetTerjeSkills() && m_ActionData.m_Player.GetTerjeSkills().GetPerkValue("med", "mastdress", perkModifier))
		{
			float effectivity 		= m_ActionData.m_MainItem.GetBandagingEffectivity();
			float adjustedTimeSpent = UATimeSpent.BANDAGE;
	
			if (effectivity > 0)
			{
				adjustedTimeSpent = adjustedTimeSpent / effectivity;
			}
	
			m_ActionData.m_ActionComponent = new CAContinuousRepeat(Math.Max(1, adjustedTimeSpent * (1.0 + perkModifier)));
		}
		else
		{
			super.CreateActionComponent();
		}
	}
}

modded class ActionBandageTargetCB
{
	override void CreateActionComponent()
	{
		float perkModifier;
		if (m_ActionData.m_Player && m_ActionData.m_Player.GetTerjeSkills() && m_ActionData.m_Player.GetTerjeSkills().GetPerkValue("med", "mastdress", perkModifier))
		{
			float effectivity 		= m_ActionData.m_MainItem.GetBandagingEffectivity();
			float adjustedTimeSpent = UATimeSpent.BANDAGE;
	
			if (effectivity > 0)
			{
				adjustedTimeSpent = adjustedTimeSpent / effectivity;
			}
	
			m_ActionData.m_ActionComponent = new CAContinuousRepeat(Math.Max(1, adjustedTimeSpent * (1.0 + perkModifier)));
		}
		else
		{
			super.CreateActionComponent();
		}
	}
}

modded class ActionBandageBase
{
	override void ApplyBandage(ItemBase item, PlayerBase player)
	{			
		if (item)
		{
			item.ApplyTerjeConsumableEffects(player, 1);
			CheckInfectionBandaging(item, player);
			
			PlayerBase operator = PlayerBase.Cast( item.GetHierarchyRootPlayer() ); 
			if (operator && operator.GetTerjeSkills())
			{
				int bandageExpGain = 0;
				if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_BANDAGE_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
				{
					operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
				}
			}
		}
		
		super.ApplyBandage(item, player);
	}
	
	void CheckInfectionBandaging(ItemBase item, PlayerBase player, PlayerBase operator = null)
	{
		if (!operator)
		{
			operator = PlayerBase.Cast( item.GetHierarchyRootPlayer() ); 
		}
		
		float operatorPerkSterilityMod = 1.0;
		if (operator)
		{
			float bandagingSepsisChance = 0;
			ItemBase gloves = operator.GetItemOnSlot("Gloves");
			if (gloves)
			{
				if (!gloves.IsDisinfected())
				{
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGING_SEPSIS_CHANCE_D_G, bandagingSepsisChance);
				}
			}
			else if (operator.HasBloodyHands())
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGING_SEPSIS_CHANCE_D_H, bandagingSepsisChance);
			}
			
			float perkValue;
			if (operator && operator.GetTerjeSkills() && operator.GetTerjeSkills().GetPerkValue("med", "cleanstr", perkValue))
			{
				operatorPerkSterilityMod = Math.Clamp(1.0 + perkValue, 0, 1);
			}
			
			if (Math.RandomFloat01() < bandagingSepsisChance * operatorPerkSterilityMod)
			{
				player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.1);
			}
		}
		
		float bandagingSepsisModifier = 1;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGING_SEPSIS_MODIFIER, bandagingSepsisModifier);
		if (Math.RandomFloat01() < item.GetInfectionChance() * operatorPerkSterilityMod * bandagingSepsisModifier)
		{
			player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.1);
		}
	}
	
	void CheckInfectionSurgery(ItemBase item, PlayerBase player, PlayerBase operator = null)
	{
		if (!operator && item)
		{
			operator = PlayerBase.Cast( item.GetHierarchyRootPlayer() ); 
		}
		
		float operatorPerkSterilityMod = 1.0;
		if (operator && operator.GetTerjeStats() && player.GetTerjeStats())
		{
			float bandagingSepsisChance = 0;
			ItemBase gloves = operator.GetItemOnSlot("Gloves");
			if (gloves)
			{
				if (!gloves.IsDisinfected())
				{
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SURGERY_SEPSIS_CHANCE_D_G, bandagingSepsisChance);
				}
			}
			else if (operator.HasBloodyHands())
			{
				bandagingSepsisChance = 1;
			}
			else if (!operator.GetTerjeStats().GetDisinfected())
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SURGERY_SEPSIS_CHANCE_D_H, bandagingSepsisChance);
			}
			
			float perkValue;
			if (operator && operator.GetTerjeSkills() && operator.GetTerjeSkills().GetPerkValue("med", "cleanstr", perkValue))
			{
				operatorPerkSterilityMod = Math.Clamp(1.0 + perkValue, 0, 1);
			}
			
			if (Math.RandomFloat01() < bandagingSepsisChance * operatorPerkSterilityMod)
			{
				player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.25);
			}
		}
		
		float bandagingSepsisModifier = 1;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SURGERY_SEPSIS_MODIFIER, bandagingSepsisModifier);
		if (player && player.GetTerjeStats() && Math.RandomFloat01() < item.GetInfectionChance() * bandagingSepsisModifier * operatorPerkSterilityMod)
		{
			player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.25);
		}
	}
	
	void ChangeBandage(ItemBase item, PlayerBase player)
	{		
		if (item)
		{
			if (player.GetTerjeStats().GetBandagesDirty() > 0)
			{
				player.GetTerjeStats().SetBandagesDirty(player.GetTerjeStats().GetBandagesDirty() - 1);
				player.GetTerjeStats().SetBandagesClean(player.GetTerjeStats().GetBandagesClean() + 1);
			}
			else if (player.GetTerjeStats().GetSuturesBandagedDirty() > 0)
			{
				player.GetTerjeStats().SetSuturesBandagedDirty(player.GetTerjeStats().GetSuturesBandagedDirty() - 1);
				player.GetTerjeStats().SetSuturesBandagedClean(player.GetTerjeStats().GetSuturesBandagedClean() + 1);
			}
			
			CheckInfectionBandaging(item, player);
	
			PlayerBase operator = PlayerBase.Cast( item.GetHierarchyRootPlayer() ); 
			if (operator && operator.GetTerjeSkills())
			{
				int bandageExpGain = 0;
				if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_BANDAGE_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
				{
					operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
				}
			}
			
			if (item.HasQuantity())
			{
				float consumeQuantity = item.ConfigGetFloat("terjeOverrideSurgeryConsumeQuantity");
				if (consumeQuantity > 0)
				{
					item.AddQuantity(-consumeQuantity, true);
				}
				else
				{
					item.AddQuantity(-1, true);
				}
			}
			else
			{
				item.Delete();
			}
		}
	}
	
	void ApplySurgeryViscera(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (Math.RandomFloat01() < item.GetTerjeSurgeryVisceraEffectivity(operator))
		{
			target.GetTerjeStats().SetViscera(false);
			
			int suturesMin = 1;
			int suturesMax = 1;
			GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_VISCERA_SUTURES_MIN, suturesMin);
			GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_VISCERA_SUTURES_MAX, suturesMax);
			
			if (suturesMin > 0 && suturesMax > 0 && suturesMin < suturesMax)
			{
				target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + Math.RandomIntInclusive(suturesMin, suturesMax));
			}
			else if (suturesMin > 0)
			{
				target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + suturesMin);
			}
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 8, "#STR_TERJEMED_SURGERY_SUCCESS", "#STR_TERJEMED_SURGERY_VISCERA_SUCCESS", "set:TerjePerk_icon image:tp_surgeryinternal");
			}
			
			if (operator.GetTerjeSkills())
			{
				int bandageExpGain = 0;
				if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_VISCERA_SURGERY_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
				{
					operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
				}
			}
		}
		else
		{
			target.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			target.DecreaseHealth("GlobalHealth", "Health", GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_FAILED_HEALTH_LOSE));
			target.DecreaseHealth("GlobalHealth", "Blood", GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_FAILED_BLOOD_LOSE));
			target.DecreaseHealth("GlobalHealth", "Shock", GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_FAILED_SHOCK_LOSE));

			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 10, "#STR_TERJEMED_SURGERY_FAILED", "#STR_TERJEMED_SURGERY_VISCERA_FAILED", "set:TerjePerkBlack_icon image:tp_surgeryinternal");
			}
		}
		
		CheckInfectionSurgery(item, target, operator);
		
		if (item.HasQuantity())
		{
			float consumeQuantity = item.ConfigGetFloat("terjeOverrideSurgeryConsumeQuantity");
			if (consumeQuantity > 0)
			{
				item.AddQuantity(-consumeQuantity, true);
			}
			else
			{
				item.AddQuantity(-1, true);
			}
		}
		else
		{
			item.Delete();
		}
	}
	
	void ApplySurgeryBullet(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (Math.RandomFloat01() < item.GetTerjeSurgeryBulletEffectivity(operator))
		{
			int bulletWounds = target.GetTerjeStats().GetBulletWounds();
			if (bulletWounds > (target.GetTerjeStats().GetStubWounds() + target.GetTerjeStats().GetBandagesClean() + target.GetTerjeStats().GetBandagesDirty()))
			{
				int suturesMin = 1;
				int suturesMax = 1;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_BULLETS_SUTURES_MIN, suturesMin);
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_BULLETS_SUTURES_MAX, suturesMax);
				
				if (suturesMin > 0 && suturesMax > 0 && suturesMin < suturesMax)
				{
					target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + Math.RandomIntInclusive(suturesMin, suturesMax));
				}
				else if (suturesMin > 0)
				{
					target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + suturesMin);
				}
			}
			
			target.GetTerjeStats().SetBulletWounds(bulletWounds - 1);
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 8, "#STR_TERJEMED_SURGERY_SUCCESS", "#STR_TERJEMED_SURGERY_BULLET_SUCCESS", "set:TerjePerk_icon image:tp_surgerybullet");
			}
			
			if (operator.GetTerjeSkills())
			{
				int bandageExpGain = 0;
				if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_BULLET_SURGERY_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
				{
					operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
				}
			}
		}
		else
		{
			target.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			target.DecreaseHealth("GlobalHealth", "Health", GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FAILED_HEALTH_LOSE));
			target.DecreaseHealth("GlobalHealth", "Blood", GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FAILED_BLOOD_LOSE));
			target.DecreaseHealth("GlobalHealth", "Shock", GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FAILED_SHOCK_LOSE));
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 10, "#STR_TERJEMED_SURGERY_FAILED", "#STR_TERJEMED_SURGERY_BULLET_FAILED", "set:TerjePerkBlack_icon image:tp_surgerybullet");
			}
		}
		
		CheckInfectionSurgery(item, target, operator);
		
		if (item.HasQuantity())
		{
			float consumeQuantity = item.ConfigGetFloat("terjeOverrideSurgeryConsumeQuantity");
			if (consumeQuantity > 0)
			{
				item.AddQuantity(-consumeQuantity, true);
			}
			else
			{
				item.AddQuantity(-1, true);
			}
		}
		else
		{
			item.Delete();
		}
	}
	
	void ApplySurgeryStub(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (Math.RandomFloat01() < item.GetTerjeSurgeryStubEffectivity(operator))
		{
			if (target.GetTerjeStats().GetStubWounds() > 0)
			{
				target.GetTerjeStats().SetStubWounds(target.GetTerjeStats().GetStubWounds() - 1);
			}
			else if (target.GetTerjeStats().GetBandagesClean() > 0)
			{
				target.GetTerjeStats().SetBandagesClean(target.GetTerjeStats().GetBandagesClean() - 1);
			}
			else if (target.GetTerjeStats().GetBandagesDirty() > 0)
			{
				target.GetTerjeStats().SetBandagesDirty(target.GetTerjeStats().GetBandagesDirty() - 1);
			}
			
			int suturesMin = 1;
			int suturesMax = 1;
			GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_STUBS_SUTURES_MIN, suturesMin);
			GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_STUBS_SUTURES_MAX, suturesMax);
			
			if (suturesMin > 0 && suturesMax > 0 && suturesMin < suturesMax)
			{
				target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + Math.RandomIntInclusive(suturesMin, suturesMax));
			}
			else if (suturesMin > 0)
			{
				target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + suturesMin);
			}
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 8, "#STR_TERJEMED_SURGERY_SUCCESS", "#STR_TERJEMED_SURGERY_WOUND_SUCCESS", "set:TerjePerk_icon image:tp_surgerystab");
			}
			
			if (operator.GetTerjeSkills())
			{
				int bandageExpGain = 0;
				if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_STUB_SURGERY_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
				{
					operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
				}
			}
		}
		else
		{
			target.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			target.DecreaseHealth("GlobalHealth", "Health", GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_FAILED_HEALTH_LOSE));
			target.DecreaseHealth("GlobalHealth", "Blood", GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_FAILED_BLOOD_LOSE));
			target.DecreaseHealth("GlobalHealth", "Shock", GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_FAILED_SHOCK_LOSE));
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 10, "#STR_TERJEMED_SURGERY_FAILED", "#STR_TERJEMED_SURGERY_WOUND_FAILED", "set:TerjePerkBlack_icon image:tp_surgerystab");
			}
		}
		
		CheckInfectionSurgery(item, target, operator);
		
		if (item.HasQuantity())
		{
			float consumeQuantity = item.ConfigGetFloat("terjeOverrideSurgeryConsumeQuantity");
			if (consumeQuantity > 0)
			{
				item.AddQuantity(-consumeQuantity, true);
			}
			else
			{
				item.AddQuantity(-1, true);
			}
		}
		else
		{
			item.Delete();
		}
	}
}

modded class ActionBandageSelf
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return super.ActionCondition(player, target, item) && player.HasTerjeBleedingSelf() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
	}
}

modded class ActionBandageTarget
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return super.ActionCondition(player, target, item) && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
	}
}
