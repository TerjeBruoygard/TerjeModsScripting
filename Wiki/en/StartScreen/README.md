# Terje Start Screen

## DESCRIPTION

This FAQ is intended for DayZ server admins configuring the **Terje Start Screen** mod. All configuration files are located in the `TerjeSettings` folder.

## CONFIG FILE STRUCTURE

```
TerjeSettings/
├── StartScreen.cfg         // Main mod settings
├── Core.cfg                // TerjeCore settings
└── StartScreen/
    ├── General.xml         // UI settings
    ├── Faces.xml           // Character faces
    ├── Loadouts.xml        // Starting gear loadouts
    └── Respawns.xml        // Spawn points
```

## Main Config File – StartScreen.cfg

### 🛡️ Player Safety Settings During Character Creation

```cfg
StartScreen.OnActiveGodMode = false;        // God mode (DISABLED for admin tool compatibility)
StartScreen.OnActiveIgnoreDamage = true;    // Ignore damage
StartScreen.OnActiveInvisible = true;       // Make player invisible
StartScreen.OnActiveNoClip = true;          // Disable collisions
StartScreen.OnActiveNoTargeting = true;     // AI can't target player
StartScreen.OnActiveFreezePos = true;       // Freeze player movement
StartScreen.OnActiveDisableSimulation = true;  // Disable player simulation
StartScreen.OnActiveDisableTemperature = true; // Disable temperature
StartScreen.OnActiveSafePos = true;         // Teleport to safe location
StartScreen.TeleportSafePos = "0 1000 0";   // Safe location coordinates
```

**⚠️ IMPORTANT:** `OnActiveGodMode` is disabled by default due to conflicts with admin tools like COT.

### 👤 Name Selection Page Settings

```cfg
StartScreen.NamePageEnabled = true;                     // Enable name entry page
StartScreen.DisplayPlayerNamesMode = 0;                 // Player name display mode
StartScreen.NamePageLengthMin = 3;                      // Minimum name length
StartScreen.NamePageLengthMax = 16;                     // Maximum name length
```

**Name Display Modes:**
- `-1` - disabled  
- `0` - always  
- `1` - only dead players  
- `2` - when the face is visible  
- `3` - dead players when face is visible  

### 🗺️ Other Settings

```cfg
StartScreen.FacePageEnabled = true;                     // Enable face selection
StartScreen.SkillsPageEnabled = true;                   // Enable skills selection (requires TerjeSkills)
StartScreen.SkillsPagePoints = 10;                      // Points available for distribution
StartScreen.LoadoutPageEnabled = true;                  // Enable gear selection
StartScreen.MapPageEnabled = true;                      // Enable spawn point selection
StartScreen.MapPageAttempts = 8;                        // Number of attempts to find a safe location
StartScreen.OverviewPageEnabled = true;                 // Enable character management page
StartScreen.OverviewPageAllowDeletion = true;           // Allow character deletion
StartScreen.AllowProfileDeletion = true;                // Allow profile deletion
```

### 💀 Souls System

```cfg
StartScreen.SoulsEnabled = true;                        // Enable souls system
StartScreen.SoulsMaxCount = 7;                          // Maximum number of souls
StartScreen.SoulsAutoDelete = true;                     // Auto-delete profile at 0 souls
StartScreen.SoulsNotifications = true;                  // Show soul change notifications
StartScreen.SoulsDisplayBadge = false;                  // Show soul badge on HUD
StartScreen.SoulsInitCount = 3;                         // Initial soul count

// Souls from kills
StartScreen.SoulsOnKillPlayerCount = 1;                 // Souls per player kill
StartScreen.SoulsOnKillPlayerChance = 1;                // Chance to gain souls (0–1)
StartScreen.SoulsOnKillAiCount = 1;                     // Souls per AI kill
StartScreen.SoulsOnKillAiChance = 0.25;                 // Chance to gain souls
StartScreen.SoulsOnKillZombieCount = 1;                 // Souls per zombie kill
StartScreen.SoulsOnKillZombieChance = 0.01;             // Chance to gain souls
StartScreen.SoulsOnKillAnimalCount = 1;                 // Souls per animal kill
StartScreen.SoulsOnKillAnimalChance = 0.05;             // Chance to gain souls

// Souls for survival
StartScreen.SoulsLongSurviveTime = 14400;               // Survival time in seconds (4 hours)
StartScreen.SoulsLongSurviveCount = 1;                  // Souls gained for long survival
StartScreen.SoulsLongSurviveChance = 1;                 // Chance to gain souls
StartScreen.SoulsGainTimeout = -1;                      // Gain timeout (-1 = disabled)
```

