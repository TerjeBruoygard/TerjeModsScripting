// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine_Protection
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeMedicine"
		};
	};
};

// This class determines the extent to which scriptable areas affect different parts of the player's body and determines their defense and exposure.
class CfgTerjeScriptableProtection
{
	class psionic
	{
		/*class SLOT_NAME
		{
			weight=1; // Determines the effect of the protection of a given body part on the body as a whole.
			protectionBodyValues={}; // Sets radiation protection for a specific body part without the use of a protection suit up to a certain radiation threshold.
			protectionBodyThresholds={}; // Protection thresholds are used to apply different levels of protection for different levels of impact on the player.
		};*/
		
		class Feet
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Legs
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Body
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Gloves
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Mask
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Headgear
		{
			weight=1.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
	};
};