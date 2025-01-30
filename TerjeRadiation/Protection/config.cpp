// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeRadiation_Protection
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeRadiation", "DZ_Data", "DZ_Gear_Crafting", "DZ_Gear_Consumables",
			"DZ_Characters_Tops", "DZ_Characters_Shoes", "DZ_Characters_Pants",
			"DZ_Characters_Masks", "DZ_Characters_Headgear", "DZ_Characters_Gloves"
		};
	};
};

// This class determines the extent to which scriptable areas affect different parts of the player's body and determines their defense and exposure.
class CfgTerjeScriptableProtection
{
	class radiation
	{
		/*class SLOT_NAME
		{
			weight=1; // Determines the effect of the protection of a given body part on the body as a whole.
			protectionBodyValues={}; // Sets radiation protection for a specific body part without the use of a protection suit up to a certain radiation threshold.
			protectionBodyThresholds={}; // Protection thresholds are used to apply different levels of protection for different levels of impact on the player.
		};*/
		
		class Feet
		{
			weight=0.5;
			protectionBodyValues[]={1.0,0.75,0.5,0.25,0.0};
			protectionBodyThresholds[]={0.8,0.85,0.9,0.95,1.0};
		};
		class Legs
		{
			weight=1.0;
			protectionBodyValues[]={1.0,0.75,0.5,0.25,0.0};
			protectionBodyThresholds[]={0.6,0.7,0.8,0.9,1.0};
		};
		class Body
		{
			weight=1.0;
			protectionBodyValues[]={1.0,0.75,0.5,0.25,0.0};
			protectionBodyThresholds[]={0.6,0.7,0.8,0.9,1.0};
		};
		class Gloves
		{
			weight=0.5;
			protectionBodyValues[]={1.0,0.75,0.5,0.25,0.0};
			protectionBodyThresholds[]={0.8,0.85,0.9,0.95,1.0};
		};
		class Headgear
		{
			weight=0.5;
			protectionBodyValues[]={1.0,0.75,0.5,0.25,0.0};
			protectionBodyThresholds[]={0.6,0.7,0.8,0.9,1.0};
		};
		class Mask
		{
			weight=2.5;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
	};
};

class CfgVehicles
{
	class Clothing;
	class Inventory_Base;
	class GasMask_Filter_Improvised: Inventory_Base
	{
		class Protection
		{
			radiation=0.7;
			
			/*
			Used for more fine-tuning similar to the parameters from CfgTerjeScriptableProtection but for a specific cloting,
			allowing you to specify protection levels based on the strength of the environment radiation.
			
			radiationValues[]={1.0,0.75,0.5,0.25,0.0};
			radiationThresholds[]={0.6,0.7,0.8,0.9,1.0};
			*/
		};
	};
	class GasMask_Filter: Inventory_Base
	{
		class Protection
		{
			radiation=0.9;
		};
	};
	class NBCJacketBase: Clothing
	{
		class Protection
		{
			radiation=0.95;
		};
	};
	class NBCBootsBase: Clothing
	{
		class Protection
		{
			radiation=0.95;
		};
	};
	class NBCPantsBase: Clothing
	{
		class Protection
		{
			radiation=0.95;
		};
	};
	class GasMask: Clothing
	{
		class Protection
		{
			radiation=0.95;
		};
	};
	class NBCHoodBase: Clothing
	{
		class Protection
		{
			radiation=0.95;
		};
	};
	class NBCGloves_ColorBase: Clothing
	{
		class Protection
		{
			radiation=0.95;
		};
	};
};