// <copyright file="PrepareFish.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PrepareFish
{
	override void Init()
	{
		super.Init();
 		m_AnimationLength = 8;	
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
			if (fishBody)
			{
				float huntingButchFishExpGainModifier;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_BUTCH_EXP_GAIN_MODIFIER, huntingButchFishExpGainModifier))
				{
					int incExp = (int)(fishBody.ConfigGetInt("terjeOnButchFishingExp") * huntingButchFishExpGainModifier);
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
}