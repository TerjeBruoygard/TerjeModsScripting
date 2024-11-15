// <copyright file="VppCompatibility.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class VPPAdminHud
{
	private override void InsertButton(string permissionType, string displayName, string image, string desc)
	{
		super.InsertButton(permissionType, displayName, image, desc);
		
		if (permissionType == "MenuPlayerManager")
		{
			super.InsertButton("TerjePlayerManager", "Terje Stats", "set:dayz_gui_vpp image:vpp_icon_players", "Edit player stats registered in the TerjeCore mod.");
		}
	}
};

class TerjePlayerManager extends AdminHudSubMenu
{
	private bool m_Init;
	private bool m_infosUpdated;
	private bool m_dataUpdated;
	private bool m_refreshPended;
	private int m_infoSelectedId = -1;
	private string m_dataGUID;
	private ref map<string, string> m_infos = new map<string, string>;
	private ref map<string, float> m_data = new map<string, float>;
	private ref Widget m_loadingWidget;
	private ref TextListboxWidget m_listbox;
	
	void TerjePlayerManager()
	{
		GetTerjeRPC().RegisterHandler("TerjeCompatibilityVPP_ReceivePlayersList", this, "TerjeCompatibilityVPP_ReceivePlayersList");
		GetTerjeRPC().RegisterHandler("TerjeCompatibilityVPP_ReceivePlayerStats", this, "TerjeCompatibilityVPP_ReceivePlayerStats");
	}
	
	private void TerjeCompatibilityVPP_ReceivePlayersList(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param1<ref map<string, string>> data;
		if(!ctx.Read(data)) return;
		
		m_infos = data.param1;
		m_infosUpdated = true;
	}
	
	private void TerjeCompatibilityVPP_ReceivePlayerStats(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param2<string, ref map<string, float>> data;
		if(!ctx.Read(data)) return;
		
		m_dataGUID = data.param1;
		m_data = data.param2;
		m_dataUpdated = true;
	}
	
	private void UpdateStatsText()
	{
		foreach (string id, float value : m_data)
		{
			ref SliderWidget slider = SliderWidget.Cast( M_SUB_WIDGET.FindAnyWidget("TerjeSlider_" + id) );
			ref TextWidget display = TextWidget.Cast( M_SUB_WIDGET.FindAnyWidget("TerjeSliderDisplay_" + id) );
			ref TerjeAdmintoolSupport_PlayerStat stat;
			if (GetTerjeAdmintoolSupport().FindPlayerStat(id, stat) && slider && display)
			{
				display.SetText(stat.GetName() + ": [" + slider.GetCurrent() + "]");
			}
		}
	}
	
	private void CreateTerjeStatWidget(Widget parent, ref TerjeAdmintoolSupport_PlayerStat stat)
	{
		string id = stat.GetId();
		ref Widget terjeStatWidget = GetGame().GetWorkspace().CreateWidgets("TerjeCompatibilityVPP/Layouts/TerjePlayerSliderWidget.layout", parent);	
		terjeStatWidget.SetName(id);
		terjeStatWidget.FindAnyWidget("TerjeApplyImg").SetName("TerjeApplyImg_" + id);
		
		float value = stat.GetMin();
		m_data.Find(id, value);
		
		ref SliderWidget slider = SliderWidget.Cast( terjeStatWidget.FindAnyWidget("TerjeSlider") );
		slider.SetName("TerjeSlider_" + id);
		slider.SetMinMax(stat.GetMin(), stat.GetMax());
		slider.SetStep( (stat.GetMax() - stat.GetMin()) / 1000 );
		slider.SetCurrent( value );
		
		ref ButtonWidget btn = ButtonWidget.Cast( terjeStatWidget.FindAnyWidget("TerjeBtnApply") );
		btn.SetName("TerjeBtnApply_" + id);
		
		ref TextWidget display = TextWidget.Cast( terjeStatWidget.FindAnyWidget("TerjeSliderDisplay") );
		display.SetName("TerjeSliderDisplay_" + id);
		display.SetText(stat.GetName() + ": [" + value + "]");
		
		ref ImageWidget icon = ImageWidget.Cast( terjeStatWidget.FindAnyWidget("TerjeIcon") );
		icon.SetName("TerjeIcon_" + id);
		icon.LoadImageFile(0, stat.GetIcon());
	}
	
