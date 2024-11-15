// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
    class TerjeMedicine_Dosimetr
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
	class TerjeDosimetrBase: Inventory_Base
	{
		scope = 0;
		attachments[] = {"BatteryD"};
		class EnergyManager
		{
			hasIcon = 1;
			autoSwitchOffWhenInCargo = 0;
			plugType = 1;
			attachmentAction = 1;
			energyUsagePerSecond = 0.0006;
			updateInterval = 1;
		};
	};
	class TerjeDosimetrPripyat: TerjeDosimetrBase
	{
		scope = 2;
		displayName = "#STR_TERJEMED_DOSIMETR_PRIPYAT_NAME";
		descriptionShort = "#STR_TERJEMED_DOSIMETR_PRIPYAT_DESC";
		model = "\TerjeMedicine\Dosimeter\Pripyat\pripyat.p3d";
		hiddenSelections[] = {"pos_1","pos_2","pos_3","pos_4"};
		hiddenSelectionsTextures[] = {"TerjeMedicine\Dosimeter\Numbers\numoff_ca.paa","TerjeMedicine\Dosimeter\Numbers\numoff_ca.paa","TerjeMedicine\Dosimeter\Numbers\numoff_ca.paa","TerjeMedicine\Dosimeter\Numbers\numoff_ca.paa"};
		itemSize[] = {2,3};
		weight = 600;
		rotationFlags = 1;
		inventorySlot[] = {"WalkieTalkie"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"TerjeMedicine\Dosimeter\Pripyat\data\pripyat_mat.rvmat"}},{0.7,{"TerjeMedicine\Dosimeter\Pripyat\data\pripyat_mat.rvmat"}},{0.5,{"TerjeMedicine\Dosimeter\Pripyat\data\pripyat_mat.rvmat"}},{0.3,{"TerjeMedicine\Dosimeter\Pripyat\data\pripyat_mat.rvmat"}},{0.0,{"TerjeMedicine\Dosimeter\Pripyat\data\pripyat_mat.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class interact
				{
					soundset = "Flashlight_TurnOn_SoundSet";
					id = 70;
				};
			};
		};
	};
	class TerjeDosimetrMkc01A: TerjeDosimetrBase
	{
		scope = 2;
		displayName = "#STR_TERJEMED_DOSIMETR_MKC01A_NAME";
		descriptionShort = "#STR_TERJEMED_DOSIMETR_MKC01A_DESC";
		model = "\TerjeMedicine\Dosimeter\Mkc01\mkc01.p3d";
		hiddenSelections[] = {"pos_1","pos_2","pos_3","pos_4"};
		hiddenSelectionsTextures[] = {"TerjeMedicine\Dosimeter\Numbers\numoff_ca.paa","TerjeMedicine\Dosimeter\Numbers\numoff_ca.paa","TerjeMedicine\Dosimeter\Numbers\numoff_ca.paa","TerjeMedicine\Dosimeter\Numbers\numoff_ca.paa"};
		itemSize[] = {2,3};
		weight = 600;
		rotationFlags = 1;
		inventorySlot[] = {"WalkieTalkie"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"TerjeMedicine\Dosimeter\Mkc01\data\mkc_mat.rvmat"}},{0.7,{"TerjeMedicine\Dosimeter\Mkc01\data\mkc_mat.rvmat"}},{0.5,{"TerjeMedicine\Dosimeter\Mkc01\data\mkc_mat.rvmat"}},{0.3,{"TerjeMedicine\Dosimeter\Mkc01\data\mkc_mat.rvmat"}},{0.0,{"TerjeMedicine\Dosimeter\Mkc01\data\mkc_mat.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class interact
				{
					soundset = "Flashlight_TurnOn_SoundSet";
					id = 70;
				};
			};
		};
	};
	class TerjeDosimetrCdv700: TerjeDosimetrBase
	{
		scope = 2;
		displayName = "#STR_TERJEMED_DOSIMETR_CDV700_NAME";
		descriptionShort = "#STR_TERJEMED_DOSIMETR_CDV700_DESC";
		model = "\TerjeMedicine\Dosimeter\Cdv700\cdv700.p3d";
		//hiddenSelections[] = {"arrow"};
		//hiddenSelectionsTextures[] = {"TerjeMedicine\Dosimeter\Arrow\arrow_0.paa"};
		itemSize[] = {4,3};
		weight = 1600;
		rotationFlags = 2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"TerjeMedicine\Dosimeter\Cdv700\data\cdv700_mat.rvmat"}},{0.7,{"TerjeMedicine\Dosimeter\Cdv700\data\cdv700_mat.rvmat"}},{0.5,{"TerjeMedicine\Dosimeter\Cdv700\data\cdv700_mat.rvmat"}},{0.3,{"TerjeMedicine\Dosimeter\Cdv700\data\cdv700_mat.rvmat"}},{0.0,{"TerjeMedicine\Dosimeter\Cdv700\data\cdv700_mat.rvmat"}}};
				};
			};
		};
		class AnimationSources
		{
			class arrow
			{
				source = "user";
				animPeriod = 1;
				initPhase = 0;
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class interact
				{
					soundset = "Flashlight_TurnOn_SoundSet";
					id = 70;
				};
			};
		};
	};
	class TerjeDosimetrDpg05: TerjeDosimetrBase
	{
		scope = 2;
		displayName = "#STR_TERJEMED_DOSIMETR_DPG05_NAME";
		descriptionShort = "#STR_TERJEMED_DOSIMETR_DPG05_DESC";
		model = "\TerjeMedicine\Dosimeter\Dpg05\dpg05.p3d";
		itemSize[] = {2,3};
		weight = 400;
		rotationFlags = 1;
		inventorySlot[] = {"WalkieTalkie"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"TerjeMedicine\Dosimeter\Dpg05\data\dpg05_mat.rvmat"}},{0.7,{"TerjeMedicine\Dosimeter\Dpg05\data\dpg05_mat.rvmat"}},{0.5,{"TerjeMedicine\Dosimeter\Dpg05\data\dpg05_mat.rvmat"}},{0.3,{"TerjeMedicine\Dosimeter\Dpg05\data\dpg05_mat.rvmat"}},{0.0,{"TerjeMedicine\Dosimeter\Dpg05\data\dpg05_mat.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class interact
				{
					soundset = "Flashlight_TurnOn_SoundSet";
					id = 70;
				};
			};
		};
	};
};
class CfgSoundShaders
{
	class TerjeGeigerLowSoundShader
	{
		samples[] = {{"\TerjeMedicine\Dosimeter\Sounds\geiger_low",0.9}};
		volume = 2;
		range = 8;
	};
	class TerjeGeigerMediumSoundShader
	{
		samples[] = {{"\TerjeMedicine\Dosimeter\Sounds\geiger_medium",0.9}};
		volume = 2;
		range = 8;
	};
	class TerjeGeigerHighSoundShader
	{
		samples[] = {{"\TerjeMedicine\Dosimeter\Sounds\geiger_high",0.9}};
		volume = 2;
		range = 8;
	};
	class TerjeGeigerAlarmSoundShader
	{
		samples[] = {{"\TerjeMedicine\Dosimeter\Sounds\geiger_alarm",0.9}};
		volume = 2;
		range = 8;
	};

