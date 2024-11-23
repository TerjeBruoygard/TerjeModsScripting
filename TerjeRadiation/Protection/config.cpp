// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
    class TerjeRadiation_Protection
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeRadiation", "DZ_Data", "DZ_Gear_Crafting", "DZ_Gear_Consumables",
            "DZ_Characters_Tops", "DZ_Characters_Shoes", "DZ_Characters_Pants",
            "DZ_Characters_Masks", "DZ_Characters_Headgear", "DZ_Characters_Gloves"
        };
    };
};

class CfgVehicles
{
    class Clothing;
    class Inventory_Base;
    class GasMask_Filter_Improvised: Inventory_Base
    {
        class Protection
        {
            radiation=0.7;
        };
    };
    class GasMask_Filter: Inventory_Base
    {
        class Protection
        {
            radiation=0.9;
        };
    };
    class NBCJacketBase: Clothing
    {
        class Protection
        {
            radiation=0.95;
        };
    };
    class NBCBootsBase: Clothing
    {
        class Protection
        {
            radiation=0.95;
        };
    };
    class NBCPantsBase: Clothing
    {
        class Protection
        {
            radiation=0.95;
        };
    };
    class GasMask: Clothing
    {
        class Protection
        {
            radiation=0.95;
        };
    };
    class GP5GasMask: Clothing
    {
        class Protection
        {
            radiation=0.8;
        };
    };
    class GP5GasMask_Filter: Inventory_Base
    {
        class Protection
        {
            radiation=0.9;
        };
    };
    class NBCHoodBase: Clothing
    {
        class Protection
        {
            radiation=0.95;
        };
    };
    class NBCGloves_ColorBase: Clothing
    {
        class Protection
        {
            radiation=0.95;
        };
    };
};