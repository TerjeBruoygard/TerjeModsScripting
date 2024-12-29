# TerjeCore

This is a core mod that is used as a base dependency for all another mods developed by Terje Bruoygard.

This repository does not provide full code of the mod need to be fully functional.
That's just interfaces and simple logic that may be helpful to other developers while using this mod as a dependency in own mods.

**IMPORTANT: Please read the [LICENSE AGREEMENT](LICENSE.md) before use.**

**ANY FORM OF COPYING, MODIFICATION, REPACKING, DISTRIBUTING IS STRICTLY PROHIBITED!**


## Provided functionality

#### [TerjeStorage](/TerjeCore/Scripts/4_World/Classes/TerjeStorage.c) - Additional functions OnTerjeStoreSave and OnTerjeStoreLoad for safe storage of object parameters.

The standard functions OnStoreSave and OnStoreLoad use the stream method of writing parameters.
This means that disabling an old or adding a new mods will change the order of reading records and will inevitably lead to DB corruption (corrupted variable error).
To avoid this we suggest you to use our own context, which saves the records as a dictionary. 
This allows you to safely add or remove object parameters without worrying about corrupting the game database.

```
class MyTestItem : ItemBase
{
	float m_myTestVariable;

	override void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		super.OnTerjeStoreSave(ctx);
		ctx.WriteFloat("my_var_id", m_myTestVariable); // Save "m_myTestVariable" as "my_var_id"
	}
	
	override void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		super.OnTerjeStoreLoad(ctx);
		if (ctx.ReadFloat("my_var_id", m_myTestVariable)) // Read "my_var_id" into "m_myTestVariable"
		{
			// Success
		}
		else
		{
			m_myTestVariable = 0; // "my_var_id" not found. Using default value.
		}
	}
}
```

#### [TerjeSettings](/TerjeCore/Scripts/4_World/Plugins/PluginTerjeSettings.c) - Interface for working with mod settings in a convenient form and with a minimum code.
```
// Register settings
modded class TerjeSettingsCollection
{
	override void OnInit()
	{
		super.OnInit();
		RegisterSettingFloat("MyCategory.MySettingName", "MyCategory", "Description for the user", 0.5 /*DEFAULT VALUE*/, true /*IS SERVER SIDE ONLY (DO NOT SYNCH WITH CLIENT)*/);
	}
}

...

// Read setting from script
float mySettingValue;
if (GetTerjeSettingFloat("MyCategory.MySettingName", mySettingValue))
{
    Print("My setting value is: " + mySettingValue);
}
```

#### [TerjeRpc](/TerjeCore/Scripts/4_World/Plugins/PluginTerjeRpc.c) - Interface for easy handling of Remote Procedure Calls.
```
// Send RPC
GetTerjeRPC().SendToServer("MyModName.MyRpcName"/*ID*/, new Param1<string>("Hello")/*Arguments*/);
GetTerjeRPC().SendToClient("MyModName.MyRpcName"/*ID*/, identity/*Recepient*/, new Param1<string>("Hello")/*Arguments*/);

// Handle RPC
GetTerjeRPC().RegisterHandler("MyModName.MyRpcName"/*ID*/, this /*Instance of handler*/, "OnReceiveRPC"/*Function name of handler*/);
...
private void OnReceiveRPC(ParamsReadContext ctx, PlayerIdentity sender)
{
    Param1<string> clientData;
    if (ctx.Read(clientData))
    {
        Print("RPC RECEIVED: " + clientData.param1);
    }
}
```

#### [TerjePlayerProfile](/TerjeCore/Scripts/4_World/Types/TerjePlayerProfile.c) - Provides an interface for writing and reading record to the player profile (that are NOT reset upon death or respawn).
```
// Register profile record
modded class TerjePlayerProfile
{
    override void OnInit()
    {
        RegisterRecord("UNIQ_RECORD_NAME", new TerjeRecordInt(0 /*INIT VALUE*/, false/*IS SERVER ONLY (DONT SYNCH WITH CLIENT)*/));
    }
}

// Read and write profile record
int recordValue;
if (player.GetTerjeProfile() && player.GetTerjeProfile().GetIntValue("UNIQ_RECORD_NAME", recordValue))
{
    recordValue = recordValue + 10;
    player.GetTerjeProfile().SetIntValue("UNIQ_RECORD_NAME", recordValue);
}
```

#### [TerjeAdmintoolSupport](/TerjeCore/Scripts/4_World/Compatibility/TerjeAdmintoolSupport.c) - Interface to support compatibility of player stats with popular admintools.
```
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

#### [TerjePlayerSkillsAccessor](/TerjeCore/Scripts/4_World/Compatibility/TerjePlayerSkillsAccessor.c) - Interface for accessing the skill and perk system. 
This is just an empty interface without implementation, necessary for optional compatibility of your mods with TerjeSkills mod.
```
float perkValue;
if (player.GetTerjeSkills().GetPerkValue("skill_name", "perk_name", perkValue))
{
    Print("PERK IS ACTIVE. VALUE IS: " + perkValue);
}
else
{
    // Perk is not active.
    // Or TerjeSkills mod is not present on the server.
    Print("PERK IS NOT ACTIVE.");
}
```

*Developed by Terje Bruoygard <terjebruoygard@proton.me>*
*Copyright (c) TerjeMods. All rights reserved.*
