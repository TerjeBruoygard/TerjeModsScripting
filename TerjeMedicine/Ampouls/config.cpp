// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine_Ampouls
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
	
	class TerjeAmpouleBase : Inventory_Base
	{
		descriptionShort="#STR_TERJEMED_AMPOULE_DESC";
		itemSize[]={1,2};
		weight=100;
		quantityBar=1;
		varQuantityInit=5;
		varQuantityMin=0;
		varQuantityMax=5;
		varQuantityDestroyOnMin=1;
		stackedUnit="percentage";
		soundImpactType="glass";
		absorbency=0;
		overdosedIncrement=0.25;
		medicalItem=1;
		medicalAmpoulsCategory=1;
		medSkillExpAddToSelf=50;
		medPainkillerMaxTimeSec=1800;
		medAntipoisonMaxTimeSec=1800;
		medAntibiohazardMaxTimeSec=1800;
		medAntibioticsMaxTimeSec=1800;
		medRabiesAntibioticMaxTimeSec=1800;
		medZAntidotMaxTimeSec=1800;
		medAntisepsisMaxTimeSec=1800;
		medConcussionHealMaxTimeSec=1800;
		medBloodHemostaticMaxTimeSec=1800;
		medBloodRegenMaxTimeSec=1800;
		medHematomaHealMaxTimeSec=1800;
		medAdrenalinMaxTimeSec=1800;
		medAntidepresantMaxTimer=1800;
	};
	
	// SIMPLE AMPOULS
	class TerjeAmpouleAlcohol : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ALCOHOL";
		descriptionShort="#STR_TERJEMED_AMPOULE_DESC";
		model="\dz\gear\medical\injectionvial.p3d";
		varQuantityInit=10;
		varQuantityMin=0;
		varQuantityMax=10;
		overdosedIncrement=4;
		medSkillExpAddToSelf=0;
		medicalAmpoulsCategory=0;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_co.paa" };
	};
	
	class TerjeAmpouleAmoxivan : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_AMOXIVAN";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntibioticLevel=2;
		medAntibioticsTimeSec=900;
		overdosedIncrement = 0.3;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_pink_co.paa" };
	};
	
	class TerjeAmpouleNovacaine : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_NOVOCAINE";
		model="\dz\gear\medical\injectionvial.p3d";
		medPainkillerLevel=2;
		medPainkillerTimeSec=1200;
		overdosedIncrement = 0.4;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_blue_co.paa" };
	};
	
	class TerjeAmpouleMetoclopramid : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_METOCLOPRAMID";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntipoisonLevel=2;
		medAntipoisonTimeSec=1200;
		overdosedIncrement = 0.4;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_green_co.paa" };
	};
	
	class TerjeAmpouleNeirox : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_NEIROX";
		model="\dz\gear\medical\injectionvial.p3d";
		medConcussionHealTimeSec=600;
		overdosedIncrement = 0.6;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_purple_co.paa" };
	};
	
	class TerjeAmpouleErythropoetin : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ERYTHROPOIETIN";
		model="\dz\gear\medical\injectionvial.p3d";
		medBloodRegenValue=1;
		medBloodRegenTimeSec = 600;
		overdosedIncrement = 0.4;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_red_co.paa" };
	};
	
	class TerjeAmpouleAdrenalin : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ADRENALIN";
		model="\dz\gear\medical\injectionvial.p3d";
		medAdrenalinTimeSec = 220;
		overdosedIncrement = 0.3;
		medSkillExpAddToSelf=10;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_yellow_co.paa" };
	};
	
	class TerjeAmpoulePentacin : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_PENTACIN";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntiradLevel = 2;
		medAntiradTimer = 400;
		overdosedIncrement = 0.5;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_ultrayellow_co.paa" };
	};
	
	class TerjeAmpouleMetralindole : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_METRALINDOLE";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntidepresantLevel = 2;
		medAntidepresantTimer = 300;
		overdosedIncrement = 0.1;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_gray_co.paa" };
	};
	
	class TerjeAmpouleVaxicam : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_VAXICAM";
		model="\dz\gear\medical\injectionvial.p3d";
		medInfluenzaVacineTime = 14400;
		overdosedIncrement = 0.8;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_vacine_a_co.paa" };
	};
	
	class TerjeAmpouleZerivax : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ZERIVAX";
		model="\dz\gear\medical\injectionvial.p3d";
		medZVirusVacineTime = 7200;
		overdosedIncrement = 1.5;
		medSkillExpAddToSelf=100;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_vacine_b_co.paa" };
	};
	
	class TerjeAmpouleRabivax : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_RABIVAX";
		model="\dz\gear\medical\injectionvial.p3d";
		medRabiesVacineTime = 14400;
		overdosedIncrement = 1.3;
		medSkillExpAddToSelf=100;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_vacine_c_co.paa" };
	};
	
	class TerjeAmpouleRabinoline : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_RABINOLINE";
		model="\dz\gear\medical\injectionvial.p3d";
		medRabiesAntibioticLevel = 2;
		medRabiesAntibioticTimeSec = 600;
		overdosedIncrement = 0.8;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_violet_co.paa" };
	};
	
	class TerjeAmpouleNeirocetal : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_NEIROCETAL";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntibiohazardLevel = 2;
		medAntibiohazardTimeSec = 500;
		overdosedIncrement = 1.25;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_neirocet_co.paa" };
	};
	
	// ADVANCED AMPOULS
	class TerjeAmpouleKetarol : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_KETAROL";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntibioticLevel=2;
		medAntibioticsTimeSec=1200;
		medPainkillerLevel=1;
		medPainkillerTimeSec=1200;
		overdosedIncrement = 0.5;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_neoblack_co.paa" };
	};
	
	class TerjeAmpouleFlemoclav : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_FLEMOCLAV";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntibioticLevel=3;
		medAntibioticsTimeSec=1200;
		medAntisepsisTimeSec=1200;
		overdosedIncrement = 0.8;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_toxicgrey_co.paa" };
	};
	
	class TerjeAmpouleImipenem : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_IMIPENEM";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntibioticLevel=3;
		medAntibioticsTimeSec=900;
		medAntisepsisTimeSec=900;
		overdosedIncrement = 0.7;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_toxicgreen_co.paa" };
	};
	
	class TerjeAmpouleMorphine : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_MORPHINE";
		model="\dz\gear\medical\injectionvial.p3d";
		medPainkillerLevel=3;
		medPainkillerTimeSec=850;
		overdosedIncrement = 0.52;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_azulred_co.paa" };
	};
	
	class TerjeAmpouleGexobarbital : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_GEXOBARBITAL";
		model="\dz\gear\medical\injectionvial.p3d";
		medPainkillerLevel=3;
		medPainkillerTimeSec=900;
		overdosedIncrement = 0.65;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_darkorange_co.paa" };
	};
	
	class TerjeAmpouleKetamin : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_KETAMIN";
		model="\dz\gear\medical\injectionvial.p3d";
		medPainkillerLevel=3;
		medPainkillerTimeSec=600;
		overdosedIncrement = 0.45;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_darkblue_co.paa" };
	};
	
	class TerjeAmpouleHeptral : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_HEPTRAL";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntipoisonLevel=3;
		medAntipoisonTimeSec=600;
		overdosedIncrement = 0.6;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_darkgreen_co.paa" };
	};
	
	class TerjeAmpouleCarboxyme : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_CARBOXYME";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntiradLevel = 2;
		medAntiradTimer = 600;
		overdosedIncrement = 0.6;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_dirtyblue_co.paa" };
	};
	
	class TerjeAmpouleActaparoxetine : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ACTAPAROXETINE";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntidepresantLevel = 2;
		medAntidepresantTimer = 400;
		overdosedIncrement = 0.4;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_dirtygreen_co.paa" };
	};
	
	class TerjeAmpouleAmitriptyline : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_AMITRIPTYLINE";
		model="\dz\gear\medical\injectionvial.p3d";
		medAntidepresantLevel = 3;
		medAntidepresantTimer = 600;
		overdosedIncrement = 0.5;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_dirtyred_co.paa" };
	};
	
	class TerjeAmpouleRifampicyne : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_RIFAMBICYNE";
		model="\dz\gear\medical\injectionvial.p3d";
		medRabiesAntibioticLevel = 3;
		medRabiesAntibioticTimeSec = 300;
		overdosedIncrement = 1.35;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_lightpink_co.paa" };
	};
	
	class TerjeAmpouleZivirol : TerjeAmpouleBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ZIVIROL";
		model="\dz\gear\medical\injectionvial.p3d";
		medZAntidotTimeSec=1000;
		overdosedIncrement=2.35;
		terjeAddHealth=-25;
		terjeAddBlood=-15;
		terjeAddShock=-100;
		medSkillExpAddToSelf=200;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Ampouls\ampoule_zivirol_co.paa" };
	};
};