## XML Configuration Files

### 📋 General.xml

```xml
<General>
    <!-- Path to background image -->
    <BackgroundImage value="Gui/textures/loading_screens/loading_screen_3_co.edds"/>
    
    <!-- Allowed characters for names (default: Latin letters only) -->
    <NamePageFilter value="ABCDEFGHIJKLMNOPQRSTUVWXYZ"/>
</General>
```

### 👥 Faces.xml

```xml
<Faces>
    <!-- You can use your own character icons -->
    <Face classname="SurvivorM_Mirek" icon="TerjeStartScreen/Faces/SurvivorM_Mirek.paa" />
    <Face classname="SurvivorF_Eva" icon="TerjeStartScreen/Faces/SurvivorF_Eva.paa" />
    <!-- ... other faces -->
</Faces>
```

### 🎒 LOADOUTS.XML CONFIGURATION – STARTER GEAR SETS

The `Loadouts.xml` file contains lists of starter gear sets that players can choose from upon respawn, when the `StartScreen.LoadoutPageEnabled` setting is enabled in `StartScreen.cfg`.

#### Basic Loadout Structure

```xml
<Loadout id="unique_identifier" displayName="Name shown to player">
    <Items>
        <!-- List of items in this loadout -->
    </Items>
    <Conditions>
        <!-- Access conditions for this loadout (optional) -->
    </Conditions>
</Loadout>
```

**Required parameters:**
- `id` – unique identifier for the loadout; must be short and unique
- `displayName` – loadout name shown to the player in the interface. You can use a key from `stringtable.csv` for localization

#### 📦 ITEMS

##### Basic Item

Each individual item can recursively contain other items.

```xml
<Item classname="TShirt_Red" 
      displayName="Red T-Shirt"                 <!-- (optional) overrides item name in selection menu -->
      quantity="0.8"                            <!-- (optional) item quantity from 0 to 1 (1=100%, 0.5=50%) -->
      count="5"                                <!-- (optional) stack count -->
      health="0.75"                            <!-- (optional) item health from 0 to 1 -->
      position="@InHands"                      <!-- (optional) spawn position -->
      liquid="Water"                           <!-- (optional) liquid type from cfgLiquidDefinitions -->
      temperature="36.6"                       <!-- (optional) item temperature in Celsius -->
      foodStage="BOILED"                       <!-- (optional) food stage: RAW, BAKED, BOILED, DRIED, BURNED, ROTTEN -->
      disinfected="1"                          <!-- (optional) sterility: 0 = no, 1 = yes -->
      agents="CHOLERA,INFLUENZA"               <!-- (optional) comma-separated list of agents -->
      quickbar="1"                             <!-- (optional) quick access slot (0-9) -->
      ammoType="Ammo_762x39"                   <!-- (optional) ammo type for spawning in mag or weapon -->
      ammoCount="30"                           <!-- (optional) ammo count in mag or weapon -->
      cost="10"                                <!-- (optional) cost in points for points selector -->
/>
```

**Value ranges:**  
You can use ranges for random values:

```xml
<Item classname="Canteen" 
      quantity="0.0:1.0"                      <!-- random fill from 0% to 100% -->
      health="0.3:0.8"                        <!-- random health from 30% to 80% -->
      temperature="36.6:41.0"                 <!-- random temperature -->
      count="10:20"                           <!-- random count from 10 to 20 -->
      ammoCount="10:20"                       <!-- random ammo count -->
/>
```

