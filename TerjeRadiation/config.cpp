// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeRadiation
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
	class TerjeRadiation
	{
		dir = "TerjeRadiation";
		picture = "TerjeRadiation/Textures/mod_icon.edds";
		action = "https://steamcommunity.com/id/terjebruoygard/myworkshopfiles/";
		hideName = 0;
		hidePicture = 0;
		name = "Terje Radiation";
		credits = "Terje Bruoygard";
		version = "1.0.0";
		author = "TerjeBruoygard";
		dependencies[] = {"Core","Game","World","Mission"};
		extra = 0;
		type = "mod"; 
		
		class defs
		{
			class imageSets
			{
				files[] = {"TerjeRadiation/Textures/icon_radiation.imageset"};
			};
			class gameScriptModule {
				value = "";
				files[] = {"TerjeRadiation/Scripts/3_Game"};
			};
			
			class worldScriptModule {
				value = "";
				files[] = {"TerjeRadiation/Scripts/4_World"};
			};

			class missionScriptModule {
				value = "";
				files[] = {"TerjeRadiation/Scripts/5_Mission"};
			};
		};
	};
};

class CfgTerjeSkills
{
	class Immunity
	{
		class Perks
		{
			class RadiationResist
			{
				id="radres";
				enabled=1;
				displayName="#STR_TERJERAD_IMMTY_RADRESISTANCE";
				description="#STR_TERJERAD_IMMTY_RADRESISTANCE_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_radiationresist";
				enabledIcon="set:TerjePerk_icon image:tp_radiationresist";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.05,0.1,0.2,0.3,0.5};
			};
			class RadiationRegen
			{
				id="radregen";
				enabled=1;
				displayName="#STR_TERJERAD_IMMTY_RADREGENERATION";
				description="#STR_TERJERAD_IMMTY_RADREGENERATION_DES";
				stagesCount=5;
				disabledIcon="set:TerjePerkBlack_icon image:tp_radiationregen";
				enabledIcon="set:TerjePerk_icon image:tp_radiationregen";
				requiredSkillLevels[]={1,5,10,15,25};
				requiredPerkPoints[]={1,1,1,1,1};
				values[]={0.1,0.25,0.5,0.75,1.0};
			};
		};
	};
};