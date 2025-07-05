// <copyright file="TerjeStartScreenMenu.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenMenu : TerjeScriptedMenu
{
	private ref TerjeStartScreenParams m_parameters = null;
	private ref TerjeWidgetImage m_backgroundImage = null;
	private ref TerjeWidgetMultitab m_multitab = null;
	private ref TerjeWidgetText m_loading = null;
	
	bool HasTerjeParams()
	{
		return (m_parameters != null);
	}
	
	void SetTerjeParams(TerjeStartScreenParams params)
	{
		if (params == null)
		{
			return;
		}
		
		if (params.GetActualContext() == null)
		{
			return;
		}
		
		if (m_backgroundImage != null && params.m_background != "")
		{
			m_backgroundImage.SetColor(ARGB(255, 255, 255, 255));
			m_backgroundImage.SetImage(params.m_background);
		}
		
		if (m_loading != null)
		{
			m_loading.Show(true);
		}
		
		m_parameters = params;
		PushCommand(new TerjeWidgetCommand_StartScreenNextPageRes());
	}
	
	override void OnInit()
	{
		super.OnInit();	
		
		DestroyAllChildren();
		m_backgroundImage = CreateRootBackgroundWidget();
		m_loading = CreateRootLoadingWidget();
		m_multitab = CreateRootMultitabWidget();
		GetTerjeRPC().RegisterHandler("startscreen.apply.callback", this, "OnTerjeStartScreenApplyCallback");
	}
	
	override void OnShow()
	{
		super.OnShow();
		if (m_multitab != null)
		{
			m_multitab.Show(false);
		}
		
		if (m_loading != null)
		{
			m_loading.Show(true);
		}
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		TerjeStartScreenContextBase pageContext;
		TerjeStartScreenPageBase pageWidget;
		if (command.IsInherited(TerjeWidgetCommand_StartScreenNextPageReq))
		{
			if (m_parameters != null && m_parameters.GetActualContext() != null)
			{
				// Close actual page
				m_multitab.Show(false);
				m_loading.Show(true);
				pageContext = m_parameters.GetActualContext();
				pageWidget = TerjeStartScreenPageBase.Cast(m_multitab.GetContentByName(pageContext.GetPageName()));
				if (pageWidget != null)
				{
					pageWidget.m_NextPageCallback = null;
					pageWidget.InitOutputContext(pageContext);
					
					TerjeStreamRpc terjeRpc;
					GetTerjeRPC().StreamToServer("startscreen.apply", terjeRpc);
					pageContext.Serialize(terjeRpc);
					terjeRpc.Flush();
				}
			}
		}
		else if (command.IsInherited(TerjeWidgetCommand_StartScreenNextPageRes))
		{
			if ((m_parameters != null) && (m_parameters.GetActualContext() != null))
			{
				// Open next page
				m_loading.Show(false);
				m_multitab.Show(true);
				pageContext = m_parameters.GetActualContext();
				pageWidget = TerjeStartScreenPageBase.Cast(m_multitab.GetContentByName(pageContext.GetPageName()));
				if (pageWidget != null)
				{
					pageWidget.m_NextPageCallback = ScriptCaller.Create(CommandNextPage);
					pageWidget.InitInputContext(pageContext);
					m_multitab.SelectTabByName(pageContext.GetPageName());
				}
			}
		}
	}
	
	override void OnClose()
	{
		m_parameters = null;
	}
	
	private void OnTerjeStartScreenApplyCallback(ParamsReadContext ctx, PlayerIdentity sender)
	{
		if (m_parameters != null)
		{
			m_parameters.Deserialize(ctx);
			
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			if (player)
			{
				player.m_terjeStartScreenParams = m_parameters;
			}
			
			PushCommand(new TerjeWidgetCommand_StartScreenNextPageRes());
		}
	}
	
	private void CommandNextPage()
	{
		PushCommand(new TerjeWidgetCommand_StartScreenNextPageReq());
	}
	
	private TerjeWidgetImage CreateRootBackgroundWidget()
	{
		TerjeWidgetImage widget = TerjeWidgetImage.Cast(CreateTerjeWidget(TerjeWidgetImage));
		if (widget != null)
		{
			widget.SetColor(ARGB(255, 0, 0, 0));
		}
		
		return widget;
	}
	
	private TerjeWidgetMultitab CreateRootMultitabWidget()
	{
		TerjeWidgetMultitab widget = TerjeWidgetMultitab.Cast(CreateTerjeWidget(TerjeWidgetMultitab));
		if (widget != null)
		{
			TerjeStartScreenPagesFactory factory();
			factory.CreateTerjeStartScreenPages(widget);
			widget.Show(false);
		}
		
		return widget;
	}
	
	private TerjeWidgetText CreateRootLoadingWidget()
	{
		TerjeWidgetText widget = TerjeWidgetText.Cast(CreateTerjeWidget(TerjeWidgetTextCentered));
		if (widget != null)
		{
			widget.SetText("#dayz_game_loading");
		}
		
		return widget;
	}
	
	override bool CanBeClosed()
	{
		return false;
	}
	
	override bool IsHudVisible()
	{
		return false;
	}
	
	override bool IsCursorVisible()
	{
		return true;
	}
	
	override bool IsInputControllerDisabled()
	{
		return true;
	}
	
	override bool IsSoundMuted()
	{
		return true;
	}
	
	override int GetBackgroundColor()
	{
		return ARGB(255, 0, 0, 0);
	}
}

class TerjeWidgetCommand_StartScreenNextPageReq : TerjeWidgetCommand
{

}

class TerjeWidgetCommand_StartScreenNextPageRes : TerjeWidgetCommand
{

}