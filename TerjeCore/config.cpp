// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeCore
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={ "DZ_Data", "DZ_Gear_Books", "DZ_Scripts" };
	};
};

class CfgMods
{
	class TerjeCore
	{
		dir = "TerjeCore";
		picture = "TerjeCore/Textures/mod_icon.edds";
		action = "https://steamcommunity.com/id/terjebruoygard/myworkshopfiles/";
		hideName = 1;
		hidePicture = 1;
		name = "Terje Core";
		credits = "Terje Bruoygard";
		version = "1.0.0";
		author = "TerjeBruoygard";
		extra = 0;
		type = "mod";
		
		class defs
		{
			class gameScriptModule {
				value = "";
				files[] = {"TerjeCore/Scripts/3_Game"};
			};
			
			class worldScriptModule {
				value = "";
				files[] = {"TerjeCore/Scripts/4_World"};
			};

			class missionScriptModule {
				value = "";
				files[] = {"TerjeCore/Scripts/5_Mission"};
			};
		};
	};
};

class CfgVehicles
{
	class ItemBook;
	class TerjeBookBase: ItemBook { };
	
	class HouseNoDestruct;
	class TerjeSoundEmitter : HouseNoDestruct { };
	class TerjeScriptableArea : HouseNoDestruct {
		terjeInnerRadius = 35.0; // Players inside this radius will receive full damage
		terjeOuterRadius = 100.0; // Players inside this radius will receive proportional damage depends on distance between two radiuses
		terjeHeightMin = -100.0; // Lower range of the area cylinder
		terjeHeightMax = 100.0; // Upper range of the area cylinder
		terjePower = 1.0; // Area power modifier
	};
	
	class Edible_Base;
	class CarpFilletMeat: Edible_Base
	{
		fishFillet=1;
	};
	class MackerelFilletMeat: Edible_Base
	{
		fishFillet=1;
	};
	class WalleyePollockFilletMeat: Edible_Base
	{
		fishFillet=1;
	};
	class SteelheadTroutFilletMeat: Edible_Base
	{
		fishFillet=1;
	};
	class Carp: Edible_Base
	{
		wholeFish=1;
	};
	class Mackerel: Edible_Base
	{
		wholeFish=1;
	};
	class WalleyePollock: Edible_Base
	{
		wholeFish=1;
	};
	class SteelheadTrout: Edible_Base
	{
		wholeFish=1;
	};
	class Sardines: Edible_Base
	{
		wholeFish=1;
	};
	class Bitterlings: Edible_Base
	{
		wholeFish=1;
	};
};

class cfgLiquidDefinitions
{
	class TerjeCustom
	{
		type=65536;
		displayName="";
		flammability=0;
		liquidFreezeThreshold=0;
		liquidThawThreshold=0;
		liquidBoilingThreshold=150;
		class Nutrition
		{
			fullnessIndex=0;
			energy=0;
			water=0;
			nutritionalIndex=75;
			toxicity=0;
			digestibility=2;
		};
	};
};

class CfgTerjeCustomLiquids
{
	// Special system for custom liquid types.
	// Allows you to define new types of liquids without fear of conflicts with other mods (since the vanilla liquid system is hardcoded to the bitmask).
	// Check TerjeMedicine mod for examples.
};