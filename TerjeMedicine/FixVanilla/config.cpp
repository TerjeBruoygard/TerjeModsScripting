// <copyright file="config.cpp" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class CfgPatches
{
    class TerjeMedicine_FixVanilla
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
    class Clothing;
    class Edible_Base;
    class Inventory_Base;
    
    class PlateCarrierVest: Clothing {
        meleeProtection = 0.8;
        firearmProtection = 0.55;
    };

    class PressVest_ColorBase: Clothing
    {
        meleeProtection = 0.6;
        firearmProtection = 0.35;
    };

    class PoliceVest: Clothing
    {
        meleeProtection = 0.6;
        firearmProtection = 0.15;
    };
    
    class NBCGloves_ColorBase: Clothing {
        radiationProtection = 0.045;
    };

    class NBCHoodBase: Clothing {
        radiationProtection = 0.045;
    };

    class NBCPantsBase: Clothing {
        radiationProtection = 0.245;
    };

    class NBCBootsBase: Clothing {
        radiationProtection = 0.045;
    };

    class NBCJacketBase: Clothing {
        radiationProtection = 0.290;
    };
    
    class GasMask: Clothing
    {
        radiationProtection = 0.31;
    };

    class GasMask_Filter: Inventory_Base
    {
        radiationProtection = 0.29;
    };
    
    class BallisticHelmet_ColorBase: Clothing
    {
        meleeProtection = 0.5;
        firearmProtection = 0.35;
    };

    class ZSh3PilotHelmet: Clothing
    {
        meleeProtection = 0.5;
        firearmProtection = 0.0;
    };

    class ConstructionHelmet_ColorBase: Clothing
    {
        meleeProtection = 0.5;
        firearmProtection = 0.0;
    };

    class MotoHelmet_ColorBase: Clothing
    {
        meleeProtection = 0.8;
        firearmProtection = 0.0;
    };

    class DarkMotoHelmet_ColorBase: Clothing
    {
        meleeProtection = 0.8;
        firearmProtection = 0.0;
    };

    class TankerHelmet: Clothing
    {
        meleeProtection = 0.5;
        firearmProtection = 0.0;
    };

    class GorkaHelmet: Clothing
    {
        meleeProtection = 0.6;
        firearmProtection = 0.25;
    };

    class FirefightersHelmet_ColorBase: Clothing
    {
        meleeProtection = 0.5;
        firearmProtection = 0.0;
    };

    class SkateHelmet_ColorBase: Clothing
    {
        meleeProtection = 0.5;
        firearmProtection = 0.0;
    };

    class Ssh68Helmet: Clothing
    {
        meleeProtection = 0.5;
        firearmProtection = 0.15;
    };

    class DirtBikeHelmet_ColorBase: Clothing
    {
        meleeProtection = 0.8;
        firearmProtection = 0.0;
    };

    class HockeyHelmet_ColorBase: Clothing
    {
        meleeProtection = 0.8;
        firearmProtection = 0.0;
    };

    class Mich2001Helmet: Clothing
    {
        meleeProtection = 0.7;
        firearmProtection = 0.35;
    };
    
    class BandageDressing: Inventory_Base
    {
        medBloodStop=2;
        medicalItem=1;
    };

    class Bandana_ColorBase: Clothing
    {
        medBloodStop=2;
    };

    class Rag: Inventory_Base
    {
        medBloodStop=2;
        canBeSplit = 1;
        varQuantityInit = 1.0;
        varQuantityMin = 0.0;
        varQuantityMax = 10.0;
        varQuantityDestroyOnMin = 1;
    };

    class SurgicalGloves_ColorBase: Clothing
    {
        medGloves=1;
        varCleannessInit=1;
        canBeDisinfected=1;
        medicalItem=1;
    };
    
    class VitaminBottle: Edible_Base
    {
        medicalItem=1;
        immunitySkillIncrement=10;
    };

    class PurificationTablets: Edible_Base
    {
        medicalItem=1;
    };

    class IodineTincture: Edible_Base
    {
        medicalItem=1;
    };

    class DisinfectantAlcohol: Edible_Base
    {
        medicalItem=1;
    };

    class DisinfectantSpray: Edible_Base
    {
        medicalItem=1;
    };

    class SalineBag: Inventory_Base
    {
        medicalItem=1;
    };

    class StartKitIV: Inventory_Base
    {
        medicalItem=1;
    };

    class SalineBagIV: Inventory_Base
    {
        medicalItem=1;
    };

    class BloodBagEmpty: Inventory_Base
    {
        medicalItem=1;
    };

    class BloodBagFull: Inventory_Base
    {
        medicalItem=1;
    };

    class BloodBagIV: Inventory_Base
    {
        medicalItem=1;
    };

    class BloodTestKit: Inventory_Base
    {
        medicalItem=1;
    };
};