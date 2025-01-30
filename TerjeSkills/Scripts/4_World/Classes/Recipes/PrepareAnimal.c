// <copyright file="PrepareAnimal.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PrepareChicken
{
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		player.m_terjeSkillsSpawnEntityOnGroundCache = new array<ItemBase>;
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsSpecificLogic(ingredients, player, results);
		player.m_terjeSkillsSpawnEntityOnGroundCache = null;
	}
}

modded class PrepareRabbit
{
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		player.m_terjeSkillsSpawnEntityOnGroundCache = new array<ItemBase>;
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsSpecificLogic(ingredients, player, results);
		player.m_terjeSkillsSpawnEntityOnGroundCache = null;
	}
}

modded class PrepareFox
{
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		player.m_terjeSkillsSpawnEntityOnGroundCache = new array<ItemBase>;
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsSpecificLogic(ingredients, player, results);
		player.m_terjeSkillsSpawnEntityOnGroundCache = null;
	}
}

modded class PrepareAnimal
{
	override float GetLengthInSecs()
	{
		float overrideSkinningTime;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_SKINNING_TIME, overrideSkinningTime) && overrideSkinningTime > 0)
		{
 			return overrideSkinningTime;
		}
		else
		{
			return super.GetLengthInSecs();
		}
	}
	
	protected void TerjeSkillsSpecificLogic(ItemBase ingredients[], PlayerBase player, array<ItemBase> results)
	{
		if (player && player.IsAlive() && player.GetTerjeSkills() && player.m_terjeSkillsSpawnEntityOnGroundCache != null)
		{
			array<ItemBase> resultItems();
			foreach (ItemBase resultItem : results)
			{
				resultItems.Insert(resultItem);
			}
			foreach (ItemBase cacheItem : player.m_terjeSkillsSpawnEntityOnGroundCache)
			{
				resultItems.Insert(cacheItem);
			}
			
			float skillModifier = 0;
			if (player.GetTerjeSkills().GetSkillModifierValue("hunt", "meatcountmod", skillModifier))
			{
				set<string> uniqItemsCache();
				foreach (ItemBase item : resultItems)
				{
					if (item)
					{
						string itemType = item.GetType();
						if (uniqItemsCache.Find(itemType) != -1)
						{
							if (Math.RandomFloat01() > skillModifier)
							{
								item.Delete();
							}
						}
						else
						{
							uniqItemsCache.Insert(itemType);
						}
					}
				}
			}
			
			float meathuntSkill = 1.0;
			if (player.GetTerjeSkills().IsPerkRegistered("hunt", "meathunt"))
			{
				if (!player.GetTerjeSkills().GetPerkValue("hunt", "meathunt", meathuntSkill))
				{
					meathuntSkill = 0;
				}
			}
			
			float plmasterSkill = 1.0;
			if (player.GetTerjeSkills().IsPerkRegistered("hunt", "plmaster"))
			{
				if (!player.GetTerjeSkills().GetPerkValue("hunt", "plmaster", plmasterSkill))
				{
					plmasterSkill = 0;
				}
			}
			
			float meathunterInitSetting;
			if (!GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_MEAT_INIT_QUANTITY, meathunterInitSetting))
			{
				meathunterInitSetting = 0.1;
			}
			
			float meathunterMinSetting;
			if (!GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_MEAT_MIN_QUANTITY, meathunterMinSetting))
			{
				meathunterMinSetting = 0.1;
			}
			
			foreach (ItemBase item2 : resultItems)
			{
				if (item2)
				{
					if (item2.IsMeat() && item2.HasQuantity())
					{
						float newQuantityMin = item2.GetQuantityMax() * meathunterMinSetting;
						float newQuantityInit = item2.GetQuantityMax() * Math.RandomFloat01() * meathunterInitSetting;
						float newQuantityAdd = (item2.GetQuantityMax() - newQuantityMin) * meathuntSkill;
						float newQuantityTotal = Math.Max(newQuantityMin, newQuantityInit + newQuantityAdd);
						item2.SetQuantity(newQuantityTotal);
					}
					else if (item2.IsPeltBase())
					{
						item2.SetHealth01("", "", plmasterSkill);
						if (item2.HasQuantity())
						{
							item2.SetQuantityNormalized(plmasterSkill);
						}
					}
					else if (item2.IsInherited(Bone))
					{
						item2.SetHealth01("", "", Math.Max(GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_BONES_INIT_HP), Math.Clamp(skillModifier, 0, 1)));
					}
					else
					{
						TerjeProcessServerSpawnedCustomItem(player, item2);
					}
				}
			}
			
			ItemBase knifeItem = ingredients[1];
			if (knifeItem && player.GetTerjeSkills().IsPerkRegistered("hunt", "mknife"))
			{
				float huntingOverrideKnifeDamage;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_KNIFE_DAMAGE, huntingOverrideKnifeDamage))
				{
					float mknifeSkill;
					if (player.GetTerjeSkills().GetPerkValue("hunt", "mknife", mknifeSkill))
					{
						mknifeSkill = Math.Clamp(1.0 + mknifeSkill, 0, 1);
					}
					else
					{
						mknifeSkill = 1.0;
					}
					
					knifeItem.DecreaseHealth(huntingOverrideKnifeDamage * mknifeSkill, false);
				}
			}
			
			ItemBase animalBody = ingredients[0];
			if (animalBody && player && player.IsAlive() && player.GetTerjeSkills())
			{
				float huntingButchAnimalExpGainModifier;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_BUTCH_ANIMAL_EXP_GAIN_MODIFIER, huntingButchAnimalExpGainModifier))
				{
					int huntExp = (int)(animalBody.ConfigGetInt("terjeOnButchHuntingExp") * huntingButchAnimalExpGainModifier);
					if (huntExp > 0)
					{
						player.GetTerjeSkills().AddSkillExperience("hunt", huntExp);
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
			if (player.GetTerjeSkills().IsPerkRegistered("hunt", "quickcut"))
			{
				float quickcutPerk;
				if (player.GetTerjeSkills().GetPerkValue("hunt", "quickcut", quickcutPerk))
				{
					result *= Math.Clamp(1.0 + quickcutPerk, 0, 1);
				}
			}
			
			ItemBase knife = player.GetItemInHands();
			if (knife)
			{
				if (knife.ConfigIsExisting("terjeSkinningModifier"))
				{
					result *= knife.ConfigGetFloat("terjeSkinningModifier");
				}
				
				if (knife.ConfigIsExisting("terjeSkinningModifierOverride"))
				{
					result = knife.ConfigGetFloat("terjeSkinningModifierOverride");
				}
			}
		}
		
		return Math.Max(0, result);
	}
	
	void TerjeProcessServerSpawnedCustomItem(PlayerBase player, ItemBase item)
	{
		// Override for custom logic handling
	}
}