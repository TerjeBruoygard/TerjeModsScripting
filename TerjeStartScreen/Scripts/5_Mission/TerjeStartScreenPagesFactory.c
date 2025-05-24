// <copyright file="TerjeStartScreenPagesFactory.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeStartScreenPagesFactory
{
	override void CreateTerjeStartScreenPages(TerjeWidgetMultitab multitabWidget)
	{
		super.CreateTerjeStartScreenPages(multitabWidget);
		
		multitabWidget.CreateTabWidgetEx("rules", TerjeStartScreenPageRules);
		multitabWidget.CreateTabWidgetEx("name", TerjeStartScreenPageName);
		multitabWidget.CreateTabWidgetEx("face", TerjeStartScreenPageFace);
		multitabWidget.CreateTabWidgetEx("skills", TerjeStartScreenPageSkills);
		multitabWidget.CreateTabWidgetEx("overview", TerjeStartScreenPageOverview);
		multitabWidget.CreateTabWidgetEx("loadout", TerjeStartScreenPageLoadout);
		multitabWidget.CreateTabWidgetEx("map", TerjeStartScreenPageMap);
	}
}