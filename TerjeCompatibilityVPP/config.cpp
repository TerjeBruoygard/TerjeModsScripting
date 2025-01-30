// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeCompatibilityVPP
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={ "TerjeCore", "DZM_VPPAdminTools" };
	};
};

class CfgMods
{
	class TerjeCompatibilityVPP
	{
		dir = "TerjeCompatibilityVPP";
		picture = "TerjeCore/Textures/mod_icon.edds";
		action = "https://steamcommunity.com/id/terjebruoygard/myworkshopfiles/";
		hideName = 1;
		hidePicture = 1;
		name = "Terje Compatibility VPP";
		credits = "Terje Bruoygard";
		version = "1.0.0";
		author = "TerjeBruoygard";
		extra = 0;
		type = "mod";
		
		class defs
		{
			class worldScriptModule {
				value = "";
				files[] = {"TerjeCompatibilityVPP/Scripts/4_World"};
			};

			class missionScriptModule {
				value = "";
				files[] = {"TerjeCompatibilityVPP/Scripts/5_Mission"};
			};
		};
	};
};