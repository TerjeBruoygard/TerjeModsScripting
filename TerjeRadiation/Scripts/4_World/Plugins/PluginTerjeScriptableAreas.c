// <copyright file="PluginTerjeScriptableAreas.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PluginTerjeScriptableAreas
{
	override bool GetTerjeRadiationZonePowerToRadLimit(out float result)
	{
		return GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_ZONE_POWER_TO_RAD_LIMIT, result);
	}
	
	override void WriteScriptableAreasWiki(FileHandle file)
	{
		super.WriteScriptableAreasWiki(file);
		
		FPrintln(file, "### Radioactive area (TerjeRadioactiveScriptableArea)");
		FPrintln(file, "");
		FPrintln(file, "**Classname:** TerjeRadioactiveScriptableArea");
		FPrintln(file, "");
		FPrintln(file, "This type of zone contaminate all items, vehicles, zombies, animals and players within it with radiation. The zone has a power gradient between the inner and outer radiuses.");
		FPrintln(file, "");
		FPrintln(file, "*IMPORTANT: It is recommended that the area size should be less then network synchronization bubble size (1200m by default) for the client-side logic of dosimeters works correctly.*");
		FPrintln(file, "");
		FPrintln(file, "Supported `Data` parameters:");
		FPrintln(file, "");
		FPrintln(file, "- `HeightMin`: The area is represented by a cylinder. The minimum height parameter defines the lower boundary of the area.");
		FPrintln(file, "- `HeightMax`: The area is represented by a cylinder. The maximum height parameter defines the upper boundary of the area.");
		FPrintln(file, "- `OuterRadius`: Outer radius of the area. The power will linearly lerped between the outer and inner radiuses.");
		FPrintln(file, "- `InnerRadius`: Inner radius of the area. Inside this radius, the power is constant.");
		FPrintln(file, "- `Power`: The power with which the area will affect the player. (recommended value is from 1 to 5).");
		FPrintln(file, "");
		FPrintln(file, "");
	}
	
	override void RegisterCustomProtection(ref TerjeCustomProtectionTypes customProtectionTypes)
	{
		super.RegisterCustomProtection(customProtectionTypes);
		customProtectionTypes.Insert("radiation");
	}
}