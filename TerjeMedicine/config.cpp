// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeCore", "DZ_Gear_Medical"
		};
	};
};

class CfgMods
{
	class TerjeMedicine
	{
		dir = "TerjeMedicine";
		picture = "TerjeMedicine/Textures/mod_icon.edds";
		action = "https://steamcommunity.com/id/terjebruoygard/myworkshopfiles/";
		hideName = 0;
		hidePicture = 0;
		name = "Terje Medicine";
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
				files[] = {"TerjeMedicine/Textures/Icon/icon_medicine.imageset"};
			};
			class gameScriptModule {
				value = "";
				files[] = {"TerjeMedicine/Scripts/3_Game"};
			};
			
			class worldScriptModule {
				value = "";
				files[] = {"TerjeMedicine/Scripts/4_World"};
			};

			class missionScriptModule {
				value = "";
				files[] = {"TerjeMedicine/Scripts/5_Mission"};
			};
		};
	};
};

class CfgTerjeSkills
{
	class Immunity
	{
		id="immunity";
		enabled=1;
		displayName="#STR_TERJESKILL_IMMUNITY_NAME";
		description="#STR_TERJESKILL_IMMUNITY_DESC";
		icon="set:TerjeSkills_icon image:ts_immun";
		perkPointsPerLevel=2;
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
			class ResistDiseasesModifier
			{
				id="resdiseasesmod";
				enabled=1;
				text="#STR_TERJESKILL_IMMUNITY_MOD0";
				value=0.01;
			};
		};
		class Perks
		{
			class ColdResist
			{
				id="coldres";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_COLDRESIST";
				description="#STR_TERJEPERK_IMMTY_COLDRESIST_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_coldresist";
				enabledIcon="set:TerjePerk_icon image:tp_coldresist";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.05,0.1,0.15,0.25,0.5};
			};
			class PoisonResist
			{
				id="poisonres";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_POISONRESIST";
				description="#STR_TERJEPERK_IMMTY_POISONRESIST_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_poisonresist";
				enabledIcon="set:TerjePerk_icon image:tp_poisonresist";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.1,0.25,0.5,1.0,1.5};
			};
			class BiohazardResist
			{
				id="biohzres";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_BIOHZRDRESIST";
				description="#STR_TERJEPERK_IMMTY_BIOHZRDRESIST_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_biohazard";
				enabledIcon="set:TerjePerk_icon image:tp_biohazard";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.1,0.25,0.5,1.0,1.5};
			};
			class HematomaRecovery
			{
				id="hematomrec";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_HEMATOMARECOVERY";
				description="#STR_TERJEPERK_IMMTY_HEMATOMARECOVERY_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_hematomarecovery";
				enabledIcon="set:TerjePerk_icon image:tp_hematomarecovery";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.2,0.4,0.8,1.0,1.5};
			};
			class WoundHealing
			{
				id="whealing";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_WOUNDHEALING";
				description="#STR_TERJEPERK_IMMTY_WOUNDHEALING_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_woundhealing";
				enabledIcon="set:TerjePerk_icon image:tp_woundhealing";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.2,0.4,0.8,1.0,1.5};
			};
			class IntoxicResist
			{
				id="intoxicres";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_INTOXICRESISTANCE";
				description="#STR_TERJEPERK_IMMTY_INTOXICRESISTANCE_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_intoxicresist";
				enabledIcon="set:TerjePerk_icon image:tp_intoxicresist";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.10,0.25,0.5,1.0,2.0};
			};
			class FastSleep
			{
				id="fsleep";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_FASTSLEEP";
				description="#STR_TERJEPERK_IMMTY_FASTSLEEP_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_fastsleep";
				enabledIcon="set:TerjePerk_icon image:tp_fastsleep";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.10,0.25,0.5,1.0,2.0};
			};
			class IronMind
			{
				id="irnmind";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_IRONMIND";
				description="#STR_TERJEPERK_IMMTY_IRONMIND_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_ironmind";
				enabledIcon="set:TerjePerk_icon image:tp_ironmind";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.10,0.25,0.5,0.75,1.0};
			};
			class RecoveryShock
			{
				id="recshock";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_RECOVERYSHOCK";
				description="#STR_TERJEPERK_IMMTY_RECOVERYSHOCK_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_recoveryshock";
				enabledIcon="set:TerjePerk_icon image:tp_recoveryshock";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.10,0.25,0.5,1.0,2.0};
			};
			class ImpactResist
			{
				id="impactres";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_IMPACTRESIST";
				description="#STR_TERJEPERK_IMMTY_IMPACTRESIST_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_impactresist";
				enabledIcon="set:TerjePerk_icon image:tp_impactresist";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.10,0.25,0.5,0.75,1.0};
			};
			class DurableLeather
			{
				id="durleath";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_DURABLELEATHER";
				description="#STR_TERJEPERK_IMMTY_DURABLELEATHER_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_durableleather";
				enabledIcon="set:TerjePerk_icon image:tp_durableleather";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
			class ResistZmbVirus
			{
				id="zmbvirres";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_RESISTZMBVIRUS";
				description="#STR_TERJEPERK_IMMTY_RESISTZMBVIRUS_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_reszmbvirus";
				enabledIcon="set:TerjePerk_icon image:tp_reszmbvirus";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
			class ResistSepsis
			{
				id="sepsisres";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_RESISTSEPSIS";
				description="#STR_TERJEPERK_IMMTY_RESISTSEPSIS_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_resistsepsis";
				enabledIcon="set:TerjePerk_icon image:tp_resistsepsis";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
			class FeetWarm
			{
				id="ftwarm";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_FEETWARM";
				description="#STR_TERJEPERK_IMMTY_FEETWARM_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_feetwarm";
				enabledIcon="set:TerjePerk_icon image:tp_feetwarm";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.25,0.5,1.0,2.0,3.0};
			};
			class SafeDinner
			{
				id="svdinner";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_SAFEDINNER";
				description="#STR_TERJEPERK_IMMTY_SAFEDINNER_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_safelaunch";
				enabledIcon="set:TerjePerk_icon image:tp_safelaunch";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={-0.1,-0.2,-0.4,-0.6,-0.8};
			};
			class QuickHealing
			{
				id="qhealing";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_QUICKHEALING";
				description="#STR_TERJEPERK_IMMTY_QUICKHEALING_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_quickhealing";
				enabledIcon="set:TerjePerk_icon image:tp_quickhealing";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
			class BloodRegen
			{
				id="bloodreg";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_BLOODREGEN";
				description="#STR_TERJEPERK_IMMTY_BLOODREGEN_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_bloodregen";
				enabledIcon="set:TerjePerk_icon image:tp_bloodregen";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
			class ThickBlood
			{
				id="thkblood";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_THICKBLOOD";
				description="#STR_TERJEPERK_IMMTY_THICKBLOOD_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_thickblood";
				enabledIcon="set:TerjePerk_icon image:tp_thickblood";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={-0.01,-0.20,-0.30,-0.40,-0.50};
			};
			class RabiesResist
			{
				id="rabres";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_RABIESRESIST";
				description="#STR_TERJEPERK_IMMTY_RABIESRESIST_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_rabiesres";
				enabledIcon="set:TerjePerk_icon image:tp_rabiesres";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.05,0.1,0.15,0.25,0.5};
			};
			class LowPainTresh
			{
				id="lowpain";
				enabled=1;
				displayName="#STR_TERJEPERK_IMMTY_LOWPAINTRESH";
				description="#STR_TERJEPERK_IMMTY_LOWPAINTRESH_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_lowpaintr";
				enabledIcon="set:TerjePerk_icon image:tp_lowpaintr";
				requiredSkillLevels[]={35};
				requiredPerkPoints[]={3};
				values[]={0.0};
			};
		};
	};
	class Medicine
	{
		id="med";
		enabled=1;
		displayName="#STR_TERJESKILL_MED_NAME";
		description="#STR_TERJESKILL_MED_DESC";
		icon="set:TerjeSkills_icon image:ts_med";
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
			class SurgeryStabWound
			{
				id="surgsw";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_SURGERYSTABWOUND";
				description="#STR_TERJEPERK_MED_SURGERYSTABWOUND_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_surgerystab";
				enabledIcon="set:TerjePerk_icon image:tp_surgerystab";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.3,0.5,0.75,1.0};
			};
			class SurgeryBulletWound
			{
				id="surgbw";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_SURGERYBULLETWOUND";
				description="#STR_TERJEPERK_MED_SURGERYBULLETWOUND_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_surgerybullet";
				enabledIcon="set:TerjePerk_icon image:tp_surgerybullet";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.3,0.5,0.75,1.0};
			};
			class SurgeryInternalWound
			{
				id="surgint";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_SURGERYINTERNAL";
				description="#STR_TERJEPERK_MED_SURGERYINTERNAL_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_surgeryinternal";
				enabledIcon="set:TerjePerk_icon image:tp_surgeryinternal";
				requiredSkillLevels[]={5,10,15,20,25,30};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.1,0.2,0.3,0.5,0.75,1.0};
			};
			class CleanlinessSterility
			{
				id="cleanstr";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_CLEANLINESS";
				description="#STR_TERJEPERK_MED_CLEANLINESS_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_cleanliness";
				enabledIcon="set:TerjePerk_icon image:tp_cleanliness";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,1};
				values[]={-0.05,-0.10,-0.15,-0.25,-0.50,-0.75};
			};
			class Pharmacologist
			{
				id="pharmac";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_PHARMACOLOGIST";
				description="#STR_TERJEPERK_MED_PHARMACOLOGIST_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_pharmacologist";
				enabledIcon="set:TerjePerk_icon image:tp_pharmacologist";
				requiredSkillLevels[]={5,10,15,20,25,30};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={0.05,0.10,0.25,0.5,0.75,1.0};
			};
			class MasterDressing
			{
				id="mastdress";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_MASTERDRESSING";
				description="#STR_TERJEPERK_MED_MASTERDRESSING_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_masterdressing";
				enabledIcon="set:TerjePerk_icon image:tp_masterdressing";
				requiredSkillLevels[]={1,5,10,15,20,25};
				requiredPerkPoints[]={1,1,1,1,1,1};
				values[]={-0.1,-0.2,-0.3,-0.4,-0.5,-0.75};
			};
			class Surgeon
			{
				id="surgeon";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_SURGEON";
				description="#STR_TERJEPERK_MED_SURGEON_DES";
				stagesCount=6;
				disabledIcon="set:TerjePerkBlack_icon image:tp_surgeon";
				enabledIcon="set:TerjePerk_icon image:tp_surgeon";
				requiredSkillLevels[]={5,10,15,20,25,30};
				requiredPerkPoints[]={1,1,1,1,1,2};
				values[]={-0.05,-0.1,-0.2,-0.3,-0.5,-0.75};
			};
			class BringingLife
			{
				id="brnlife";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_BRINGINGLIFE";
				description="#STR_TERJEPERK_MED_BRINGINGLIFE_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_crushingsquall";
				enabledIcon="set:TerjePerk_icon image:tp_crushingsquall";
				requiredSkillLevels[]={1};
				requiredPerkPoints[]={1};
				values[]={0.0};
			};
			class PillRecognition
			{
				id="pillrecog";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_PILLRECOGNITION";
				description="#STR_TERJEPERK_MED_PILLRECOGNITION_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_pilrecognition";
				enabledIcon="set:TerjePerk_icon image:tp_pilrecognition";
				requiredSkillLevels[]={1};
				requiredPerkPoints[]={1};
				values[]={0.0};
			};
			class AmpouleRecognition
			{
				id="amplrecog";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_AMPOULERECOGNITION";
				description="#STR_TERJEPERK_MED_AMPOULERECOGNITION_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_ampoulerecognition";
				enabledIcon="set:TerjePerk_icon image:tp_ampoulerecognition";
				requiredSkillLevels[]={10};
				requiredPerkPoints[]={1};
				values[]={0.0};
			};
			class InjectorRecognition
			{
				id="injrecog";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_INJECTORRECOGNITION";
				description="#STR_TERJEPERK_MED_INJECTORRECOGNITION_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_injectorrecognition";
				enabledIcon="set:TerjePerk_icon image:tp_injectorrecognition";
				requiredSkillLevels[]={20};
				requiredPerkPoints[]={1};
				values[]={0.0};
			};
			class Stethoscope
			{
				id="stethscp";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_STETHOSCOPE";
				description="#STR_TERJEPERK_MED_STETHOSCOPE_DES";
				stagesCount=3;
				disabledIcon="set:TerjePerkBlack_icon image:tp_stethoscope";
				enabledIcon="set:TerjePerk_icon image:tp_stethoscope";
				requiredSkillLevels[]={5,15,30};
				requiredPerkPoints[]={1,1,1};
				values[]={0.0,0.0,0.0};
				hints[]={"#STR_TERJEPERK_MED_STETHOSCOPE_HINT_1", "#STR_TERJEPERK_MED_STETHOSCOPE_HINT_2", "#STR_TERJEPERK_MED_STETHOSCOPE_HINT_3"};
			};
			class ExpertAntibiotics
			{
				id="expantib";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_EXPERTANTIBIOTICS";
				description="#STR_TERJEPERK_MED_EXPERTANTIBIOTICS_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_expertantibiotics";
				enabledIcon="set:TerjePerk_icon image:tp_expertantibiotics";
				requiredSkillLevels[]={40};
				requiredPerkPoints[]={2};
				values[]={0.0};
			};
			class Anesthesiolog
			{
				id="anestlog";
				enabled=1;
				displayName="#STR_TERJEPERK_MED_ANESTHESIOLOGIST";
				description="#STR_TERJEPERK_MED_ANESTHESIOLOGIST_DES";
				stagesCount=1;
				disabledIcon="set:TerjePerkBlack_icon image:tp_anesthesiolog";
				enabledIcon="set:TerjePerk_icon image:tp_anesthesiolog";
				requiredSkillLevels[]={40};
				requiredPerkPoints[]={3};
				values[]={0.0};
			};
		};
	};
};