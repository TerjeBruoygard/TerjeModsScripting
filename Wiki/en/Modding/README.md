# TerjeModding

![image](../../logos/General.png)

Developer's guide for modding.  
Create your own modified items, mods, and much more using an advanced API that includes powerful tools for customization and integration.

## DESCRIPTION

1. This guide assumes that you already understand what modding is in the game DayZ.

2. You have already set up and installed DayZ Tools, created a P drive, unpacked the game onto it, and know how to create your own mod.

3. Throughout the text, we will reference the folder as well as the mod itself — **TerjeModding**, created on the P drive.

4. If you are modding scripts, create the following folders:
```cs
TerjeModding/scripts/3_Game
TerjeModding/scripts/4_World
TerjeModding/scripts/5_Mission
```
5. Alternatively, download a ready-made template from [this link](/Wiki/examples/TerjeModding) and place it on the P drive.

6. After making the required changes, package the resulting mod into a PBO file and place it in your client-side mod (not server-side).

7. Note that this guide assumes you create a new mod **TerjeModding** with a new `config.cpp` every time. However, you can combine multiple settings in one `config.cpp`. It is not mandatory to create a new one each time.

## TerjeMedicine

Modding the medicine mod for DayZ

### MEDICINE

#### HEALING PROPERTIES

##### 1. BASED ON AN ITEM

If you want to create custom items with specific healing functions, you will need to create a mod that contains overriding files for the base mod.  
In this guide, we will give **Apple** (you can choose any other item) the property of curing a cold.

1. Create a `config.cpp` in the root of your mod.  

2. Since we are going to override a vanilla item, we need to find the name of the mod it is in and specify it in **requiredAddons** (this is also required for any item from third-party mods).  

3. Locate the `config.cpp` file at the following path: **P:/DZ/gear/food/config.cpp**. (If it is in `.bin` format, use DayZ Tools to convert it to `.cpp`).  

4. Search the file to ensure the item **Apple** is present, and copy its name along with its inheritance: **class Apple: Edible_Base**.  

5. Go to the top of the file and copy the name of the class located in **CfgPatches**. In our case, it will be **DZ_Gear_Food**.  

6. Go to your `config.cpp` and add the name **DZ_Gear_Food** in **class TerjeModding** under **requiredAddons** after **TerjeMedicine**, separated by a comma.  

7. Next, go to **CfgVehicles** in your `config.cpp` and define your item **Apple**, ensuring it inherits from **Edible_Base**.  

8. Visit the Wiki [TerjeMedicine](/Wiki/en/Medicine/README.md), copy the required data for curing a cold, and paste it into the class of your **Apple** item.

The final `config.cpp` should look like this:
```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "DZ_Gear_Food"
        };
    };
};

class CfgVehicles
{
    class Edible_Base;
    class Apple: Edible_Base
	{
		medAntibioticLevel = 1; // Strength
		medAntibioticsTimeSec = 10; // Duration (in seconds)
		overdosedIncrement = 0.00; // Overdose increment
	}
};
```

##### 2. BASED ON A LIQUID

Using the **TerjeMedicine** mod, you can now add an unlimited number of liquids. [Learn more](/Wiki/en/Medicine/README.md). Let’s examine how to create a healing effect for a specific liquid. For example, we want vodka to reduce radiation in small amounts:

1. Complete steps 1 and 2 from Section 1.  

2. Locate the `config.cpp` file where all vanilla liquids are defined, at the path **P:/DZ/data/config.cpp**.  

3. Search for **class cfgLiquidDefinitions** and find the definition for the liquid you need. In our case, **class Vodka**. Copy both the class name and its definition.  

4. Go to the top of the `config.cpp` file and copy the name of the class located in **CfgPatches**. In our case, this will be **DZ_Data**.  

5. Add the class name **DZ_Data** to your `config.cpp` in **class TerjeModding** under **requiredAddons** after **TerjeMedicine**, separated by a comma.  

6. Next, scroll down and add **class cfgLiquidDefinitions**, defining the liquid **Vodka** within it.  

7. Visit the Wiki [TerjeMedicine](/Wiki/en/Medicine/README.md), copy the required data for radiation treatment, and paste it into the class of your liquid **Vodka**.

The resulting `config.cpp` should look like this:
```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "DZ_Data"
        };
    };
};

class cfgLiquidDefinitions
{
    class Vodka
    {
        medAntiradLevel = 1; // Strength
        medAntiradTimer = 10; // Duration (in seconds)
        overdosedIncrement = 0.15; // Overdose increment
    };
};
```

