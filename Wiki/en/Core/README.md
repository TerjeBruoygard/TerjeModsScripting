# TerjeCore

This is the main mod that is used as a base dependency for all other mods.

![image](/Wiki/logos/TerjeCore.jpg)

## DESCRIPTION

* This instruction assumes that you already understand what modding in DayZ is.
* You already have DayZ Tools set up and installed, drive P created, the game unpacked onto it, and you know how to create your own mod.
* Next, we will consider the folder, as well as the name of the mod itself - **TerjeModding**, created on drive P.
* If you are modding scripts accordingly, create folders:
```cs
TerjeModding/scripts/3_Game
TerjeModding/scripts/4_World
TerjeModding/scripts/5_Mission
```
* Or download a ready-made template from [the link](/Wiki/examples/TerjeModding) - and place it on drive P.

* After making the required changes, package the resulting mod into a pbo.

## MODDING

### FUNCTIONAL FEATURES

#### [TerjeSettings](/TerjeCore/Scripts/4_World/Plugins/PluginTerjeSettings.c) - An interface for working with mod settings in a convenient way and with minimal code.

```cs
// Registering settings
modded class TerjeSettingsCollection
{
    override void OnInit()
    {
        super.OnInit();
        RegisterSettingFloat("MyCategory.MySettingName", "MyCategory", "Description for the user", 0.5 /*DEFAULT VALUE*/, true /*SERVER-SIDE ONLY (NOT SYNCHRONIZED WITH CLIENT).*/);
    }
}

...

// Reading settings from the script
float mySettingValue;
if (GetTerjeSettingFloat("MyCategory.MySettingName", mySettingValue))
{
    Print("My setting value is: " + mySettingValue);
}
```

#### [TerjeRpc](/TerjeCore/Scripts/4_World/Plugins/PluginTerjeRpc.c) - An interface for convenient work with Remote Procedure Calls (RPC).

```cs
// Sending RPC
GetTerjeRPC().SendToServer("MyModName.MyRpcName"/*ID*/, new Param1<string>("Hello")/*Argument*/);
GetTerjeRPC().SendToClient("MyModName.MyRpcName"/*ID*/, identity/*Recipient*/, new Param1<string>("Hello")/*Argument*/);

// Handling RPC
GetTerjeRPC().RegisterHandler("MyModName.MyRpcName"/*ID*/, this /*Handler instance*/, "OnReceiveRPC"/*Handler function name*/);

private void OnReceiveRPC(ParamsReadContext ctx, PlayerIdentity sender)
{
    Param1<string> clientData;
    if (ctx.Read(clientData))
    {
        Print("RPC RECEIVED: " + clientData.param1);
    }
}
```

#### [TerjePlayerProfile](/TerjeCore/Scripts/4_World/Types/TerjePlayerProfile.c) - Provides an interface for writing and reading data in the player's profile (which does NOT reset after death or respawn).

```cs
// Registering profile data
modded class TerjePlayerProfile
{
    override void OnInit()
    {
        RegisterRecord("UNIQ_RECORD_NAME", new TerjeRecordInt(0 /*INIT VALUE*/, false/*SERVER-SIDE ONLY (NOT SYNCHRONIZED WITH CLIENT).*/));
    }
}

// Reading and writing profile data
int recordValue;
if (player.GetTerjeProfile() && player.GetTerjeProfile().GetIntValue("UNIQ_RECORD_NAME", recordValue))
{
    recordValue = recordValue + 10;
    player.GetTerjeProfile().SetIntValue("UNIQ_RECORD_NAME", recordValue);
}
```

#### [TerjeAdmintoolSupport](/TerjeCore/Scripts/4_World/Compatibility/TerjeAdmintoolSupport.c) - An interface for supporting player statistics compatibility with popular administration tools.

```cs
modded class TerjeAdmintoolSupport
{
    override void OnInit()
    {
        super.OnInit();
        RegisterPlayerStat(new TerjeAdmintoolSupport_MyCustomStat("MyStatID", "Display Name", "PATH TO ICON", 0/*MIN VALUE*/, 100/*MAX VALUE*/));
    }
}

class TerjeAdmintoolSupport_MyCustomStat : TerjeAdmintoolSupport_PlayerStat
{
    override float GetValue(PlayerBase player)
    {
        return player.GetMyCustomParameter();
    }
    
    override void SetValue(PlayerBase player, float value)
    {
        player.SetMyCustomParameter(value);
    }
};
```

#### [TerjePlayerSkillsAccessor](/TerjeCore/Scripts/4_World/Classes/TerjePlayerSkillsAccessor.c) - An interface for accessing the skill and perk system.

```cs
float perkValue;
if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("skill_name", "perk_name", perkValue))
{
    Print("PERK IS ACTIVE. VALUE IS: " + perkValue);
}
else
{
    // Perk is not active.
    // Or the TerjeSkills mod is not present on the server.
    Print("PERK IS NOT ACTIVE.");
}
```

### CREATING A NEW LIQUID

Thanks to this mod, the vanilla limitation on creating liquids in the amount of 32 (since the vanilla liquid system is hard-coded into a bitmask) is removed. Now you can create new types of liquids without fear of conflicts with other mods.

#### Creating a liquid named - **MeatSoup**.

Create a config.cpp file
```cs
class CfgPatches
{
    class TerjeModding_Liquids
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
    class MeatSoup
    {
        displayName="#STR_TERJEMED_MEATSOUP_WATER"; //Name of the liquid
        flammability=-10; //Flammability
        liquidFreezeThreshold=0; //Liquid freeze threshold
        liquidThawThreshold=0; //Liquid thaw threshold
        liquidBoilingThreshold=150; //Liquid boiling threshold
        class Nutrition
        {
            fullnessIndex=1; //Fullness index
            energy=-5; //Amount of food added per 100 ml of liquid.
            water=5; //Amount of water added per 100 ml of liquid.
            nutritionalIndex=75; //Nutritional value index
            toxicity=0; //Toxicity
            digestibility=2; //Digestibility
            agents=0; //Agents
        };
    };
};

class CfgVehicles
{
    class CanisterGasoline;

    class CanisterWithMeatSoup : CanisterGasoline
    {
        varTerjeCustomLiquidTypeInit="MeatSoup"; // <= Set custom liquid as init liquid for your item.
    };
};
```

#### Functions for Working with Liquids:

Get the name of the liquid (string) - **GetTerjeLiquidClassname();**
```cs
    // Example usage:
    void MyTestFunction(ItemBase item)
    {
        string liquidClass = item.GetTerjeLiquidClassname();
        Print("My liquid is " + liquidClass);
    }
```
Set the liquid type - **SetLiquidType();**
```cs
    // Example usage:
    void FillMyTestContainer(ItemBase item, float amount)
    {
        item.SetTerjeLiquidClassname("MeatSoup"); // Set liquid type
        item.SetQuantity(amount); // Set its volume
    }
```
