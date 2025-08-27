# TerjeModding
Developer's guide for modding Terje's mods.  

![image](../../logos/General.png)

Create your own modified items, mods, and much more using an advanced API that includes powerful tools for customization and integration.

# DESCRIPTION

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

# TerjeMedicine

Modding TerjeMedicine, the overhaul medical guide.

## MEDICINE

### HEALING PROPERTIES

#### 1. BASED ON AN ITEM

There are two options to configure it:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

###### EDITING GameOverrides.xml
This option only allows editing existing items.
```xml
<CfgVehicles>
	<Apple>
		<medAntibioticLevel>1</medAntibioticLevel>
		<medAntibioticsTimeSec>0</medAntibioticsTimeSec>
		<medAntibioticsMaxTimeSec>10</medAntibioticsMaxTimeSec>
		<terjeAddBlood>25</terjeAddBlood>
		<terjeAddHealth>-15</terjeAddHealth>
		<terjeAddShock>50</terjeAddShock>
		<overdosedIncrement>0.0</overdosedIncrement>
	</Apple>
</CfgVehicles>
```

###### CREATING Config.cpp
If you want to create custom items with specific healing functions, you will need to create a mod that contains overriding files for the base mod. In this guide, we will give **Apple** (you can choose any other item) the property of curing a cold.  

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
		medAntibioticLevel = 1;
		medAntibioticsTimeSec = 10;
		medAntibioticsMaxTimeSec=1800;
		terjeAddBlood = 25;
		terjeAddHealth = 15;
		terjeAddShock = 50;
		overdosedIncrement = 0.00;
	};
};
```
How is the total time of action of the drug calculated when the item is consumed. Let's take the following data as an example:
```css
      medAntidepresantLevel=1;     
      medAntidepresantTimer=120;
      medAntidepresantMaxTimer=1800;
```
Let's say you have an item with a volume of 1000 g/mL. A timer is calculated for each unit (quantity) of the item. When you consume 100 g/mL (100 * medAntidepresantTimer), you get a timer of 1200 seconds. If you consume 500 g/mL, the timer would be calculated as (100 * medAntidepresantTimer) = 5000 seconds. However, if the **medAntidepresantMaxTimer** parameter is specified, the maximum time will be capped at 1800 seconds, regardless of the amount consumed.  

#### 2. BASED ON A LIQUID

There are two options to configure it:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

###### EDITING GameOverrides.xml
This option only allows editing existing items.
```xml
<cfgLiquidDefinitions>
	<Vodka>
		<medAntibioticLevel>1</medAntibioticLevel>
		<medAntibioticsTimeSec>0</medAntibioticsTimeSec>
		<medAntibioticsMaxTimeSec>10</medAntibioticsMaxTimeSec>
		<terjeAddBlood>25</terjeAddBlood>
		<terjeAddHealth>-15</terjeAddHealth>
		<terjeAddShock>50</terjeAddShock>
		<overdosedIncrement>0.0</overdosedIncrement>
	</Vodka>
</cfgLiquidDefinitions>
```

###### CREATING Config.cpp
Using the **TerjeMedicine** mod, you can now add an unlimited number of liquids. Let’s examine how to create a healing effect for a specific liquid. For example, we want vodka to reduce radiation in small amounts.

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
		medAntiradLevel = 1; //Strength
		medAntiradTimer = 10; // Time of action (s)
		medAntiradMaxTimeSec=1800; //Maximum time of action (s), after consuming the entire amount.
		terjeAddBlood = 1; //Add 1 Blood per 1 ml (Negative values - reduce).
		terjeAddHealth = 2; //Add 2 Health per 1 ml (Negative values - reduce).
		terjeAddShock = 3; //Add 3 Shocks per 1 ml (Negative values - decrease).
		overdosedIncrement = 0.15; // Overdose
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
			"TerjeCore"
		};
	};
};

class CfgTerjeCustomLiquids
{
	class MyTestLiquid
	{
		displayName="MY LIQUID";
		flammability=-10;
		liquidFreezeThreshold=0;
		liquidThawThreshold=0;
		liquidBoilingThreshold=150;
		terjeRadiationCleanupForce=1;
		medAntiradLevel = 1; //Strength
		medAntiradTimer = 10; // Action Time (s)
		medAntiradMaxTimeSec=1800; //Maximum time of action (s), after consuming the full amount.
		terjeAddBlood = 1; //Add 1 Blood per 1 ml (Negative values - reduce).
		terjeAddHealth = 2; //Add 2 Health per 1 ml (Negative values - reduce).
		terjeAddShock = 3; //Add 3 Shocks per 1 ml (Negative values - decrease).
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
};
```

