// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeSkills
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeCore"
		};
	};
};

class CfgMods
{
	class TerjeSkills
	{
		dir = "TerjeSkills";
		picture = "TerjeSkills/Textures/mod_icon.edds";
		action = "https://steamcommunity.com/id/terjebruoygard/myworkshopfiles/";
		hideName = 0;
		hidePicture = 0;
		name = "Terje Skills";
		credits = "Terje Bruoygard";
		version = "1.0.0";
		author = "TerjeBruoygard";
		dependencies[] = {"Core","Game","World","Mission"};
		extra = 0;
		type = "mod"; 
		
		class defs
		{
			class imageSets
			{
				files[] = {
					"TerjeSkills/Textures/Icons/TerjeSkills.imageset", 
					"TerjeSkills/Textures/Icons/PerkBorders.imageset", 
					"TerjeSkills/Textures/Icons/PerkLevels.imageset", 
					"TerjeSkills/Textures/Icons/TerjePerk.imageset",
					"TerjeSkills/Textures/Icons/TerjePerkBlack.imageset"};
			};
			class gameScriptModule {
				value = "";
				files[] = {"TerjeSkills/Scripts/3_Game"};
			};
			
			class worldScriptModule {
				value = "";
				files[] = {"TerjeSkills/Scripts/4_World"};
			};

			class missionScriptModule {
				value = "";
				files[] = {"TerjeSkills/Scripts/5_Mission"};
			};
		};
	};
};

