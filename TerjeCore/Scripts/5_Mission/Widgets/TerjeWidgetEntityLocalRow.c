// <copyright file="TerjeWidgetEntityLocalRow.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetEntityLocalRow : TerjeWidgetBase
{
	protected Widget m_widgetBody;
	protected TextWidget m_widgetText;
	protected ItemPreviewWidget m_widgetRender;
	protected EntityAI m_localOwnedEntity = null;
	
	void ~TerjeWidgetEntityLocalRow()
	{
		if (m_localOwnedEntity != null)
		{
			GetGame().ObjectDelete(m_localOwnedEntity);
			m_localOwnedEntity = null;
		}
	}
	
	override void OnInit()
	{
		super.OnInit();
		m_widgetBody = GetNativeWidget().FindAnyWidget("TerjeWidgetTextPanel");
		m_widgetText = TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetText"));
		m_widgetRender = ItemPreviewWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetRender"));
	}
	
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetEntityLocalRow.layout";
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_SetEntityLocal))
		{
			TerjeWidgetCommand_SetEntityLocal setCmd = TerjeWidgetCommand_SetEntityLocal.Cast(command);
			SetLocalEntityImmediately(setCmd.m_classname, setCmd.m_title);
			return;
		}
	}
	
	TerjeWidgetBase CreateAdditionalContentWidget(typename name)
	{
		return CreateTerjeWidgetEx(name, m_widgetBody);
	}
	
	void SetLocalEntity(string classname, string title = "")
	{
		PushCommand(new TerjeWidgetCommand_SetEntityLocal(classname, title));
	}
	
	void SetLocalEntityImmediately(string classname, string title = "")
	{
		if (m_localOwnedEntity != null)
		{
			GetGame().ObjectDelete(m_localOwnedEntity);
			m_localOwnedEntity = null;
		}
		
		Object obj = GetGame().CreateObject(classname, vector.Zero, true, false, false);
		if (obj && !obj.IsInherited(EntityAI))
		{
			GetGame().ObjectDelete(obj);
			return;
		}
		
		EntityAI entity = EntityAI.Cast(obj);
		if (entity)
		{
			if (title == string.Empty)
			{
				m_widgetText.SetText(entity.GetDisplayName());
			}
			else
			{
				m_widgetText.SetText(title);
			}
			
			m_widgetRender.SetItem(entity);
			m_localOwnedEntity = entity;
		}
		
		GetNativeWidget().Update();
	}
}

class TerjeWidgetCommand_SetEntityLocal : TerjeWidgetCommand
{
	string m_classname;
	string m_title;
	
	void TerjeWidgetCommand_SetEntityLocal(string classname, string title)
	{
		m_classname = classname;
		m_title = title;
	}
}