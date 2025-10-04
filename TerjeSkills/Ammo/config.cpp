// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeSkills_Ammo
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeSkills", "DZ_Weapons_Melee"
		};
	};
};

class CfgAmmo
{
	class MeleeDamage;
	
	class MeleeFistLight: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
	};
	
	class MeleeFistHeavy: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
	};
	
	class MeleeFist: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
	};
	
	class MeleeFist_Heavy: MeleeFist
	{
		terjeIgnoreExpStrength = 1;
	};
	
	class MeleeSoft: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
	};
	
	class MeleeSoft_Heavy: MeleeSoft
	{
		terjeIgnoreExpStrength = 1;
	};
	
	class Dummy_Light: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
	};
	
	class Dummy_Heavy: Dummy_Light
	{
		terjeIgnoreExpStrength = 1;
	};
	
	class Dummy_TerjeStrengthLight: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
		class DamageApplied
		{
			type="Melee";
			class Health
			{
				damage=1;
			};
			class Blood
			{
				damage=0;
			};
			class Shock
			{
				damage=0;
			};
		};
	};
	
	class Dummy_TerjeStrengthHeavy: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
		class DamageApplied
		{
			type="Melee";
			class Health
			{
				damage=1;
			};
			class Blood
			{
				damage=0;
			};
			class Shock
			{
				damage=0;
			};
		};
	};
	
	class Dummy_TerjeStrengthMStroke: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
		class DamageApplied
		{
			type="Melee";
			class Health
			{
				damage=0;
			};
			class Blood
			{
				damage=0;
			};
			class Shock
			{
				damage=100;
			};
		};
	};
	
	class Dummy_TerjeStrengthMStrokeAlt: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
		class DamageApplied
		{
			type="Melee";
			class Health
			{
				damage=1000;
			};
			class Blood
			{
				damage=0;
			};
			class Shock
			{
				damage=0;
			};
		};
	};
	
	class Dummy_TerjeHuntingMelee: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
		class DamageApplied
		{
			type="Melee";
			class Health
			{
				damage=1;
			};
			class Blood
			{
				damage=0;
			};
			class Shock
			{
				damage=0;
			};
		};
	};
	
	class Dummy_TerjeHuntingProjectile: MeleeDamage
	{
		terjeIgnoreExpStrength = 1;
		class DamageApplied
		{
			type="Melee";
			class Health
			{
				damage=1;
			};
			class Blood
			{
				damage=0;
			};
			class Shock
			{
				damage=0;
			};
		};
	};
};