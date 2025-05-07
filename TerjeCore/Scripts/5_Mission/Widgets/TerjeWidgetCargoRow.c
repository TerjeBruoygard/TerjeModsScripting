// <copyright file="TerjeWidgetCargoRow.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetCargoRow : TerjeWidgetBase
{
	protected ref SizeToChild	m_Resizer1;
	protected ref SizeToParent	m_Resizer2;
	
	override void OnInit()
	{
		super.OnInit();
		GetNativeWidget().FindAnyWidget("CargoRowRoot").GetScript(m_Resizer1);
		GetNativeWidget().FindAnyWidget("SpacerTop").GetScript(m_Resizer2);
	}
	
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetCargoRow.layout";
	}
	
	void SetRowWidth(int width)
	{
		PushCommand(new TerjeWidgetCommand_SetCargoRowWidth(width));
	}
	
	void SetEntityIcon(EntityAI entity, int row, int col, int width, int height, bool flip)
	{
		PushCommand(new TerjeWidgetCommand_SetCargoEntity(entity, row, col, width, height, flip));
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_SetCargoRowWidth))
		{
			TerjeWidgetCommand_SetCargoRowWidth widthCmd = TerjeWidgetCommand_SetCargoRowWidth.Cast(command);
			SetRowWidthImmediately(widthCmd.m_width);
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_SetCargoEntity))
		{
			TerjeWidgetCommand_SetCargoEntity entityCmd = TerjeWidgetCommand_SetCargoEntity.Cast(command);
			SetEntityIconImmediately(entityCmd.m_entity, entityCmd.m_row, entityCmd.m_col, entityCmd.m_width, entityCmd.m_height, entityCmd.m_flip);
			return;
		}
	}
	
	void SetRowWidthImmediately(int width)
	{
		for (int i = 0; i < 10; i++)
		{
			bool show = (i < width);
			int spacerId = i + 1;
			GetNativeWidget().FindAnyWidget("Icon" + i).Show(show);
			GetNativeWidget().FindAnyWidget("Spacer" + spacerId).Show(show);
		}
		
		m_Resizer2.Refresh();
		GetNativeWidget().FindAnyWidget("CargoRowRoot").Update();	
		m_Resizer1.ResizeParentToChild();
	}
	
	TerjeWidgetEntityIcon SetEntityIconImmediately(EntityAI entity, int row, int col, int width, int height, bool flip)
	{
		TerjeWidgetEntityIcon icon = null;
		Widget cell = GetNativeWidget().FindAnyWidget("IconBody" + col);
		if (cell)
		{
			icon = TerjeWidgetEntityIcon.Cast(CreateTerjeWidgetEx(TerjeWidgetEntityIcon, cell));
			icon.SetSize(width, height, true);
			icon.SetColorable(true);
			icon.SetHighlightable(true);
			icon.DisplayTooltip(true);
			icon.SetEntity(entity, flip);
		}
		
		return icon;
	}
}

class TerjeWidgetCommand_SetCargoRowWidth : TerjeWidgetCommand
{
	int m_width;
	
	void TerjeWidgetCommand_SetCargoRowWidth(int width)
	{
		m_width = width;
	}
}

class TerjeWidgetCommand_SetCargoEntity : TerjeWidgetCommand
{
	EntityAI m_entity;
	int m_row;
	int m_col;
	int m_width;
	int m_height;
	bool m_flip;
	
	void TerjeWidgetCommand_SetCargoEntity(EntityAI entity, int row, int col, int width, int height, bool flip)
	{
		m_entity = entity;
		m_row = row;
		m_col = col;
		m_width = width;
		m_height = height;
		m_flip = flip;
	}
}