// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine_Drinks
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeMedicine", "DZ_Gear_Drinks"
		};
	};
};

class CfgVehicles
{
	class SodaCan_ColorBase;
	class TerjeEnergyDrink : SodaCan_ColorBase
	{ 
		scope=0;
		class AnimEvents
		{
			class SoundWeapon
			{
				class SodaCan_in_B
				{
					soundSet="SodaCan_in_B_SoundSet";
					id=202;
				};
				class WellPond_loop
				{
					soundSet="WellPond_loop_SoundSet";
					id=209;
				};
				class WellBottle_loop
				{
					soundSet="WellBottle_loop_SoundSet";
					id=210;
				};
				class pickup
				{
					soundSet="SodaCan_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SodaCan_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class TerjeDrinkMadBull: TerjeEnergyDrink
	{
		scope=2;
		medSleepingIncrementValue = 8;
		medSleepingIncrementTimeSec = 1.0; // Time per 1ml
		displayName="#STR_TERJEDRINK_MADBULL_NAME";
		descriptionShort="#STR_TERJEDRINK_MADBULL_DESC";
		hiddenSelectionsTextures[]=
		{
			"TerjeMedicine\Drinks\madbull.paa"
		};
	};
	class TerjeDrinkGang: TerjeEnergyDrink
	{
		scope=2;
		medSleepingIncrementValue = 6;
		medSleepingIncrementTimeSec = 1.0; // Time per 1ml
		displayName="#STR_TERJEDRINK_GANG_NAME";
		descriptionShort="#STR_TERJEDRINK_GANG_DESC";
		hiddenSelectionsTextures[]=
		{
			"TerjeMedicine\Drinks\gang.paa"
		};
	};
	class TerjeDrinkYaguar: TerjeEnergyDrink
	{
		scope=2;
		medSleepingIncrementValue = 10;
		medSleepingIncrementTimeSec = 1.0; // Time per 1ml
		displayName="#STR_TERJEDRINK_YAGUAR_NAME";
		descriptionShort="#STR_TERJEDRINK_YAGUAR_DESC";
		hiddenSelectionsTextures[]=
		{
			"TerjeMedicine\Drinks\yaguar.paa"
		};
	};
	class TerjeDrinkPrayboy: TerjeEnergyDrink
	{
		scope=2;
		medSleepingIncrementValue = 4;
		medSleepingIncrementTimeSec = 1.0; // Time per 1ml
		displayName="#STR_TERJEDRINK_PRAYBOY_NAME";
		descriptionShort="#STR_TERJEDRINK_PRAYBOY_DESC";
		hiddenSelectionsTextures[]=
		{
			"TerjeMedicine\Drinks\prayboy.paa"
		};
	};
	class TerjeDrink6Energy: TerjeEnergyDrink
	{
		scope=2;
		medSleepingIncrementValue = 8;
		medSleepingIncrementTimeSec = 0.8; // Time per 1ml
		displayName="#STR_TERJEDRINK_6ENERGY_NAME";
		descriptionShort="#STR_TERJEDRINK_6ENERGY_DESC";
		hiddenSelectionsTextures[]=
		{
			"TerjeMedicine\Drinks\6energy.paa"
		};
	};
};