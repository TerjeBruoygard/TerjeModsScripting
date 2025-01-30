// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeSkills_Books
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"TerjeCore", "TerjeSkills"};
	};
};

class CfgVehicles
{
	class TerjeBookBase;
	class TerjeBookAthletic1: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_ATHLETIC1";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_athletic1_co.paa" };
		
		terjeSkillId="athlc";
		terjeSkillMinLevel=0;
		terjeSkillMaxLevel=10;
		terjeSkillExpGain=300;
	};
	class TerjeBookAthletic2: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_ATHLETIC2";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_athletic2_co.paa" };
		
		terjeSkillId="athlc";
		terjeSkillMinLevel=10;
		terjeSkillMaxLevel=20;
		terjeSkillExpGain=600;
	};
	class TerjeBookAthletic3: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_ATHLETIC3";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_athletic3_co.paa" };
		
		terjeSkillId="athlc";
		terjeSkillMinLevel=20;
		terjeSkillMaxLevel=30;
		terjeSkillExpGain=1200;
	};
	class TerjeBookAthletic4: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_ATHLETIC4";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_athletic4_co.paa" };
		
		terjeSkillId="athlc";
		terjeSkillMinLevel=30;
		terjeSkillMaxLevel=40;
		terjeSkillExpGain=3000;
	};
	class TerjeBookAthletic5: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_ATHLETIC5";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_athletic5_co.paa" };
		
		terjeSkillId="athlc";
		terjeSkillMinLevel=40;
		terjeSkillMaxLevel=50;
		terjeSkillExpGain=6000;
	};
	class TerjeBookFishing1: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_FISHING1";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_fishing1_co.paa" };
		
		terjeSkillId="fish";
		terjeSkillMinLevel=0;
		terjeSkillMaxLevel=10;
		terjeSkillExpGain=300;
	};
	class TerjeBookFishing2: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_FISHING2";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_fishing2_co.paa" };
		
		terjeSkillId="fish";
		terjeSkillMinLevel=10;
		terjeSkillMaxLevel=20;
		terjeSkillExpGain=600;
	};
	class TerjeBookFishing3: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_FISHING3";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_fishing3_co.paa" };
		
		terjeSkillId="fish";
		terjeSkillMinLevel=20;
		terjeSkillMaxLevel=30;
		terjeSkillExpGain=1200;
	};
	class TerjeBookFishing4: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_FISHING4";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_fishing4_co.paa" };
		
		terjeSkillId="fish";
		terjeSkillMinLevel=30;
		terjeSkillMaxLevel=40;
		terjeSkillExpGain=3000;
	};
	class TerjeBookFishing5: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_FISHING5";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_fishing5_co.paa" };
		
		terjeSkillId="fish";
		terjeSkillMinLevel=40;
		terjeSkillMaxLevel=50;
		terjeSkillExpGain=6000;
	};
	class TerjeBookHunting1: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_HUNTING1";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_hunting1_co.paa" };
		
		terjeSkillId="hunt";
		terjeSkillMinLevel=0;
		terjeSkillMaxLevel=10;
		terjeSkillExpGain=300;
	};
	class TerjeBookHunting2: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_HUNTING2";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_hunting2_co.paa" };
		
		terjeSkillId="hunt";
		terjeSkillMinLevel=10;
		terjeSkillMaxLevel=20;
		terjeSkillExpGain=600;
	};
	class TerjeBookHunting3: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_HUNTING3";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_hunting3_co.paa" };
		
		terjeSkillId="hunt";
		terjeSkillMinLevel=20;
		terjeSkillMaxLevel=30;
		terjeSkillExpGain=1200;
	};
	class TerjeBookHunting4: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_HUNTING4";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_hunting4_co.paa" };
		
		terjeSkillId="hunt";
		terjeSkillMinLevel=30;
		terjeSkillMaxLevel=40;
		terjeSkillExpGain=3000;
	};
	class TerjeBookHunting5: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_HUNTING5";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_hunting5_co.paa" };
		
		terjeSkillId="hunt";
		terjeSkillMinLevel=40;
		terjeSkillMaxLevel=50;
		terjeSkillExpGain=6000;
	};
	class TerjeBookMetabolism1: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_METABOLISM1";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_metabolism1_co.paa" };
		
		terjeSkillId="mtblsm";
		terjeSkillMinLevel=0;
		terjeSkillMaxLevel=10;
		terjeSkillExpGain=300;
	};
	class TerjeBookMetabolism2: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_METABOLISM2";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_metabolism2_co.paa" };
		
		terjeSkillId="mtblsm";
		terjeSkillMinLevel=10;
		terjeSkillMaxLevel=20;
		terjeSkillExpGain=600;
	};
	class TerjeBookMetabolism3: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_METABOLISM3";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_metabolism3_co.paa" };
		
		terjeSkillId="mtblsm";
		terjeSkillMinLevel=20;
		terjeSkillMaxLevel=30;
		terjeSkillExpGain=1200;
	};
	class TerjeBookMetabolism4: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_METABOLISM4";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_metabolism4_co.paa" };
		
		terjeSkillId="mtblsm";
		terjeSkillMinLevel=30;
		terjeSkillMaxLevel=40;
		terjeSkillExpGain=3000;
	};
	class TerjeBookMetabolism5: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_METABOLISM5";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_metabolism5_co.paa" };
		
		terjeSkillId="mtblsm";
		terjeSkillMinLevel=40;
		terjeSkillMaxLevel=50;
		terjeSkillExpGain=6000;
	};
	class TerjeBookStealth1: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STEALTH1";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_stealth1_co.paa" };
		
		terjeSkillId="stlth";
		terjeSkillMinLevel=0;
		terjeSkillMaxLevel=10;
		terjeSkillExpGain=300;
	};
	class TerjeBookStealth2: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STEALTH2";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_stealth2_co.paa" };
		
		terjeSkillId="stlth";
		terjeSkillMinLevel=10;
		terjeSkillMaxLevel=20;
		terjeSkillExpGain=600;
	};
	class TerjeBookStealth3: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STEALTH3";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_stealth3_co.paa" };
		
		terjeSkillId="stlth";
		terjeSkillMinLevel=20;
		terjeSkillMaxLevel=30;
		terjeSkillExpGain=1200;
	};
	class TerjeBookStealth4: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STEALTH4";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_stealth4_co.paa" };
		
		terjeSkillId="stlth";
		terjeSkillMinLevel=30;
		terjeSkillMaxLevel=40;
		terjeSkillExpGain=3000;
	};
	class TerjeBookStealth5: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STEALTH5";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_stealth5_co.paa" };
		
		terjeSkillId="stlth";
		terjeSkillMinLevel=40;
		terjeSkillMaxLevel=50;
		terjeSkillExpGain=6000;
	};
	class TerjeBookStrength1: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STRENGTH1";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_strength1_co.paa" };
		
		terjeSkillId="strng";
		terjeSkillMinLevel=0;
		terjeSkillMaxLevel=10;
		terjeSkillExpGain=300;
	};
	class TerjeBookStrength2: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STRENGTH2";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_strength2_co.paa" };
		
		terjeSkillId="strng";
		terjeSkillMinLevel=10;
		terjeSkillMaxLevel=20;
		terjeSkillExpGain=600;
	};
	class TerjeBookStrength3: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STRENGTH3";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_strength3_co.paa" };
		
		terjeSkillId="strng";
		terjeSkillMinLevel=20;
		terjeSkillMaxLevel=30;
		terjeSkillExpGain=1200;
	};
	class TerjeBookStrength4: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STRENGTH4";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_strength4_co.paa" };
		
		terjeSkillId="strng";
		terjeSkillMinLevel=30;
		terjeSkillMaxLevel=40;
		terjeSkillExpGain=3000;
	};
	class TerjeBookStrength5: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_STRENGTH5";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_strength5_co.paa" };
		
		terjeSkillId="strng";
		terjeSkillMinLevel=40;
		terjeSkillMaxLevel=50;
		terjeSkillExpGain=6000;
	};
	class TerjeBookSurvival1: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_SURVIVAL1";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_survival1_co.paa" };
		
		terjeSkillId="surv";
		terjeSkillMinLevel=0;
		terjeSkillMaxLevel=10;
		terjeSkillExpGain=300;
	};
	class TerjeBookSurvival2: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_SURVIVAL2";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_survival2_co.paa" };
		
		terjeSkillId="surv";
		terjeSkillMinLevel=10;
		terjeSkillMaxLevel=20;
		terjeSkillExpGain=600;
	};
	class TerjeBookSurvival3: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_SURVIVAL3";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_survival3_co.paa" };
		
		terjeSkillId="surv";
		terjeSkillMinLevel=20;
		terjeSkillMaxLevel=30;
		terjeSkillExpGain=1200;
	};
	class TerjeBookSurvival4: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_SURVIVAL4";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_survival4_co.paa" };
		
		terjeSkillId="surv";
		terjeSkillMinLevel=30;
		terjeSkillMaxLevel=40;
		terjeSkillExpGain=3000;
	};
	class TerjeBookSurvival5: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_SURVIVAL5";
		hiddenSelectionsTextures[]={ "TerjeSkills\Books\data\book_survival5_co.paa" };
		
		terjeSkillId="surv";
		terjeSkillMinLevel=40;
		terjeSkillMaxLevel=50;
		terjeSkillExpGain=6000;
	};
};