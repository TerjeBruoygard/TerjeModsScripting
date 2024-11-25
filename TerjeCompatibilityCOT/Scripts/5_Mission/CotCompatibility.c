// <copyright file="CotCompatibility.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		
		GetTerjeRPC().RegisterHandler("JM_COT_SetTerjeValue", this, "OnReceive_JM_COT_SetTerjeValue");
	}
	
	private void OnReceive_JM_COT_SetTerjeValue(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param3<string, float, array<string>> clientData;
		if (!ctx.Read(clientData))
		{
			return;
		}
		
		string id = clientData.param1;
		float value = clientData.param2;
		array< string > guids = clientData.param3;

		JMPlayerInstance instance;
		if ( !GetPermissionsManager().HasPermission( "Admin.Player.Set.Health", sender, instance ) )
			return;

		ref TerjeAdmintoolSupport_PlayerStat stat;
		if (!GetTerjeAdmintoolSupport().FindPlayerStat(id, stat))
			return;
		
		if (!stat)
			return;
		
		array< JMPlayerInstance > players = GetPermissionsManager().GetPlayers( guids );
		for ( int i = 0; i < players.Count(); i++ )
		{
			PlayerBase player = PlayerBase.Cast( players[i].PlayerObject );
			if ( !player )
				continue;

			stat.SetValue(player, value);
			GetCommunityOnlineToolsBase().Log( sender, "Set " + stat.GetName() + " To " + value + " [guid=" + players[i].GetGUID() + "]" );
			players[i].Update();
		}
	}
}

modded class JMPlayerModule
{
	private override void Exec_Heal( array< string > guids, PlayerIdentity ident, JMPlayerInstance instance = NULL  )
	{
		array< JMPlayerInstance > players = GetPermissionsManager().GetPlayers( guids );
		for ( int i = 0; i < players.Count(); i++ )
		{
			PlayerBase player = PlayerBase.Cast( players[i].PlayerObject );
			if ( !player )
				continue;

			GetTerjeAdmintoolSupport().OnHeal(player);
		}
		
		super.Exec_Heal(guids, ident, instance);
	}
	
	void SetTerjeValue( string id, float value, array< string > guids )
	{
		GetTerjeRPC().SendToServer("JM_COT_SetTerjeValue", new Param3<string, float, array<string>>(id, value, guids));
	}
}

modded class JMPlayerForm
{
	private UIActionButton m_TerjeRefreshStats;
	private UIActionButton m_TerjeApplyStats;
	private UIActionSlider m_TerjeUnused;
	
	private ref map<string, UIActionSlider> m_TerjeControls;
	private ref set<string> m_TerjeUpdatedControls;

	override void OnClientPermissionsUpdated()
	{
		super.OnClientPermissionsUpdated();
		
		if (m_TerjeControls)
		{
			foreach (string id, UIActionSlider control : m_TerjeControls)
			{
				UpdatePermission( control, "Admin.Player.Set.Health" );
			}
		}
	}
	
	override private Widget InitActionWidgetsStats( Widget actionsParent )
	{
		Widget result = super.InitActionWidgetsStats(actionsParent);
		Widget actions = UIActionManager.CreateGridSpacer( result, 4, 2 );

		array<ref TerjeAdmintoolSupport_PlayerStat> registeredStats = new array<ref TerjeAdmintoolSupport_PlayerStat>;
		GetTerjeAdmintoolSupport().GetPlayerStats(registeredStats);
		
		m_TerjeControls = new map<string, UIActionSlider>;
		m_TerjeUpdatedControls = new set<string>;
		foreach (ref TerjeAdmintoolSupport_PlayerStat stat : registeredStats)
		{
			m_TerjeControls[stat.GetId()] = UIActionManager.CreateSlider( actions, stat.GetName(), stat.GetMin(), stat.GetMax(), this, "Click_SetTerjeStat" );
			m_TerjeControls[stat.GetId()].SetSliderWidth(0.5);
		}
		
		if (m_TerjeControls.Count() % 2 != 0)
		{
			m_TerjeUnused = UIActionManager.CreateSlider( actions, "[Unused]", 0, 0, this, "Click_SetTerjeUnused" );
			m_TerjeUnused.SetSliderWidth(0.5);
			m_TerjeUnused.SetEnabled(false);
		}
				
		m_TerjeApplyStats = UIActionManager.CreateButton( actions, "#STR_COT_PLAYER_MODULE_RIGHT_PLAYER_VARIABLES_APPLY", this, "Click_ApplyStats" );
		m_TerjeRefreshStats = UIActionManager.CreateButton( actions, "#STR_COT_PLAYER_MODULE_RIGHT_PLAYER_VARIABLES_REFRESH", this, "Click_RefreshStats" );
		
		return result;
	}
	
	override void RefreshStats(bool force = false)
	{
		super.RefreshStats(force);
		
		if ( !m_SelectedInstance )
			return;
		
		if (m_SelectedInstance.GetDataLastUpdatedTime() < m_LastChangeTime)
			return;
		
		if (force)
		{
			m_TerjeUpdatedControls.Clear();
		}
		
		foreach (string id, UIActionSlider control : m_TerjeControls)
		{
			if (control && m_TerjeUpdatedControls.Find(id) == -1)
			{
				control.SetCurrent( m_SelectedInstance.GetTerjeStat(id) );
			}
		}
	}
	
	override void Click_ApplyStats( UIEvent eid, UIActionBase action )
	{
		super.Click_ApplyStats(eid, action);
		
		foreach (string id : m_TerjeUpdatedControls)
		{
			UIActionSlider control;
			if (m_TerjeControls.Find(id, control) && control)
			{
				m_Module.SetTerjeValue( id, control.GetCurrent(), JM_GetSelected().GetPlayers() );
			}
		}
		
		m_TerjeUpdatedControls.Clear();
	}
	
	void Click_SetTerjeStat( UIEvent eid, UIActionBase action )
	{
		if ( eid != UIEvent.CHANGE )
			return;

		UpdateLastChangeTime();
		
		string resultedId = "";
		foreach (string id, UIActionSlider control : m_TerjeControls)
		{
			if (control && control == action)
			{
				resultedId = id;
				break;
			}
		}
		
		if (resultedId != "")
		{
			m_TerjeUpdatedControls.Insert(resultedId);
		}
	}
	
	void Click_SetTerjeUnused( UIEvent eid, UIActionBase action )
	{

	}
}