If we use our own new liquid created based on the TerjeMedicine mod, the **config.cpp** file will look like this:
```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "TerjeMedicine_Liquids"
        };
    };
};

class CfgTerjeCustomLiquids
{
    class CustomLiquids
    {
        medAntiradLevel = 1; // Strength
        medAntiradTimer = 10; // Duration (in seconds)
        overdosedIncrement = 0.15; // Overdose increment
    };
};
```

#### INJURY PROTECTION

Creating items that provide protection against stab wounds and gunshots.  
For example, we will use any vanilla clothing item, such as the base class **ParamedicPants_ColorBase**.

1. Create a `config.cpp` file in the root of your **TerjeModding** mod.  

2. Since we are going to override a vanilla item, we need to find the name of the mod it is in and specify it in **requiredAddons** (the same applies to any other clothing item from a third-party mod).  

3. Locate the `config.cpp` file at the path **P:/DZ/characters/pants/config.cpp**. (If it is in `.bin` format, use DayZ Tools to convert it to `.cpp`).  

4. Search for the clothing item **ParamedicPants_ColorBase** in this `config.cpp`, and copy its name along with its inheritance: **class ParamedicPants_ColorBase: Clothing**.  

5. Go to the top of the file and copy the name of the class located in **CfgPatches**. In our case, it will be **DZ_Characters_Pants**.  

6. Add the class name **DZ_Characters_Pants** to your `config.cpp` in **class TerjeModding** under **requiredAddons**, after **TerjeMedicine**, separated by a comma.  

7. Scroll down to **CfgVehicles** in your `config.cpp` and define your item **ParamedicPants_ColorBase**, ensuring it inherits from **Clothing**.  

8. Add the required protection parameters to your clothing item. Use the example provided at [this link](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/TerjeRadiation/Protection/config.cpp).  

```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "DZ_Characters_Pants"
        };
    };
};

class CfgVehicles
{
    class Clothing;
    class ParamedicPants_ColorBase: Clothing
    {
        class Protection
        {
		melee = 0.3; // Protects against stab wounds (approximately level 3 armor)
		firearm = 0.4; // Protects against gunshot wounds (approximately level 4 armor)
        };
    };
};
```

### ZONES

#### ZONE CONFIGURATION
The configuration of Psi-zones and Radiation zones is done in the configuration file located at:  
**DayZServer/mpmissions/your_map/terje_config/spawn_scriptable_areas.json**

Example configuration for 2 zones: a Radiation zone (**TerjeRadioactiveScriptableArea**) and a Psi-zone (**TerjePsionicScriptableArea**):
```javascript
{
    "Areas": [
        {
            "Active": 1,
            "Classname": "TerjeRadioactiveScriptableArea",
            "Position": [
                341.0,
                0.0,
                9401.0
            ],
            "SpawnChance": 1.0,
            "Data": {
                "HeightMin": -100.0,
                "HeightMax": 100.0,
                "OuterRadius": 150.0,
                "InnerRadius": 50.0,
                "Power": 2.5
            }
        },
        {
            "Active": 1,
            "Classname": "TerjePsionicScriptableArea",
            "Position": [
                1254.0,
                0.0,
                4401.0
            ],
            "SpawnChance": 1.0,
            "Data": {
                "HeightMin": -100.0,
                "HeightMax": 100.0,
                "OuterRadius": 150.0,
                "InnerRadius": 50.0,
                "Power": 2.5
            }
        }
    ]
}
```
Parameters:
* **Active** - 1/0 - Enabled/Disabled
* **Classname** - Name of the zone (specified in quotation marks)
* **Position** - Coordinates of the zone's location. Use zero for height.
* **SpawnChance** - Chance of spawning the zone, where 1.0 = 100%.
* **Data** - Configurable zone parameters.
* **HeightMin** - Minimum height of the zone. The lower boundary of the cylinder's area.
* **HeightMax** - Maximum height of the zone. The upper boundary of the cylinder's area.
* **OuterRadius** - Outer radius of the zone. Players within this radius take proportional damage based on the distance between the two radii.
* **InnerRadius** - Inner radius of the zone. Players within this radius take full damage.
* **Power** - Zone power modifier.

