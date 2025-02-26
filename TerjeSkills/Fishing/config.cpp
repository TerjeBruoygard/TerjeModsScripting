// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeSkills_Fishing
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeSkills", "DZ_Gear_Tools"
		};
	};
};

class CfgVehicles
{
	class FishingRod_Base_New;
	
	class ImprovisedFishingRod: FishingRod_Base_New
	{
		terjeFishingExpModifier=0.5;
	};
	
	class FishingRod: FishingRod_Base_New
	{
		terjeFishingExpModifier=1.0;
	};
};