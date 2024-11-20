// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
    class TerjeMedicine_Sounds
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
    class TerjeSoundEmitter;

    class TerjeSoundEmitter_SleepingMale: TerjeSoundEmitter
    {
        scope=2;
        emitterLifetime=5;
        emitterRange=10;
        emitterSound="sleeping_male";
    };
    class TerjeSoundEmitter_SleepingFemale: TerjeSoundEmitter
    {
        scope=2;
        emitterLifetime=4;
        emitterRange=10;
        emitterSound="sleeping_female";
    };
};

class CfgSounds
{
    class default;
    class sleeping_male: default
    {
        sound[]=
        {
            "TerjeMedicine\Sounds\sleeping_male.ogg", 1, 1, 10
        };
    };
    class sleeping_female: default
    {
        sound[]=
        {
            "TerjeMedicine\Sounds\sleeping_female.ogg", 3, 1, 10
        };
    }; 
};

class CfgSoundShaders
{
    class baseCharacter_SoundShader;
    class hearthbit_Soundshader: baseCharacter_SoundShader
    {
        samples[]=
        {
            {
                "TerjeMedicine\Sounds\hearthbit_overdose.ogg", 1
            }
        };
        volume=0.3;
    };
    class psyonicWaveTerje_Soundshader: baseCharacter_SoundShader
    {
        samples[]=
        {
            {
                "TerjeMedicine\Sounds\psyonic_wave.ogg", 1
            }
        };
        volume=0.4;
    };
};

class CfgSoundSets
{
    class baseCharacter_SoundSet;
    class hearthbit_SoundSet: baseCharacter_SoundSet
    {
        soundShaders[]=
        {
            "hearthbit_Soundshader"
        };
    };
    class psyonicWaveTerje_SoundSet: baseCharacter_SoundSet
    {
        soundShaders[]=
        {
            "psyonicWaveTerje_Soundshader"
        };
    };
};