# 🔒 CONDITIONS

The conditions system allows you to specify in the XML configuration file the conditions for using certain elements of the mod (crafts, loadouts, starting points, etc.)

Example:
```xml
<Conditions>
	<Timeout id="myTimer1" minutes="15" />
	<SkillLevel skillId="hunt" requiredLevel="25" />
	<SkillPerk skillId="hunt" perkId="exphunter" requiredLevel="1" />
</Conditions>
```

## SUPPORTED CONDITIONS

### Timeout
This is a condition with timer, starts when the condition is applied.

> **id**: (required) - timeout string id. Should be short because it used in game DB. Uniq value is not required since it can be used to apply same timeout for a multiple s.

> **hours**: (optional) timeout in hours

> **minutes**: (optional) timeout in minutes

> **seconds**: (optional) timeout in seconds

> **hideOwnerWhenFalse**: (optional, default "0") when this attribute is set to "1", the conditioned item will be hidden for players who do not equal this condition. Used for s and respawn points.

> **displayText**: (optional) Replaces the default condition text with the one you have defined here (for both success and failed).

> **successText**: (optional) Replaces the default condition text with the one you have defined here when condition is success..

> **failText**: (optional) Replaces the default condition text with the one you have defined here when condition is failed.

```xml
<Timeout id="myTimer" hours="6" minutes="30" seconds="15" />
```



### Skill Level (requires TerjeSkills mod)
Condition of matching the player skill level
You can see the list of skill IDs in the `Skills.cfg` file in the `Enabled skills` section.
> skillId: (required) skill identifier.

> requiredLevel: (required) skill level must be equal to or higher than this value.

> **hideOwnerWhenFalse**: (optional, default "0") when this attribute is set to "1", the conditioned item will be hidden for players who do not equal this condition. Used for s and respawn points.

> **displayText**: (optional) Replaces the default condition text with the one you have defined here (for both success and failed).

> **successText**: (optional) Replaces the default condition text with the one you have defined here when condition is success..

> **failText**: (optional) Replaces the default condition text with the one you have defined here when condition is failed.

```xml
<SkillLevel skillId="hunt" requiredLevel="25" />
```



### Perk Level (requires TerjeSkills mod)
Condition of matching the player perk level
You can see the list of perk IDs in the `Skills.cfg` file in the `Enabled perks` section.
> skillId: (required) skill identifier.

> perkId: (required) perk identifier.

> requiredLevel: (required) perk level must be equal to or higher than this value to have access.

> **hideOwnerWhenFalse**: (optional, default "0") when this attribute is set to "1", the conditioned item will be hidden for players who do not equal this condition. Used for s and respawn points.

> **displayText**: (optional) Replaces the default condition text with the one you have defined here (for both success and failed).

> **successText**: (optional) Replaces the default condition text with the one you have defined here when condition is success..

> **failText**: (optional) Replaces the default condition text with the one you have defined here when condition is failed.

```xml
<SkillPerk skillId="hunt" perkId="exphunter" requiredLevel="1" />
```



### Specific Players
List of players for which this condition will be available.
You can use standart Steam ID or Steam GUID as well.

> **hideOwnerWhenFalse**: (optional, default "0") when this attribute is set to "1", the conditioned item will be hidden for players who do not equal this condition. Used for s and respawn points.

> **displayText**: (optional) Replaces the default condition text with the one you have defined here (for both success and failed).

> **successText**: (optional) Replaces the default condition text with the one you have defined here when condition is success..

> **failText**: (optional) Replaces the default condition text with the one you have defined here when condition is failed.

```xml
<SpecificPlayers hideOwnerWhenFalse="1">
    <SpecificPlayer steamGUID="76561198..." />
    <SpecificPlayer steamGUID="76561198..." />
</SpecificPlayers>
```



### Custom Condition
For advanced users – a special custom condition:
> classname: (required) the name of the class that will be used to as a custom condition handler.

> **hideOwnerWhenFalse**: (optional, default "0") when this attribute is set to "1", the conditioned item will be hidden for players who do not equal this condition. Used for s and respawn points.

> **displayText**: (optional) Replaces the default condition text with the one you have defined here (for both success and failed).

