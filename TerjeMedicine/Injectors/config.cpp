// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
	class TerjeMedicine_Injectors
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
	
	class TerjeInjectorBase : Inventory_Base
	{
		descriptionShort="#STR_TERJEMED_INJECTOR_DESC";
		rotationFlags=17;
		itemSize[]={1,2};
		weight=60;
		overdosedIncrement=0.4;
		medicalItem=1;
		medSkillExpAddToSelf=100;
		medicalInjectorsCategory=1;
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
		class AnimEvents
		{
			class SoundWeapon
			{
				class Morphine_spear
				{
					soundSet="Morphine_spear_SoundSet";
					id=201;
				};
				class Morphine_out
				{
					soundSet="Morphine_out_SoundSet";
					id=202;
				};
			};
		};
	};
	
	// Compatibility
	class TerjeAntiradInjector : Inventory_Base
	{
		descriptionShort="#STR_TERJEMED_INJECTOR_DESC";
	};
	
	// Basic
	class Epinephrine: Inventory_Base
	{
		descriptionShort="#STR_TERJEMED_INJECTOR_DESC";
		medAdrenalinTimeSec = 720;
		overdosedIncrement = 0.55;
		medicalItem=1;
		medSkillExpAddToSelf=50;
		medicalInjectorsCategory=1;
	};
	
	class Morphine: Inventory_Base
	{
		descriptionShort="#STR_TERJEMED_INJECTOR_DESC";
		medPainkillerLevel = 3;
		medPainkillerTimeSec = 300;
		overdosedIncrement = 0.75;
		medicalItem=1;
		medicalInjectorsCategory=1;
	};
	
	class AntiChemInjector: Inventory_Base
	{
		descriptionShort="#STR_TERJEMED_INJECTOR_DESC";
		medAntibiohazardLevel = 3;
		medAntibiohazardTimeSec = 180;
		overdosedIncrement = 1.1;
		medicalItem=1;
		medicalInjectorsCategory=1;
	};
	
	class TerjeInjectorZivirol : TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ZIVIROL";
		model="\dz\gear\medical\morphine.p3d";
		medZAntidotTimeSec=1200;
		overdosedIncrement=2.5;
		terjeAddHealth=-20;
		terjeAddBlood=-10;
		terjeAddShock=-100;
		medSkillExpAddToSelf=250;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_purple_co.paa" };
	};
	
	class TerjeInjectorAmoxiclav : TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_AMOXICLAV";
		model="\dz\gear\medical\morphine.p3d";
		medAntibioticLevel=3;
		medAntibioticsTimeSec=1800;
		medAntisepsisTimeSec=300;
		overdosedIncrement = 0.6;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_blue_co.paa" };
	};
	
	class TerjeInjectorNeirox : TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_NEIROX";
		model="\dz\gear\medical\morphine.p3d";
		medConcussionHealTimeSec=500;
		overdosedIncrement = 0.3;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_agua_co.paa" };
	};
	
	class TerjeInjectorErythropoietin : TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ERYTHROPOIETIN";
		model="\dz\gear\medical\morphine.p3d";
		medBloodRegenValue=1;
		medBloodRegenTimeSec=900;
		overdosedIncrement = 0.4;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_darkred_co.paa" };
	};
	
	class TerjeInjectorNovichek : TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_NOVICHEK";
		model="\dz\gear\medical\morphine.p3d";
		overdosedIncrement=5;
		biohazardIncrement=5;
		terjeAddShock=-100;
		medSkillExpAddToSelf=10;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_black_co.paa" };
	};
	
	// Advanced
	class TerjeInjectorPromidol: TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_PROMIDOL";
		model="\dz\gear\medical\morphine.p3d";
		medPainkillerLevel = 3;
		medPainkillerTimeSec = 600;
		overdosedIncrement = 0.45;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_viogreen_co.paa" };
	};
	
	class TerjeInjectorTopoizomeraza: TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_TOPOIZOMERAZA";
		model="\dz\gear\medical\morphine.p3d";
		medAntibioticLevel=3;
		medAntibioticsTimeSec=900;
		medAntisepsisTimeSec=600;
		overdosedIncrement = 0.65;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_pinkred_co.paa" };
	};
	
	class TerjeInjectorErytromixelin: TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ERYTROMIXELIN";
		model="\dz\gear\medical\morphine.p3d";
		medBloodHemostaticValue=3;
		medBloodHemostaticTimeSec=300;
		medBloodRegenValue=2;
		medBloodRegenTimeSec = 150;
		overdosedIncrement = 0.32;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_orangebrown_co.paa" };
	};
	
	class TerjeInjectorStomaproxidal: TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_STOMAPROXIDAL";
		model="\dz\gear\medical\morphine.p3d";
		medAntipoisonLevel=3;
		medAntipoisonTimeSec=900;
		overdosedIncrement = 0.68;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_dirtyviolete_co.paa" };
	};
	
	class TerjeInjectorRabinucoline: TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_RABINUCOLINE";
		model="\dz\gear\medical\morphine.p3d";
		medRabiesAntibioticLevel = 3;
		medRabiesAntibioticTimeSec = 900;
		overdosedIncrement = 1.46;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_celugreen_co.paa" };
	};
	
	class TerjeInjectorAmfitalicyne : TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_AMFITALICYNE";
		model="\dz\gear\medical\morphine.p3d";
		medAntidepresantLevel = 3;
		medAntidepresantTimer = 520;
		overdosedIncrement = 0.6;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_bluered_co.paa" };
	};
	
	class TerjeInjectorReanimatal : TerjeInjectorBase
	{
		scope=2;
		displayName="#STR_TERJEMED_REANIMATAL";
		model="\dz\gear\medical\morphine.p3d";
		medPainkillerLevel = 1;
		medPainkillerTimeSec = 240;
		terjeAddBlood = 25;
		terjeAddHealth = 15;
		terjeAddShock = -50;
		overdosedIncrement = 1.85;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = { "TerjeMedicine\Injectors\injector_infistar_co.paa" };
	};
};