**Placement positions (position):**
- `@Attachment` or the name of the attachment slot where the item will spawn
- `@Magazine` – spawn as a weapon magazine
- `@InHands` – spawn in the player's hands
- `@Cargo` – spawn in the first free inventory slot
- `@Cargo:0:3:h` – spawn in a specific inventory slot (column:row:orientation v/h)

**Agents:**
`CHOLERA, INFLUENZA, SALMONELLA, BRAIN, FOOD_POISON, CHEMICAL_POISON, WOUND_AGENT, NERVE_AGENT, HEAVYMETAL`

##### Examples of Nested Items:

```xml
<!-- Backpack with contents -->
<Item classname="FieldBackpack">
    <Item classname="BandageDressing" count="3" disinfected="1" />
    <Item classname="Morphine" />
    <Item classname="TacticalBaconCan" count="2" />
    <Item classname="WaterBottle" liquid="Water" quantity="1.0" />
</Item>

<!-- Weapon with attachments and magazine -->
<Item classname="M4A1" ammoType="Ammo_556x45Tracer" position="@InHands">
    <Item classname="M4_CQBBttstck" />                      <!-- Stock -->
    <Item classname="M4_RISHndgrd" />                       <!-- Handguard -->
    <Item classname="M4_Suppressor" />                      <!-- Suppressor -->
    <Item classname="M4_T3NRDSOptic" />                     <!-- Sight -->
    <Item classname="Mag_STANAG_60Rnd" ammoType="Ammo_556x45Tracer" ammoCount="60" />
</Item>

<!-- Boots with a knife inside -->
<Item classname="MilitaryBoots_Black">
    <Item classname="HuntingKnife" health="0.25" />
</Item>

<!-- Jacket with GPS and battery (multi-level nesting) -->
<Item classname="HuntingJacket_Brown">
    <Item classname="GPSReceiver">
        <Item classname="Battery9V" />
    </Item>
</Item>
```

#### 🎯 SELECTORS

Selectors group several items together, allowing the player to select only one item either by choice or randomly.

```xml
<Selector type="SELECTOR_TYPE" 
          displayName="Name shown to player"           <!-- (optional) selector name in UI -->
          pointsCount="25"                             <!-- (for MULTIPLE only) points amount -->
          pointsHandler="MyPointsHandler"              <!-- (for MULTIPLE only) points handler class -->
          pointsIcon="path/to/icon.paa">               <!-- (for MULTIPLE only) points icon -->
    <!-- Items to select from -->
</Selector>
```

**Selector Types:**

##### 1. RANDOM – Random selection by the server
```xml
<Selector type="RANDOM">
    <Item classname="Chemlight_Red" />
    <Item classname="Chemlight_Green" />
    <Item classname="Chemlight_Yellow" />
    <Item classname="Chemlight_White" />
</Selector>
```

##### 2. SINGLE - Player selects one item
```xml
<Selector type="SINGLE" displayName="CHOOSE A WEAPON">
    <Item classname="TShirt_Beige" health="0.6:0.8" />
    <Item classname="TShirt_Black" health="0.6:0.8" />
    <Item classname="TShirt_Blue" health="0.6:0.8" />
</Selector>
```

##### 3. MULTIPLE - Player selects multiple items with points
```xml
<Selector type="MULTIPLE" displayName="EQUIPMENT" pointsCount="20">
    <Item classname="WaterBottle" liquid="Gasoline" quantity="0.1:0.5" cost="5" displayName="Brain Fuel" />
    <Item classname="HumanSteakMeat" foodStage="BOILED" agents="BRAIN" cost="5" displayName="Breakfast" />
    <Item classname="MimeMask_Male" cost="5" />
    <Item classname="SteakKnife" cost="10" />
    <Item classname="Machete" cost="15" />
</Selector>
```

**Points Handler (pointsHandler):**  
For advanced users – a class used to determine the points amount for a specific loadout and player:

```cpp
// In the mission's init.c file
class MyPointsHandler : TerjeCustomPointsHandler
{
    override int GetPoints(PlayerBase player, string loadoutId, int selectionId)
    {
        return 25; // Return the points amount
    }
}
```

