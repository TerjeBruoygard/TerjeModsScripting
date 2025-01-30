// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeRadiation_Container
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeRadiation", "DZ_Gear_Camping"
		};
	};
};

class CfgVehicles
{
	class Container_Base;
	class WoodenCrate;

	class TerjeCaseRadMilitary: WoodenCrate
	{
		scope = 2;
		displayName="#STR_TERJERAD_CASEMILITARY_NAME";
		descriptionShort="#STR_TERJERAD_CASEMILITARY_DESC";
		model = "\TerjeRadiation\Container\military\military_case.p3d";
		hologramMaterial = "military_case";
		hologramMaterialPath = "TerjeRadiation\Container\military";
		slopeTolerance = 0.4;
		yawPitchRollLimit[] = {45,45,45};
		weight = 10000;
		itemSize[] = {10,6};
		itemBehaviour = 0;
		carveNavmesh = 1;
		canBeDigged = 1;
		rotationFlags = 2;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"\TerjeRadiation\Container\military\data\military_case_co.paa"};
		soundImpactType = "wood";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 400;
					transferToAttachmentsCoef = 0.06;
					healthLevels[] = {{1.0,{"TerjeRadiation\Container\military\data\military_mat.rvmat"}},{0.7,{"TerjeRadiation\Container\military\data\military_mat.rvmat"}},{0.5,{"TerjeRadiation\Container\military\data\military_mat_damage.rvmat"}},{0.3,{"TerjeRadiation\Container\military\data\military_mat_damage.rvmat"}},{0.0,{"TerjeRadiation\Container\military\data\military_mat_destruct.rvmat"}}};
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage = 1.0;
					};
					class Blood
					{
						damage = 1.0;
					};
					class Shock
					{
						damage = 1.0;
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[] = {9,5};
			openable = 0;
			allowOwnedCargoManipulation = 1;
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet = "seachest_movement_SoundSet";
					id = 1;
				};
				class pickUpItem_Light
				{
					soundSet = "pickUpSeaChest_SoundSet";
					id = 796;
				};
				class pickUpItem
				{
					soundSet = "pickUpSeaChest_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "seachest_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
	class TerjeCaseRadSpecial: Container_Base
	{
		scope = 2;
		displayName="#STR_TERJERAD_CASESPECIAL_NAME";
		descriptionShort="#STR_TERJERAD_CASESPECIAL_DESC";
		model = "\TerjeRadiation\Container\special\special_case.p3d";
		rotationFlags = 17;
		weight = 2500;
		itemSize[] = {7,5};
		itemsCargoSize[] = {6,4};
		allowOwnedCargoManipulation = 1;
		canBeDigged = 1;
		isMeleeWeapon = 1;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"\TerjeRadiation\Container\special\data\special_case_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"TerjeRadiation\Container\special\data\special_mat.rvmat"}},{0.7,{"TerjeRadiation\Container\special\data\special_mat.rvmat"}},{0.5,{"TerjeRadiation\Container\special\data\special_mat_damage.rvmat"}},{0.3,{"TerjeRadiation\Container\special\data\special_mat_damage.rvmat"}},{0.0,{"TerjeRadiation\Container\special\data\special_mat_destruct.rvmat"}}};
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage = 1.0;
					};
					class Blood
					{
						damage = 1.0;
					};
					class Shock
					{
						damage = 1.0;
					};
				};
			};
		};
		soundImpactType = "textile";
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet = "pickUpCourierBag_Light_SoundSet";
					id = 796;
				};
				class pickUpItem
				{
					soundSet = "pickUpCourierBag_SoundSet";
					id = 797;
				};
			};
		};
	};
};