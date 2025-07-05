## 🔒 CONDITIONS

##### Timeout
This is a condition with timer, starts when the condition is applied.
> id: (required) - timeout string id. Should be short because it used in game DB. Uniq value is not required since it can be used to apply same timeout for a multiple loadouts.
> hours: (optional) timeout in hours
> minutes: (optional) timeout in minutes
> seconds: (optional) timeout in seconds
> hideOwnerWhenFalse: (optional, default "0") when this attribute is set to "1", the conditioned item will be hidden for players who do not equal this condition. Used for loadouts and respawn points.

```xml
<Timeout id="myTimer" hours="6" minutes="30" seconds="15" />
```

##### Skill Level (requires TerjeSkills mod)
Condition of matching the player skill level
You can see the list of skill IDs in the `Skills.cfg` file in the `Enabled skills` section.
> skillId: (required) skill identifier (you can see all skills identifiers in config.cpp CfgTerjeSkills section.
> requiredLevel: (required) skill level must be equal to or higher than this value to have access to this loadout.
> hideOwnerWhenFalse: (optional, default "0") when this attribute is set to "1", the loadout will be hidden for players who do not equal this condition.

```xml
<SkillLevel skillId="hunt" requiredLevel="25" />
```

##### Perk Level (requires TerjeSkills mod)
Condition of matching the player perk level
You can see the list of perk IDs in the `Skills.cfg` file in the `Enabled perks` section.
> skillId: (required) skill identifier (you can see all skills identifiers in config.cpp CfgTerjeSkills section.
> perkId: (required) perk identifier (you can see all perks identifiers in config.cpp CfgTerjeSkills section.
> requiredLevel: (required) perk level must be equal to or higher than this value to have access to this loadout.
> hideOwnerWhenFalse: (optional, default "0") when this attribute is set to "1", the loadout will be hidden for players who do not equal this condition.

```xml
<SkillPerk skillId="hunt" perkId="exphunter" requiredLevel="1" />
```

##### Specific Players (SpecificPlayers)
List of players for which this condition will be available.
You can use standart Steam ID or Steam GUID as well.
> hideOwnerWhenFalse: (optional, default "0") when this attribute is set to "1", the loadout will be hidden for players who do not equal this condition.

```xml
<SpecificPlayers hideOwnerWhenFalse="1">
    <SpecificPlayer steamGUID="76561198..." />
    <SpecificPlayer steamGUID="76561198..." />
</SpecificPlayers>
```

##### Custom Condition (CustomCondition)  
For advanced users – a special custom condition:
> classname: (required) the name of the class that will be used to as a custom condition handler.
> hideOwnerWhenFalse: (optional, default "0") when this attribute is set to "1", the loadout will be hidden for players who do not equal this condition.

```xml
<CustomCondition classname="MyCustomConditionHandler" />
```

```cpp
// In init.c file OR in 4_World scripts in your mod.
class MyCustomConditionHandler : TerjeCustomConditionHandler
{
    override bool ProcessCondition(PlayerBase player, TerjeXmlObject condition)
    {
        return player.GetMoney() >= 100; // Check condition
    }
    
    void ApplyCondition(PlayerBase player, TerjeXmlObject condition)
    {
        player.AddMoney(-100); // Apply condition
    }
    
    override string GetConditionText(PlayerBase player, TerjeXmlObject condition)
    {
        return "Price: 100 coins"; // Condition text
    }
}
```