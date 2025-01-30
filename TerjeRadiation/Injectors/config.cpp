// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeRadiation_Injectors
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeRadiation"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class TerjeAntiradInjector: Inventory_Base
	{
		scope=2;
		displayName="#STR_TERJERAD_RADIOPROTECTOR";
		model="\dz\gear\medical\Epinephrine.p3d";
		debug_ItemCategory=7;
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"TerjeRadiation\Injectors\radprotector_co.paa"
		};
		rotationFlags=17;
		itemSize[]={1,2};
		weight=60;
		soundImpactType="plastic";
		medAntiradLevel=3;
		medAntiradTimer=600;
		medAntiradMaxTimer=1800;
		overdosedIncrement = 0.75;
		medicalItem=1;
		medSkillExpAddToSelf=50;
		medicalInjectorsCategory=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=50;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\medical\data\epipen.rvmat"
							}
						},
						
						{
							0.75,
							
							{
								"DZ\gear\medical\data\epipen.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\medical\data\epipen_damage.rvmat"
							}
						},
						
						{
							0.25,
							
							{
								"DZ\gear\medical\data\epipen_damage.rvmat"
							}
						},
						
						{
							0,
							{
								"DZ\gear\medical\data\epipen_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
};