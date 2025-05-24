// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeStartScreen
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeCore"
		};
	};
};

class CfgMods
{
	class TerjeStartScreen
	{
		dir = "TerjeStartScreen";
		picture = "TerjeStartScreen/Textures/mod_icon.edds";
		action = "https://steamcommunity.com/id/terjebruoygard/myworkshopfiles/";
		hideName = 0;
		hidePicture = 0;
		name = "Terje Start Screen";
		credits = "Terje Bruoygard";
		version = "1.0.0";
		author = "TerjeBruoygard";
		dependencies[] = {"Core","Game","World","Mission"};
		defines[] = { "TERJE_START_SCREEN_MOD" };
		extra = 0;
		type = "mod"; 
		
		class defs
		{
			class imageSets
			{
				files[] = {"TerjeStartScreen/Textures/startscreen_icons.imageset"};
			};
			class gameScriptModule {
				value = "";
				files[] = {"TerjeStartScreen/Scripts/3_Game"};
			};
			
			class worldScriptModule {
				value = "";
				files[] = {"TerjeStartScreen/Scripts/4_World", "TerjeStartScreen/Scripts/4_Compatibility"};
			};

			class missionScriptModule {
				value = "";
				files[] = {"TerjeStartScreen/Scripts/5_Mission", "TerjeStartScreen/Scripts/5_Compatibility"};
			};
		};
	};
};