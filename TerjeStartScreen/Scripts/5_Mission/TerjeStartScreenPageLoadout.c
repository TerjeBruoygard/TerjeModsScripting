// <copyright file="TerjeStartScreenPageLoadout.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenPageLoadout : TerjeStartScreenPageBase
{
	protected bool m_processing;
	protected bool m_requestPended;
	protected ref TerjeXmlObject m_loadoutsObject;
	protected ref TerjeXmlObject m_selectedLoadoutObject;
	
	protected Widget m_nextButton;
	protected Widget m_loadoutsPanel;
	protected Widget m_loadoutsHeader;
	protected Widget m_infoActionPanel;
	protected Widget m_infoLoadingPanel;
	protected TextWidget m_infoLoadingText;
	protected Widget m_detailsNativePanel;
	protected Widget m_playerPreviewPanel;
	
	protected TerjeWidgetScrollList m_loadoutsScrollList;
	protected TerjeWidgetScrollArea m_detailsScrollArea;
	protected TerjeWidgetPlayerPreview m_playerPreview;
	protected TerjeStartScreenLoadoutSelectionsPanel m_selectionsPanel;
	
	override void OnInit()
	{
		super.OnInit();
		m_nextButton = GetNativeWidget().FindAnyWidget("ButtonOk");
		m_loadoutsPanel = GetNativeWidget().FindAnyWidget("LoadoutsPanel");
		m_loadoutsHeader = GetNativeWidget().FindAnyWidget("LoadoutsHeader");
		m_infoActionPanel = GetNativeWidget().FindAnyWidget("InfoActionPanel");
		m_infoLoadingPanel = GetNativeWidget().FindAnyWidget("InfoLoadingPanel");
		m_infoLoadingText = TextWidget.Cast(GetNativeWidget().FindAnyWidget("InfoLoadingText"));
		m_detailsNativePanel = GetNativeWidget().FindAnyWidget("SelectionsPanel");
		m_playerPreviewPanel = GetNativeWidget().FindAnyWidget("PlayerPanel");
		GetTerjeRPC().RegisterHandler("startscreen.loadout.ready", this, "OnTerjeStartScreenEquipCallback");
		
		m_processing = false;
		m_requestPended = false;
		m_selectedLoadoutObject = null;
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/PageLoadout.layout";
	}
	
	override void InitInputContext(TerjeStartScreenContextBase context)
	{
		super.InitInputContext(context);
		
		TerjeStartScreenContextLoadout loadoutContext = TerjeStartScreenContextLoadout.Cast(context);
		if (loadoutContext != null)
		{
			m_loadoutsObject = loadoutContext.m_inputLoadouts;
			m_selectedLoadoutObject = null;
			m_processing = false;
			m_requestPended = false;
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenLoadoutsRefresh(loadoutContext.m_inputLoadouts));
		}
	}
	
	override void InitOutputContext(TerjeStartScreenContextBase context)
	{
		super.InitOutputContext(context);
		
		TerjeStartScreenContextLoadout loadoutContext = TerjeStartScreenContextLoadout.Cast(context);
		if (loadoutContext != null)
		{
			if (m_selectedLoadoutObject != null)
			{
				m_selectedLoadoutObject.DeepCopy(loadoutContext.m_outputSelectedLoadout, true, false);
			}
			
			loadoutContext.m_inputLoadouts.Clear();
		}
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_Clicked))
		{
			if (!m_processing)
			{
				ExecuteNextPage();
			}
		}
		else if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenLoadoutsRefresh))
		{
			OnCommandLoadoutsRefresh(TerjeWidgetCommand_TerjeStartScreenLoadoutsRefresh.Cast(command));
		}
		else if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenDetailsRefresh))
		{
			OnCommandDetailsRefresh(TerjeWidgetCommand_TerjeStartScreenDetailsRefresh.Cast(command));
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		if (m_selectedLoadoutObject != null)
		{
			if (m_requestPended && !m_processing)
			{
				m_requestPended = false;
				m_processing = true;
				SynchLoadoutWithServer(m_selectedLoadoutObject);
			}
			
			if ((m_selectionsPanel != null) && (m_selectionsPanel.ValidateSelectors()) && m_selectedLoadoutObject.EqualAttribute("$valid", "1"))
			{
				m_infoActionPanel.Show(!m_processing);
				m_infoLoadingPanel.Show(m_processing);
				if (m_processing)
				{
					m_infoLoadingText.SetText("#STR_TERJESTARTSCREEN_PAGE_LOADOUT_LOADING");
				}
			}
			else
			{
				m_infoActionPanel.Show(false);
				m_infoLoadingPanel.Show(true);
				if (m_processing)
				{
					m_infoLoadingText.SetText("#STR_TERJESTARTSCREEN_PAGE_LOADOUT_LOADING");
				}
				else
				{
					m_infoLoadingText.SetText("#STR_TERJESTARTSCREEN_PAGE_LOADOUT_ALERT");
				}
			}
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if ((m_nextButton != null) && (w == m_nextButton) && (button == 0))
		{
			PushCommand(new TerjeWidgetCommand_Clicked(button));
			return true;
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	protected void OnCommandLoadoutsRefresh(TerjeWidgetCommand_TerjeStartScreenLoadoutsRefresh refreshCommand)
	{
		DestroyAllChildren();
		CreateLoadoutItemsView();
		CreatePlayerPreview();
		CreateDetailsView();
		
		int validLoadoutsCount = 0;
		TerjeXmlObject loadoutsXml = refreshCommand.m_loadouts;
		for (int index0 = 0; index0 < loadoutsXml.GetChildrenCount(); index0++)
		{
			if (loadoutsXml.GetChild(index0).EqualAttribute("$valid", "1"))
			{
				validLoadoutsCount++;
			}
		}
		
		if (validLoadoutsCount == 0)
		{
			ExecuteNextPage();
			return;
		}
		
		m_loadoutsPanel.Show(true);
		for (int index = 0; index < loadoutsXml.GetChildrenCount(); index++)
		{
			CreateLoadoutItemWidget(loadoutsXml.GetChild(index));
		}
	}
	
	protected void OnCommandDetailsRefresh(TerjeWidgetCommand_TerjeStartScreenDetailsRefresh refreshCommand)
	{
		m_detailsScrollArea.Clear();
		m_selectionsPanel = TerjeStartScreenLoadoutSelectionsPanel.Cast( m_detailsScrollArea.CreateChildWidget(TerjeStartScreenLoadoutSelectionsPanel) );
		m_selectionsPanel.SetLoadoutData(refreshCommand.m_loadout);
		m_selectionsPanel.OnChangedEvent.Insert(OnLoadoutSelectionChanged);
		m_detailsScrollArea.CreateChildWidget(TerjeStartScreenLoadoutInventoryPanel);
	}
	
	protected void CreateLoadoutItemsView()
	{
		float w;
		float h;
		m_loadoutsHeader.GetScreenSize(w, h);
		
		TerjeWidgetPadding paddingWidget = TerjeWidgetPadding.Cast(CreateTerjeWidgetEx(TerjeWidgetPadding, m_loadoutsPanel));
		paddingWidget.SetPadding(h, 0, 0, 0);
		
		m_loadoutsScrollList = TerjeWidgetScrollList.Cast(paddingWidget.CreateContentWidget(TerjeWidgetScrollList));
		m_loadoutsScrollList.OnItemSelectedEvent.Insert(OnLoadoutItemWidgetSelected);
	}
	
	protected void CreatePlayerPreview()
	{
		m_playerPreview = TerjeWidgetPlayerPreview.Cast(CreateTerjeWidgetEx(TerjeWidgetPlayerPreview, m_playerPreviewPanel));
		m_playerPreview.ShowImmediately(false);
	}
	
	protected void CreateDetailsView()
	{
		m_detailsScrollArea = TerjeWidgetScrollArea.Cast(CreateTerjeWidgetEx(TerjeWidgetScrollArea, m_detailsNativePanel));
	}
	
	protected void CreateLoadoutItemWidget(TerjeXmlObject loadout)
	{
		string id;
		if (!loadout.FindAttribute("id", id))
		{
			return;
		}
		
		TerjeWidgetText textWidget;
		TerjeWidgetListItem itemWidget = m_loadoutsScrollList.CreateItemWidget(id, loadout.EqualAttribute("$selected", "1"));
		
		int spacing = 0;
		string loadoutDisplayName;
		if (loadout.FindAttribute("displayName", loadoutDisplayName))
		{
			textWidget = TerjeWidgetText.Cast(itemWidget.CreateChildWidget(TerjeWidgetTextLabel));
			textWidget.SetTextImmediately(loadoutDisplayName);
			spacing = 12;
		}
		
		TerjeXmlObject loadoutConditions = loadout.GetChildByNodeName("Conditions");
		if (loadoutConditions != null)
		{
			TerjePlayerConditions loadoutFilter();
			for (int condId = 0; condId < loadoutConditions.GetChildrenCount(); condId++)
			{
				TerjeXmlObject loadoutCondition = loadoutConditions.GetChild(condId);
				string text = loadoutFilter.StringifyCondition(loadoutCondition);
				if (text != string.Empty)
				{
					if (spacing > 0)
					{
						TerjeWidgetSpacer.Cast(itemWidget.CreateChildWidget(TerjeWidgetSpacerH)).SetSpacingImmediately(spacing);
					}
					
					if (loadoutCondition.EqualAttribute("$valid", "1"))
					{
						textWidget = TerjeWidgetText.Cast(itemWidget.CreateChildWidget(TerjeWidgetTextSmall));
						textWidget.SetTextImmediately(text);
					}
					else
					{
						textWidget = TerjeWidgetText.Cast(itemWidget.CreateChildWidget(TerjeWidgetTextError));
						textWidget.SetTextImmediately(text);
					}
					
					spacing = 6;
				}
			}
		}
	}
	
	protected void OnLoadoutItemWidgetSelected(TerjeWidgetScrollList parent, TerjeWidgetListItem item, bool state)
	{
		if (state && m_loadoutsObject != null)
		{
			TerjeXmlObject loadoutObject = m_loadoutsObject.GetChildByAttrPair("Loadout", "id", item.GetItemId());
			if (loadoutObject != null)
			{
				OnLoadoutSelected(loadoutObject);
			}
		}
	}
	
	protected void OnLoadoutSelected(TerjeXmlObject loadout)
	{
		if (m_selectedLoadoutObject != loadout)
		{
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenDetailsRefresh(loadout));
			m_selectedLoadoutObject = loadout;
			m_requestPended = true;
			
			for (int i = 0; i < m_loadoutsObject.GetChildrenCount(); i++)
			{
				m_loadoutsObject.GetChild(i).SetAttribute("$selected", "0");
			}
			
			loadout.SetAttribute("$selected", "1");
		}
	}
	
	protected void OnLoadoutSelectionChanged()
	{
		if (m_selectedLoadoutObject != null)
		{
			m_requestPended = true;
		}
	}
	
	protected void OnTerjeStartScreenEquipCallback(ParamsReadContext ctx, PlayerIdentity sender)
	{
		m_processing = false;
		
		if (m_playerPreview != null)
		{
			m_playerPreview.Show(true);
		}
	}
	
	protected void SynchLoadoutWithServer(TerjeXmlObject loadout)
	{
		TerjeStreamRpc ctx;
		GetTerjeRPC().StreamToServer("startscreen.loadout.equip", ctx);
		if (loadout.Binarize(ctx))
		{
			ctx.Flush();
		}
	}
}

class TerjeWidgetCommand_TerjeStartScreenLoadoutsRefresh : TerjeWidgetCommand
{
	ref TerjeXmlObject m_loadouts;
	
	void TerjeWidgetCommand_TerjeStartScreenLoadoutsRefresh(TerjeXmlObject loadouts)
	{
		m_loadouts = loadouts;
	}
}

class TerjeWidgetCommand_TerjeStartScreenDetailsRefresh : TerjeWidgetCommand
{
	ref TerjeXmlObject m_loadout;
	
	void TerjeWidgetCommand_TerjeStartScreenDetailsRefresh(TerjeXmlObject loadout)
	{
		m_loadout = loadout;
	}
}