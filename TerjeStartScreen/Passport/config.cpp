// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeStartScreen_Passport
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeStartScreen"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;

	class TerjePassport : Inventory_Base
	{
		scope=2;
		displayName="#STR_TERJESTARTSCREEN_PASSPORT_NAME";
		descriptionShort="#STR_TERJESTARTSCREEN_PASSPORT_DESC";
		model="\TerjeStartScreen\Passport\passport.p3d";
		isMeleeWeapon = 1;
		weight = 2;
		absorbency = 1;
		itemSize[] = {1,1};
		rotationFlags = 17;
		inventorySlot[] = {"Paper"};
		varWetMax = 1.0;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeStartScreen\Passport\Data\passport_co.paa" };
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 15;
					healthLevels[] = {{1.0,{"TerjeStartScreen\Passport\Data\passport_mat.rvmat"}},{0.7,{"TerjeStartScreen\Passport\Data\passport_mat.rvmat"}},{0.5,{"TerjeStartScreen\Passport\Data\passport_damage.rvmat"}},{0.3,{"TerjeStartScreen\Passport\Data\passport_damage.rvmat"}},{0.0,{"TerjeStartScreen\Passport\Data\passport_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet = "pickUpPaper_SoundSet";
					id = 797;
				};
			};
		};
	};
};