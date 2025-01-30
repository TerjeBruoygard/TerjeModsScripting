// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine_FirstAidKit
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

class CfgVehicles
{
	class Container_Base;
	class Inventory_Base;
	class FirstAidKit: Container_Base
	{
		displayName="#STR_MEDCONTAINER_SMALL_NAME";
		descriptionShort="#STR_MEDCONTAINER_SMALL_DESC";
		rotationFlags=17;
		weight=140;
		itemSize[]={3,3};
		itemsCargoSize[]={6,6};
		allowOwnedCargoManipulation=1;
		repairableWithKits[] = {2};
		repairCosts[] = {25.0};
	};

	class TerjeFirstAidKitAdvancedBase: Container_Base
	{
		scope=0;
		displayName="#STR_MEDCONTAINER_AFAK_NAME";
		descriptionShort="#STR_MEDCONTAINER_AFAK_DESC";
		model="TerjeMedicine\FirstAidKit\afak\afak.p3d";
		rotationFlags=17;
		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		varQuantityInit=20;
		varQuantityMin=0;
		varQuantityMax=20;
		quantityBar=1;
		stackedUnit="percentage";
		itemsCargoSize[]={8,4};
		allowOwnedCargoManipulation=1;
		medBloodStop=3;
		medBloodHemostaticValue=3;
		medBloodHemostaticTimeSec=60;
		terjeSurgeryKitRefill=1;
		terjeSurgeryVisceraEffectivity=0.3;
		terjeSurgeryVisceraTime=40;
		terjeSurgeryBulletEffectivity=0.6;
		terjeSurgeryBulletTime=30;
		terjeSurgeryStubEffectivity=0.8;
		terjeSurgeryStubTime=20;
		weight=500;
		absorbency=0.0;
		itemSize[]={4,4};
		varCleannessInit=1;
		repairableWithKits[] = {2};
		repairCosts[] = {35.0};
		hiddenSelections[] = {"zbytek"};
		inventorySlot[] = {"Belt_Back"};
		vehicleClass = "Clothing";
		itemInfo[] = {"Clothing","Belt"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"TerjeMedicine\FirstAidKit\afak\data\afak_mat.rvmat"}},{0.7,{"TerjeMedicine\FirstAidKit\afak\data\afak_mat.rvmat"}},{0.5,{"TerjeMedicine\FirstAidKit\afak\data\afak_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\FirstAidKit\afak\data\afak_mat_damage.rvmat"}},{0,{"TerjeMedicine\FirstAidKit\afak\data\afak_mat_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
			};
		};
	};
	class TerjeFirstAidKitAdvance_Black: TerjeFirstAidKitAdvancedBase
	{
		scope=2;
		hiddenSelectionsTextures[] = {"TerjeMedicine\FirstAidKit\afak\data\afak_co.paa"};
	};
	class TerjeFirstAidKitAdvance_Brown: TerjeFirstAidKitAdvancedBase
	{
		scope=2;
		hiddenSelectionsTextures[] = {"TerjeMedicine\FirstAidKit\afak\data\afak_2_co.paa"};
	};
	class TerjeFirstAidKitAdvance_Green: TerjeFirstAidKitAdvancedBase
	{
		scope=2;
		hiddenSelectionsTextures[] = {"TerjeMedicine\FirstAidKit\afak\data\afak_3_co.paa"};
	};
	class TerjeFirstAidKitAdvance_Camo: TerjeFirstAidKitAdvancedBase
	{
		scope=2;
		hiddenSelectionsTextures[] = {"TerjeMedicine\FirstAidKit\afak\data\afak_4_co.paa"};
	};
	
	class TerjeFirstAidKitIndividualBase: Container_Base
	{
		scope=0;
		displayName="#STR_MEDCONTAINER_IFAK_NAME";
		descriptionShort="#STR_MEDCONTAINER_IFAK_DESC";
		model="TerjeMedicine\FirstAidKit\ifak\ifak.p3d";
		rotationFlags=17;
		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		varQuantityInit=10;
		varQuantityMin=0;
		varQuantityMax=10;
		quantityBar=1;
		stackedUnit="percentage";
		itemsCargoSize[]={8,2};
		allowOwnedCargoManipulation=1;
		terjeSurgeryKitRefill=1;
		terjeSurgeryVisceraEffectivity=0.3;
		terjeSurgeryVisceraTime=60;
		terjeSurgeryBulletEffectivity=0.6;
		terjeSurgeryBulletTime=30;
		terjeSurgeryStubEffectivity=0.8;
		terjeSurgeryStubTime=15;
		medBloodStop=2;
		weight=500;
		absorbency=0.0;
		itemSize[]={3,3};
		varCleannessInit=1;
		repairableWithKits[] = {2};
		repairCosts[] = {25.0};
		hiddenSelections[] = {"zbytek"};
		vehicleClass = "Clothing";
		inventorySlot[]=
		{
			"VestHolster",
			"Belt_Right"
		};
		itemInfo[]=
		{
			"Clothing",
			"Vest"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"TerjeMedicine\FirstAidKit\ifak\data\ifak_mat.rvmat"}},{0.7,{"TerjeMedicine\FirstAidKit\ifak\data\ifak_mat.rvmat"}},{0.5,{"TerjeMedicine\FirstAidKit\ifak\data\ifak_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\FirstAidKit\ifak\data\ifak_mat_damage.rvmat"}},{0,{"TerjeMedicine\FirstAidKit\ifak\data\ifak_mat_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
			};
		};
	};

	class TerjeFirstAidKitIndividual_Black: TerjeFirstAidKitIndividualBase
	{
		scope=2;
		hiddenSelectionsTextures[] = {"TerjeMedicine\FirstAidKit\ifak\data\ifak_co.paa"};
	};
	class TerjeFirstAidKitIndividual_Brown: TerjeFirstAidKitIndividualBase
	{
		scope=2;
		hiddenSelectionsTextures[] = {"TerjeMedicine\FirstAidKit\ifak\data\ifak_2_co.paa"};
	};
	class TerjeFirstAidKitIndividual_Green: TerjeFirstAidKitIndividualBase
	{
		scope=2;
		hiddenSelectionsTextures[] = {"TerjeMedicine\FirstAidKit\ifak\data\ifak_3_co.paa"};
	};
	class TerjeFirstAidKitIndividual_Camo: TerjeFirstAidKitIndividualBase
	{
		scope=2;
		hiddenSelectionsTextures[] = {"TerjeMedicine\FirstAidKit\ifak\data\ifak_4_co.paa"};
	};

	class TerjeFirstAidKitMedium: Container_Base
	{
		scope=2;
		displayName="#STR_MEDCONTAINER_MIDLE_NAME";
		descriptionShort="#STR_MEDCONTAINER_MIDLE_DESC";
		model="TerjeMedicine\FirstAidKit\mfak\mfak.p3d";
		rotationFlags=17;
		weight=250;
		itemSize[]={4,4};
		itemsCargoSize[]={8,8};
		allowOwnedCargoManipulation=1;
		randomQuantity=2;
		canBeDigged=0;
		isMeleeWeapon=1;
		repairableWithKits[] = {2};
		repairCosts[] = {30.0};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"TerjeMedicine\FirstAidKit\mfak\data\mfak_mat.rvmat"}},{0.7,{"TerjeMedicine\FirstAidKit\mfak\data\mfak_mat.rvmat"}},{0.5,{"TerjeMedicine\FirstAidKit\mfak\data\mfak_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\FirstAidKit\mfak\data\mfak_mat_damage.rvmat"}},{0,{"TerjeMedicine\FirstAidKit\mfak\data\mfak_mat_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
			};
		};
	};

	class TerjeFirstAidKitLarge: Container_Base
	{
		scope=2;
		displayName="#STR_MEDCONTAINER_LARGE_NAME";
		descriptionShort="#STR_MEDCONTAINER_LARGE_DESC";
		model="TerjeMedicine\FirstAidKit\lfak\lfak.p3d";
		rotationFlags=17;
		weight=500;
		itemSize[]={5,5};
		itemsCargoSize[]={10,10};
		allowOwnedCargoManipulation=1;
		randomQuantity=2;
		canBeDigged=1;
		isMeleeWeapon=1;
		repairableWithKits[] = {8};
		repairCosts[] = {30.0};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"TerjeMedicine\FirstAidKit\lfak\data\lfak_mat.rvmat"}},{0.7,{"TerjeMedicine\FirstAidKit\lfak\data\lfak_mat.rvmat"}},{0.5,{"TerjeMedicine\FirstAidKit\lfak\data\lfak_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\FirstAidKit\lfak\data\lfak_mat_damage.rvmat"}},{0,{"TerjeMedicine\FirstAidKit\lfak\data\lfak_mat_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
			};
		};
	};
};