### INJURY PROTECTION

There are two options to configure it:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

###### EDITING GameOverrides.xml
This option only allows editing existing items.
```xml
<CfgVehicles>
	<ParamedicPants>
		<Protection>
			<melee>0.3</melee>
			<firearm>0.4</firearm>
		<Protection>
	</ParamedicPants>
</CfgVehicles>
```

###### CREATING Config.cpp
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

Protection parameters relative to real body armor.

- Level 2 (Kevlar) = 0.2
- Level 2+ (Kevlar) = 0.25
- Level 3 (SAPI III) = 0.3
- Level 3+ (SAPI III+) = 0.35
- Level 4 (SAPI IV) = 0.4
- Level 4+ (SAPI IV+) = 0.45
- Level 5 (SAPI V) = 0.5
- Level 6 (SAPI VI) = 0.6

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

### ANIMALS, ZOMBIES, MUTANTS CUSTOMIZATION

There are two options to configure it:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

###### EDITING GameOverrides.xml
This option only allows editing existing items.
```xml
<CfgVehicles>
	<Animal_UrsusArctos>
		<ignorePlayerBlock>0</ignorePlayerBlock>
		<overrideDefaultInjueries>0</overrideDefaultInjueries>
		
		<lightBleedingChance>0.1</lightBleedingChance> 
		<heavyBleedingChance>0.0</heavyBleedingChance> 
		<internalBleedingChance>0.2</internalBleedingChance> 
		
		<hematomaChance>0.1</hematomaChance> 
		
		<lightContussionChance>0.1</lightContussionChance> 
		<heavyContussionChance>0.1</heavyContussionChance> 
		
		<chemicalPoisonChance>0.1</chemicalPoisonChance> 
		<chemicalPoisonValue>1.0</chemicalPoisonValue> 
		
		<infuenzaInfectionChance>0.1</infuenzaInfectionChance> 
		<infuenzaInfectionValue>1.0</infuenzaInfectionValue> 
		
		<radiationChance>0.1</radiationChance> 
		<radiationValue>1.0</radiationValue> 
		
		<zombieVirusChance>0.1</zombieVirusChance> 
		<zombieVirusValue>1.0</zombieVirusValue> 
		
		<sepsisInfectionChance>0.1</sepsisInfectionChance> 
		<sepsisInfectionValue>1.0</sepsisInfectionValue> 
		
		<rabiesVirusChance>0.1</rabiesVirusChance> 
		<rabiesVirusValue>1.0</rabiesVirusValue> 
		
		<psiDamageChance>0.1</psiDamageChance> 
		<psiDamageValue>0.1</psiDamageValue> 
		<psiDamageTime>1.0</psiDamageTime> 
		
		<sleepDamageChance>0.1</sleepDamageChance> 
		<sleepDamageValue>0.1</sleepDamageValue> 
		<sleepDamageTime>1.0</sleepDamageTime> 
	</Animal_UrsusArctos>
</CfgVehicles>
```

###### CREATING Config.cpp
You can add (customize) any animal, zombie, mutant, additional modified damage to the player. Let's take a bear as an example - **Animal_UrsusArctos**.

1. Create config.cpp in the root of your mod **TerjeModding** on disk P. 
2. Since we are going to override an existing animal, we need to find the name of the mod (CfgPatches class) in which it is located, to write it in **requiredAddons** (the same should be done with any other animal, zombie, mutant from a third-party mod).
3. find the config.cpp file at the given path - **P:\DZ\animals_bliss\ursus_arctos\config.cpp**. (if you have it in .bin format, use DayZ Tools and convert it to .cpp).
4. Check that the animal **Animal_UrsusArctos** is present in this config.cpp, copy its name with its inheritance - **class Animal_UrsusArctos: AnimalBase**.
5. Go to the very top and copy the name of the class found in **CfgPatches**. In our case it will be - **DZ_Animals_ursus_arctos**.
6. Go to our config.cpp and we put this name - **DZ_Animals_ursus_arctos** in **class TerjeModding** in **requiredAddons** after **TerjeMedicine** with commas.
7. Then we go below to **CfgVehicles** and write our animal - **DZ_Animals_ursus_arctos**, calling **AnimalBase** which inherits this animal.
8. In the **TerjeCustomInjuries** class we need additional modifiers.

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
			"DZ_Data",
			"TerjeMedicine",
			"DZ_Animals_ursus_arctos"
		};
	};
};

