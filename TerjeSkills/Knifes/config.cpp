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
		terjeSkinningTimeModifier = 2.0;
		terjeSkinningExpModifier=0.5;
		
		//You can completely override the knife modifier so that it is not affected by the character's skills by next parameter.
		//terjeSkinningTimeModifierOverride = 0.1;
	};
	
	class Cleaver: Inventory_Base
	{
		terjeSkinningTimeModifier = 0.5;
		terjeSkinningExpModifier=1.0;
	};
	
	class CrudeMachete: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.0;
		terjeSkinningExpModifier=1.0;
	};
	
	class FangeKnife: Inventory_Base
	{
		terjeSkinningTimeModifier = 0.5;
		terjeSkinningExpModifier=1.0;
	};
	
	class FirefighterAxe: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class Crowbar: Inventory_Base
	{
		terjeSkinningTimeModifier = 5.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class HandSaw: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class HayHook: Inventory_Base
	{
		terjeSkinningTimeModifier = 5.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class Iceaxe: Inventory_Base
	{
		terjeSkinningTimeModifier = 3.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class Hacksaw: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class Hatchet: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class HuntingKnife: Inventory_Base
	{
		terjeSkinningTimeModifier = 0.75;
		terjeSkinningExpModifier=2.0;
	};
	
	class KitchenKnife: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.5;
		terjeSkinningExpModifier=1.0;
	};
	
	class KukriKnife: Inventory_Base
	{
		terjeSkinningTimeModifier = 0.75;
		terjeSkinningExpModifier=1.0;
	};
	
	class Machete: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.0;
		terjeSkinningExpModifier=1.0;
	};
	
	class OrientalMachete: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.0;
		terjeSkinningExpModifier=1.0;
	};
	
	class Pickaxe: Inventory_Base
	{
		terjeSkinningTimeModifier = 3.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class Screwdriver: Inventory_Base
	{
		terjeSkinningTimeModifier = 5.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class Sickle: Inventory_Base
	{
		terjeSkinningTimeModifier = 2.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class SteakKnife: Inventory_Base
	{
		terjeSkinningTimeModifier = 2.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class StoneKnife: Inventory_Base
	{
		terjeSkinningTimeModifier = 2.0;
		terjeSkinningExpModifier=0.5;
	};
	
	class Sword: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.5;
		terjeSkinningExpModifier=0.5;
	};
	
	class WoodAxe: Inventory_Base
	{
		terjeSkinningTimeModifier = 1.0;
		terjeSkinningExpModifier=0.5;
	};
};