#### 🔗 ITEM GROUPS (Group)

Groups combine several items together. Can be used inside a selector to choose multiple items at once.

```xml
<Group cost="20">                                    <!-- group cost in points -->
    <Item classname="Izh43Shotgun" position="@InHands" ammoType="Ammo_12gaPellets" health="0.25" />
    <Item classname="Ammo_12gaPellets" ammoCount="4:8" />
</Group>
```

### 🔒 CONDITIONS

[CONDITIONS WIKI PAGE](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/Wiki/en/Conditions/README.md)

### 🗺️ RESPAWNS.XML CONFIGURATION – RESPAWN POINTS

The `Respawns.xml` file contains a list of respawn points that players can choose from when creating a character, provided the `StartScreen.MapPageEnabled` setting is enabled in `StartScreen.cfg`.

#### Basic Respawn Structure

```xml
<Respawn id="unique_identifier" displayName="Name shown to player">
    <Options>
        <!-- Additional respawn settings -->
    </Options>
    <Points>
        <!-- List of fixed respawn points -->
    </Points>
    <!-- OR -->
    <Objects>
        <!-- List of objects to use as respawn points -->
    </Objects>
    <Conditions>
        <!-- Access conditions for the respawn point -->
    </Conditions>
</Respawn>
```

**Required parameters:**
- `id` – unique identifier of the respawn point
- `displayName` – name shown to the player in the interface

#### 📍 RESPAWN POINTS (Points vs Objects)

##### Fixed Points (Points)  
Each individual respawn point:

```xml
<Point pos="14162.81, 12405.00" />                    <!-- position in format from https://dayz.xam.nu/ -->
<Point pos="14162.81, 12405.00" angle="180" />        <!-- with rotation angle (0-360) -->

<!-- Alternative coordinate format -->
<Point x="14162.81" y="0" z="12405.00" angle="90" />
```

##### Respawn Objects (Objects)  
Objects that the player can use as custom respawn points (sleeping bags, flags):

```xml
<Object classname="TerjeSleepingBag_Blue" />
<Object classname="TerritoryFlag" handler="MyRespawnObjectHandler" />
```

**Object Handler (handler):**  
For advanced users – allows defining additional logic and conditions for the object:

```cpp
// Example for Expansion Territory Flag
class MyRespawnObjectHandler : TerjeRespawnObjectHandler
{
    override bool SetAsRespawnObject(PlayerBase player, Object object, string respawnId)
    {
        TerritoryFlag territoryFlag = TerritoryFlag.Cast(object);
        if (territoryFlag && territoryFlag.GetTerritory() && player.GetIdentity())
        {
            return territoryFlag.GetTerritory().IsMember(player.GetIdentity().GetId());
        }
        return false;
    }
    
    override bool RespawnOnObject(PlayerBase player, Object object, string respawnId)
    {
        TerritoryFlag territoryFlag = TerritoryFlag.Cast(object);
        if (territoryFlag && territoryFlag.GetTerritory() && player.GetIdentity())
        {
            return territoryFlag.GetTerritory().IsMember(player.GetIdentity().GetId());
        }
        return false;
    }
}
```

#### ⚙️ ADDITIONAL SETTINGS (Options)

##### Safe Radii (SafeRadius)  
Sets safe radii when selecting a respawn point for the player:

```xml
<SafeRadius zombie="15"                               <!-- minimum distance to zombies -->
            animal="25"                               <!-- minimum distance to animals -->
            player="50"                               <!-- minimum distance to other players -->
            other="5"                                 <!-- minimum distance to static objects -->
/>
```

##### Map Image Preview (MapImage)  
Uses the image at the specified path as the preview:

```xml
<MapImage path="TerjeStartScreen\Textures\chernarusplus.paa" />
```

##### Map Rendering (MapRender)  
Uses a map rendering widget to display the target position as a preview:

