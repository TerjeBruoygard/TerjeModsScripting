// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeRadiation_Tools
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeRadiation", "DZ_Vehicles_Parts"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class CanisterGasoline;

	class TerjeCanisterChemical : CanisterGasoline
	{
		scope=2;
		displayName="#STR_TERJERAD_CANISTRECHEMICAL_NAME";
		descriptionShort="#STR_TERJERAD_CANISTRECHEMICAL_DESC";
		model="\TerjeRadiation\Tools\canistre\canistre.p3d";
		rotationFlags=0;
		itemSize[] = {4,5};
		weight = 1000;
		absorbency = 0;
		canBeSplit = 0;
		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		varQuantityInit = 10000;
		varQuantityMin = 0;
		varQuantityMax = 10000;
		varLiquidTypeInit=65536;
		varTerjeCustomLiquidTypeInit="RadDesactivator";
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"TerjeRadiation\Tools\canistre\data\canistra_co.paa"};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpCanisterGasoline_Light
				{
					soundSet = "pickUpCanisterGasolineLight_SoundSet";
					id = 796;
				};
				class pickUpCanisterGasoline
				{
					soundSet = "pickUpCanisterGasoline_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "canistergasoline_drop_SoundSet";
					id = 898;
				};
			};
		};
		soundImpactType = "plastic";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"TerjeRadiation\Tools\canistre\data\canistra_mat.rvmat"}},{0.7,{"TerjeRadiation\Tools\canistre\data\canistra_mat.rvmat"}},{0.5,{"TerjeRadiation\Tools\canistre\data\canistra_mat_damage.rvmat"}},{0.3,{"TerjeRadiation\Tools\canistre\data\canistra_mat_damage.rvmat"}},{0.0,{"TerjeRadiation\Tools\canistre\data\canistra_mat_destruct.rvmat"}}};
				};
			};
		};
	};
	
	class TerjeSoap : Inventory_Base
	{
		scope=2;
		displayName="#STR_TERJERAD_SOAP_NAME";
		descriptionShort="#STR_TERJERAD_SOAP_DESC";
		model="\TerjeRadiation\Tools\soap\soap.p3d";
		rotationFlags=1;
		itemSize[]={1,1};
		weight=40;
		absorbency = 0;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"TerjeRadiation\Tools\soap\data\soap_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"TerjeRadiation\Tools\soap\data\soap_mat.rvmat"}},{0.7,{"TerjeRadiation\Tools\soap\data\soap_mat.rvmat"}},{0.5,{"TerjeRadiation\Tools\soap\data\soap_mat_damage.rvmat"}},{0.3,{"TerjeRadiation\Tools\soap\data\soap_mat_damage.rvmat"}},{0.0,{"TerjeRadiation\Tools\soap\data\soap_mat_destruct.rvmat"}}};
				};
			};
		};
	};
};