	override void OnCreate(Widget RootW)
	{
		super.OnCreate(RootW);
		
		M_SUB_WIDGET  = CreateWidgets("TerjeCompatibilityVPP/Layouts/TerjePlayerManager.layout");
		M_SUB_WIDGET.SetHandler(this);
		m_TitlePanel  = Widget.Cast( M_SUB_WIDGET.FindAnyWidget( "Header") );
		m_closeButton = ButtonWidget.Cast( M_SUB_WIDGET.FindAnyWidget( "BtnClose") );
		m_loadingWidget = M_SUB_WIDGET.FindAnyWidget("TextTerjeLoading");
		m_listbox = TextListboxWidget.Cast( M_SUB_WIDGET.FindAnyWidget("ListboxTerjePlayers") );
		
		m_Init = true;
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		if (!IsSubMenuVisible() && M_SUB_WIDGET == null)
			return;
		
		if (m_infosUpdated)
		{
			m_infosUpdated = false;
			
			array<string> ids = m_infos.GetKeyArray();
			ids.Sort();
			
			string selectedSteamId = "";
			int selectedRow = m_listbox.GetSelectedRow();
			if (selectedRow >= 0 && selectedRow < m_listbox.GetNumItems())
			{
				Param1<string> guid;
				m_listbox.GetItemData(selectedRow, 0, guid);
				selectedSteamId = guid.param1;
			}
			
			int newSelectedRow = -1;
			m_listbox.ClearItems();
			foreach (string id : ids)
			{
				m_listbox.AddItem(m_infos.Get(id), new Param1<string>(id), 0);
				
				if (selectedSteamId != "" && selectedSteamId == id)
				{
					newSelectedRow = m_listbox.GetNumItems() - 1;
				}
			}
			
			if (newSelectedRow >= 0 && newSelectedRow < m_listbox.GetNumItems())
			{
				m_listbox.SelectRow(newSelectedRow);
			}
		}
		
		if ( (m_refreshPended || m_infoSelectedId != m_listbox.GetSelectedRow()) && !m_loadingWidget.IsVisible())
		{
			m_refreshPended = false;
			m_infoSelectedId = m_listbox.GetSelectedRow();
			m_loadingWidget.Show(true);
			
			Param1<string> guid2;
			m_listbox.GetItemData(m_infoSelectedId, 0, guid2);
			GetTerjeRPC().SendToServer("TerjeCompatibilityVPP_GetPlayerStats", guid2);
		}
		
		if (m_dataUpdated)
		{
			m_dataUpdated = false;
			
			m_loadingWidget.Show(false);
			
			ref Widget statsPanel = M_SUB_WIDGET.FindAnyWidget("GridTerjePlayerInfo");
			while (true)
			{
				ref Widget child = statsPanel.GetChildren();
				if (child)
				{
					statsPanel.RemoveChild(child);
				}
				else
				{
					break;
				}
			}
			
			array<ref TerjeAdmintoolSupport_PlayerStat> registeredStats = new array<ref TerjeAdmintoolSupport_PlayerStat>;
			GetTerjeAdmintoolSupport().GetPlayerStats(registeredStats);
			
			foreach (ref TerjeAdmintoolSupport_PlayerStat stat : registeredStats)
			{
				CreateTerjeStatWidget(statsPanel, stat);
			}
		}
		
		if (m_data && m_data.Count() > 0)
		{
			UpdateStatsText();
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (w.GetName() == "BtnTerjeRefresh")
		{
			m_refreshPended = true;
		}
		else if (w.GetName().IndexOf("TerjeBtnApply_") == 0)
		{
			string statId = w.GetName().Substring(14, w.GetName().Length() - 14);
			ref SliderWidget slider = SliderWidget.Cast( M_SUB_WIDGET.FindAnyWidget("TerjeSlider_" + statId) );
			if (slider)
			{
				float statValue = slider.GetCurrent();
				GetTerjeRPC().SendToServer("TerjeCompatibilityVPP_SetStatValue", new Param3<string, float, string>(statId, statValue, m_dataGUID));
			}
		}
		
		return super.OnClick(w, x, y, button);
	}

	override void HideSubMenu()
	{
		super.HideSubMenu();
	}
	
	override void ShowSubMenu()
	{
		super.ShowSubMenu();
		m_loadingWidget.Show(false);
		GetTerjeRPC().SendToServer("TerjeCompatibilityVPP_GetPlayersList", new Param1<int>(0));
	}
};

modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		
		GetTerjeRPC().RegisterHandler("TerjeCompatibilityVPP_GetPlayersList", this, "OnReceive_TerjeCompatibilityVPP_GetPlayersList");
		GetTerjeRPC().RegisterHandler("TerjeCompatibilityVPP_GetPlayerStats", this, "OnReceive_TerjeCompatibilityVPP_GetPlayerStats");
		GetTerjeRPC().RegisterHandler("TerjeCompatibilityVPP_SetStatValue", this, "OnReceive_TerjeCompatibilityVPP_SetStatValue");
	};
	
	private void OnReceive_TerjeCompatibilityVPP_GetPlayersList(ParamsReadContext ctx, PlayerIdentity sender)
	{
		string adminID  = sender.GetPlainId();
		if (!GetPermissionManager().VerifyPermission(adminID, "TerjePlayerManager")) return;
		
		ref map<string, string> infos = new map<string, string>;
		autoptr array<Man> players = new array<Man>;
       	GetGame().GetWorld().GetPlayerList( players );
		
		for (int i = 0; i < players.Count(); i++)
		{
			PlayerBase player = PlayerBase.Cast(players[i]);
			if(player && player.GetIdentity())
			{
				infos.Insert(player.GetIdentity().GetPlainId(), player.GetIdentity().GetName());
			}
		}
		
		GetTerjeRPC().SendToClient("TerjeCompatibilityVPP_ReceivePlayersList", sender, new Param1<ref map<string, string>>(infos));
	};
	
	private void OnReceive_TerjeCompatibilityVPP_GetPlayerStats(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param1<string> data;
		if(!ctx.Read(data)) return;
		
		string adminID  = sender.GetPlainId();
		if (!GetPermissionManager().VerifyPermission(adminID, "TerjePlayerManager")) return;
		
		ref map<string, float> targetStats = new map<string, float>;
		PlayerBase targetPlayer = GetPermissionManager().GetPlayerBaseByID(data.param1);
		if (targetPlayer && targetPlayer.GetIdentity())
		{
			array<ref TerjeAdmintoolSupport_PlayerStat> registeredStats = new array<ref TerjeAdmintoolSupport_PlayerStat>;
			GetTerjeAdmintoolSupport().GetPlayerStats(registeredStats);
			foreach (ref TerjeAdmintoolSupport_PlayerStat stat : registeredStats)
			{
				targetStats[stat.GetId()] = stat.GetValue(targetPlayer);
			}
		}
		
		string targetId = targetPlayer.GetIdentity().GetPlainId();
		GetTerjeRPC().SendToClient("TerjeCompatibilityVPP_ReceivePlayerStats", sender, new Param2<string, ref map<string, float>>(targetId, targetStats));
	};
	
	private void OnReceive_TerjeCompatibilityVPP_SetStatValue(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param3<string, float, string> clientData;
       	if (!ctx.Read(clientData ))
			return;
		
		string adminID  = sender.GetPlainId();
		if (!GetPermissionManager().VerifyPermission(adminID, "TerjePlayerManager")) return;
		
		string id = clientData.param1;
		float value = clientData.param2;
		string guid = clientData.param3;

		ref TerjeAdmintoolSupport_PlayerStat stat;
		if (!GetTerjeAdmintoolSupport().FindPlayerStat(id, stat))
			return;
		
		if (!stat)
			return;
		
		PlayerBase player = GetPermissionManager().GetPlayerBaseByID(guid);
		if (player && player.GetIdentity())
		{
			stat.SetValue(player, value);
		}
	}
};