class CfgVehicles
{
	class AnimalBase; //Base class Animal or Zombie: class ZombieBase;
	
	class YourCustomAnimal: AnimalBase //YourCustomAnimal or Zombie class: class YourCustomZmb: ZombieBase 
	{
		class TerjeCustomInjuries
		{
			// Ignore player's block and armor when calculating hits. 
			ignorePlayerBlock=0; // 0 = false, 1 = true
			
			// Overwrite default wounds with wounds from the configuration or supplement them.
			// If 1 - then wounds come only from this conifg. 
			// If 0 - then to the default wounds (prescribed to this or that type of animals and zombies).
			// - stab wounds, bruises, etc.) will be additionally added wounds from this config. 
			overrideDefaultInjueries=1; // 0 = false, 1 = true
			
			// Probability of bleeding on hit
			lightBleedingChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			heavyBleedingChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			internalBleedingChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%.
			
			// Probability of hematoma formation (bruise)
			hematomaChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%.
			
			// Probability of head concussion (brain contusion)
			lightContussionChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			heavyContussionChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%.
			
			// Chemical poisoning
			chemicalPoisonChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			chemicalPoisonValue=0.0; // Value 1.0 for level 1, 2.0 for level 2, etc...
			
			// Cold
			infuenzaInfectionChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			infuenzaInfectionValue=0.0; // Value 1.0 for level 1, 2.0 for level 2, etc...
			
			// Radiation (if TerjeRadiation mod is installed)
			radiationChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			radiationValue=0.0; // Value added to player's radiation buffer
			
			// Zombie Virus
			zombieVirusChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			zombieVirusValue=0.0; // Value 1.0 for level 1, 2.0 for level 2, etc...
			
			// Sepsis (blood infection)
			sepsisInfectionChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			sepsisInfectionValue=0.0; // Value 1.0 for level 1, 2.0 for level 2, etc...
			
			// Rabies
			rabiesVirusChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			rabiesVirusValue=0.0; // Value 1.0 for level 1, 2.0 for level 2, etc...
			
			// Mental state.
			psiDamageChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			psiDamageValue=0.0; // Mind damage per second (e.g. 10)
			psiDamageTime=0.0; // Action time in seconds (e.g. 5)
			
			// Sleep
			sleepDamageChance=0.0; // Chance 0.0 = 0%, 1.0 = 100%
			sleepDamageValue=0.0; // Sleep damage per second (e.g. 10)
			sleepDamageTime=0.0; // Action time in seconds (e.g. 5)
		};
	};
};
```

### ZONES

#### ZONE CONFIGURATION
The configuration of Psionic zones and Radiation zones is done in the configuration file located at:  
**profiles/TerjeSettings/ScriptableAreas/ScriptableAreasSpawner.xml**

Example configuration for 2 zones: a Radiation zone (**TerjeRadioactiveScriptableArea**) and a Psionic zone (**TerjePsionicScriptableArea**):
```xml
<Areas>
	<Area>
		<Active>1</Active>
		<Classname>TerjeRadioactiveScriptableArea</Classname>
		<Position>341.0 0.0 9401.0</Position>
		<SpawnChance>1</SpawnChance>
		<Data>
			<OuterRadius>150</OuterRadius>
			<InnerRadius>50</InnerRadius>
			<HeightMin>-100</HeightMin>
			<HeightMax>100</HeightMax>
			<Power>2.5</Power>
		</Data>
	</Area>
	<Area>
		<Active>1</Active>
		<Classname>TerjePsionicScriptableArea</Classname>
		<Position>1254.0 0.0 4401.0</Position>
		<SpawnChance>1</SpawnChance>
		<Data>
			<OuterRadius>150</OuterRadius>
			<InnerRadius>50</InnerRadius>
			<HeightMin>-100</HeightMin>
			<HeightMax>100</HeightMax>
			<Power>2.5</Power>
		</Data>
	</Area>
</Areas>
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

You can also create zones that can be spawned as items via the admin panel. Create a `config.cpp` file in the root of your **TerjeModding** mod and include the following:
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
            "TerjeCore",
            "TerjeRadiation"
        };
    };
};

