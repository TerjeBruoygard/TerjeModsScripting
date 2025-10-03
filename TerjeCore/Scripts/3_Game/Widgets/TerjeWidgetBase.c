// <copyright file="TerjeWidgetBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetBase : ScriptedWidgetEventHandler
{
	protected Widget m_nativeWidget;
	protected ref map<string, ref Param> m_terjeUserParams = new map<string, ref Param>;
	protected ref array<ref TerjeWidgetBase> m_terjeWidgets = new array<ref TerjeWidgetBase>;
	protected ref array<ref TerjeWidgetCommand> m_terjeQueuedCommands = new array<ref TerjeWidgetCommand>;
	protected ref array<ref TerjeWidgetCommand> m_terjeActualCommands = null;
	protected ref array<ref TerjeWidgetCommand> m_terjeQueuedPostCommands = new array<ref TerjeWidgetCommand>;
	protected ref array<ref TerjeWidgetCommand> m_terjeActualPostCommands = null;
	
	void OnCreate(Widget parent)
	{
		m_nativeWidget = GetGame().GetWorkspace().CreateWidgets(GetNativeLayout(), parent);
		if (m_nativeWidget != null)
		{
			m_nativeWidget.SetHandler(this);
		}
	}
	
	void OnInit()
	{
		
	}
	
	string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetEmpty.layout";
	}
	
	Widget GetNativeWidget()
	{
		return m_nativeWidget;
	}
	
	int GetChildrenCount()
	{
		return m_terjeWidgets.Count();
	}
	
	TerjeWidgetBase GetChild(int index)
	{
		return m_terjeWidgets.Get(index);
	}
	
	void SetUserParam(string key, Param value)
	{
		m_terjeUserParams.Set(key, value);
	}
	
	Param GetUserParam(string key)
	{
		Param result;
		if (m_terjeUserParams.Find(key, result))
		{
			return result;
		}
		else
		{
			return null;
		}
	}
	
	void Show(bool state)
	{
		PushCommand(new TerjeWidgetCommand_Show(state));
	}
	
	void ShowImmediately(bool state)
	{
		GetNativeWidget().Show(state);
	}
	
	void SetColor(int color)
	{
		PushCommand(new TerjeWidgetCommand_Color(color));
	}
	
	void SetColorImmediately(int color)
	{
		GetNativeWidget().SetColor(color);
	}
	
	void SetSize(float width, float height, bool relative = false)
	{
		PushCommand(new TerjeWidgetCommand_SetSize(width, height, relative));
	}
	
	void SetSizeImmediately(float width, float height, bool relative = false)
	{
		if (relative)
		{
			GetNativeWidget().SetSize(width, height);
		}
		else
		{
			GetNativeWidget().SetScreenSize(width, height);
		}
	}
	
	void SetWidth(float width, bool relative = false)
	{
		PushCommand(new TerjeWidgetCommand_SetWidth(width, relative));
	}
	
	void SetWidthImmediately(float width, bool relative = false)
	{
		float w;
		float h;
		if (relative)
		{
			GetNativeWidget().GetSize(w, h);
			GetNativeWidget().SetSize(width, h);
		}
		else
		{
			GetNativeWidget().GetScreenSize(w, h);
			GetNativeWidget().SetScreenSize(width, h);
		}
	}
	
	void SetHeight(float height, bool relative = false)
	{
		PushCommand(new TerjeWidgetCommand_SetHeight(height, relative));
	}
	
	void SetHeightImmediately(float height, bool relative = false)
	{
		
		float w;
		float h;
		if (relative)
		{
			GetNativeWidget().GetSize(w, h);
			GetNativeWidget().SetSize(w, height);
		}
		else
		{
			GetNativeWidget().GetScreenSize(w, h);
			GetNativeWidget().SetScreenSize(w, height);
		}
	}
	
	void SetPos(float x, float y, bool relative = false)
	{
		PushCommand(new TerjeWidgetCommand_SetPos(x, y, relative));
	}
	
	void SetPosImmediately(float x, float y, bool relative = false)
	{
		if (relative)
		{
			GetNativeWidget().SetSize(x, y, relative);
		}
		else
		{
			GetNativeWidget().SetScreenSize(x, y, relative);
		}
	}
	
	void GetPos(out float x, out float y, bool relative = false)
	{
		if (relative)
		{
			GetNativeWidget().GetPos(x, y);
		}
		else
		{
			GetNativeWidget().GetScreenPos(x, y);
		}
	}
	
	void GetSize(out float w, out float h, bool relative = false)
	{
		if (relative)
		{
			GetNativeWidget().GetSize(w, h);
		}
		else
		{
			GetNativeWidget().GetScreenSize(w, h);
		}
	}
	
	float GetPosX(bool relative = false)
	{
		float x;
		float y;
		if (relative)
		{
			GetNativeWidget().GetPos(x, y);
		}
		else
		{
			GetNativeWidget().GetScreenPos(x, y);
		}
		
		return x;
	}
	
	float GetPosY(bool relative = false)
	{
		float x;
		float y;
		if (relative)
		{
			GetNativeWidget().GetPos(x, y);
		}
		else
		{
			GetNativeWidget().GetScreenPos(x, y);
		}
		
		return y;
	}
	
	float GetWidth(bool relative = false)
	{
		float w;
		float h;
		if (relative)
		{
			GetNativeWidget().GetSize(w, h);
		}
		else
		{
			GetNativeWidget().GetScreenSize(w, h);
		}
		
		return w;
	}
	
	float GetHeight(bool relative = false)
	{
		float w;
		float h;
		if (relative)
		{
			GetNativeWidget().GetSize(w, h);
		}
		else
		{
			GetNativeWidget().GetScreenSize(w, h);
		}
		
		return h;
	}
	
	protected void PushCommand(TerjeWidgetCommand command)
	{
		m_terjeQueuedCommands.Insert(command);
	}
	
	protected void PushPostCommand(TerjeWidgetCommand command)
	{
		m_terjeQueuedPostCommands.Insert(command);
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
				if (widget.GetNativeWidget())
				{
					widget.GetNativeWidget().Unlink();
				}
				
				m_terjeWidgets.Remove(index);
			}
		}
	}
	
	protected void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		if (command.IsInherited(TerjeWidgetCommand_Show))
		{
			ShowImmediately(TerjeWidgetCommand_Show.Cast(command).m_state);
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_Color))
		{
			SetColorImmediately(TerjeWidgetCommand_Color.Cast(command).m_color);
		}
		else if (command.IsInherited(TerjeWidgetCommand_SetSize))
		{
			TerjeWidgetCommand_SetSize csize = TerjeWidgetCommand_SetSize.Cast(command);
			SetSizeImmediately(csize.m_width, csize.m_height, csize.m_relative);
		}
		else if (command.IsInherited(TerjeWidgetCommand_SetWidth))
		{
			TerjeWidgetCommand_SetWidth wsize = TerjeWidgetCommand_SetWidth.Cast(command);
			SetWidthImmediately(wsize.m_width, wsize.m_relative);
		}
		else if (command.IsInherited(TerjeWidgetCommand_SetHeight))
		{
			TerjeWidgetCommand_SetHeight hsize = TerjeWidgetCommand_SetHeight.Cast(command);
			SetHeightImmediately(hsize.m_height, hsize.m_relative);
		}
		else if (command.IsInherited(TerjeWidgetCommand_SetPos))
		{
			TerjeWidgetCommand_SetPos cpos = TerjeWidgetCommand_SetPos.Cast(command);
			SetPosImmediately(cpos.m_x, cpos.m_y, cpos.m_relative);
		}
	}
	
	void OnUpdate(float timeslice)
	{
		if (m_terjeQueuedCommands.Count() > 0)
		{
			m_terjeActualCommands = m_terjeQueuedCommands;
			m_terjeQueuedCommands = new array<ref TerjeWidgetCommand>;
		
			foreach (ref TerjeWidgetCommand cmd : m_terjeActualCommands)
			{
				if (cmd != null)
				{
					OnCommand(cmd, timeslice);
				}
			}
			
			m_terjeActualCommands.Clear();
			m_terjeActualCommands = null;
		}
		
		foreach (ref TerjeWidgetBase tw : m_terjeWidgets)
		{
			if (tw != null)
			{
				tw.OnUpdate(timeslice);
			}
		}
		
		if (m_terjeQueuedPostCommands.Count() > 0)
		{
			m_terjeActualPostCommands = m_terjeQueuedPostCommands;
			m_terjeQueuedPostCommands = new array<ref TerjeWidgetCommand>;
		
			foreach (ref TerjeWidgetCommand cmdPost : m_terjeActualPostCommands)
			{
				if (cmdPost != null)
				{
					OnCommand(cmdPost, timeslice);
				}
			}
			
			m_terjeActualPostCommands.Clear();
			m_terjeActualPostCommands = null;
		}
	}
}

