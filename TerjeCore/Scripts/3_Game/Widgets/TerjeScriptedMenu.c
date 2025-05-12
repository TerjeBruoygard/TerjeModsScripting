// <copyright file="TerjeScriptedMenu.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeScriptedMenu : UIScriptedMenu
{	
	protected bool m_terjeInitialized = false;
	protected ref array<ref TerjeWidgetBase> m_terjeWidgets = new array<ref TerjeWidgetBase>;
	protected ref array<ref TerjeWidgetCommand> m_terjeQueuedCommands = new array<ref TerjeWidgetCommand>;
	protected ref array<ref TerjeWidgetCommand> m_terjeActualCommands = null;
	
	override Widget Init()
	{
		if (!m_terjeInitialized)
		{
			OnCreate();
			OnInit();
			OnUpdate(0);
			m_terjeInitialized = true;
		}
		
		return layoutRoot;
	}
	
	protected void PushCommand(TerjeWidgetCommand command)
	{
		m_terjeQueuedCommands.Insert(command);
	}
	
	string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeScriptedMenu.layout";
	}
	
	Widget GetNativeWidget()
	{
		return layoutRoot;
	}
	
	void PushCommandClose()
	{
		PushCommand(new TerjeWidgetCommand_Close);
	}
	
	protected bool CanBeClosed()
	{
		return true;
	}
	
	protected bool IsHudVisible()
	{
		return true;
	}
	
	protected bool IsCursorVisible()
	{
		return true;
	}
	
	protected bool IsInputControllerDisabled()
	{
		return false;
	}
	
	protected bool IsSoundMuted()
	{
		return false;
	}
	
	protected int GetBackgroundColor()
	{
		return ARGB(0, 0, 0, 0);
	}
	
	protected string GetBackgroundImage()
	{
		return "";
	}
	
	protected void OnCreate()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets(GetNativeLayout());
		if (layoutRoot != null)
		{
			string backgroundImage = GetBackgroundImage();
			if (backgroundImage != string.Empty)
			{
				ImageWidget.Cast(layoutRoot).LoadImageFile(0, backgroundImage);
			}
			
			layoutRoot.SetColor(GetBackgroundColor());
		}
	}
	
	protected void OnInit()
	{
	
	}
	
	protected void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		
	}
	
	protected int GetChildrenCount()
	{
		return m_terjeWidgets.Count();
	}
	
	protected TerjeWidgetBase GetChild(int index)
	{
		return m_terjeWidgets.Get(index);
	}
	
	protected TerjeWidgetBase CreateTerjeWidget(typename name)
	{
		ref TerjeWidgetBase widget = TerjeWidgetBase.Cast(name.Spawn());
		if (widget)
		{
			widget.OnCreate(GetNativeWidget());
			widget.OnInit();
			m_terjeWidgets.Insert(widget);
			return widget;
		}
		
		TerjeLog_Error("Failed to crate terje widget: " + name.ToString());
		return null;
	}
	
	protected TerjeWidgetBase CreateTerjeWidgetEx(typename name, Widget parent)
	{
		ref TerjeWidgetBase widget = TerjeWidgetBase.Cast(name.Spawn());
		if (widget)
		{
			widget.OnCreate(parent);
			widget.OnInit();
			m_terjeWidgets.Insert(widget);
			return widget;
		}
		
		TerjeLog_Error("Failed to crate terje widget: " + name.ToString());
		return null;
	}
	
	protected void DestroyAllChildren()
	{
		foreach (TerjeWidgetBase child : m_terjeWidgets)
		{
			if (child && child.GetNativeWidget())
			{
				child.GetNativeWidget().Unlink();
			}
		}
		
		m_terjeWidgets.Clear();
	}
	
	protected void DestroyTerjeWidget(TerjeWidgetBase widget)
	{
		if (widget)
		{
			int index = m_terjeWidgets.Find(widget);
			if (index != -1)
			{
				m_terjeWidgets.Remove(index);
				if (widget.GetNativeWidget())
				{
					widget.GetNativeWidget().Unlink();
				}
			}
		}
	}
	
	override void OnShow()
	{
		super.OnShow();

		if (GetGame())
		{
			if (GetGame().GetPlayer() && GetGame().GetPlayer().GetInputController() != null)
			{
				GetGame().GetPlayer().GetInputController().SetDisabled(IsInputControllerDisabled());
			}
			
			if (GetGame().GetMission() != null && GetGame().GetMission().GetHud() != null)
			{
				GetGame().GetMission().GetHud().Show(IsHudVisible());
			}
			
			if (GetGame().GetUIManager() != null)
			{
				GetGame().GetUIManager().ShowCursor(IsCursorVisible());
			}
			
			if (GetGame().GetSoundScene() != null && IsSoundMuted())
			{
				GetGame().GetSoundScene().SetSoundVolume(0, 0);
			}
		}
	}

	override void OnHide()
	{
		super.OnHide();

		if (GetGame())
		{
			if (GetGame().GetPlayer() && GetGame().GetPlayer().GetInputController() != null)
			{
				GetGame().GetPlayer().GetInputController().SetDisabled(false);
			}
			
			if (GetGame().GetMission() != null && GetGame().GetMission().GetHud() != null)
			{
				GetGame().GetMission().GetHud().Show(true);
			}
			
			if (GetGame().GetUIManager() != null)
			{
				GetGame().GetUIManager().ShowCursor(false);
			}
			
			if (GetGame().GetSoundScene() != null && IsSoundMuted())
			{
				GetGame().GetSoundScene().SetSoundVolume(1, 1);
			}
		}
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (!m_terjeInitialized)
		{
			return;
		}
		
		if (CanBeClosed() && GetUApi().GetInputByID(UAUIBack).LocalPress())
		{
			Close();
			return;
		}
		
		if (m_terjeQueuedCommands.Count() > 0)
		{
			bool specialCloseCommand = false;
			m_terjeActualCommands = m_terjeQueuedCommands;
			m_terjeQueuedCommands = new array<ref TerjeWidgetCommand>;
		
			foreach (ref TerjeWidgetCommand cmd : m_terjeActualCommands)
			{
				if (cmd != null)
				{
					OnCommand(cmd, timeslice);
					
					if (cmd.IsInherited(TerjeWidgetCommand_Close))
					{
						specialCloseCommand = true;
					}
				}
			}
			
			m_terjeActualCommands.Clear();
			m_terjeActualCommands = null;
			
			if (specialCloseCommand)
			{
				Close();
				OnClose();
				return;
			}
		}
		
		OnUpdate(timeslice);
	}
	
	void OnUpdate(float timeslice)
	{
		foreach (ref TerjeWidgetBase tw : m_terjeWidgets)
		{
			if (tw != null)
			{
				tw.OnUpdate(timeslice);
			}
		}
	}
	
	void OnClose()
	{
	
	}
}

class TerjeWidgetCommand_Close : TerjeWidgetCommand
{
	void TerjeWidgetCommand_Close()
	{

	}
}