class CfgVehicles
{
    class TerjePsionicScriptableArea;
    class TerjeRadioactiveScriptableArea;
	class TerjePsiCustomArea: TerjePsionicScriptableArea // Your custom Psionic zone.
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

Creating items that provide protection against Psionic and Radiation zones. For example, we will use any vanilla clothing item, such as **BomberJacket_ColorBase**.

There are two options to configure it:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

###### EDITING GameOverrides.xml
This option only allows editing existing items.
```xml
<CfgVehicles>
	<ParamedicPants>
		<Protection>
			<radiation>0.3</radiation>
			<psionic>0.4</psionic>
		<Protection>
	</ParamedicPants>
</CfgVehicles>
```

###### CREATING Config.cpp
1. Create a `config.cpp` file in the root of your **TerjeModding** mod.  
2. Since we are going to override a vanilla item, we need to find the name of the mod it is in and specify it in **requiredAddons** (the same applies to any other clothing item from a third-party mod).  
3. Locate the `config.cpp` file at the path **P:/DZ/characters/tops/config.cpp**. (If it is in `.bin` format, use DayZ Tools to convert it to `.cpp`).  
4. Search for the clothing item **BomberJacket_ColorBase** in this `config.cpp` and copy its name along with its inheritance: **class BomberJacket_ColorBase: Clothing**.  
5. Go to the top of the file and copy the name of the class located in **CfgPatches**. In our case, this will be **DZ_Characters_Vests**.  
6. Add the class name **DZ_Characters_Vests** to your `config.cpp` in **class TerjeModding** under **requiredAddons**, after **TerjeMedicine**, separated by a comma.  
7. Scroll down to **CfgVehicles** in your `config.cpp` and define your item **BomberJacket_ColorBase**, ensuring it inherits from **Clothing**.  
8. Add the required protection parameters to your clothing item. Use the example provided at [this link](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/TerjeMedicine/Protection/config.cpp#L50).

Note that the player's total protection from zone effects is cumulative across six clothing items: Gas Mask, Pants, Jacket, Gloves, Hood, and Boots.
##### Method #1 (Standard)
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
		psionic = 1.0; // Protects against Psionic zones by 100%
        };
    };
};
```

##### Method #2 (Optional, only for TerjeRadiation mod)
This method allows items to provide different levels of protection based on the strength of radiation. The calculation also factors in the influence (weight) of body parts but does not account for the protection specified in the radiation parameter.  

###### EDITING GameOverrides.xml
This option only allows editing existing items.
```xml
<CfgVehicles>
	<ParamedicPants>
		<Protection>
			<radiation>1.0</radiation> 
			<radiationValues type="[]"> 
				<i>1.0</i>
				<i>0.75</i>
				<i>0.5</i>
				<i>0.25</i>
				<i>0.0</i>
			</radiationValues>
			<radiationThresholds type="[]"> 
				<i>0.6</i>
				<i>0.7</i>
				<i>0.8</i>
				<i>0.9</i>
				<i>1.0</i>
			</radiationThresholds>
		<Protection>
	</ParamedicPants>
</CfgVehicles>
```

###### CREATING Config.cpp
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
			radiation=1.0; //This parameter is set to the standard value of 1.0, allowing clothes to accumulate radiation
			radiationValues[]={1.0,0.75,0.5,0.25,0.0}; //Defines clothing protection at different radioactive zone strength levels (1.0 = 100% protection, gradually decreasing)
			radiationThresholds[]={0.6,0.7,0.8,0.9,1.0}; //Specifies the strength levels of the radioactive zone at which the corresponding protection values apply
        };
    };
};
```

# TerjeRadiation