class CfgTerjeSkills
{
	class Athletic
	{
		id="athlc";
		enabled=1;
		displayName="#STR_TERJESKILL_ATHLETIC_NAME";
		description="#STR_TERJESKILL_ATHLETIC_DESC";
		icon="set:TerjeSkills_icon image:ts_athletic";
		perkPointsPerLevel=1;
		expLoseOnDeath=-100;
		levels[]=
		{
			100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // 1-10
			1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // 11-20
			6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // 20-30
			16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // 31-40
			37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // 41-50
		};
		class Modifiers
		{
			class MaxStaminaModifier
			{
				id="maxstaminamod";
				enabled=1;
				text="#STR_TERJESKILL_ATHLETIC_MOD0";
				value=0.02;
			};
		};
		class Perks
		{
			class QuickFeet
			{
				id="quickf";
				enabled=1;
				displayName="#STR_TERJEPERK_ATH_QUICKFEET";
				description="#STR_TERJEPERK_ATH_QUICKFEET_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_quickfeet";
				enabledIcon="set:TerjePerk_icon image:tp_quickfeet";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,1};
				values[]={-0.05,-0.1,-0.2,-0.3,-0.4,-0.8};
			};
			class Marathoner
			{
				id="marathon";
				enabled=1;
				displayName="#STR_TERJEPERK_ATH_MARATHONER";
				description="#STR_TERJEPERK_ATH_MARATHONER_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_marathoner";
				enabledIcon="set:TerjePerk_icon image:tp_marathoner";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.05,0.1,0.2,0.3,0.5,1.0};
			};
			class ProperBreathing
			{
				id="pbreath";
				enabled=1;
				displayName="#STR_TERJEPERK_ATH_PROPERBREATHING";
				description="#STR_TERJEPERK_ATH_PROPERBREATHING_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_properbreathing";
				enabledIcon="set:TerjePerk_icon image:tp_properbreathing";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.3,0.4,0.5,1.0};
			};
			class Swimmer
			{
				id="swimmer";
				enabled=1;
				displayName="#STR_TERJEPERK_ATH_SWIMMER";
				description="#STR_TERJEPERK_ATH_SWIMMER_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_swimmer";
				enabledIcon="set:TerjePerk_icon image:tp_swimmer";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,1};
				values[]={0.05,0.1,0.2,0.3,0.4,0.5};
			};
			class StairMaster
			{
				id="ladder";
				enabled=1;
				displayName="#STR_TERJEPERK_ATH_STAIRMASTER";
				description="#STR_TERJEPERK_ATH_STAIRMASTER_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_stairmaster";
				enabledIcon="set:TerjePerk_icon image:tp_stairmaster";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,1};
				values[]={0.1,0.2,0.3,0.4,0.5,0.75};
			};
			
			class NoPanting
			{
				id="npant";
				enabled=1;
				displayName="#STR_TERJEPERK_ATH_NOPANTING";
				description="#STR_TERJEPERK_ATH_NOPANTING_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_nopanting";
				enabledIcon="set:TerjePerk_icon image:tp_nopanting";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.1,-0.2,-0.4,-0.6,-0.8,-1.0};
			};
			class Enduring
			{
				id="enduring";
				enabled=1;
				displayName="#STR_TERJEPERK_ATH_ENDURING";
				description="#STR_TERJEPERK_ATH_ENDURING_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_enduring";
				enabledIcon="set:TerjePerk_icon image:tp_enduring";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.4,0.6,0.8,1.0};
			};
			class Stuntman
			{
				id="stuntman";
				enabled=1;
				displayName="#STR_TERJEPERK_ATH_STUNTMAN";
				description="#STR_TERJEPERK_ATH_STUNTMAN_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_stuntman";
				enabledIcon="set:TerjePerk_icon image:tp_stuntman";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,1};
				values[]={-0.05,-0.1,-0.2,-0.3,-0.5,-0.75};
			};
			class StrongBones
			{
				id="strbones";
				enabled=1;
				displayName="#STR_TERJEPERK_ATH_STRONGBONES";
				description="#STR_TERJEPERK_ATH_STRONGBONES_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_bonecrusher";
				enabledIcon="set:TerjePerk_icon image:tp_bonecrusher";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,1};
				values[]={-0.05,-0.1,-0.2,-0.3,-0.5,-0.75};
			};
		};
	};
	class Strength
	{
		id="strng";
		enabled=1;
		displayName="#STR_TERJESKILL_STRENGTH_NAME";
		description="#STR_TERJESKILL_STRENGTH_DESC";
		icon="set:TerjeSkills_icon image:ts_strength";
		perkPointsPerLevel=1;
		expLoseOnDeath=-100;
		levels[]=
		{
			100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // 1-10
			1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // 11-20
			6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // 20-30
			16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // 31-40
			37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // 41-50
		};
		class Modifiers
		{
			class MaxWeightModifier
			{
				id="maxweightmod";
				enabled=1;
				text="#STR_TERJESKILL_STRENGTH_MOD0";
				value=0.02;
			};
		};
		class Perks
		{
			class HeavyWeight
			{
				id="hvweight";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_HEAVYWEIGHT";
				description="#STR_TERJEPERK_STRNG_HEAVYWEIGHT_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_heavyweight";
				enabledIcon="set:TerjePerk_icon image:tp_heavyweight";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
			class Jumper
			{
				id="jumper";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_JUMPER";
				description="#STR_TERJEPERK_STRNG_JUMPER_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_jumper";
				enabledIcon="set:TerjePerk_icon image:tp_jumper";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.1,-0.2,-0.4,-0.6,-0.8};
			};
			class MasterOfDefence
			{
				id="mrdefence";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_MRPROTECTION";
				description="#STR_TERJEPERK_STRNG_MRPROTECTION_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_masterdefense";
				enabledIcon="set:TerjePerk_icon image:tp_masterdefense";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.1,-0.15,-0.25,-0.5,-0.8};
			};
			class MasterOfEvasion
			{
				id="mrevasion";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_MREVASION";
				description="#STR_TERJEPERK_STRNG_MREVASION_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_masterevasion";
				enabledIcon="set:TerjePerk_icon image:tp_masterevasion";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
			class LightAttacksSpeed
			{
				id="lattkspeed";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_GUSTYSQUALL";
				description="#STR_TERJEPERK_STRNG_GUSTYSQUALL_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_gustysquall";
				enabledIcon="set:TerjePerk_icon image:tp_gustysquall";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.1,-0.15,-0.25,-0.5,-0.8};
			};
			class LightAttacksForce
			{
				id="lattkforce";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_CRUSHINGSQUALL";
				description="#STR_TERJEPERK_STRNG_CRUSHINGSQUALL_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_crushingsquall";
				enabledIcon="set:TerjePerk_icon image:tp_crushingsquall";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={0.10,0.25,0.5,0.75,1.0};
			};
			class HeavyAttacksSpeed
			{
				id="hattkspeed";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_HEAVYONSLAUGHT";
				description="#STR_TERJEPERK_STRNG_HEAVYONSLAUGHT_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_heavyonslaught";
				enabledIcon="set:TerjePerk_icon image:tp_heavyonslaught";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.1,-0.15,-0.25,-0.5,-0.8};
			};
			class HeavyAttacksForce
			{
				id="hattkforce";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_DESTRUCTONSLAUGHT";
				description="#STR_TERJEPERK_STRNG_DESTRUCTONSLAUGHT_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_destronslaught";
				enabledIcon="set:TerjePerk_icon image:tp_destronslaught";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={0.10,0.25,0.5,1.0,2.0};
			};
			class LightweightArmor
			{
				id="ltarmor";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_LIGHTARMOR";
				description="#STR_TERJEPERK_STRNG_LIGHTARMOR_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_lightarmor";
				enabledIcon="set:TerjePerk_icon image:tp_lightarmor";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.1,-0.25,-0.5,-0.75,-1.0};
			};
			class StrongHands
			{
				id="strhands";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_STRONGHANDS";
				description="#STR_TERJEPERK_STRNG_STRONGHANDS_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_stronghands";
				enabledIcon="set:TerjePerk_icon image:tp_stronghands";
				requiredSkillLevels[]={1};
				requiredPerkPoints[]={1};
				values[]={0.0};
			};
			class MasterStroke
			{
				id="mrstroke";
				enabled=1;
				displayName="#STR_TERJEPERK_STRNG_MASTERSTROKE";
				description="#STR_TERJEPERK_STRNG_MASTERSTROKE_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_masterstroke";
				enabledIcon="set:TerjePerk_icon image:tp_masterstroke";
				requiredSkillLevels[]={35};
				requiredPerkPoints[]={1};
				values[]={0.0};
			};
		};
	};
	class Metabolism
	{
		id="mtblsm";
		enabled=1;
		displayName="#STR_TERJESKILL_METABLSM_NAME";
		description="#STR_TERJESKILL_METABLSM_DESC";
		icon="set:TerjeSkills_icon image:ts_metablsm";
		perkPointsPerLevel=1;
		expLoseOnDeath=-100;
		levels[]=
		{
			100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // 1-10
			1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // 11-20
			6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // 20-30
			16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // 31-40
			37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // 41-50
		};
		class Modifiers
		{
			class EnergyConsumptionModifier
			{
				id="energconsmod";
				enabled=1;
				text="#STR_TERJESKILL_METABLSM_MOD0";
				value=-0.01;
			};
		};
		class Perks
		{
			class IncreasedCalorie
			{
				id="incalorie";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_INCREASEDCALORIE";
				description="#STR_TERJEPERK_METABLSM_INCREASEDCALORIE_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_incrcalorie";
				enabledIcon="set:TerjePerk_icon image:tp_incrcalorie";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
			class IncreasedHydration
			{
				id="incrhydr";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_INCREASEDHYDRAT";
				description="#STR_TERJEPERK_METABLSM_INCREASEDHYDRAT_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_incrhydration";
				enabledIcon="set:TerjePerk_icon image:tp_incrhydration";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
			class EnergySaving
			{
				id="enrgsave";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_ENREGYSAVE";
				description="#STR_TERJEPERK_METABLSM_ENREGYSAVE_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_energysaving";
				enabledIcon="set:TerjePerk_icon image:tp_energysaving";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.05,-0.15,-0.25,-0.5,-0.75};
			};
			class WaterSaving
			{
				id="watrsave";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_WATERSAVE";
				description="#STR_TERJEPERK_METABLSM_WATERSAVE_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_watersaving";
				enabledIcon="set:TerjePerk_icon image:tp_watersaving";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.05,-0.15,-0.25,-0.5,-0.75};
			};
			class EnergyControl
			{
				id="enrgcontr";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_ENERGYCONTROL";
				description="#STR_TERJEPERK_METABLSM_ENERGYCONTROL_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_energycontrol";
				enabledIcon="set:TerjePerk_icon image:tp_energycontrol";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.05,-0.1,-0.15,-0.25,-0.5};
			};
			class HydrationControl
			{
				id="hydrcontr";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_HYDRATIONCONTROL";
				description="#STR_TERJEPERK_METABLSM_HYDRATIONCONTROL_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_hydrationcontrol";
				enabledIcon="set:TerjePerk_icon image:tp_hydrationcontrol";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.05,-0.1,-0.15,-0.25,-0.5};
			};
			class EnregyContainment
			{
				id="enrgconta";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_ENERGYCONTAIN";
				description="#STR_TERJEPERK_METABLSM_ENERGYCONTAIN_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_enregycontain";
				enabledIcon="set:TerjePerk_icon image:tp_enregycontain";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={-0.05,-0.15,-0.25,-0.5,-0.75};
			};
			class WaterContainment
			{
				id="watrconta";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_WATERCONTAIN";
				description="#STR_TERJEPERK_METABLSM_WATERCONTAIN_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_watercontain";
				enabledIcon="set:TerjePerk_icon image:tp_watercontain";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={-0.05,-0.15,-0.25,-0.5,-0.75};
			};
			class ResistWater
			{
				id="reswater";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_RESISTWATER";
				description="#STR_TERJEPERK_METABLSM_RESISTWATER_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_resistwater";
				enabledIcon="set:TerjePerk_icon image:tp_resistwater";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.05,-0.15,-0.25,-0.5,-0.75};
			};
			class ResistHunger
			{
				id="reshunger";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_RESISTHUNGER";
				description="#STR_TERJEPERK_METABLSM_RESISTHUNGER_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_resisthunger";
				enabledIcon="set:TerjePerk_icon image:tp_resisthunger";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.05,-0.15,-0.25,-0.5,-0.75};
			};
			class WildMeatLover
			{
				id="wmlover";
				enabled=1;
				displayName="#STR_TERJEPERK_METABLSM_WMLOVER";
				description="#STR_TERJEPERK_METABLSM_WMLOVER_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_wmlover";
				enabledIcon="set:TerjePerk_icon image:tp_wmlover";
				requiredSkillLevels[]={35};
				requiredPerkPoints[]={2};
				values[]={0.0};
			};
		};
	};
	class Stealth
	{
		id="stlth";
		enabled=1;
		displayName="#STR_TERJESKILL_STEALCH_NAME";
		description="#STR_TERJESKILL_STEALCH_DESC";
		icon="set:TerjeSkills_icon image:ts_stealth";
		perkPointsPerLevel=1;
		expLoseOnDeath=-100;
		levels[]=
		{
			100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // 1-10
			1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // 11-20
			6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // 20-30
			16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // 31-40
			37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // 41-50
		};
		class Perks
		{
			class QuietStep
			{
				id="qtstep";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_QUIETSTEP";
				description="#STR_TERJEPERK_STLTH_QUIETSTEP_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_quiestep";
				enabledIcon="set:TerjePerk_icon image:tp_quiestep";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.05,-0.10,-0.25,-0.5,-0.75};
			};
			class ColdBlooded
			{
				id="coldbldd";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_COLDBLOODED";
				description="#STR_TERJEPERK_STLTH_COLDBLOODED_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_coldblooded";
				enabledIcon="set:TerjePerk_icon image:tp_coldblooded";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.1,-0.25,-0.5,-0.75,-1.0};
			};
			class QuietShooter
			{
				id="qshooter";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_QUIETSHOOTER";
				description="#STR_TERJEPERK_STLTH_QUIETSHOOTER_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_quietshooter";
				enabledIcon="set:TerjePerk_icon image:tp_quietshooter";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.05,-0.10,-0.25,-0.5,-0.75};
			};
			class FittingEquipment
			{
				id="fitequip";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_FITTINGEQUIP";
				description="#STR_TERJEPERK_STLTH_FITTINGEQUIP_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_fittingequipment";
				enabledIcon="set:TerjePerk_icon image:tp_fittingequipment";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.1,-0.2,-0.4,-0.6,-0.8};
			};
			class InvisibleMan
			{
				id="invisman";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_INVISIBLEMAN";
				description="#STR_TERJEPERK_STLTH_INVISIBLEMAN_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_invisibleman";
				enabledIcon="set:TerjePerk_icon image:tp_invisibleman";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.05,-0.10,-0.25,-0.5,-0.75};
			};
			class CatVision
			{
				id="catvis";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_CATVISION";
				description="#STR_TERJEPERK_STLTH_CATVISION_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_catvision";
				enabledIcon="set:TerjePerk_icon image:tp_catvision";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={0.25,0.5,0.75,1.0,1.5};
			};
			class WolfInstinct
			{
				id="wolfinst";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_WOLFINSTINCT";
				description="#STR_TERJEPERK_STLTH_WOLFINSTINCT_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_wolfinstinct";
				enabledIcon="set:TerjePerk_icon image:tp_wolfinstinct";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.1,-0.2,-0.3,-0.6,-0.9};
			};
			class BearsFriend
			{
				id="bearfrnd";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_FRIENDBEAR";
				description="#STR_TERJEPERK_STLTH_FRIENDBEAR_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_friendbear";
				enabledIcon="set:TerjePerk_icon image:tp_friendbear";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,2};
				values[]={-0.1,-0.2,-0.3,-0.6,-0.9};
			};
			class SilentKiller
			{
				id="silentkilr";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_SILENTKILLER";
				description="#STR_TERJEPERK_STLTH_SILENTKILLER_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_silentkiller";
				enabledIcon="set:TerjePerk_icon image:tp_silentkiller";
				requiredSkillLevels[]={1};
				requiredPerkPoints[]={2};
				values[]={0.0};
			};
			class Ninja
			{
				id="ninja";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_NINJA";
				description="#STR_TERJEPERK_STLTH_NINJA_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_ninja";
				enabledIcon="set:TerjePerk_icon image:tp_ninja";
				requiredSkillLevels[]={30};
				requiredPerkPoints[]={3};
				values[]={-0.5};
			};
			class ShadowTracker
			{
				id="shadowtrc";
				enabled=1;
				displayName="#STR_TERJEPERK_STLTH_SHADOWTRACKER";
				description="#STR_TERJEPERK_STLTH_SHADOWTRACKER_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_shadowtrack";
				enabledIcon="set:TerjePerk_icon image:tp_shadowtrack";
				requiredSkillLevels[]={40};
				requiredPerkPoints[]={3};
				values[]={0.0};
			};
		};
	};	class Survival
	{
		id="surv";
		enabled=1;
		displayName="#STR_TERJESKILL_SURVIVAL_NAME";
		description="#STR_TERJESKILL_SURVIVAL_DESC";
		icon="set:TerjeSkills_icon image:ts_survival";
		perkPointsPerLevel=1;
		expLoseOnDeath=-100;
		levels[]=
		{
			100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // 1-10
			1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // 11-20
			6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // 20-30
			16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // 31-40
			37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // 41-50
		};
		class Modifiers
		{
			class ReducedTempModifier
			{
				id="survtempmod";
				enabled=1;
				text="#STR_TERJESKILL_SURVIVAL_MOD0";
				value=-0.01;
			};
			class ReducedZombDmgModifier
			{
				id="survzmbmod";
				enabled=1;
				text="#STR_TERJESKILL_SURVIVAL_MOD1";
				value=-0.01;
			};
			class ReducedFireStartModifier
			{
				id="survfiremod";
				enabled=1;
				text="#STR_TERJESKILL_SURVIVAL_MOD2";
				value=-0.02;
			};
		};
		class Perks
		{
			class StartingFire
			{
				id="startfire";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_STARTFIRE";
				description="#STR_TERJESKILL_SURV_STARTFIRE_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_startingfire";
				enabledIcon="set:TerjePerk_icon image:tp_startingfire";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.4,0.6,0.8,1.0};
			};
			class ColdResistance
			{
				id="coldres";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_COLDRESISTANCE";
				description="#STR_TERJESKILL_SURV_COLDRESISTANCE_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_freezeresist";
				enabledIcon="set:TerjePerk_icon image:tp_freezeresist";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.05,0.1,0.2,0.3,0.4,0.5};
			};
			class RoughFeet
			{
				id="rghfeet";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_ROUGHFEET";
				description="#STR_TERJESKILL_SURV_ROUGHFEET_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_roughfeet";
				enabledIcon="set:TerjePerk_icon image:tp_roughfeet";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.1,-0.2,-0.4,-0.6,-0.8,-1.0};
			};
			class RoughHands
			{
				id="rghhands";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_ROUGHHANDS";
				description="#STR_TERJESKILL_SURV_ROUGHHANDS_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_roughhands";
				enabledIcon="set:TerjePerk_icon image:tp_roughhands";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.1,-0.2,-0.4,-0.6,-0.8,-1.0};
			};
			class AncestralTechnologies
			{
				id="anctech";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_ANCESTRALTECHNOLOGIE";
				description="#STR_TERJESKILL_SURV_ANCESTRALTECHNOLOGIE_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_ancestechno";
				enabledIcon="set:TerjePerk_icon image:tp_ancestechno";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.35,0.45,0.55,0.65,0.75,1.0};
			};
			class MaintainingFire
			{
				id="maintngfire";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_MAINTAININGFIRE";
				description="#STR_TERJESKILL_SURV_MAINTAININGFIRE_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_maintainingfire";
				enabledIcon="set:TerjePerk_icon image:tp_maintainingfire";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.25,0.5,1.0,1.5,2.0,3.0};
			};
			class DurableEquipment
			{
				id="durequip";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_DURABLEEQUIPMENT";
				description="#STR_TERJESKILL_SURV_DURABLEEQUIPMENT_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_durableequip";
				enabledIcon="set:TerjePerk_icon image:tp_durableequip";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.1,-0.2,-0.4,-0.6,-0.7,-0.85};
			};
			class Bushcraft
			{
				id="bushcraft";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_CRAFTS";
				description="#STR_TERJESKILL_SURV_CRAFTS_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_survcrafts";
				enabledIcon="set:TerjePerk_icon image:tp_survcrafts";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.35,0.45,0.55,0.65,0.75,1.0};
			};
			class Expert
			{
				id="expert";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_EXPERT";
				description="#STR_TERJESKILL_SURV_EXPERT_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_expert";
				enabledIcon="set:TerjePerk_icon image:tp_expert";
				requiredSkillLevels[]={15};
				requiredPerkPoints[]={1};
				values[]={0.0};
			};
			class Stashes
			{
				id="stashes";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_STASHES";
				description="#STR_TERJESKILL_SURV_STASHES_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_caches";
				enabledIcon="set:TerjePerk_icon image:tp_caches";
				requiredSkillLevels[]={15};
				requiredPerkPoints[]={2};
				values[]={0.0};
			};
			class SurvivalInstinct
			{
				id="survinst";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_SURVIVALINSTINCT";
				description="#STR_TERJESKILL_SURV_SURVIVALINSTINCT_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_survinstinct";
				enabledIcon="set:TerjePerk_icon image:tp_survinstinct";
				requiredSkillLevels[]={15};
				requiredPerkPoints[]={2};
				values[]={0.0};
			};
			class MushroomPremonition
			{
				id="mushprem";
				enabled=1;
				displayName="#STR_TERJESKILL_SURV_MUSHROOMPREMONITION";
				description="#STR_TERJESKILL_SURV_MUSHROOMPREMONITION_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_mushpremonition";
				enabledIcon="set:TerjePerk_icon image:tp_mushpremonition";
				requiredSkillLevels[]={35};
				requiredPerkPoints[]={2};
				values[]={0.0};
			};
		};
	};	class Hunting
	{
		id="hunt";
		enabled=1;
		displayName="#STR_TERJESKILL_HUNTING_NAME";
		description="#STR_TERJESKILL_HUNTING_DESC";
		icon="set:TerjeSkills_icon image:ts_hunting";
		perkPointsPerLevel=1;
		expLoseOnDeath=-100;
		levels[]=
		{
			100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // 1-10
			1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // 11-20
			6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // 20-30
			16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // 31-40
			37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // 41-50
		};
		class Modifiers
		{
			class MeatCountModifier
			{
				id="meatcountmod";
				enabled=1;
				text="#STR_TERJESKILL_HUNTING_MOD0";
				value=0.02;
			};
		};
		class Perks
		{
			class MeatHunter
			{
				id="meathunt";
				enabled=1;
				displayName="#STR_TERJESKILL_HUNT_MEATHUNTER";
				description="#STR_TERJESKILL_HUNT_MEATHUNTER_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_meathunt";
				enabledIcon="set:TerjePerk_icon image:tp_meathunt";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,2,3};
				values[]={0.1,0.2,0.4,0.6,0.8,1.0};
			};
			class QuickSkinning
			{
				id="quickcut";
				enabled=1;
				displayName="#STR_TERJESKILL_HUNT_QUICKCUTTING";
				description="#STR_TERJESKILL_HUNT_QUICKCUTTING_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_quickcutm";
				enabledIcon="set:TerjePerk_icon image:tp_quickcutm";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.1,-0.2,-0.3,-0.4,-0.6,-0.8};
			};
			class MasterKnife
			{
				id="mknife";
				enabled=1;
				displayName="#STR_TERJESKILL_HUNT_MASTERKNIFE";
				description="#STR_TERJESKILL_HUNT_MASTERKNIFE_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_masterknife";
				enabledIcon="set:TerjePerk_icon image:tp_masterknife";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.1,-0.2,-0.3,-0.5,-0.7,-0.9};
			};
			class TrapExpert
			{
				id="trapexp";
				enabled=1;
				displayName="#STR_TERJESKILL_HUNT_TRAPEXPERT";
				description="#STR_TERJESKILL_HUNT_TRAPEXPERT_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_trapexpert";
				enabledIcon="set:TerjePerk_icon image:tp_trapexpert";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.4,0.6,0.8,1.0};
			};
			class PeltMaster
			{
				id="plmaster";
				enabled=1;
				displayName="#STR_TERJESKILL_HUNT_SKINMASTER";
				description="#STR_TERJESKILL_HUNT_SKINMASTER_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_prhides";
				enabledIcon="set:TerjePerk_icon image:tp_prhides";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.3,0.5,0.75,1.0};
			};
			class ExperiencedHunter
			{
				id="exphunter";
				enabled=1;
				displayName="#STR_TERJESKILL_HUNT_EXPERIENCEDHUNTER";
				description="#STR_TERJESKILL_HUNT_EXPERIENCEDHUNTER_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_exphunter";
				enabledIcon="set:TerjePerk_icon image:tp_exphunter";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.25,0.5,1.0,2.0,3.0};
			};
			class KnowledgeAnatomy
			{
				id="knwanatomy";
				enabled=1;
				displayName="#STR_TERJESKILL_HUNT_KNOWLEDGEANATOMY";
				description="#STR_TERJESKILL_HUNT_KNOWLEDGEANATOMY_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_knwanatomy";
				enabledIcon="set:TerjePerk_icon image:tp_knwanatomy";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.25,0.5,1.0,2.0,3.0};
			};
			class RemovingRot
			{
				id="remvrot";
				enabled=1;
				displayName="#STR_TERJESKILL_HUNT_REMOVINGROT";
				description="#STR_TERJESKILL_HUNT_REMOVINGROT_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_removrot";
				enabledIcon="set:TerjePerk_icon image:tp_removrot";
				requiredSkillLevels[]={1};
				requiredPerkPoints[]={1};
				values[]={0.0};
			};
			class Pathfinder
			{
				id="pathfindr";
				enabled=1;
				displayName="#STR_TERJESKILL_HUNT_PATHFINDER";
				description="#STR_TERJESKILL_HUNT_PATHFINDER_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_pathfindr";
				enabledIcon="set:TerjePerk_icon image:tp_pathfindr";
				requiredSkillLevels[]={35};
				requiredPerkPoints[]={4};
				values[]={0.0};
			};
		};
	};	class Fishing
	{
		id="fish";
		enabled=1;
		displayName="#STR_TERJESKILL_FISHING_NAME";
		description="#STR_TERJESKILL_FISHING_DESC";
		icon="set:TerjeSkills_icon image:ts_fushing";
		perkPointsPerLevel=1;
		expLoseOnDeath=-100;
		levels[]=
		{
			100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // 1-10
			1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // 11-20
			6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // 20-30
			16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // 31-40
			37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // 41-50
		};
		
		class Perks
		{
			class MasterFillet
			{
				id="masterf";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_MASTERFILLET";
				description="#STR_TERJESKILL_FISH_MASTERFILLET_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_mastfile";
				enabledIcon="set:TerjePerk_icon image:tp_mastfile";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.4,0.6,0.8,1.0};
			};
			class QuickClean
			{
				id="quickclean";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_QUICKCLEANING";
				description="#STR_TERJESKILL_FISH_QUICKCLEANING_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_quickclean";
				enabledIcon="set:TerjePerk_icon image:tp_quickclean";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.1,-0.2,-0.3,-0.5,-0.75,-0.95};
			};
			class StraightArms
			{
				id="strgarms";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_STRAIGHTARMS";
				description="#STR_TERJESKILL_FISH_STRAIGHTARMS_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_straightarms";
				enabledIcon="set:TerjePerk_icon image:tp_straightarms";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.1,-0.2,-0.4,-0.6,-0.8,-1.0};
			};
			class MasterTrap
			{
				id="mastrap";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_MASTERTRAPS";
				description="#STR_TERJESKILL_FISH_MASTERTRAPS_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_mastrtrap";
				enabledIcon="set:TerjePerk_icon image:tp_mastrtrap";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.4,0.6,0.8,1.0};
			};
			class SkilledFisherman
			{
				id="skfishman";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_SKILLEDFISHERMAN";
				description="#STR_TERJESKILL_FISH_SKILLEDFISHERMAN_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_skillfishman";
				enabledIcon="set:TerjePerk_icon image:tp_skillfishman";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.25,0.5,0.75,1.0,2.5};
			};
			class FishermanLuck
			{
				id="fishmluck";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_FISHERMANLUCK";
				description="#STR_TERJESKILL_FISH_FISHERMANLUCK_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_fishmanluck";
				enabledIcon="set:TerjePerk_icon image:tp_fishmanluck";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.4,0.6,0.8,1.0};
			};
			class ReliableGear
			{
				id="reliabgear";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_RELIABLEGEAR";
				description="#STR_TERJESKILL_FISH_RELIABLEGEAR_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_reliablegear";
				enabledIcon="set:TerjePerk_icon image:tp_reliablegear";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.1,-0.2,-0.4,-0.6,-0.8,-1.0};
			};
			class WormHunter
			{
				id="wormhunt";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_WORMHUNTER";
				description="#STR_TERJESKILL_FISH_WORMHUNTER_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_wormhunter";
				enabledIcon="set:TerjePerk_icon image:tp_wormhunter";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.25,0.5,0.75,1.0,2.0,3.0};
			};
			class CraftsMan
			{
				id="craftsman";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_CRAFTSMAN";
				description="#STR_TERJESKILL_FISH_CRAFTSMAN_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_craftsman";
				enabledIcon="set:TerjePerk_icon image:tp_craftsman";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.35,0.45,0.55,0.65,0.75,1.0};
			};
			class RemoveRottenFish
			{
				id="remrotf";
				enabled=1;
				displayName="#STR_TERJESKILL_FISH_REMROT";
				description="#STR_TERJESKILL_FISH_REMROT_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_cleanwizard";
				enabledIcon="set:TerjePerk_icon image:tp_cleanwizard";
				requiredSkillLevels[]={1};
				requiredPerkPoints[]={1};
				values[]={0.0};
			};
		};
	};};