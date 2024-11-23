// <copyright file="TerjeSettingsCollection.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeSettingsCollection
{
	static int SKILLS_EXPERIENCE_GAIN_MODIFIER;
	static int SKILLS_EXPERIENCE_LOSE_MODIFIER;
	static int SKILLS_EXPERIENCE_LOSE_ON_RESET_PERKS;
	
	static int SKILLS_ATHLETIC_CHECK_DISTANCE;
	static int SKILLS_ATHLETIC_EXP_GAIN;
	
	static int SKILLS_STRENGTH_MELEE_LIGHT_GAIN_CHANCE;
	static int SKILLS_STRENGTH_MELEE_LIGHT_GAIN_EXP;
	static int SKILLS_STRENGTH_MELEE_HEAVY_GAIN_CHANCE;
	static int SKILLS_STRENGTH_MELEE_HEAVY_GAIN_EXP;
	static int SKILLS_STRENGTH_ITEMS_USE_GAIN_CHANCE;
	static int SKILLS_STRENGTH_ITEMS_USE_GAIN_EXP;
	
	static int SKILLS_METABOLISM_CONSUME_FOOD_EXP_MOD;
	static int SKILLS_METABOLISM_CONSUME_WATER_EXP_MOD;
	
	static int SKILLS_STEALTH_CAT_VISION_POWER;
	static int SKILLS_STEALTH_CHECK_DISTANCE;
	static int SKILLS_STEALTH_EXP_GAIN;
	static int SKILLS_STEALTH_INVISIBLE_MAN_CRIT_DISTANCE;
	static int SKILLS_STEALTH_WOLF_INSTINCT_CRIT_DISTANCE;
	static int SKILLS_STEALTH_BEARS_FRIEND_CRIT_DISTANCE;
	
	static int SKILLS_SURV_TEMPERATURE_MODIFIER;
	static int SKILLS_SURV_IGNITE_FIRE_BASE_CHANCE;
	static int SKILLS_SURV_IGNITE_FIRE_ADV_CHANCE;
	static int SKILLS_SURV_MAKE_FIRE_SUCCESS_GAIN_EXP;
	static int SKILLS_SURV_MAKE_FIRE_FAIL_GAIN_EXP;
	static int SKILLS_SURV_KILL_ZOMBIE_GAIN_EXP;
	static int SKILLS_SURV_LIFETIME_GAIN_EXP;
	static int SKILLS_SURV_LIFETIME_OFFSET;
	static int SKILLS_SURV_OVERRIDE_START_FIRE_TIME;
	
	static int SKILLS_HUNTING_KILL_ANIMAL_EXP_GAIN_MODIFIER;
	static int SKILLS_HUNTING_HEADSHOT_ANIMAL_EXP_GAIN_MODIFIER;
	static int SKILLS_HUNTING_BUTCH_ANIMAL_EXP_GAIN_MODIFIER;
	static int SKILLS_HUNTING_TRAP_ANIMAL_EXP_GAIN_MODIFIER;
	static int SKILLS_HUNTING_OVERRIDE_SKINNING_TIME;
	static int SKILLS_HUNTING_OVERRIDE_KNIFE_DAMAGE;
	static int SKILLS_HUNTING_OVERRIDE_MEAT_INIT_QUANTITY;
	static int SKILLS_HUNTING_OVERRIDE_MEAT_MIN_QUANTITY;

	static int SKILLS_FISHING_SUCCESS_CATCH_EXP_GAIN;
	static int SKILLS_FISHING_FAILED_CATCH_EXP_GAIN;
	static int SKILLS_FISHING_OVERRIDE_FILLET_MIN_QUANTITY;
	static int SKILLS_FISHING_OVERRIDE_ROD_DAMAGE;
	static int SKILLS_FISHING_OVERRIDE_HOOK_DAMAGE;
	static int SKILLS_FISHING_FISH_SIZE_MODIFIER;
	static int SKILLS_FISHING_BUTCH_EXP_GAIN_MODIFIER;
	
	override void OnInit()
	{
		super.OnInit();
		
		RegisterRegion("Skills", "General settings");
		SKILLS_EXPERIENCE_GAIN_MODIFIER = RegisterSettingFloat("Skills.ExperienceGainModifier", "Skills", "Modifier of gaining skill experience. Set to 2.5 to take 2.5 times more skill experience. Default value is 1.0", 1.0, false);
		SKILLS_EXPERIENCE_LOSE_MODIFIER = RegisterSettingFloat("Skills.ExperienceLoseModifier", "Skills", "Modifier of losing skill experience when died. Set to 0 to disable experience lose on death. Default value is 1.0", 1.0, false);
		SKILLS_EXPERIENCE_LOSE_ON_RESET_PERKS = RegisterSettingFloat("Skills.ExperienceLoseOnResetPerks", "Skills", "Sets the percentage of experience that the player will get back after resetting skill perks where 0.5 is 50% of experience. Set to 1.0 to take all experience back after reset. Default value is 0.5", 0.5, false);
		
		RegisterRegion("Skills", "Athletic");
		SKILLS_ATHLETIC_CHECK_DISTANCE = RegisterSettingInt("Skills.AthleticCheckDistance", "Skills", "Sets the distance a player must run to gain athletic experience. Default value is 100", 100, true);
		SKILLS_ATHLETIC_EXP_GAIN = RegisterSettingInt("Skills.AthleticExpGain", "Skills", "Sets the value of experience points that the player will gain by running. This parameter is also affected by 'ExperienceGainModifier'. Default value is 10", 10, true);

		RegisterRegion("Skills", "Strength");
		SKILLS_STRENGTH_MELEE_LIGHT_GAIN_CHANCE = RegisterSettingFloat("Skills.StrengthMeleeLightGainChance", "Skills", "Sets the chance the player will gain experience for a successful light melee attack. Default value is 0.1", 0.1, true);
		SKILLS_STRENGTH_MELEE_LIGHT_GAIN_EXP = RegisterSettingInt("Skills.StrengthMeleeLightGainExp", "Skills", "Sets the value of experience points that the player will gain for a successful light melee attack. This parameter is also affected by 'ExperienceGainModifier'. Default value is 15", 15, true);
		SKILLS_STRENGTH_MELEE_HEAVY_GAIN_CHANCE = RegisterSettingFloat("Skills.StrengthMeleeHeavyGainChance", "Skills", "Sets the chance the player will gain experience for a successful heavy melee attack. Default value is 0.5", 0.5, true);
		SKILLS_STRENGTH_MELEE_HEAVY_GAIN_EXP = RegisterSettingInt("Skills.StrengthMeleeHeavyGainExp", "Skills", "Sets the value of experience points that the player will gain for a successful heavy melee attack. This parameter is also affected by 'ExperienceGainModifier'. Default value is 30", 30, true);
		SKILLS_STRENGTH_ITEMS_USE_GAIN_CHANCE = RegisterSettingFloat("Skills.StrengthItemsUseGainChance", "Skills", "Sets the chance the player will gain experience for the use of tools (chopping firewood, extracting stones, etc). Default value is 0.2", 0.2, true);
		SKILLS_STRENGTH_ITEMS_USE_GAIN_EXP = RegisterSettingInt("Skills.StrengthItemsUseGainExp", "Skills", "Sets the value of experience points that the player will gain for the use of tools (chopping firewood, extracting stones, etc). This parameter is also affected by 'ExperienceGainModifier'. Default value is 10", 10, true);
		
		RegisterRegion("Skills", "Metabolism");
		SKILLS_METABOLISM_CONSUME_FOOD_EXP_MOD = RegisterSettingFloat("Skills.MetabolismConsumeFoodExpMod", "Skills", "Sets the modifier for gained metabolism skill experience when player is eating a food. Default value is 1.0", 1.0, true);
		SKILLS_METABOLISM_CONSUME_WATER_EXP_MOD = RegisterSettingFloat("Skills.MetabolismConsumeWaterExpMod", "Skills", "Sets the modifier for gained metabolism skill experience when player is drinking a water. Default value is 1.0", 1.0, true);
		
		RegisterRegion("Skills", "Stealth");
		SKILLS_STEALTH_CAT_VISION_POWER = RegisterSettingFloat("Skills.StealthCatVisionPower", "Skills", "Sets the modifier of power for the CatVision perk. Default value is 1.0", 1.0, false);
		SKILLS_STEALTH_CHECK_DISTANCE = RegisterSettingInt("Skills.StealthCheckDistance", "Skills", "Sets the distance a player must run to gain stealth experience. Default value is 30", 30, true);
		SKILLS_STEALTH_EXP_GAIN = RegisterSettingInt("Skills.StealthExpGain", "Skills", "Sets the value of experience points that the player will gain by crouching. This parameter is also affected by 'ExperienceGainModifier'. Default value is 10", 10, true);
		SKILLS_STEALTH_INVISIBLE_MAN_CRIT_DISTANCE = RegisterSettingFloat("Skills.StealthInvisibleManCritDistance", "Skills", "Sets the minimum distance value. If the player comes closer than this distance to the zombie - the perk InvisibleMan stops working. Default value is 2.5", 2.5, true);
		SKILLS_STEALTH_WOLF_INSTINCT_CRIT_DISTANCE = RegisterSettingFloat("Skills.StealthWolfInstinctCritDistance", "Skills", "Sets the minimum distance value. If the player comes closer than this distance to the wolf - the perk WolfInstinct stops working. Default value is 5.0", 5.0, true);
		SKILLS_STEALTH_BEARS_FRIEND_CRIT_DISTANCE = RegisterSettingFloat("Skills.StealthBearsFriendCritDistance", "Skills", "Sets the minimum distance value. If the player comes closer than this distance to the bear - the perk BearsFriend stops working. Default value is 10.0", 10.0, true);
		
		RegisterRegion("Skills", "Survival");
		SKILLS_SURV_TEMPERATURE_MODIFIER = RegisterSettingFloat("Skills.SurvTemperatureModifier", "Skills", "Sets the modifier value that is multiplied by the environment temperature modifier calculated from ReducedTempModifier of the survival skill. Default value is 0.5", 0.5, true);
		SKILLS_SURV_IGNITE_FIRE_BASE_CHANCE = RegisterSettingFloat("Skills.SurvIgniteFireBaseChance", "Skills", "Sets the base chance of starting fire in additional to the StartingFire perk chance. Default value is 0.2", 0.2, true);
		SKILLS_SURV_IGNITE_FIRE_ADV_CHANCE = RegisterSettingFloat("Skills.SurvIgniteFireAdvChance", "Skills", "Sets the base chance of starting fire with HandDrill without AncestralTechnologies perk. Default value is 0.0", 0.0, true);
		SKILLS_SURV_MAKE_FIRE_SUCCESS_GAIN_EXP = RegisterSettingInt("Skills.SurvMakeFireSuccessGainExp", "Skills", "Sets the value of experience points that the player will gain for successfully making a fire. This parameter is also affected by 'ExperienceGainModifier'. Default value is 50", 50, true);
		SKILLS_SURV_MAKE_FIRE_FAIL_GAIN_EXP = RegisterSettingInt("Skills.SurvMakeFireFailGainExp", "Skills", "Sets the value of experience points that the player will gain for trying to making a fire. This parameter is also affected by 'ExperienceGainModifier'. Default value is 10", 10, true);
		SKILLS_SURV_KILL_ZOMBIE_GAIN_EXP = RegisterSettingInt("Skills.SurvKillZombieGainExp", "Skills", "Sets the value of experience points that the player will gain when kill a zombie. This parameter is also affected by 'ExperienceGainModifier'. Default value is 5", 5, true);
		SKILLS_SURV_LIFETIME_GAIN_EXP = RegisterSettingInt("Skills.SurvLifetimeGainExp", "Skills", "Sets the value of experience points that the player will gain when survived for a long time. This parameter is also affected by 'ExperienceGainModifier'. Default value is 100", 100, true);
		SKILLS_SURV_LIFETIME_OFFSET = RegisterSettingInt("Skills.SurvLifetimeOffset", "Skills", "Sets the cyclic time interval in seconds after which the player will be awarded additional experience points for the survival skill. Default value is 3600 seconds", 3600, true);
		SKILLS_SURV_OVERRIDE_START_FIRE_TIME = RegisterSettingFloat("Skills.SurvOverrideStartFireTime", "Skills", "Overrides the time for starting the fire. If the value is -1, the default value will be used instead. Default value is 15 sec", 15.0, false);
		
		RegisterRegion("Skills", "Hunting");
		SKILLS_HUNTING_KILL_ANIMAL_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.HuntingKillAnimalExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after killing an animal. This modifier is multiplied by the parameter terjeOnKillHuntingExp from the animal's config. Default value is 1.0", 1.0, true);
		SKILLS_HUNTING_HEADSHOT_ANIMAL_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.HuntingHeadshotAnimalExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after killing an animal with headshot in additional to HuntingKillAnimalExpGainModifier. This modifier is multiplied by the parameter terjeOnHeadshotHuntingExp from the animal's config. Default value is 1.0", 1.0, true);
		SKILLS_HUNTING_BUTCH_ANIMAL_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.HuntingButchAnimalExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after butchering an animal. This modifier is multiplied by the parameter terjeOnButchHuntingExp from the animal's config. Default value is 1.0", 1.0, true);
		SKILLS_HUNTING_TRAP_ANIMAL_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.HuntingTrapAnimalExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after cathing an animal by the trap. This modifier is multiplied by the parameter terjeOnCatchAnimalHuntingExp from the trap's config. Default value is 1.0", 1.0, true);
		SKILLS_HUNTING_OVERRIDE_SKINNING_TIME = RegisterSettingFloat("Skills.HuntingOverrideSkinningTime", "Skills", "Sets the time of skinning animal carcasses for use with the QuickSkinning perk. If the value is -1, the default value will be used instead. Default value is 60 sec", 60.0, false);
		SKILLS_HUNTING_OVERRIDE_KNIFE_DAMAGE = RegisterSettingFloat("Skills.HuntingOverrideKnifeDamage", "Skills", "Sets the absolute damage value for a knife when skinning animal carcasses. Affected by MasterKnife perk. Default value is 100", 100.0, true);
		SKILLS_HUNTING_OVERRIDE_MEAT_INIT_QUANTITY = RegisterSettingFloat("Skills.HuntingOverrideMeatInitQuantity", "Skills", "Sets the maximum initial random quantity for the one peace of meat that can be produced during the skinning without skills. The MeatHunter modifier will be added to this value. Value range from 0 (0%) to 1 (100%). Default value is 0.2 (20%)", 0.2, true);
		SKILLS_HUNTING_OVERRIDE_MEAT_MIN_QUANTITY = RegisterSettingFloat("Skills.HuntingOverrideMeatMinQuantity", "Skills", "Sets the minimum quantity for the one peace of meat that can be produced during the skinning without skills. Value range from 0 (0%) to 1 (100%). Default value is 0.1 (10%)", 0.1, true);
		
		RegisterRegion("Skills", "Fishing");
		SKILLS_FISHING_SUCCESS_CATCH_EXP_GAIN = RegisterSettingInt("Skills.FishingSuccessCatchGainExp", "Skills", "Sets the experience value that the player will receive if the catch is successful. This parameter is also affected by 'ExperienceGainModifier'. Default value is 200", 200, true);
		SKILLS_FISHING_FAILED_CATCH_EXP_GAIN = RegisterSettingInt("Skills.FishingFailedCatchGainExp", "Skills", "Sets the experience value that the player will receive if the catch is failed. This parameter is also affected by 'ExperienceGainModifier'. Default value is 50", 50, true);
		SKILLS_FISHING_OVERRIDE_FILLET_MIN_QUANTITY = RegisterSettingFloat("Skills.FishingOverrideFilletMinQuantity", "Skills", "Sets the minimum quantity for the one peace of fish fillet that can be produced during the skinning without skills. Value range from 0 (0%) to 1 (100%). Default value is 0.2 (20%)", 0.2, true);
		SKILLS_FISHING_OVERRIDE_ROD_DAMAGE = RegisterSettingFloat("Skills.FishingOverrideRodDamage", "Skills", "Sets the absolute damage value for a fishing rod after a fishing action. Affected by StraightArms perk. Default value is 5", 5, true);
		SKILLS_FISHING_OVERRIDE_HOOK_DAMAGE = RegisterSettingFloat("Skills.FishingOverrideHookDamage", "Skills", "Sets the absolute damage value for a fishing hook after a fishing action. Affected by StraightArms perk. Default value is 5", 5, true);
		SKILLS_FISHING_FISH_SIZE_MODIFIER = RegisterSettingFloat("Skills.FishingFishSizeModifier", "Skills", "Sets the fish size modifier. It is used for the player to catch fish of different sizes for correct work of FishermanLuck skill. Default value is 0.2", 0.2, true);
		SKILLS_FISHING_BUTCH_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.FishingButchExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after butchering (cleaning) an fish. This modifier is multiplied by the parameter terjeOnButchHuntingExp from the fish's config. Default value is 1.0", 1.0, true);
	}
};
