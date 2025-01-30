// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeSkills_Knifes
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeSkills", "DZ_Gear_Tools", "DZ_Weapons_Melee_Blade"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	
	class BoneKnife: Inventory_Base
	{
		terjeSkinningModifier = 2.0;
		
		//You can completely override the knife modifier so that it is not affected by the character's skills by next parameter.
		//terjeSkinningModifierOverride = 0.1;
	};
	
	class Cleaver: Inventory_Base
	{
		terjeSkinningModifier = 0.5;
	};
	
	class CrudeMachete: Inventory_Base
	{
		terjeSkinningModifier = 1.0;
	};
	
	class FangeKnife: Inventory_Base
	{
		terjeSkinningModifier = 0.5;
	};
	
	class FirefighterAxe: Inventory_Base
	{
		terjeSkinningModifier = 1.0;
	};
	
	class Crowbar: Inventory_Base
	{
		terjeSkinningModifier = 5.0;
	};
	
	class HandSaw: Inventory_Base
	{
		terjeSkinningModifier = 1.0;
	};
	
	class HayHook: Inventory_Base
	{
		terjeSkinningModifier = 5.0;
	};
	
	class Iceaxe: Inventory_Base
	{
		terjeSkinningModifier = 3.0;
	};
	
	class Hacksaw: Inventory_Base
	{
		terjeSkinningModifier = 1.0;
	};
	
	class Hatchet: Inventory_Base
	{
		terjeSkinningModifier = 1.0;
	};
	
	class HuntingKnife: Inventory_Base
	{
		terjeSkinningModifier = 0.75;
	};
	
	class KitchenKnife: Inventory_Base
	{
		terjeSkinningModifier = 1.5;
	};
	
	class KukriKnife: Inventory_Base
	{
		terjeSkinningModifier = 0.75;
	};
	
	class Machete: Inventory_Base
	{
		terjeSkinningModifier = 1.0;
	};
	
	class OrientalMachete: Inventory_Base
	{
		terjeSkinningModifier = 1.0;
	};
	
	class Pickaxe: Inventory_Base
	{
		terjeSkinningModifier = 3.0;
	};
	
	class Screwdriver: Inventory_Base
	{
		terjeSkinningModifier = 5.0;
	};
	
	class Sickle: Inventory_Base
	{
		terjeSkinningModifier = 2.0;
	};
	
	class SteakKnife: Inventory_Base
	{
		terjeSkinningModifier = 2.0;
	};
	
	class StoneKnife: Inventory_Base
	{
		terjeSkinningModifier = 2.0;
	};
	
	class Sword: Inventory_Base
	{
		terjeSkinningModifier = 1.5;
	};
	
	class WoodAxe: Inventory_Base
	{
		terjeSkinningModifier = 1.0;
	};
};