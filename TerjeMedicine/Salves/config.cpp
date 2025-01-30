// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine_Salves
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
	class Inventory_Base;
	
	class TerjeSalveBase : Inventory_Base
	{
		descriptionShort="#STR_TERJEMED_SALVE_DESC";
		model="\TerjeMedicine\Salves\cosmetic_tube.p3d";
		rotationFlags=17;
		itemSize[]={1,2};
		weight=120;
		quantityBar=1;
		varQuantityInit=5;
		varQuantityMin=0;
		varQuantityMax=5;
		varQuantityDestroyOnMin=1;
		absorbency=0;
		overdosedIncrement=0.01;
		medicalItem=1;
		hiddenSelections[] = {"zbytek"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"TerjeMedicine\Salves\data\cosmetic_tube_mat.rvmat"}},{0.7,{"TerjeMedicine\Salves\data\cosmetic_tube_mat.rvmat"}},{0.5,{"TerjeMedicine\Salves\data\cosmetic_tube_mat_damage.rvmat"}},{0.3,{"TerjeMedicine\Salves\data\cosmetic_tube_mat_damage.rvmat"}},{0,{"TerjeMedicine\Salves\data\cosmetic_tube_mat_destruct.rvmat"}}};
				};
			};
		};
	};

	class TerjeSalveFinalgon : TerjeSalveBase
	{
		scope=2;
		displayName="#STR_TERJEMED_FINALGON";
		medHematomaHeal=1;
		medHematomaHealTimeSec=300;
		hiddenSelectionsTextures[] = {"TerjeMedicine\Salves\data\finalgon_co.paa"};
	};

	class TerjeSalveCapsicum : TerjeSalveBase
	{
		scope=2;
		displayName="#STR_TERJEMED_CAPSICUM";
		medHematomaHeal=1;
		medHematomaHealTimeSec=400;
		hiddenSelectionsTextures[] = {"TerjeMedicine\Salves\data\capsicum_co.paa"};
	};

	class TerjeSalveViprosal : TerjeSalveBase
	{
		scope=2;
		displayName="#STR_TERJEMED_VIPROSAL";
		medHematomaHeal=1;
		medHematomaHealTimeSec=600;
		hiddenSelectionsTextures[] = {"TerjeMedicine\Salves\data\viprosal_co.paa"};
	};
};