// <copyright file="TerjeConsumableEffects.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeConsumableEffects
{	
	void Apply(EntityAI entity, string classname, PlayerBase player, float amount)
	{
		PlayerBase operator = null;
		if (entity)
		{
			operator = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
		}
		
		float skillIncrement;
		array<ref TerjeSkillCfg> skills();
		GetTerjeSkillsRegistry().GetSkills(skills);
		foreach (ref TerjeSkillCfg skill : skills)
		{
			if (operator && operator.GetTerjeSkills())
			{
				skillIncrement = GetGame().ConfigGetFloat( classname + " " + skill.GetId() + "SkillExpAddToSelf" );
				if (skillIncrement >= 1)
				{
					operator.GetTerjeSkills().AddSkillExperience(skill.GetId(), (int)skillIncrement);
				}
			}
			
			if (player && player.GetTerjeSkills())
			{
				skillIncrement = GetGame().ConfigGetFloat( classname + " " + skill.GetId() + "SkillExpAddToTarget" );
				if (skillIncrement >= 1)
				{
					player.GetTerjeSkills().AddSkillExperience(skill.GetId(), (int)skillIncrement);
				}
			}
		}

		if (player)
		{
			float healthDmg = GetGame().ConfigGetFloat( classname + " terjeAddHealth" );
			if (healthDmg != 0)
			{
				player.AddHealth("GlobalHealth", "Health", healthDmg * amount);
			}
			
			float bloodDmg = GetGame().ConfigGetFloat( classname + " terjeAddBlood" );
			if (bloodDmg != 0)
			{
				player.AddHealth("GlobalHealth", "Blood", bloodDmg * amount);
			}
			
			float shockDmg = GetGame().ConfigGetFloat( classname + " terjeAddShock" );
			if (shockDmg != 0)
			{
				player.AddHealth("", "Shock", shockDmg * amount);
			}
		}
	}
	
	string Describe(EntityAI entity, string classname)
	{
		string result = "";
		ItemBase item = ItemBase.Cast(entity);
		
		array<ref TerjeSkillCfg> skills();
		GetTerjeSkillsRegistry().GetSkills(skills);
		foreach (ref TerjeSkillCfg skill : skills)
		{
			float skillIncrement = GetGame().ConfigGetFloat( classname + " " + skill.GetId() + "SkillIncrement" );
			if (skillIncrement >= 1)
			{
				int skillValue = (int)skillIncrement;
				result = result + skill.GetDisplayName() + " <color rgba='0,148,255,255'>+" + skillValue + " EXP</color><br/>";
			}
		}
		
		float healthDmg = GetGame().ConfigGetFloat( classname + " terjeAddHealth" );
		if (healthDmg > 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_HEALTH <color rgba='97,215,124,255'>+" + (int)(healthDmg) + " HP</color><br/>";
		}
		else if (healthDmg < 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_HEALTH <color rgba='198,59,64,255'>" + (int)(healthDmg) + " HP</color><br/>";
		}
		
		float bloodDmg = GetGame().ConfigGetFloat( classname + " terjeAddBlood" );
		if (bloodDmg > 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_BLOOD <color rgba='97,215,124,255'>+" + (int)(bloodDmg) + " HP</color><br/>";
		}
		else if (bloodDmg < 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_BLOOD <color rgba='198,59,64,255'>" + (int)(bloodDmg) + " HP</color><br/>";
		}
		
		float shockDmg = GetGame().ConfigGetFloat( classname + " terjeAddShock" );
		if (shockDmg > 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_SHOCK <color rgba='97,215,124,255'>+" + (int)(shockDmg) + " HP</color><br/>";
		}
		else if (shockDmg < 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_SHOCK <color rgba='198,59,64,255'>" + (int)(shockDmg) + " HP</color><br/>";
		}
		
		float nutritionEnergy = GetGame().ConfigGetFloat( classname + " Nutrition energy" );
		if (nutritionEnergy == 0 && item != null && item.GetFoodStage())
		{
			nutritionEnergy = FoodStage.GetEnergy(item.GetFoodStage());
		}
		
		if (nutritionEnergy > 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_ENERGY <color rgba='97,215,124,255'>+" + (int)(nutritionEnergy) + " cal</color><br/>";
		}
		else if (nutritionEnergy < 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_ENERGY <color rgba='198,59,64,255'>" + (int)(nutritionEnergy) + " cal</color><br/>";
		}
		
		float nutritionWater = GetGame().ConfigGetFloat( classname + " Nutrition water" );
		if (nutritionWater == 0 && item != null && item.GetFoodStage())
		{
			nutritionWater = FoodStage.GetWater(item.GetFoodStage());
		}
		
		if (nutritionWater > 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_WATER <color rgba='97,215,124,255'>+" + (int)(nutritionWater) + " ml</color><br/>";
		}
		else if (nutritionWater < 0)
		{
			result = result + "#STR_TERJECORE_EFFECT_WATER <color rgba='198,59,64,255'>" + (int)(nutritionWater) + " ml</color><br/>";
		}
		
		return result;
	}
}