// <copyright file="PluginTerjeScriptableAreas.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PluginTerjeScriptableAreas
{
	override void WriteScriptableAreasWiki(FileHandle file)
	{
		super.WriteScriptableAreasWiki(file);
		
		FPrintln(file, "### Skills experience modifier area (TerjeExperienceModScriptableArea)");
		FPrintln(file, "");
		FPrintln(file, "**Classname:** TerjeExperienceModScriptableArea");
		FPrintln(file, "**Filter**: A list of skill ids separated by comma that will be affected by this zone. (Example `hunt,fish`). Leave this field empty so that the experience modifier is applied to all skills at once.");
		FPrintln(file, "");
		FPrintln(file, "This area type overwrites the global experience modifier for all players inside the area. Use this type of area for example if you want the player to get more experience for the hunting skill in a certain place on the map. This zone is a server-side zone and does not contain client logic, so it can have absolutely any radius.");
		FPrintln(file, "");
		FPrintln(file, "Supported `Data` parameters:");
		FPrintln(file, "");
		FPrintln(file, "- `HeightMin`: The area is represented by a cylinder. The minimum height parameter defines the lower boundary of the area.");
		FPrintln(file, "- `HeightMax`: The area is represented by a cylinder. The maximum height parameter defines the upper boundary of the area.");
		FPrintln(file, "- `Radius`: Radius of the area.");
		FPrintln(file, "- `Power`: Value of experience multiplier.");
		FPrintln(file, "");
		FPrintln(file, "");
	}
}