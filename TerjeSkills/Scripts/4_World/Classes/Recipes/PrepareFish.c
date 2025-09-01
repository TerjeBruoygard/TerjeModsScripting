// <copyright file="PrepareFish.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PrepareFish
{
	override float GetLengthInSecs()
	{
		float overrideSkinningTime;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_SKINNING_TIME, overrideSkinningTime) && overrideSkinningTime > 0)
		{
 			return overrideSkinningTime;
		}
		else
		{
			return super.GetLengthInSecs();
		}
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		super.Do(ingredients, player, results, specialty_weight);
		
		if (GetGame().IsDedicatedServer() && player && player.IsAlive() && player.GetTerjeSkills())
		{
			if (player.GetTerjeSkills().IsPerkRegistered("fish", "masterf"))
			{
				float initQuantity = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_FILLET_MIN_QUANTITY);	
				float perkQuantity = 0.0;
				player.GetTerjeSkills().GetPerkValue("fish", "masterf", perkQuantity);
				
				float totalQuantity = initQuantity + ((1.0 - initQuantity) * Math.Clamp(perkQuantity, 0, 1));
				for (int i=0; i < results.Count(); i++)
				{
					ItemBase item_result = ItemBase.Cast(results.Get(i));
					if (item_result)
					{
						item_result.SetQuantityNormalized(item_result.GetQuantityNormalized() * totalQuantity);
					}
				}
			}
			
			ItemBase fishBody = ingredients[0];
			ItemBase knifeItem = ingredients[1];
			if (knifeItem && player.GetTerjeSkills().IsPerkRegistered("fish", "strgarms"))
			{
				float fishingOverrideKnifeDamage;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_KNIFE_DAMAGE, fishingOverrideKnifeDamage))
				{
					float mknifeSkill;
					if (player.GetTerjeSkills().GetPerkValue("fish", "strgarms", mknifeSkill))
					{
						mknifeSkill = Math.Clamp(1.0 + mknifeSkill, 0, 1);
					}
					else
					{
						mknifeSkill = 1.0;
					}
					
					float fishBodyMod = 1.0;
					if (fishBody && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + fishBody.GetType() + " terjeSkinningKnifeDamageModifier"))
					{
						fishBodyMod = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + fishBody.GetType() + " terjeSkinningKnifeDamageModifier");
					}
					
					knifeItem.DecreaseHealth(fishingOverrideKnifeDamage * mknifeSkill * fishBodyMod, false);
				}
			}
			
			if (fishBody)
			{
				float huntingButchFishExpGainModifier;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_BUTCH_EXP_GAIN_MODIFIER, huntingButchFishExpGainModifier))
				{
					int expCfg = GetTerjeGameConfig().ConfigGetInt("CfgVehicles " + fishBody.GetType() + " terjeOnButchFishingExp");
					int incExp = (int)(expCfg * huntingButchFishExpGainModifier);
					if (knifeItem && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + knifeItem.GetType() + " terjeSkinningExpModifier"))
					{
						incExp = (int)(incExp * GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + knifeItem.GetType() + " terjeSkinningExpModifier"));
					}
					
					if (incExp > 0)
					{
						player.GetTerjeSkills().AddSkillExperience("fish", incExp);
					}
				}
			}
		}
	}
	
	override float GetTerjeCraftingTimeModifier(PlayerBase player)
	{
		float result = super.GetTerjeCraftingTimeModifier(player);
		if (player && player.IsAlive() && player.GetTerjeSkills() != null)
		{
			if (player.GetTerjeSkills().IsPerkRegistered("fish", "quickclean"))
			{
				float quickcutPerk;
				if (player.GetTerjeSkills().GetPerkValue("fish", "quickclean", quickcutPerk))
				{
					result *= Math.Clamp(1.0 + quickcutPerk, 0, 1);
				}
			}
		}
		
		return Math.Max(0, result);
	}
}