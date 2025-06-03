// <copyright file="PluginTerjeCore.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeCore extends PluginBase
{
	private ref array<string> m_submodules;
	
	override void OnInit()
	{
		m_submodules = new array<string>;
		RegisterSubmodules(m_submodules);
	}
	
	protected void RegisterSubmodules(array<string> submodules)
	{
		submodules.Insert("TerjeCore");
	}
}