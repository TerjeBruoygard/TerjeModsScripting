// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
    class TerjeMedicine_Liquids
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine", "TerjeCore"
        };
    };
};

class CfgTerjeCustomLiquids
{
    class SoapyWater
    {
        displayName="#STR_TERJEMED_SOAPY_WATER";
        flammability=-10;
        liquidFreezeThreshold=0;
        liquidThawThreshold=0;
        liquidBoilingThreshold=150;
        terjeRadiationCleanupForce=10;
        class Nutrition
        {
            fullnessIndex=1;
            energy=-5;
            water=5;
            nutritionalIndex=75;
            toxicity=1;
            digestibility=2;
            agents=16;
        };
    };
    class RadDesactivator
    {
        displayName="#STR_TERJEMED_RAD_DISACTIVATOR";
        flammability=-10;
        liquidFreezeThreshold=0;
        liquidThawThreshold=0;
        liquidBoilingThreshold=150;
        terjeRadiationCleanupForce=50;
        terjeOverrideLiquidColor=-10267848; // Use https://argb-int-calculator.netlify.app/ to calculate int color value.
        class Nutrition
        {
            fullnessIndex=1;
            energy=-5;
            water=0;
            nutritionalIndex=75;
            toxicity=1;
            digestibility=2;
            agents=16;
        };
    };
};

class cfgLiquidDefinitions
{
    class Water
    {
        terjeRadiationCleanupForce=1;
    };
    class RiverWater
    {
        terjeRadiationCleanupForce=1;
    };
};