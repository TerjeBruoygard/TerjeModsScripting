// <copyright file="TerjeWidgetText.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetText : TerjeWidgetBase
{
	void SetText(string text)
	{
		PushCommand(new TerjeWidgetCommand_Text(text));
	}
	
	void SetTextImmediately(string text)
	{
		TextWidget.Cast(GetNativeWidget()).SetText(text);
	}

	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetText.layout";
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_Text))
		{
			SetTextImmediately(TerjeWidgetCommand_Text.Cast(command).m_text);
			return;
		}
	}
}

class TerjeWidgetTextLabel : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetTextLabel.layout";
	}
}

class TerjeWidgetTextCentered : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetTextCentered.layout";
	}
}

class TerjeWidgetTextSmall : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetTextSmall.layout";
	}
}

class TerjeWidgetTextError : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetTextError.layout";
	}
}

class TerjeWidgetCommand_Text : TerjeWidgetCommand
{
	string m_text;
	
	void TerjeWidgetCommand_Text(string text)
	{
		m_text = text;
	}
}