modded class JMObjectSpawnerModule
{
	override private void SetupEntity( EntityAI entity, float quantity, float health, float temp, int itemState, PlayerBase player, COT_ObjectSetupMode mode = COT_ObjectSetupMode.NONE )
	{
		ItemBase item;
		if ( itemState < 0 && Class.CastTo( item, entity ) && item.IsLiquidContainer() )
		{
			super.SetupEntity(entity, quantity, health, temp, 0, player, mode);
			item.SetTerjeLiquidType(-itemState);
		}
		else
		{
			super.SetupEntity(entity, quantity, health, temp, itemState, player, mode);
		}
	}
}

modded class JMObjectSpawnerForm
{
	override void OnInit()
	{
		super.OnInit();
		
		foreach (int liquidType, ref LiquidInfo liquidInfo: TerjeCustomLiquids.GetInstance().m_LiquidInfosByType)
		{
			string liquidClsName = liquidInfo.m_LiquidClassName;
			string displayName = liquidInfo.m_LiquidDisplayName;

			if (displayName.IndexOf("#") == 0)
			{
				displayName = Widget.TranslateString(displayName);
			}

			m_ObjItemStateLiquid.Insert(-liquidType);
			m_ObjItemStateLiquidText.Insert(displayName);
		}
	}
	
	override void UpdateItemStateType(int mode, int liquidType = 0)
	{
		if (mode == 0 && liquidType == LIQUID_TERJE_CUSTOM && m_PreviewItem && m_PreviewItem.IsInherited(ItemBase))
		{
			int terjeLiquidType = ItemBase.Cast(m_PreviewItem).GetTerjeCustomLiquidTypeInit();
			if (terjeLiquidType > 0)
			{
				liquidType = -terjeLiquidType;
			}
		}
		
		super.UpdateItemStateType(mode, liquidType);
	}
}

modded class JMESPMeta
{
	UIActionEditableText m_terjeRadiation;
	
	override void CreateActions( Widget parent )
	{
		super.CreateActions(parent);
		
		m_terjeRadiation = UIActionManager.CreateEditableText( parent, "Radiation:" );
		m_terjeRadiation.SetOnlyNumbers( true );
		m_terjeRadiation.Disable();
	}
	
	override void Update()
	{
		super.Update();
		
		if ( m_terjeRadiation && !m_terjeRadiation.IsFocused() && !m_terjeRadiation.IsEdited() )
		{
			float radValue = 0;
			EntityAI targetEntity = EntityAI.Cast(target);
			if (targetEntity)
			{
				radValue = GetTerjeScriptableAreas().GetTerjeRadiationFromEntity(targetEntity);
			}
			
			m_terjeRadiation.SetText( FloatToString( radValue ) );
		}
	}
	
	override void UpdateActions()
	{
		super.UpdateActions();
		
		if ( m_terjeRadiation && !m_terjeRadiation.IsFocused() && !m_terjeRadiation.IsEdited() )
		{
			float radValue = 0;
			EntityAI targetEntity = EntityAI.Cast(target);
			if (targetEntity)
			{
				radValue = GetTerjeScriptableAreas().GetTerjeRadiationFromEntity(targetEntity);
			}
			
			m_terjeRadiation.SetText( FloatToString( radValue ) );
		}
	}
}