> **successText**: (optional) Replaces the default condition text with the one you have defined here when condition is success..

> **failText**: (optional) Replaces the default condition text with the one you have defined here when condition is failed.

```xml
<CustomCondition classname="MyCustomConditionHandler" />
```

Define your cutom handler in `init.c` file OR in `4_World` scripts in your mod.
```cpp
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



### Set user variable
This condition is always true, but when applied it sets the user variable to the specified value (integer) for player.
Can be used to save states between different screens of the TerjeStartScreen mod

> **name**: (required) - the name of the user variable.

> **value**: (required) - the integer value of user variable.

> **persist**: (optional) - when sets to "0" (default value) stores variable inside the player (reset on death). When sets to "1", stores variable to the character profile (not reset on death).

```xml
<Set name="myVar1" value="1" />
```



### Compare user variables
This condition compares the user variable to the specified value. 

> **name**: (required) - the name of the user variable.

> **value**: (required) - the integer value of user variable to compare.

> **persist**: (optional) - when sets to "0" (default value) reads variable from the player. When sets to "1", reads variable to the character profile.

> **hideOwnerWhenFalse**: (optional, default "0") when this attribute is set to "1", the conditioned item will be hidden for players who do not equal this condition. Used for s and respawn points.

> **displayText**: (optional) Replaces the default condition text with the one you have defined here (for both success and failed).

> **successText**: (optional) Replaces the default condition text with the one you have defined here when condition is success..

> **failText**: (optional) Replaces the default condition text with the one you have defined here when condition is failed.

```xml
<!-- The variable is equal to specified value -->
<Equal name="myVar1" value="1" />

<!-- The variable is not equal to specified value -->
<NotEqual name="myVar1" value="1" />

<!-- The variable is less then specified value -->
<LessThen name="myVar1" value="1" />

<!-- The variable is greater then specified value -->
<GreaterThen name="myVar1" value="1" />

<!-- The variable is less or equal then specified value -->
<LessOrEqual name="myVar1" value="1" />

<!-- The variable is greater or equal then specified value -->
<GreaterOrEqual name="myVar1" value="1" />
```



### Math with user variables
This condition is always true, but when applied math functions to the user variables.

> **name**: (required) - the name of the user variable.

> **value**: (required) - the integer value as argument for the math operation.

> **min**: (optional) - sets the minimum limit value to clamp the result.

> **max**: (optional) - sets the maximum limit value to clamp the result.

> **persist**: (optional) - when sets to "0" (default value) process variable inside the player (reset on death). When sets to "1", process variable in the character profile (not reset on death).

```xml
<!-- Sum variable and value (myVar1 + 1) -->
<Sum name="myVar1" value="1" />

<!-- Subtract value from variable (myVar1 - 1) -->
<Subtract name="myVar1" value="1" />

<!-- Multiply variable and value (myVar1 * 2) -->
<Multiply name="myVar1" value="2" />

<!-- Divide variable to value (myVar1 / 2) -->
<Divide name="myVar1" value="2" />
```



### Special conditions
This is a special type of conditions created specifically to handle subsets of nested conditions

> **hideOwnerWhenFalse**: (optional, default "0") when this attribute is set to "1", the conditioned item will be hidden for players who do not equal this condition. Used for s and respawn points.

> **displayText**: (optional) Replaces the default condition text with the one you have defined here (for both success and failed).

> **successText**: (optional) Replaces the default condition text with the one you have defined here when condition is success..

> **failText**: (optional) Replaces the default condition text with the one you have defined here when condition is failed.

```xml
<!-- All nested conditions should be success -->
<All successText="All is fine" failText="Shit happens...">
    <Equal name="myVar1" value="1" />
    <SkillLevel skillId="hunt" requiredLevel="25" />
</All>

<!-- Any nested condition should be success (one or multiple) -->
<Any successText="All is fine" failText="Shit happens...">
    <Equal name="myVar1" value="1" />
    <SkillLevel skillId="hunt" requiredLevel="25" />
</Any>

<!-- Only one of nested conditions should be success -->
<One successText="All is fine" failText="Shit happens...">
    <Equal name="myVar1" value="1" />
    <SkillLevel skillId="hunt" requiredLevel="25" />
</One>
```
