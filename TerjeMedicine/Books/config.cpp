// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine_Books
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"TerjeCore", "TerjeMedicine"};
	};
};

class CfgVehicles
{
	class TerjeBookBase;
	class TerjeBookImmunity1: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_IMMUNITY1";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_immunity1_co.paa" };
		
		terjeSkillId="immunity";
		terjeSkillMinLevel=0;
		terjeSkillMaxLevel=10;
		terjeSkillExpGain=300;
	};
	class TerjeBookImmunity2: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_IMMUNITY2";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_immunity2_co.paa" };
		
		terjeSkillId="immunity";
		terjeSkillMinLevel=10;
		terjeSkillMaxLevel=20;
		terjeSkillExpGain=600;
	};
	class TerjeBookImmunity3: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_IMMUNITY3";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_immunity3_co.paa" };
		
		terjeSkillId="immunity";
		terjeSkillMinLevel=20;
		terjeSkillMaxLevel=30;
		terjeSkillExpGain=1200;
	};
	class TerjeBookImmunity4: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_IMMUNITY4";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_immunity4_co.paa" };
		
		terjeSkillId="immunity";
		terjeSkillMinLevel=30;
		terjeSkillMaxLevel=40;
		terjeSkillExpGain=3000;
	};
	class TerjeBookImmunity5: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_IMMUNITY5";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_immunity5_co.paa" };
		
		terjeSkillId="immunity";
		terjeSkillMinLevel=40;
		terjeSkillMaxLevel=50;
		terjeSkillExpGain=6000;
	};
	class TerjeBookMedicine1: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_MEDICINE1";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_medicine1_co.paa" };
		
		terjeSkillId="med";
		terjeSkillMinLevel=0;
		terjeSkillMaxLevel=10;
		terjeSkillExpGain=300;
	};
	class TerjeBookMedicine2: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_MEDICINE2";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_medicine2_co.paa" };
		
		terjeSkillId="med";
		terjeSkillMinLevel=10;
		terjeSkillMaxLevel=20;
		terjeSkillExpGain=600;
	};
	class TerjeBookMedicine3: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_MEDICINE3";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_medicine3_co.paa" };
		
		terjeSkillId="med";
		terjeSkillMinLevel=20;
		terjeSkillMaxLevel=30;
		terjeSkillExpGain=1200;
	};
	class TerjeBookMedicine4: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_MEDICINE4";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_medicine4_co.paa" };
		
		terjeSkillId="med";
		terjeSkillMinLevel=30;
		terjeSkillMaxLevel=40;
		terjeSkillExpGain=3000;
	};
	class TerjeBookMedicine5: TerjeBookBase
	{
		scope=2;
		rotationFlags=1;
		displayName="#STR_TERJESKILL_BOOK_MEDICINE5";
		hiddenSelectionsTextures[]={ "TerjeMedicine\Books\data\book_medicine5_co.paa" };
		
		terjeSkillId="med";
		terjeSkillMinLevel=40;
		terjeSkillMaxLevel=50;
		terjeSkillExpGain=6000;
	};
};