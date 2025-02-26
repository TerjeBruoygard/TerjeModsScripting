// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine_Headgear
	{
		units[] = {"TerjeHeadgearPsiHelm"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"TerjeMedicine", "DZ_Data","DZ_Characters"};
	};
};
class CfgVehicles
{
	class Clothing;
	class TerjeHeadgearPsiHelm: Clothing
	{
		scope = 2;
		displayName = "#STR_TERJEHEADGEAR_PSIHELM_NAME";
		descriptionShort = "#STR_TERJEHEADGEAR_PSIHELM_DESC";
		model = "\TerjeMedicine\Headgear\psihelmet\psihelmet_g.p3d";
		vehicleClass = "Clothing";
		simulation = "clothing";
		attachments[] = {"BatteryD"};
		inventorySlot[] = {"Headgear"};
		itemInfo[] = {"Clothing","Headgear"};
		rotationFlags = 2;
		itemSize[] = {3,3};
		weight = 250;
		repairableWithKits[] = {7};
		repairCosts[] = {45};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 150;
					healthLevels[] = {{1.0,{"TerjeMedicine\Headgear\psihelmet\data\psihelmet_mat.rvmat"}},{0.7,{"TerjeMedicine\Headgear\psihelmet\data\psihelmet_mat.rvmat"}},{0.5,{"TerjeMedicine\Headgear\psihelmet\data\psihelmet_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\Headgear\psihelmet\data\psihelmet_mat_damage.rvmat"}},{0.0,{"TerjeMedicine\Headgear\psihelmet\data\psihelmet_mat_destruct.rvmat"}}};
				};
			};
		};
		class Protection
		{
			psionic=0.95;
		};
		class EnergyManager
		{
			hasIcon = 1;
			energyUsagePerSecond = 0.09;
			plugType = 1;
			attachmentAction = 1;
		};
		class ClothingTypes
		{
			male = "\TerjeMedicine\Headgear\psihelmet\psihelmet.p3d";
			female = "\TerjeMedicine\Headgear\psihelmet\psihelmet.p3d";
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet = "SportGlasses_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "SportGlasses_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
	class HouseNoDestruct;
	class Static_TerjeHeadgearPsiHelm: HouseNoDestruct
	{
		scope = 1;
		model = "\TerjeMedicine\Headgear\psihelmet\psihelmet_g.p3d";
	};
};