You can also create zones that can be spawned as items via the admin panel.  
Create a `config.cpp` file in the root of your **TerjeModding** mod and include the following:
```cs
class CfgPatches
{
    class TerjeModdingAreas
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine", 
            "TerjeCore",
            "TerjeMedicine_Areas"
        };
    };
};

class CfgVehicles
{
    class TerjePsionicScriptableArea;
    class TerjeRadioactiveScriptableArea;
	class TerjePsiCustomArea: TerjePsionicScriptableArea // Your custom Psi-zone.
	{
		scope = 2;
		terjeInnerRadius = 50.0; // Inner radius of the zone. Players inside this radius take full damage.
		terjeOuterRadius = 150.0; // Outer radius of the zone. Players inside this radius take proportional damage based on the distance between the two radii.
		terjeHeightMin = -100.0; // Minimum height of the zone. Lower boundary of the cylinder's area.
		terjeHeightMax = 100.0; // Maximum height of the zone. Upper boundary of the cylinder's area.
		terjePower = 2.0; // Zone power modifier.
	};

	class TerjeRadCustomArea: TerjeRadioactiveScriptableArea // Your custom Radiation zone.
	{
		scope = 2;
		terjeInnerRadius = 50.0; // Inner radius of the zone. Players inside this radius take full damage.
		terjeOuterRadius = 150.0; // Outer radius of the zone. Players inside this radius take proportional damage based on the distance between the two radii.
		terjeHeightMin = -100.0; // Minimum height of the zone. Lower boundary of the cylinder's area.
		terjeHeightMax = 100.0; // Maximum height of the zone. Upper boundary of the cylinder's area.
		terjePower = 2.0; // Zone power modifier.
	};
};
```

#### ZONE PROTECTION

Creating items that provide protection against Psi and Radiation zones.  
For example, we will use any vanilla clothing item, such as **BomberJacket_ColorBase**.

1. Create a `config.cpp` file in the root of your **TerjeModding** mod.  

2. Since we are going to override a vanilla item, we need to find the name of the mod it is in and specify it in **requiredAddons** (the same applies to any other clothing item from a third-party mod).  

3. Locate the `config.cpp` file at the path **P:/DZ/characters/tops/config.cpp**. (If it is in `.bin` format, use DayZ Tools to convert it to `.cpp`).  

4. Search for the clothing item **BomberJacket_ColorBase** in this `config.cpp` and copy its name along with its inheritance: **class BomberJacket_ColorBase: Clothing**.  

5. Go to the top of the file and copy the name of the class located in **CfgPatches**. In our case, this will be **DZ_Characters_Vests**.  

6. Add the class name **DZ_Characters_Vests** to your `config.cpp` in **class TerjeModding** under **requiredAddons**, after **TerjeMedicine**, separated by a comma.  

7. Scroll down to **CfgVehicles** in your `config.cpp` and define your item **BomberJacket_ColorBase**, ensuring it inherits from **Clothing**.  