class TerjeWidgetCommand_Show : TerjeWidgetCommand
{
	bool m_state;
	
	void TerjeWidgetCommand_Show(bool state)
	{
		m_state = state;
	}
}

class TerjeWidgetCommand_Color : TerjeWidgetCommand
{
	int m_color;
	
	void TerjeWidgetCommand_Color(int color)
	{
		m_color = color;
	}
}

class TerjeWidgetCommand_SetSize : TerjeWidgetCommand
{
	float m_width;
	float m_height;
	bool m_relative;
	
	void TerjeWidgetCommand_SetSize(float width, float height, bool relative)
	{
		m_width = width;
		m_height = height;
		m_relative = relative;
	}
}

class TerjeWidgetCommand_SetWidth : TerjeWidgetCommand
{
	float m_width;
	bool m_relative;
	
	void TerjeWidgetCommand_SetWidth(float width, bool relative)
	{
		m_width = width;
		m_relative = relative;
	}
}

class TerjeWidgetCommand_SetHeight : TerjeWidgetCommand
{
	float m_height;
	bool m_relative;
	
	void TerjeWidgetCommand_SetHeight(float height, bool relative)
	{
		m_height = height;
		m_relative = relative;
	}
}

class TerjeWidgetCommand_SetPos : TerjeWidgetCommand
{
	float m_x;
	float m_y;
	bool m_relative;
	
	void TerjeWidgetCommand_SetPos(float x, float y, bool relative)
	{
		m_x = x;
		m_y = y;
		m_relative = relative;
	}
}