Protection parameters for items are described above in [PROTECTION FROM ZONES](#zone-protection).

Parameters for configuring radioactive zones are described above in [ZONE CONFIGURATION](#zone-configuration).

Check out the standard protection settings in **Config.cpp** - [link](../../../TerjeRadiation/Protection/config.cpp).

Let's set it up so that only a gas mask is required to fully protect the player

There are two options to configure it:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

###### EDITING GameOverrides.xml
This option only allows editing existing items.
```xml
<CfgTerjeScriptableProtection>
	<Radiation>
		<Feet>
			<weight>0</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Feet>
		<Legs>
			<weight>0</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Legs>
		<Body>
			<weight>0</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Body>
		<Gloves>
			<weight>0</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Gloves>
		<Headgear>
			<weight>0</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Headgear>
		<Armband>
			<weight>0</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Armband>
		<Back>
			<weight>0</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Back>
		<Mask>
			<weight>1</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Mask>
		<Eyewear>
			<weight>0</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Eyewear>
	</Radiation>
</CfgTerjeScriptableProtection>
```

###### CREATING Config.cpp
```cs
class CfgTerjeScriptableProtection
{
	class radiation
	{
		class Feet
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Legs
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Body
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Gloves
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Headgear
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Armband
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Back
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Mask
		{
			weight=1.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
		class Eyewear
		{
			weight=0.0;
			protectionBodyValues[]={};
			protectionBodyThresholds[]={};
		};
	};
};
```
## PARAMETER **weight**

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


### ADDING AN ITEM WITH STATIC RADIATION

You can add the ability to add static radiation to any item.

To create such an item, you will need to take any of your items and add the following parameter to this item - **terjeStaticRadiationValue**.
Let's take a stone as an example - **Stone** with the ability to add/remove radiation

There are two configuration options:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

##### EDITING GameOverrides.xml
This method only allows editing existing items.
```xml
<CfgVehicles>
	<Stone>
		<!-- Adds radiation to the player when the item is in the inventory -->
		<terjeStaticRadiationValue>500</terjeStaticRadiationValue>
	</Stone>
</CfgVehicles>
```
##### CREATION Config.cpp
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
			"TerjeRadiation"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class Stone: Inventory_Base
	{
		terjeStaticRadiationValue=500; // Adds radiation to the player when the item is in the inventory
		//terjeStaticRadiationValue=-500; // Removes radiation from the player when the item is in the inventory
	};
};
```


# TerjeSkills

## SKILLS AND PERKS SETTINGS

**Config.cpp** with the full list of perks and their settings - [link](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/TerjeSkills/config.cpp#L68).

To configure perks, you will need to create your own mod with a `config.cpp` file.  
Let's examine an example configuration for the skill **Athletics** and the perk **Quick Feet**.

There are two options for setting up:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

##### EDITING GameOverrides.xml
```xml
<CfgTerjeSkills>
	<Athletic>
		<!-- Enable, disable skill -->
		<enabled>1</enabled>
		
		<!-- How many perk points are awarded for each leveled-up level -->
		<perkPointsPerLevel>1</perkPointsPerLevel>
		
		<!-- How much experience is subtracted from the skill upon death -->
		<expLoseOnDeath>-500</expLoseOnDeath>
		
		<!-- Number of levels and required number of points to get the next level -->
		<levels type="[]">
			<!-- 1-10 - each value separated by commas is equal to a level, there are 10 levels in this line -->
			<i>100</i><i>200</i><i>300</i><i>400</i><i>500</i><i>700</i><i>900</i><i>1100</i><i>1300</i><i>1500</i>
			<!-- from 11 to 20 levels -->
			<i>1750</i><i>2000</i><i>2250</i><i>2500</i><i>2750</i><i>3000</i><i>3500</i><i>4000</i><i>4500</i><i>5000</i>
			<!-- from 21 to 30 levels --> 
			<i>6000</i><i>6750</i><i>7500</i><i>8250</i><i>9000</i><i>10000</i><i>11000</i><i>12000</i><i>13000</i><i>14000</i> 
			<!-- from level 31 to 40 --> 
			<i>16000</i><i>18000</i><i>20000</i><i>22000</i><i>24000</i><i>26000</i><i>28000</i><i>30000</i><i>32000</i><i>34000</i> 
			<!-- from level 41 to 50 -->
			<i>37000</i><i>40000</i><i>43000</i><i>46000</i><i>50000</i><i>55000</i><i>60000</i><i>70000</i><i>80000</i><i>100000</i>
		</levels>
		<Modifiers>
			<!-- Skill modifier that is summed up over all levels.-->
			<MaxStaminaModifier>
				<!-- Enable, disable modifier -->
				<enabled>1</enabled>
				
				<!-- Value per level -->
				<value>0.02</value>
			</MaxStaminaModifier>
		</Modifiers>
		<Perks>
			<!-- Perk name -->
			<QuickFeet>
				<!-- Enable, disable perk -->
				<enabled>1</enabled>
				
				<!-- Number of stages for perk -->
				<stagesCount>6</stagesCount>
				
				<!-- Skill levels required to obtain the next stage of perk -->
				<requiredSkillLevels type="[]">
					<i>1</i><i>10</i><i>20</i><i>30</i><i>40</i><i>45</i>
				</requiredSkillLevels>
				
				<!-- Number of perk points required to activate the corresponding stage of perk -->
				<requiredPerkPoints type="[]">
					<i>1</i><i>2</i><i>3</i><i>4</i><i>5</i><i>10</i>
				</requiredPerkPoints>
				
				<!-- Value used in scripts for each skill stage. Change only if you understand how it works. -->
				<values type="[]">
					<i>-0.05</i><i>-0.1</i><i>-0.2</i><i>-0.3</i><i>-0.4</i><i>-0.8</i>
				</values>
			</QuickFeet>
		</Perks>
	</Athletic>
</CfgTerjeSkills>
```

##### CREATING Config.cpp
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

## EXPERIENCE SETTINGS 

**Config.cpp** with sample customization of vanilla animals - [link](../../../TerjeSkills/Animals/config.cpp#L47).

To customize getting experience when killing mod animals and zombies, you will need to create a config.cpp file in the root of your **TerjeModding** mod.

There are two options for setting up:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod
###### EDITING GameOverrides.xml
This method only allows editing existing animals, zombies.
```xml
<CfgVehicles>
<Zmb_mutant> <!-- Zombie mutant -->
<!-- The number of hunting points awarded for killing. -->
<terjeOnKillHuntingExp>500</terjeOnKillHuntingExp>
<!-- The number of hunting points awarded for hitting the head. -->
<terjeOnHeadshotHuntingExp>250</terjeOnHeadshotHuntingExp>
<!-- The number of hunting points awarded for butchering. -->
<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
</Zmb_mutant>
<BlackWolf> <!-- Zombie mutant -->
<!-- Amount of hunting points awarded for a kill. -->
<terjeOnKillHuntingExp>500</terjeOnKillHuntingExp>
<!-- Amount of hunting points awarded for a headshot. -->
<terjeOnHeadshotHuntingExp>250</terjeOnHeadshotHuntingExp>
<!-- Amount of hunting points awarded for butchering. -->
<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
<!-- Toggles particles displayed when the "Pathfinder" perk is upgraded. -->
<terjeHighlightWithPathfinder>0</terjeHighlightWithPathfinder>
</BlackWolf>
<Squirrel> <!-- Squirrel -->
<!-- Hunting points awarded for a kill. -->
<terjeOnKillHuntingExp>400</terjeOnKillHuntingExp>
<!-- Hunting points awarded for a headshot. -->
<terjeOnHeadshotHuntingExp>100</terjeOnHeadshotHuntingExp>
<!-- Hunting points awarded for butchering. -->
<terjeOnButchHuntingExp>100</terjeOnButchHuntingExp>
<!-- Toggles particles displayed when the "Pathfinder" perk is upgraded. -->
<terjeHighlightWithPathfinder>1</terjeHighlightWithPathfinder>
</Squirrel>
<DeadSquirrel> <!-- Dead Squirrel (Since small animals change their class after killing -->
<!-- The amount of hunting points awarded when cutting. -->
<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
</DeadSquirrel>
<Pike> <!-- Pike -->
<!-- The amount of hunting points awarded when cutting. -->
<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
</Pike>
</CfgVehicles>
```
###### CREATING Config.cppThere are two options for setting up:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

###### EDITING GameOverrides.xml
This method only allows editing existing animals, zombies.
```xml
<CfgVehicles>
	<Zmb_mutant>
		<!-- Zombie mutant -->
		<!-- The number of hunting points awarded for killing. -->
		<terjeOnKillHuntingExp>500</terjeOnKillHuntingExp>
		
		<!-- The number of hunting points awarded for hitting the head. -->
		<terjeOnHeadshotHuntingExp>250</terjeOnHeadshotHuntingExp>
		
		<!-- The number of hunting points awarded for butchering. -->
		<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
	</Zmb_mutant>
	<BlackWolf>
		<!-- Zombie mutant -->
		<!-- Hunting points awarded for a kill. -->
		<terjeOnKillHuntingExp>500</terjeOnKillHuntingExp>
		
		<!-- Hunting points awarded for a headshot. -->
		<terjeOnHeadshotHuntingExp>250</terjeOnHeadshotHuntingExp>
		
		<!-- Hunting points awarded for butchering. -->
		<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
		
		<!-- Toggles particles displayed when the Pathfinder perk is upgraded. -->
		<terjeHighlightWithPathfinder>0</terjeHighlightWithPathfinder>
	</BlackWolf>
	<Squirrel>
		<!-- Squirrel -->
		<!-- Hunting points awarded for a kill. -->
		<terjeOnKillHuntingExp>400</terjeOnKillHuntingExp>
		
		<!-- Hunting points awarded for a headshot. -->
		<terjeOnHeadshotHuntingExp>100</terjeOnHeadshotHuntingExp>
		
		<!-- Hunting points awarded for butchering. -->
		<terjeOnButchHuntingExp>100</terjeOnButchHuntingExp>
		
		<!-- Toggles particles displayed when the Pathfinder perk is upgraded. -->
		<terjeHighlightWithPathfinder>1</terjeHighlightWithPathfinder>
	</Squirrel>
	<DeadSquirrel>
		<!-- Dead Squirrel (Since small animals change their class after being killed -->
		<!-- Hunting points awarded when butchering. -->
		<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
	</DeadSquirrel>
	<Pike>
		<!-- Pike -->
		<!-- The amount of hunting points awarded when butchering. -->
		<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
	</Pike>
</CfgVehicles>
```
###### CREATING Config.cpp

Let's look at the **config.cpp** example to add mod animals - **BlackWolf**, **Squirrel**, zombies - **Zmb_mutant** and mod fish - **Pike**

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
			"TerjeSkills",
			"Mod_BlackWolf", //Don't forget to specify the CfgPatches class of the edited animal.
			"Mod_Squirrel", //Don't forget to specify the CfgPatches of the edited animal.
			"Mod_Zmb_mutant", //Don't forget to specify the CfgPatches of the editable zombie.
			"Mod_Pike" //Don't forget to specify the class CfgPatches of the edited animal.
		};
	};
};
class CfgVehicles
{
	class AnimalBase;
	class ZombieBase;
	class Edible_Base;
	
	class Zmb_mutant: ZombieBase //Zombie mutant
	{
		terjeOnKillHuntingExp = 500; //The number of hunting points for a kill.
		terjeOnHeadshotHuntingExp = 250; //The number of hunting points awarded for a hit to the head.
		terjeOnButchHuntingExp = 250; //Number of hunting points for a kill.
	};
	class BlackWolf: AnimalBase // Black Wolf
	{
		terjeOnKillHuntingExp = 500; //Number of hunting points for killing.
		terjeOnHeadshotHuntingExp = 250; //The number of hunting points awarded for a headshot. (the last registered damage to the head is taken into account when you die).
		terjeOnButchHuntingExp = 250; //Number of hunting points awarded when cutting.
		terjeHighlightWithPathfinder = 0; //On/Off partials displayed when the "Pathfinder" perk is activated.
	};
	class Squirrel: AnimalBase //Squirrel
	{
		terjeOnKillHuntingExp = 500; //Number of hunting points for a kill.
		terjeOnHeadshotHuntingExp = 250; //The number of hunting points for a headshot. (the last registered damage to the head is taken into account when you die).
		terjeHighlightWithPathfinder = 0; //On/Off partials displayed when the "Pathfinder" perk is activated.
	};
	class DeadSquirrel: Edible_Base // Dead Squirrel (Since small animals change their class in the game after killing, you should use class Dead..... to add points for cutting. )
	{
		terjeOnButchHuntingExp = 250; //The number of hunting points awarded when cutting.
	};
	class Pike: Edible_Base // Pike
	{
		terjeOnButchFishingExp = 250; //The number of hunting points that are awarded when cutting.
	};
};
```

## CUTTING SPEED SETTINGS
You can customize the cutting speed of animals for any type of knife.

**Config.cpp** with a sample customization for vanilla knives is [link](../../../TerjeSkills/Knifes/config.cpp#L19).

To customize the cutting speed, you will need to create a config.cpp file in the root of your **TerjeModding** mod.

There are two options for customization:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod

###### EDITING GameOverrides.xml
This method only allows editing existing items.
```xml
<CfgVehicles>
	<HuntingKnife>
		<!-- Vanilla knife 5 seconds -->
		<!-- knife cutting modifier taking into account skills. -->
		<terjeSkinningTimeModifier>0.5</terjeSkinningTimeModifier>
		<!--
			That is, for example, the standard cutting time is 10 seconds.
			The fourth level of the "Fast Cutting" skill gives a modifier of 0.6, the knife also gives a modifier of 0.5.
			As a result, we get 10 * 0.6 * 0.5 = 3 sec at perk level 4. (5 seconds without skill)
		-->
	</HuntingKnife>
	<CustomKnifeFast>
		<!-- Mod knife with fast cutting ignoring skill leveling -->
		<!-- knife cutting modifier ignoring skill leveling. -->
		<terjeSkinningModifierOverride>0.1</terjeSkinningModifierOverride>
		<!--
			That is, for example, the standard cutting time is 10 seconds.
			The perk modifier is not taken into account.
			As a result, we get 10 * 0.1 = 1 sec.
		-->
	</CustomKnifeFast>
</CfgVehicles>
```
###### CREATING Config.cpp

Let's look at the **config.cpp** example to modify mod knives - **YourCustomKnife_1**, **YourCustomKnife_2**, vanilla knife - **HuntingKnife**.

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
			"TerjeSkills", 
			"DZ_Gear_Tools", 
			"DZ_Weapons_Melee_Blade", //Class CfgPatches of vanilla knives
			"CLASS CfgPatches of your mod knife"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	
	class HuntingKnife: Inventory_Base // Vanilla Bone Knife
	{
		terjeSkinningTimeModifier = 0.75; // skill-based knife cutting modifier.
		// I.e. for example the standard cutting time is 10 seconds. 
		// The fourth level of the skill "Fast cutting" gives a modifier 0.6, the knife gives another modifier 0.75. 
		// As a result we get 10 * 0.6 * 0.75 = 4.5 seconds at the 4th level of the skill. (7.5 seconds without skill)
	};
	class CustomKnife5seconds: Inventory_Base // Mod knife 5 seconds
	{
		terjeSkinningTimeModifier = 0.5; // skill-based knife cutting modifier.
		// I.e. for example the standard cutting time is 10 seconds. 
		// The fourth level of the skill "Fast cutting" gives a modifier 0.6, the knife gives another modifier 0.75. 
		// As a result we get 10 * 0.6 * 0.5 = 3 seconds at the 4th level of perk. (5 seconds without skill)
	};
	class CustomKnifeFast: Inventory_Base // Mod knife with quick cutting
	{
		terjeSkinningTimeModifierOverride = 0.1; // knife cutting modifier ignoring the skill pumping.
		// I.e. for example standard cutting time is 10 seconds. 
		// Perk modifier is not taken into account.
		// As a result we get 10 * 0.1 = 1 sec.
	};
};
```

## BOOK EXPERIENCE

You can customize the experience accrued for any perk when you read a specific book.
**Config.cpp** with vanilla knives customization sample is [link](../../../TerjeSkills/Books/config.cpp#L22).

To customize the experience accrued, you will need to create a config.cpp file in the root of your **TerjeModding** mod.

There are two options for setting up:
- by editing the **GameOverrides.xml** file in the **profiles\TerjeSettings\Core** folder
- by creating config.cpp and creating your own mod
###### EDITING GameOverrides.xml
This method only allows editing existing books.
```xml
<CfgVehicles>
	<TerjeBookAthletic1> <!-- Book class -->
		<terjeSkillId>athlc</terjeSkillId> <!-- Skill ID that the book upgrades -->
		<terjeSkillMinLevel>0</terjeSkillMinLevel> <!-- Minimum required level -->
		<terjeSkillMaxLevel>10</terjeSkillMaxLevel> <!-- Maximum allowable level -->
		<terjeSkillExpGain>300</terjeSkillExpGain> <!-- Amount of experience after reading -->
	</TerjeBookAthletic1>
</CfgVehicles>
```

###### CREATING Config.cpp
Let's look at the **config.cpp** example to change the experience of books - **TerjeBookAthletic1**, **TerjeBookAthletic5**.
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
			"TerjeSkills"
		};
	};
};

class CfgVehicles
{
	class TerjeBookBase;
	
	class TerjeBookAthletic1: TerjeBookBase //Класс книги наследуемый от TerjeBookBase
	{
		terjeSkillId="athlc"; // ID of the skill which the book pumps
		terjeSkillMinLevel=0; // Minimum required level
		terjeSkillMaxLevel=10; // Maximum allowed level
		terjeSkillExpGain=300; // Amount of experience after reading the book
	};
		class YourCustomBookAthletic10: TerjeBookBase //Your custom book inherited from TerjeBookBase
	{
		rotationFlags=1;
		displayName="#STR_TERJEMODDING_BOOK_ATHLETIC1"; //BookName
		//descriptionShort= do not add, instead of the description the experience and perk data is automatically pulled in.
		hiddenSelectionsTextures[]={"TerjeModding\Books\data\book_athletic10_co.paa"}; //Path to your book texture.
		terjeSkillId="athlc"; // The ID of the skill that the book pumps.
		terjeSkillMinLevel=30; // Minimum level required
		terjeSkillMaxLevel=50; // Maximum allowed level
		terjeSkillExpGain=10000; // Amount of experience after reading the book
	};
};
```

To create a new book you will need the skil IDs.

You can find the skill IDs in config.cpp [link](../../../TerjeSkills/Books/config.cpp#L22) with the books.

### General ID list

Skill name | ID |
|:-----------:|:-----------:|
| IMMUNITY | immunity| 
| MEDICINE | med| 
| athletics | athlc| 
| fishing | fish| 
| hunt | hunt| 
| METABOLISM | mtblsm| 
| || REMINDER || stlth| 
| strength | strng| 
| Survival | surv| 
