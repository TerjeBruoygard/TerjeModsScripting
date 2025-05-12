// <copyright file="TerjeStartScreenPageOverview.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenPageOverview : TerjeStartScreenPageBase
{
	protected bool m_blocked = true;
	
	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/PageOverview.layout";
	}
	
	override void InitInputContext(TerjeStartScreenContextBase context)
	{
		super.InitInputContext(context);
		
		TerjeStartScreenContextOverview overviewContext = TerjeStartScreenContextOverview.Cast(context);
		if (overviewContext != null)
		{
			m_blocked = false;
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenOverviewRefresh(overviewContext));
		}
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenOverviewRefresh))
		{
			OnCommandOverviewRefresh(TerjeWidgetCommand_TerjeStartScreenOverviewRefresh.Cast(command));
			return;
		}
	}
	
	protected void OnCommandOverviewRefresh(TerjeWidgetCommand_TerjeStartScreenOverviewRefresh refreshCommand)
	{
		DestroyAllChildren();
		
		TextWidget.Cast(GetNativeWidget().FindAnyWidget("CharName")).SetText(refreshCommand.m_context.m_characterName);
		
		bool showNext = (!refreshCommand.m_context.m_showSouls) || (refreshCommand.m_context.m_soulsCount > 0);
		GetNativeWidget().FindAnyWidget("NextPanel").Show(showNext);
		if (showNext)
		{
			TerjeWidgetButton nextBtn = TerjeWidgetButton.Cast(CreateTerjeWidgetEx(TerjeWidgetButton, GetNativeWidget().FindAnyWidget("NextPanelContent")));
			nextBtn.SetText("#STR_USRACT_NEXT_ACTION");
			nextBtn.OnClickEvent.Insert(OnNextPageClicked);
		}
		
		GetNativeWidget().FindAnyWidget("DeletionPanel").Show(refreshCommand.m_context.m_allowDeletion);
		if (refreshCommand.m_context.m_allowDeletion)
		{
			TerjeWidgetButtonHold delBtn = TerjeWidgetButtonHold.Cast(CreateTerjeWidgetEx(TerjeWidgetButtonHold, GetNativeWidget().FindAnyWidget("DeletionPanelContent")));
			delBtn.SetText("#STR_TERJESTARTSCREEN_OVERVIEW_DEL");
			delBtn.OnClickEvent.Insert(OnDeleteProfileClicked);
		}
		
		GetNativeWidget().FindAnyWidget("SoulsPanel").Show(refreshCommand.m_context.m_showSouls);
		if (refreshCommand.m_context.m_showSouls)
		{
			ImageWidget.Cast(GetNativeWidget().FindAnyWidget("SoulsIcon")).LoadImageFile(0, TerjePlayerSoulsAccessor.SOULS_ICON);
			TextWidget.Cast(GetNativeWidget().FindAnyWidget("SoulsCount")).SetText(refreshCommand.m_context.m_soulsCount.ToString());
			GetNativeWidget().FindAnyWidget("SoulsPanelGrid").Update();
		}
		
		GetNativeWidget().FindAnyWidget("GridSpacerPanel").Update();
	}
	
	protected void OnDeleteProfileClicked(TerjeWidgetButtonHold w)
	{
		if (!m_blocked)
		{
			m_blocked = true;
			GetTerjeRPC().SendToServer("startscreen.overview.del", new Param1<int>(0));
		}
	}
	
	protected void OnNextPageClicked(TerjeWidgetButton w)
	{
		if (!m_blocked)
		{
			m_blocked = true;
			ExecuteNextPage();
		}
	}
}

class TerjeWidgetCommand_TerjeStartScreenOverviewRefresh : TerjeWidgetCommand
{
	ref TerjeStartScreenContextOverview m_context;
	
	void TerjeWidgetCommand_TerjeStartScreenOverviewRefresh(TerjeStartScreenContextOverview context)
	{
		m_context = context;
	}
}