8. Add the required protection parameters to your clothing item. Use the example provided at [this link](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/TerjeMedicine/Protection/config.cpp#L50).

Note that the player's total protection from zone effects is cumulative across six clothing items: Gas Mask, Pants, Jacket, Gloves, Hood, and Boots.
```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "DZ_Characters_Vests"
        };
    };
};

class CfgVehicles
{
    class Clothing;
    class BomberJacket_ColorBase: Clothing
    {
        class Protection
        {
		radiation = 0.95; // Protects against radiation zones by 95%
		psionic = 1.0; // Protects against Psi zones by 100%
        };
    };
};
```
## TerjeRadiation

Protection parameters for items are described above in [PROTECTION FROM ZONES](#protection-from-zones).

Parameters for configuring radioactive zones are described above in [ZONE CONFIGURATION](#zone-configuration).

Check out the standard protection settings in **Config.cpp** - [link](../../../TerjeRadiation/Protection/config.cpp).

Let's consider the parameters for configuring player slots, as well as the individual influence of each part of the protective suit.
```cs
class CfgTerjeScriptableProtection
{
    class radiation
    {
        class Gloves // Slot on the character
        {
            weight=0.5; // weight of each element of the protective suit
            protectionBodyValues[]={1.0,0.75,0.5,0.25,0.0}; // slot protection at different levels of radioactive zone strength (where 1.0 - 100%)
            protectionBodyThresholds[]={0.6,0.7,0.8,0.9,1.0}; // different levels of radioactive zone strength
        };
        class Mask // Slot on the character
        {
            weight=2.5; // weight of each element of the protective suit
            protectionBodyValues[]={}; // slot protection at different levels of radioactive zone strength (where 1.0 - 100%)
            protectionBodyThresholds[]={}; // different levels of radioactive zone strength
        };
    };
};
```
#### PARAMETER **weight**

Let's examine the influence (weight) on protection for all body parts:
```cs
Feet - weight=0.5;
Legs - weight=1.0;
Body - weight=1.0;
Gloves - weight=0.5;
Headgear - weight=0.5;
Mask - weight=2.5;
```
Regardless of the numbers specified in the weight, it will always equal 100% of the total protection.

Based on this, we obtain the following percentage ratios.

Total sum of weights - (0.5 + 1.0 + 1.0 + 0.5 + 0.5 + 2.5) = 6.0
Calculating percentage ratios:
```cs
Feet - 0.5 / 6.0 * 100 = 8.33%;
Legs - 1.0 / 6.0 * 100 = 16.67%;
Body - 1.0 / 6.0 * 100 = 16.67%;
Gloves - 0.5 / 6.0 * 100 = 8.33%;
Headgear - 0.5 / 6.0 * 100 = 8.33%;
Mask - 2.5 / 6.0 * 100 = 41.67%;
```
Based on these percentages, we understand that the absence of a gas mask, which has the greatest influence (weight) (41.67%), significantly reduces the overall protection level. For example, if the gas mask is absent, the total influence (weight) of the remaining suit parts will be only **58.33%** of the total protection. Thus, we can adjust which body part will have the suit piece with the greatest or least influence on calculating the overall suit protection.

#### PARAMETERS **protectionBodyValues** and **protectionBodyThresholds**

The values of `protectionBodyValues` depend on the values of `protectionBodyThresholds`. Here, `protectionBodyValues` represents the percentage of protection for a body part, and `protectionBodyThresholds` represents the strength of the zone.

Consider the body part `Gloves`:
```cs
class Gloves
{
    weight=0.5;
    protectionBodyValues[]={1.0,0.75,0.5,0.25,0.0};
    protectionBodyThresholds[]={0.6,0.7,0.8,0.9,1.0};
};
```
> At a zone strength less than or equal to 0.6 (`protectionBodyThresholds`), there will be 100% hand protection (value 1.0 in `protectionBodyValues`) from the radioactive zone.

> At a zone strength from 0.6 to 0.7 (`protectionBodyThresholds`), there will be 75% hand protection (value 0.75 in `protectionBodyValues`) from the radioactive zone.

Consider the body part `Mask`:
```cs
class Mask
{
    weight=2.5;
    protectionBodyValues[]={};
    protectionBodyThresholds[]={};
};
```
> With empty parameters `protectionBodyValues` and `protectionBodyThresholds`, protection does not apply to this body part.

**Conclusion:**

Suppose the radiation zone has a total strength of 2.5. At the edges of this zone, radiation is weaker, starting from 0.01 and increasing closer to the center. With the parameters we considered above, at the edge of the zone, contamination will not occur through the hands slot but will through the mask slot. If a gas mask is present in the mask slot, we achieve that for staying in the weakly contaminated part of the zone, we only need a gas mask (provided that other body parts also have specified `protectionBodyValues` and `protectionBodyThresholds`). However, when moving closer to the center of the zone, a full set of protective suit will be required.

## TerjeSkills

**Config.cpp** with the full list of perks and their settings - [link](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/TerjeSkills/config.cpp#L68).

To configure perks, you will need to create your own mod with a `config.cpp` file.  
Let's examine an example configuration for the skill **Athletics** and the perk **Quick Feet**.
```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeCore",
            "TerjeSkills"
        };
    };
};
class CfgTerjeSkills
{
    class Athletic
    {
        enabled = 1; // Enable or disable the skill
        perkPointsPerLevel = 1; // Points awarded per level
        expLoseOnDeath = -100; // Points deducted upon death
        levels[] = // Number of levels and required points for the next level
        {
            100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // Levels 1-10
            1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // Levels 11-20
            6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // Levels 21-30
            16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // Levels 31-40
            37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // Levels 41-50
        };
        class Modifiers
        {
            class MaxStaminaModifier // Modifier automatically upgraded per level
            {
                enabled = 1; // Enable or disable the modifier
                value = 0.02; // Amount added per level
            };
        };
        class Perks
        {
            class QuickFeet
            {
                enabled = 1; // Enable or disable the perk
                stagesCount = 6; // Number of stages for the perk
                requiredSkillLevels[] = {1, 10, 20, 30, 40, 50}; // Skill levels required for each perk stage
                requiredPerkPoints[] = {1, 2, 3, 4, 5, 10}; // Points required for each stage
                values[] = {-0.05, -0.1, -0.2, -0.3, -0.4, -0.8}; // Percentage improvement for each stage
            };
        };
    };
};
```
Key information about parameters:
- You can configure any number of skill levels using the **levels[]** array.
- Class names must not be changed under any circumstances; doing so will break the mod.
- The **values[]** parameter represents a percentage (e.g., 0.05 = 5%).
- When modifying the **values[]** parameter in perks, pay attention to the existing values. If they are negative by default, continue using negative values in subsequent configurations.
- To change the number of perk stages, adjust the **stagesCount** parameter to the desired number. However, you must also update the number of stages in the **requiredSkillLevels**, **requiredPerkPoints**, and **values[]** fields accordingly.
- The maximum number of perk stages is 10.