```xml
<MapRender pos="10363.13, 2182.50"                    <!-- center position of the map -->
           x="10363.13" y="0" z="2182.50"             <!-- alternative coordinate format -->
           zoom="0.25"                                <!-- map zoom level (recommended 0.1-1.0) -->
           showPoints="always"                        <!-- display respawn points -->
           showMarker="always"                        <!-- display marker -->
           showMarkerName="1"                         <!-- show name next to marker -->
           allowInteraction="1"                       <!-- enable map interactivity -->
           markerPath="path/to/marker.paa"            <!-- path to marker icon -->
           pointsPath="path/to/dot.paa"               <!-- path to points icon -->
           activePointsColor="0xFFB40000"             <!-- active points color (ARGB) -->
           inactivePointsColor="0xFF191919"           <!-- inactive points color (ARGB) -->
           activeMarkerColor="0xFFB40000"             <!-- active marker color (ARGB) -->
           inactiveMarkerColor="0xFF191919"           <!-- inactive marker color (ARGB) -->
/>
```

**Display parameters:**  
- `showPoints` / `showMarker`:  
  - `"never"` – never show  
  - `"active"` – show only when this set of points is active  
  - `"always"` – always show  

##### Player Stats (PlayerStats)  
The player will respawn with the following specific stats:

```xml
<PlayerStats health="100"                             <!-- player health (1-100) -->
             blood="5000"                             <!-- player blood (2500-5000) -->
             shock="0"                                <!-- player shock (0-100) -->
             energy="5000"                            <!-- player energy/food (0-5000) -->
             water="5000"                             <!-- player water (0-5000) -->
             sleep="14000"                            <!-- player sleep (0-14000, requires TerjeMedicine) -->
             mind="100"                               <!-- player mind (0-100, requires TerjeMedicine) -->
             heatComfort="0"                          <!-- heat comfort (-1 to 1) -->
             heatBuffer="30"                          <!-- heat buffer (-30 to 30) -->
/>
```

### 🔒 CONDITIONS

[CONDITIONS WIKI PAGE](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/Wiki/en/Conditions/README.md)

## Frequently Asked Questions

### ❓ How to disable specific pages on player login?

Set the corresponding parameter to `false`:
```cfg
StartScreen.NamePageEnabled = false;        // Disable name selection
StartScreen.FacePageEnabled = false;        // Disable face selection
StartScreen.SkillsPageEnabled = false;      // Disable skills selection
StartScreen.LoadoutPageEnabled = false;     // Disable loadout selection
StartScreen.MapPageEnabled = false;         // Disable respawn point selection
```

### ❓ How to change the background image?

In the file `TerjeSettings/StartScreen/General.xml`:
```xml
<BackgroundImage value="path/to/your/image.edds"/>
```

Supported formats: `.paa`, `.edds`, or imageset.

### ❓ How to add Cyrillic support in player names?

In the file `TerjeSettings/StartScreen/General.xml`:
```xml
<NamePageFilter value="ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"/>
```

### ❓ How to configure the Souls system for a hardcore server?

```cfg
StartScreen.SoulsMaxCount = 3;               // Lower maximum souls
StartScreen.SoulsInitCount = 1;              // Lower starting souls
StartScreen.SoulsOnKillZombieChance = 0.005; // Decrease soul gain chance
StartScreen.SoulsLongSurviveTime = 28800;    // Increase survival time (8 hours)
StartScreen.SoulsGainTimeout = 3600;         // Add timeout (1 hour)
```

### ❓ How to change the safe teleport location?

```cfg
StartScreen.TeleportSafePos = "X Y Z";      // Replace with desired coordinates
```

For example: `"7500 0 7500"`

### ❓ How to get coordinates for respawn points?

1. Use the website https://dayz.xam.nu/
2. Find the desired location on the map
3. Press Ctrl+C to copy the coordinates
4. Paste in the format `pos="X, Z"`

### ❓ How to create a custom points handler for loadouts?

In your mission's `init.c` file:
```cpp
class MyPointsHandler : TerjeCustomPointsHandler
{
    override int GetPoints(PlayerBase player, string loadoutId, int selectionId)
    {
        // Return points amount based on conditions
        if (loadoutId == "military")
            return player.GetLevel() * 5; // Example
        return 25; // Default
    }
}
```
