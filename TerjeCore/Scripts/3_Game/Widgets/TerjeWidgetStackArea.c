// <copyright file="TerjeWidgetStackArea.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetStackArea : TerjeWidgetBase
{
	override void OnInit()
	{
		super.OnInit();
		RecalculateLayout();
	}
	
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetStackArea.layout";
	}
	
	void RecalculateLayout()
	{
		PushPostCommand(new TerjeWidgetCommand_StackAreaRecalc());
	}
	
	void RecalculateLayoutImmediately()
	{
		GetNativeWidget().Update();
	}
	
	void Clear()
	{
		DestroyAllChildren();
	}
	
	TerjeWidgetBase CreateChildWidget(typename name)
	{
		return CreateTerjeWidget(name);
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_StackAreaRecalc))
		{
			RecalculateLayoutImmediately();
			return;
		}
	}
}

class TerjeWidgetCommand_StackAreaRecalc : TerjeWidgetCommand
{
}