// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
    class TerjeRadiation_Tent
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
class CfgSlots
{
	class Slot_CanisterGasoline
	{
		name = "CanisterGasoline";
		displayName = "$STR_Canister_Gasoline";
		selection = "CanisterGasoline";
		ghostIcon = "gascanister";
	};
	class Slot_Shower
	{
		name = "Shower";
		displayName = "#STR_Shower";
		selection = "Shower";
		ghostIcon = "barrel";
	};
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyJerryCan: ProxyAttachment
	{
		model = "\dz\vehicles\parts\JerryCan.p3d";
		inventoryslot[] += {"CanisterGasoline"};
	};
	class ProxyShower: ProxyAttachment
	{
		model = "\TerjeRadiation\Tent\data\shower.p3d";
		inventoryslot[] += {"Shower"};
	};
};
class CfgVehicles
{
    class TentBase;
	class Bottle_Base;
	class CanisterGasoline: Bottle_Base
	{
		inventorySlot[] +=
		{
			"CanisterGasoline"
		};
	};

    class TerjeRadTent: TentBase
	{
		scope=2;
		displayName="$STR_CfgVehicles_CarTent0";
		descriptionShort="$STR_CfgVehicles_CarTent1";
		model="\TerjeRadiation\Tent\RadTent.p3d";
		bounding="BSphere";
		overrideDrawArea="3.0";
		forceFarBubble="true";
		slopeTolerance=0.30000001;
		yawPitchRollLimit[]={15,15,15};
		hiddenSelections[]=
		{
			"bags",
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"TerjeRadiation\Tent\data\radtent_co.paa",
			"TerjeRadiation\Tent\data\radtentplace_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"TerjeRadiation\Tent\data\radtent_mat.rvmat",
			"TerjeRadiation\Tent\data\radtentplace_mat.rvmat"
		};
		openable=0;
		carveNavmesh=1;
		weight=60000;
		itemSize[]={10,5};
		itemsCargoSize[]={10,50};
		itemBehaviour=0;
		lootCategory="Tents";
		placement="ForceSlopeOnTerrain";
		physLayer="item_large";
		repairableWithKits[]={5,2};
		repairCosts[]={30,25};
		attachments[]=
		{
			"CanisterGasoline",
			"Shower"
		};
		minPlacingDist=10;
		rotationFlags=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1700;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								""
							}
						},
						
						{
							0.69999999,
							
							{
								""
							}
						},
						
						{
							0.5,
							
							{
								""
							}
						},
						
						{
							0.30000001,
							
							{
								""
							}
						},
						
						{
							0,
							
							{
								""
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0.050000001;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0.30000001;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=8;
					};
				};
			};
			class DamageZones
			{
				class Body
				{
					class Health
					{
						hitpoints=1700;
						transferToGlobalCoef=0.5;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat.rvmat",
									"DZ\gear\camping\data\tent_pristine_co.paa"
								}
							},
							
							{
								0.69999999,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat.rvmat",
									"DZ\gear\camping\data\tent_worn_co.paa"
								}
							},
							
							{
								0.5,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat_damage.rvmat",
									"DZ\gear\camping\data\tent_damage_co.paa"
								}
							},
							
							{
								0.30000001,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat_damage.rvmat",
									"DZ\gear\camping\data\tent_destruct_co.paa"
								}
							},
							
							{
								0,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat_destruct.rvmat",
									"DZ\gear\camping\data\tent_destruct_co.paa"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=0.050000001;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.30000001;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=8;
							};
						};
					};
					componentNames[]=
					{
						"body"
					};
					transferToZonesNames[]=
					{
						"Inventory"
					};
					transferToZonesCoefs[]={1};
					fatalInjuryCoef=-1;
				};
				class Inventory
				{
					class Health
					{
						hitpoints=1700;
						transferToGlobalCoef=0.5;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat.rvmat",
								}
							},
							
							{
								0.69999999,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat.rvmat",
								}
							},
							
							{
								0.5,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat_damage.rvmat",
								}
							},
							
							{
								0.30000001,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat_damage.rvmat",
								}
							},
							
							{
								0,
								
								{
									"TerjeRadiation\Tent\data\radtent_mat_destruct.rvmat",
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=0.050000001;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.30000001;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=8;
							};
						};
					};
					componentNames[]=
					{
						"inventory"
					};
					transferToZonesNames[]=
					{
						"Body"
					};
					transferToZonesCoefs[]={1,1};
					fatalInjuryCoef=-1;
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				name="$STR_attachment_accessories";
				description="";
				attachmentSlots[]=
				{
					"CanisterGasoline",
					"Shower"
				};
				icon="set:dayz_inventory image:cat_fp_tents";
				view_index=1;
			};
		};
		class AnimationSources
		{
			class Body
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Shower
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
            class CanisterGasoline
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Inventory
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Cord_folded
			{
				source="user";
				initPhase=1;
				animPeriod=0.0099999998;
			};
			class Cord_plugged
			{
				source="user";
				initPhase=1;
				animPeriod=0.0099999998;
			};
			class Pack
			{
				source="user";
				initPhase=1;
				animPeriod=0.0099999998;
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
	class TerjeRadTentPlacing: TerjeRadTent
	{
		scope=1;
		displayName="This is a hologram";
		descriptionShort="Nothing to see here, move along";
		model="\TerjeRadiation\Tent\RadTentPlacing.p3d";
		storageCategory=10;
		hiddenSelections[]=
		{
			"placing"
		};
		hiddenSelectionsTextures[]=
		{
			"TerjeRadiation\Tent\data\radtentplace_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"TerjeRadiation\Tent\data\radtentplace_mat.rvmat"
		};
		hologramMaterial="radtentplace_mat";
		hologramMaterialPath="TerjeRadiation\Tent\data";
		class AnimationSources
		{
			class Placing
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
		};
	};
};