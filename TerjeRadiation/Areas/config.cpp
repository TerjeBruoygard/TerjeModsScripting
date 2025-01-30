// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeRadiation_Areas
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeRadiation"
		};
	};
};

class CfgVehicles
{
	class TerjeScriptableArea;
	class TerjeRadioactiveScriptableArea: TerjeScriptableArea
	{
		scope=2;
		terjeInnerRadius = 25.0; // Players inside this radius will receive full damage
		terjeOuterRadius = 150.0; // Players inside this radius will receive proportional damage depends on distance between two radiuses
		terjeHeightMin = -100.0; // Lower range of the area cylinder
		terjeHeightMax = 100.0; // Upper range of the area cylinder
		terjePower = 1.0; // Area power modifier
	};
};