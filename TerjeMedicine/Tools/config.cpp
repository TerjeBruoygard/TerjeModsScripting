// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine_Tools
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
	class Box_Base;
	class Inventory_Base;
	class BandageDressing;
	class Clothing;
	class BaseBuildingBase;
	
	class TerjePlaster : BandageDressing
	{
		scope=2;
		displayName="#STR_TERJEMED_PLASTER_NAME";
		descriptionShort="#STR_TERJEMED_PLASTER_DESC";
		model="\TerjeMedicine\Tools\plaster\plaster.p3d";
		rotationFlags=17;
		itemSize[]={1,2};
		weight=20;
		varTemperatureMin = 0;
		varTemperatureMax = 0;
		absorbency = 0.7;
		medicalItem=1;
		medBloodStop=1;
		canBeSplit = 1;
		varQuantityInit = 10;
		varQuantityMin = 0;
		varQuantityMax = 10;
		varQuantityDestroyOnMin = 1;
		stackedUnit = "pills";
		quantityBar = 0;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"TerjeMedicine\Tools\plaster\data\plaster_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\plaster\data\plaster_mat.rvmat"}},{0.7,{"TerjeMedicine\Tools\plaster\data\plaster_mat.rvmat"}},{0.5,{"TerjeMedicine\Tools\plaster\data\plaster_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\plaster\data\plaster_mat_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\plaster\data\plaster_mat_destruct.rvmat"}}};
				};
			};
		};
	};

	class TerjeSyringeNew : Box_Base
	{
		scope=2;
		displayName="#STR_TERJEMED_SYRINGE_NEW_NAME";
		descriptionShort="#STR_TERJEMED_SYRINGE_NEW_DESC";
		model="\TerjeMedicine\Tools\syringe\syringe_new.p3d";
		rotationFlags=17;
		itemSize[]={1,2};
		weight=20;
		absorbency=0;
		medicalItem=1;
		varCleannessInit=1;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"TerjeMedicine\Tools\syringe\data\syringe_new_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\syringe\data\syringe_new_mat.rvmat"}},{0.7,{"TerjeMedicine\Tools\syringe\data\syringe_new_mat.rvmat"}},{0.5,{"TerjeMedicine\Tools\syringe\data\syringe_new_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\syringe\data\syringe_new_mat_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\syringe\data\syringe_new_mat_destruct.rvmat"}}};
				};
			};
		};
		class Resources
		{
			class TerjeSyringeEmpty
			{
				value=1;
				variable="quantity";
			};
		};
	};
	
	class TerjeSyringeEmpty : Inventory_Base
	{
		scope=2;
		displayName="#STR_TERJEMED_SYRINGE_EMPTY_NAME";
		descriptionShort="#STR_TERJEMED_SYRINGE_EMPTY_DESC";
		model="\TerjeMedicine\Tools\syringe\syringe_empty.p3d";
		rotationFlags=17;
		itemSize[]={1,2};
		weight=20;
		absorbency=0;
		medicalItem=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 80;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\syringe\data\syringe_glass_mat.rvmat"}},{0.7,{"TerjeMedicine\Tools\syringe\data\syringe_glass_mat.rvmat"}},{0.5,{"TerjeMedicine\Tools\syringe\data\syringe_glass_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\syringe\data\syringe_glass_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\syringe\data\syringe_glass_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Syringe_out
				{
					soundSet="Syringe_out_SoundSet";
					id=201;
				};
				class Syringe_spear
				{
					soundSet="Syringe_spear_SoundSet";
					id=202;
				};
				class Syringe_splash
				{
					soundSet="Syringe_splash_SoundSet";
					id=203;
				};
			};
		};
	};
	class TerjeImprovisedSyringeEmpty : TerjeSyringeEmpty
	{
		scope=2;
		displayName="#STR_TERJEMED_SYRINGE_EMPTY_NAME";
		descriptionShort="#STR_TERJEMED_SYRINGE_EMPTY_DESC";
		model="\TerjeMedicine\Tools\syringe\syringe_plast_empty.p3d";
		rotationFlags=17;
		itemSize[]={1,2};
		weight=20;
		absorbency=0;
		medicalItem=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 30;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_mat.rvmat"}},{0.7,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_mat.rvmat"}},{0.5,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Syringe_out
				{
					soundSet="Syringe_out_SoundSet";
					id=201;
				};
				class Syringe_spear
				{
					soundSet="Syringe_spear_SoundSet";
					id=202;
				};
				class Syringe_splash
				{
					soundSet="Syringe_splash_SoundSet";
					id=203;
				};
			};
		};
	};

	class TerjeSyringeFull : Inventory_Base
	{
		scope=2;
		displayName="#STR_TERJEMED_SYRINGE_FULL_NAME";
		descriptionShort="#STR_TERJEMED_SYRINGE_FULL_DESC";
		model="\TerjeMedicine\Tools\syringe\syringe_full.p3d";
		rotationFlags=17;
		itemSize[]={1,2};
		weight=100;
		absorbency=0;
		medicalItem=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 80;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\syringe\data\syringe_glass_mat.rvmat"}},{0.7,{"TerjeMedicine\Tools\syringe\data\syringe_glass_mat.rvmat"}},{0.5,{"TerjeMedicine\Tools\syringe\data\syringe_glass_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\syringe\data\syringe_glass_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\syringe\data\syringe_glass_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Syringe_out
				{
					soundSet="Syringe_out_SoundSet";
					id=201;
				};
				class Syringe_spear
				{
					soundSet="Syringe_spear_SoundSet";
					id=202;
				};
				class Syringe_splash
				{
					soundSet="Syringe_splash_SoundSet";
					id=203;
				};
			};
		};
	};

	class TerjeImprovisedSyringeFull : TerjeSyringeFull
	{
		scope=2;
		displayName="#STR_TERJEMED_SYRINGE_FULL_NAME";
		descriptionShort="#STR_TERJEMED_SYRINGE_FULL_DESC";
		model="\TerjeMedicine\Tools\syringe\syringe_plast_full.p3d";
		rotationFlags=17;
		itemSize[]={1,2};
		weight=100;
		absorbency=0;
		medicalItem=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 30;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_mat.rvmat"}},{0.7,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_mat.rvmat"}},{0.5,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\syringe\data\syringe_pl_glass_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Syringe_out
				{
					soundSet="Syringe_out_SoundSet";
					id=201;
				};
				class Syringe_spear
				{
					soundSet="Syringe_spear_SoundSet";
					id=202;
				};
				class Syringe_splash
				{
					soundSet="Syringe_splash_SoundSet";
					id=203;
				};
			};
		};
	};

	class TerjeBandageHemostatic: BandageDressing
	{
		scope=2;
		displayName="#STR_TERJEMED_BANDAGE_NAME";
		descriptionShort="#STR_TERJEMED_BANDAGE_DESC";
		model="TerjeMedicine\Tools\hemostatic_bandage\hemostatic_bandage.p3d";
		inventorySlot[]=
		{
			"MedicalBandage"
		};
		isMeleeWeapon=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=1;
		quantityBar=1;
		varQuantityDestroyOnMin=1;
		rotationFlags=17;
		weight=150;
		absorbency=0.0;
		itemSize[]={1,1};
		medBloodStop=3;
		medBloodHemostaticValue=5;
		medBloodHemostaticTimeSec=270;
		varCleannessInit=1;
		medicalItem=1;
		class AnimEvents
		{
			class SoundWeapon
			{
				class Bandage_loop1
				{
					soundSet="Bandage_loop_SoundSet";
					id=201;
				};
				class Bandage_loop2
				{
					soundSet="Bandage_loop_SoundSet";
					id=202;
				};
				class Bandage_loop3
				{
					soundSet="Bandage_loop_SoundSet";
					id=203;
				};
				class Bandage_start
				{
					soundSet="Bandage_start_SoundSet";
					id=204;
				};
				class Bandage_end
				{
					soundSet="Bandage_end_SoundSet";
					id=205;
				};
			};
		};
	};

	class TerjeSurgicalKit: Inventory_Base
	{
		scope=2;
		displayName="#STR_TERJEMED_SURGKIT_NAME";
		descriptionShort="#STR_TERJEMED_SURGKIT_DESC";
		model="\TerjeMedicine\Tools\surgical_kit\surgical_kit.p3d";
		rotationFlags=17;
		varQuantityInit=5;
		varQuantityMin=0;
		varQuantityMax=5;
		quantityBar=1;
		stackedUnit="percentage";
		varQuantityDestroyOnMin=1;
		weight=300;
		absorbency=0.0;
		itemSize[]={2,1};
		varCleannessInit=1;
		medicalItem=1;
		terjeSurgeryKitRefill=1;
		terjeSurgeryVisceraEffectivity=0.2;
		terjeSurgeryVisceraTime=40;
		terjeSurgeryBulletEffectivity=0.5;
		terjeSurgeryBulletTime=25;
		terjeSurgeryStubEffectivity=0.7;
		terjeSurgeryStubTime=20;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"TerjeMedicine\Tools\surgical_kit\data\surgical_kit_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\surgical_kit\data\surgical_kit_mat.rvmat"}},{0.7,{"TerjeMedicine\Tools\surgical_kit\data\surgical_kit_mat.rvmat"}},{0.5,{"TerjeMedicine\Tools\surgical_kit\data\surgical_kit_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\surgical_kit\data\surgical_kit_mat_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\surgical_kit\data\surgical_kit_mat_destruct.rvmat"}}};
				};
			};
		};
	};
	
	class TerjeSurgicalTool_ColorBase : Inventory_Base
	{
		displayName="#STR_TERJEMED_SURGTOOLS_NAME";
		descriptionShort="#STR_TERJEMED_SURGTOOLS_DESC";
		varCleannessInit=0;
		medicalItem=1;
		terjeSurgeryKitRefill=1;
		terjeSurgeryVisceraEffectivity=0.05;
		terjeSurgeryVisceraTime=90;
		terjeSurgeryBulletEffectivity=0.2;
		terjeSurgeryBulletTime=40;
		terjeSurgeryStubEffectivity=0.4;
		terjeSurgeryStubTime=30;
	};
	class TerjeSurgicalTool_White: TerjeSurgicalTool_ColorBase
	{
		scope=2;
		model="\TerjeMedicine\Tools\surgical_tool\surgical_tool.p3d";
		rotationFlags=0;
		weight=100;
		absorbency=0.0;
		itemSize[]={1,2};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_mat.rvmat"}},{0.7,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_mat.rvmat"}},{0.5,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_mat_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_mat_destruct.rvmat"}}};
				};
			};
		};
	};
	class TerjeSurgicalTool_Ceramic: TerjeSurgicalTool_ColorBase
	{
		scope=2;
		model="\TerjeMedicine\Tools\surgical_tool\surgical_tool_ceramic.p3d";
		rotationFlags=0;
		weight=100;
		absorbency=0.0;
		itemSize[]={1,2};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_ceramic_mat.rvmat"}},{0.7,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_ceramic_mat.rvmat"}},{0.5,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_ceramic_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_ceramic_mat_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\surgical_tool\data\surgical_tool_ceramic_mat_destruct.rvmat"}}};
				};
			};
		};
	};
	class TerjeStethoscope: Clothing
	{
		scope=2;
		displayName="#STR_TERJEMED_STETHOSCOPE_NAME";
		descriptionShort="#STR_TERJEMED_STETHOSCOPE_DESC";
		model="TerjeMedicine\Tools\stethoscope\stethoscope_g.p3d";
		vehicleClass="Clothing";
		simulation="clothing";
		medicalItem=1;
		inventorySlot[]=
		{
			"Eyewear"
		};
		itemInfo[]=
		{
			"Clothing",
			"Eyewear"
		};
		rotationFlags=17;
		itemSize[]={3,2};
		weight=200;
		lootCategory="Eyewear";
		lootTag[]=
		{
			"Civilian"
		};
		hiddenSelections[]=
		{
			"camoGround",
			"camoMale",
			"camoFemale"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=50;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
		class ClothingTypes
		{
			male="TerjeMedicine\Tools\stethoscope\stethoscope_m.p3d";
			female="TerjeMedicine\Tools\stethoscope\stethoscope_m.p3d";
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="SportGlasses_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SportGlasses_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class TentBase;
	class TerjeSleepingBag : TentBase 
	{
		scope=0;
		displayName="#STR_TERJEMED_SLEEPINGBAG_NAME";
		descriptionShort="#STR_TERJEMED_SLEEPINGBAG_DESC";
		model="TerjeMedicine\Tools\sleepingbag\sbag_packed.p3d";
		weight=2000;
		bounding="BSphere";
		projectionTypename="TerjeSleepingBagPlacing";
		overrideDrawArea="3.0";
		forceFarBubble="true";
		slopeTolerance=0.3;
		yawPitchRollLimit[]={15,15,15};
		hiddenSelections[]=
		{
			"camo",
			"body"
		};
		hiddenSelectionsTextures[]=
		{
			"TerjeMedicine\Tools\sleepingbag\data\sbag_packed_blue.paa",
			"TerjeMedicine\Tools\sleepingbag\data\sbag_placed_blue.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"TerjeMedicine\Tools\sleepingbag\data\sbag_packed.rvmat",
			"TerjeMedicine\Tools\sleepingbag\data\sbag_placed.rvmat"
		};
		openable=0;
		absorbency = 0;
		carveNavmesh=1;
		itemSize[]={3,4};
		itemsCargoSize[]={0,0};
		itemBehaviour=0;
		lootCategory="Tents";
		placement="ForceSlopeOnTerrain";
		physLayer="item_large";
		repairableWithKits[]={5,2};
		repairCosts[]={30,25};
		minPlacingDist=10;
		rotationFlags=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"TerjeMedicine\Tools\sleepingbag\data\sbag_packed.rvmat"}},{0.7,{"TerjeMedicine\Tools\sleepingbag\data\sbag_packed.rvmat"}},{0.5,{"TerjeMedicine\Tools\sleepingbag\data\sbag_packed_damage.rvmat"}},{0.3,{"TerjeMedicine\Tools\sleepingbag\data\sbag_packed_damage.rvmat"}},{0.0,{"TerjeMedicine\Tools\sleepingbag\data\sbag_packed_destruct.rvmat"}}};
				};
			};
		};
		class AnimationSources
		{
			class Body
			{
				source="user";
				animPeriod=0.01;
				initPhase=1;
			};
			class Bags
			{
				source="user";
				animPeriod=0.01;
				initPhase=1;
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet="cartent_movement_SoundSet";
					id=1;
				};
				class pickUpItem_Light
				{
					soundSet="pickUpTentLight_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpTent_SoundSet";
					id=797;
				};
				class mediumtent_drop
				{
					soundset="mediumtent_drop_SoundSet";
					id=898;
				};
			};
		};
	};

	class TerjeSleepingBagPlacing : TerjeSleepingBag 
	{
		scope=1;
		model="TerjeMedicine\Tools\sleepingbag\sbag_placed.p3d";
		hologramMaterial="sbag_placed";
		hologramMaterialPath="TerjeMedicine\Tools\sleepingbag\data";
		storageCategory=10;
		hiddenSelections[]=
		{
			"placing"
		};
		hiddenSelectionsTextures[]=
		{
			"TerjeMedicine\Tools\sleepingbag\data\sbag_packed_blackwhite.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"TerjeMedicine\Tools\sleepingbag\data\sbag_placed.rvmat"
		};
	};

	class TerjeSleepingBag_Blue : TerjeSleepingBag 
	{
		scope=2;
		hiddenSelectionsTextures[]=
		{
			"TerjeMedicine\Tools\sleepingbag\data\sbag_packed_blue.paa",
			"TerjeMedicine\Tools\sleepingbag\data\sbag_placed_blue.paa"
		};
	};

	class TerjeSleepingBag_Woodland : TerjeSleepingBag 
	{
		scope=2;
		hiddenSelectionsTextures[]=
		{
			"TerjeMedicine\Tools\sleepingbag\data\sbag_packed_woodland.paa",
			"TerjeMedicine\Tools\sleepingbag\data\sbag_placed_woodland.paa"
		};
	};
};