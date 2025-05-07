// <copyright file="TerjeUiManager.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeUiManager
{
	protected static ref TerjeUiManager m_instance = null;
	protected ref map<typename, ref TerjeScriptedMenu> m_terjeScriptedMenuCache = new map<typename, ref TerjeScriptedMenu>;
	protected Widget m_terjeGlobalTooltip = null;
	protected ref Timer m_terjeGlobalTimer = null;
	
	static ref TerjeUiManager GetInstance()
	{
		if (GetGame() && GetGame().IsClient())
		{
			if (m_instance == null)
			{
				m_instance = new TerjeUiManager;
				m_instance.OnInit();
			}
		}
		else
		{
			TerjeLog_Error("TerjeUiManager::GetInstance allowed only on client side.");
		}
		
		return m_instance;
	}
	
	protected void OnInit()
	{
	
	}

	ref TerjeScriptedMenu GetScriptedMenu(typename name)
	{
		ref TerjeScriptedMenu menu = null;
		if (GetGame() && GetGame().IsClient())
		{
			if (!m_terjeScriptedMenuCache.Find(name, menu) || menu == null)
			{
				menu = TerjeScriptedMenu.Cast(name.Spawn());
				m_terjeScriptedMenuCache[name] = menu;
			}
		}
		
		return menu;
	}
	
	ref TerjeScriptedMenu ShowScriptedMenu(typename name)
	{
		ref TerjeScriptedMenu menu = GetScriptedMenu(name);
		if (menu != null)
		{
			GetGame().GetUIManager().ShowScriptedMenu(menu, null);
		}
		
		return menu;
	}
	
	void HideGlobalTooltip()
	{
		if (m_terjeGlobalTimer != null)
		{
			m_terjeGlobalTimer.Stop();
			m_terjeGlobalTimer = null;
		}
		
		if (m_terjeGlobalTooltip != null)
		{
			m_terjeGlobalTooltip.Unlink();
			m_terjeGlobalTooltip = null;
		}
	}
	
	void ShowGlobalTooltip(string layout, ScriptCaller init, int x, int y, float delay = 0.25)
	{
		HideGlobalTooltip();
		
		UIScriptedMenu menu = GetGame().GetUIManager().GetMenu();
		if (menu != null && menu.GetLayoutRoot() != null)
		{
			m_terjeGlobalTooltip = GetGame().GetWorkspace().CreateWidgets(layout, menu.GetLayoutRoot());
			if (m_terjeGlobalTooltip != null)
			{
				if (init != null)
				{
					init.Invoke(m_terjeGlobalTooltip);
				}
				
				int screenWidth;
				int screenHeight;
				float tooltipWidth;
				float tooltipHeight;
				GetScreenSize(screenWidth, screenHeight);
				m_terjeGlobalTooltip.GetScreenSize(tooltipWidth, tooltipHeight);
				
				screenWidth -= 10;
				screenHeight -= 10;
				
				int rightEdge = x + tooltipWidth;
				if (rightEdge > screenWidth)
				{
					x = screenWidth - tooltipWidth;
				}
				
				int bottomEdge = y + tooltipHeight;
				if (bottomEdge > screenHeight)
				{
					y = screenHeight - tooltipHeight;
				}
				
				m_terjeGlobalTooltip.SetScreenPos(x, y);
				
				if (delay > 0)
				{
					m_terjeGlobalTooltip.Show(false);
					m_terjeGlobalTimer = new Timer();
					m_terjeGlobalTimer.Run(delay, this, "DisplayGlobalTooltip");
				}
				else
				{
					m_terjeGlobalTooltip.Show(true);
				}
			}
		}
	}
	
	protected void DisplayGlobalTooltip()
	{
		if (m_terjeGlobalTimer != null)
		{
			m_terjeGlobalTimer.Stop();
			m_terjeGlobalTimer = null;
		}
		
		if (m_terjeGlobalTooltip != null)
		{
			m_terjeGlobalTooltip.Show(true);
		}
	}
}