	class TerjeGeigerElectroLowSoundShader
	{
		samples[] = {{"\TerjeMedicine\Dosimeter\Sounds\electro_low",0.9}};
		volume = 2;
		range = 8;
	};
	class TerjeGeigerElectroMediumSoundShader
	{
		samples[] = {{"\TerjeMedicine\Dosimeter\Sounds\electro_medium",0.9}};
		volume = 2;
		range = 8;
	};
	class TerjeGeigerElectroHighSoundShader
	{
		samples[] = {{"\TerjeMedicine\Dosimeter\Sounds\electro_high",0.9}};
		volume = 2;
		range = 8;
	};
	class TerjeGeigerElectroAlarmSoundShader
	{
		samples[] = {{"\TerjeMedicine\Dosimeter\Sounds\electro_alarm",0.9}};
		volume = 2;
		range = 8;
	};
};
class CfgSoundSets
{
	class TerjeGeigerClasic0_SoundSet
	{
		sound3DProcessingType = "infected3DProcessingType";
		volumeCurve = "infectedAttenuationCurve";
		spatial = 1;
		doppler = 0;
		loop = 0;
		soundShaders[] = {"TerjeGeigerLowSoundShader"};
	};
	class TerjeGeigerClasic1_SoundSet
	{
		sound3DProcessingType = "infected3DProcessingType";
		volumeCurve = "infectedAttenuationCurve";
		spatial = 1;
		doppler = 0;
		loop = 0;
		soundShaders[] = {"TerjeGeigerMediumSoundShader"};
	};
	class TerjeGeigerClasic2_SoundSet
	{
		sound3DProcessingType = "infected3DProcessingType";
		volumeCurve = "infectedAttenuationCurve";
		spatial = 1;
		doppler = 0;
		loop = 0;
		soundShaders[] = {"TerjeGeigerHighSoundShader"};
	};
	class TerjeGeigerClasic3_SoundSet
	{
		sound3DProcessingType = "infected3DProcessingType";
		volumeCurve = "infectedAttenuationCurve";
		spatial = 1;
		doppler = 0;
		loop = 0;
		soundShaders[] = {"TerjeGeigerAlarmSoundShader"};
	};
	class TerjeGeigerElectro0_SoundSet
	{
		sound3DProcessingType = "infected3DProcessingType";
		volumeCurve = "infectedAttenuationCurve";
		spatial = 1;
		doppler = 0;
		loop = 0;
		soundShaders[] = {"TerjeGeigerElectroLowSoundShader"};
	};
	class TerjeGeigerElectro1_SoundSet
	{
		sound3DProcessingType = "infected3DProcessingType";
		volumeCurve = "infectedAttenuationCurve";
		spatial = 1;
		doppler = 0;
		loop = 0;
		soundShaders[] = {"TerjeGeigerElectroMediumSoundShader"};
	};
	class TerjeGeigerElectro2_SoundSet
	{
		sound3DProcessingType = "infected3DProcessingType";
		volumeCurve = "infectedAttenuationCurve";
		spatial = 1;
		doppler = 0;
		loop = 0;
		soundShaders[] = {"TerjeGeigerElectroHighSoundShader"};
	};
	class TerjeGeigerElectro3_SoundSet
	{
		sound3DProcessingType = "infected3DProcessingType";
		volumeCurve = "infectedAttenuationCurve";
		spatial = 1;
		doppler = 0;
		loop = 0;
		soundShaders[] = {"TerjeGeigerElectroAlarmSoundShader"};
	};
};