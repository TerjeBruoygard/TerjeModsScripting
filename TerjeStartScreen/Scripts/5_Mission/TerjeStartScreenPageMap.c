// <copyright file="TerjeStartScreenPageMap.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenPageMap : TerjeStartScreenPageBase
{
	protected const float MAP_INTERACTION_RADIUS = 16;
	
	protected ref TerjeXmlObject m_respawnsXml;
	protected string m_selectedRespawnId;
	protected bool m_mapRenderAutozoom = true;
	protected vector m_mapLastMousePos = vector.Zero;
	
	protected Widget m_nextButton;
	protected Widget m_respawnsPanel;
	protected Widget m_respawnsHeader;
	protected Widget m_infoActionPanel;
	protected Widget m_infoAlertPanel;
	protected MapWidget m_mapRender;
	protected ImageWidget m_mapImage;
	
	protected TerjeWidgetScrollList m_respawnsScrollList;
	
	override void OnInit()
	{
		super.OnInit();
		m_nextButton = GetNativeWidget().FindAnyWidget("ButtonOk");
		m_respawnsPanel = GetNativeWidget().FindAnyWidget("RespawnsPanel");
		m_respawnsHeader = GetNativeWidget().FindAnyWidget("RespawnsHeader");
		m_infoActionPanel = GetNativeWidget().FindAnyWidget("InfoActionPanel");
		m_infoAlertPanel = GetNativeWidget().FindAnyWidget("InfoAlertPanel");
		m_mapRender = MapWidget.Cast(GetNativeWidget().FindAnyWidget("MapRender"));
		m_mapImage = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("MapImage"));
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/PageMap.layout";
	}
	
	override void InitInputContext(TerjeStartScreenContextBase context)
	{
		super.InitInputContext(context);
		
		TerjeStartScreenContextMap mapContext = TerjeStartScreenContextMap.Cast(context);
		if (mapContext != null)
		{
			m_respawnsXml = mapContext.m_inputRespawns;
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenMapRefresh(mapContext.m_inputRespawns));
		}
	}
	
	override void InitOutputContext(TerjeStartScreenContextBase context)
	{
		super.InitOutputContext(context);
		
		TerjeStartScreenContextMap mapContext = TerjeStartScreenContextMap.Cast(context);
		if (mapContext != null)
		{
			mapContext.m_outputSelectedRespawnId = m_selectedRespawnId;
			mapContext.m_inputRespawns.Clear();
			m_respawnsXml = null;
		}
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_Clicked))
		{
			ExecuteNextPage();
		}
		else if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenMapRefresh))
		{
			OnCommandRespawnsRefresh(TerjeWidgetCommand_TerjeStartScreenMapRefresh.Cast(command));
		}
		else if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenMapView))
		{
			OnCommandMapView(TerjeWidgetCommand_TerjeStartScreenMapView.Cast(command));
		}
		else if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenMapRender))
		{
			TerjeWidgetCommand_TerjeStartScreenMapRender renderCmd = TerjeWidgetCommand_TerjeStartScreenMapRender.Cast(command);
			m_mapRender.SetScale(renderCmd.m_scale);
			m_mapRender.SetMapPos(renderCmd.m_pos);
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
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		if ((m_mapRender != null) && (w == m_mapRender) && (button == 0))
		{
			m_mapLastMousePos = Vector(x, y, 0);
		}
		 
		return super.OnMouseButtonDown(w, x, y, button);
	}
	
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		if ((m_mapRender != null) && (w == m_mapRender) && (button == 0))
		{
			if (vector.Distance(m_mapLastMousePos, Vector(x, y, 0)) < MAP_INTERACTION_RADIUS)
			{
				vector screenPos = Vector(x, y, 0);
				vector worldPos = m_mapRender.ScreenToMap(screenPos);
				OnMapClickEvent(screenPos, worldPos);
			}
		}
		
		return super.OnMouseButtonUp(w, x, y, button);
	}
	
	protected void OnMapClickEvent(vector screenPos, vector worldPos)
	{
		if (m_respawnsXml != null && m_respawnsScrollList != null)
		{
			for (int i = 0; i < m_respawnsXml.GetChildrenCount(); i++)
			{
				string id;
				TerjeXmlObject respawnXml = m_respawnsXml.GetChild(i);
				if ((respawnXml != null) && (respawnXml.FindAttribute("id", id)))
				{
					TerjeXmlObject optionsXml = respawnXml.GetChildByNodeName("Options");
					if (optionsXml != null)
					{
						TerjeXmlObject renderXml = optionsXml.GetChildByNodeName("MapRender");
						if ((renderXml != null) && (renderXml.EqualAttribute("allowInteraction", "1")))
						{
							vector markerPos = m_mapRender.MapToScreen(TerjeVectorHelper.XmlToVector(renderXml));
							if (vector.Distance(markerPos, screenPos) < MAP_INTERACTION_RADIUS)
							{
								m_mapRenderAutozoom = false;
								m_respawnsScrollList.SelectItem(id);
								return;
							}
						}
					}
				}
			}
		}
	}
	
	protected void OnCommandRespawnsRefresh(TerjeWidgetCommand_TerjeStartScreenMapRefresh refreshCommand)
	{
		DestroyAllChildren();
		CreateRespawnItemsView();
		
		int validRespawnsCount = 0;
		TerjeXmlObject respawnsXml = refreshCommand.m_respawns;
		for (int index0 = 0; index0 < respawnsXml.GetChildrenCount(); index0++)
		{
			if (respawnsXml.GetChild(index0).EqualAttribute("$valid", "1"))
			{
				validRespawnsCount++;
			}
		}
		
		if (validRespawnsCount == 0)
		{
			ExecuteNextPage();
			return;
		}
		
		m_respawnsPanel.Show(true);
		for (int index = 0; index < respawnsXml.GetChildrenCount(); index++)
		{
			CreateRespawnItemWidget(respawnsXml.GetChild(index));
		}
	}
	
	protected void CreateRespawnItemsView()
	{
		float w;
		float h;
		m_respawnsHeader.GetScreenSize(w, h);
		
		TerjeWidgetPadding paddingWidget = TerjeWidgetPadding.Cast(CreateTerjeWidgetEx(TerjeWidgetPadding, m_respawnsPanel));
		paddingWidget.SetPadding(h, 0, 0, 0);
		
		m_respawnsScrollList = TerjeWidgetScrollList.Cast(paddingWidget.CreateContentWidget(TerjeWidgetScrollList));
		m_respawnsScrollList.OnItemSelectedEvent.Insert(OnRespawnItemWidgetSelected);
	}
	
	protected void CreateRespawnItemWidget(TerjeXmlObject respawn)
	{
		string id;
		if (!respawn.FindAttribute("id", id))
		{
			return;
		}
		
		TerjeWidgetText textWidget;
		TerjeWidgetListItem itemWidget = m_respawnsScrollList.CreateItemWidget(id, respawn.EqualAttribute("$selected", "1"));
		
		int spacing = 0;
		string respawnDisplayName;
		if (respawn.FindAttribute("displayName", respawnDisplayName))
		{
			textWidget = TerjeWidgetText.Cast(itemWidget.CreateChildWidget(TerjeWidgetTextLabel));
			textWidget.SetTextImmediately(respawnDisplayName);
			spacing = 12;
		}
		
		TerjeXmlObject respawnConditions = respawn.GetChildByNodeName("Conditions");
		if (respawnConditions != null)
		{
			TerjePlayerConditions respawnFilter();
			for (int condId = 0; condId < respawnConditions.GetChildrenCount(); condId++)
			{
				TerjeXmlObject respawnCondition = respawnConditions.GetChild(condId);
				string text = respawnFilter.StringifyCondition(respawnCondition);
				if (text != string.Empty)
				{
					if (spacing > 0)
					{
						TerjeWidgetSpacer.Cast(itemWidget.CreateChildWidget(TerjeWidgetSpacerH)).SetSpacingImmediately(spacing);
					}
					
					if (respawnCondition.EqualAttribute("$valid", "1"))
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
	
	protected void OnRespawnItemWidgetSelected(TerjeWidgetScrollList parent, TerjeWidgetListItem item, bool state)
	{
		if (state && (m_respawnsXml != null))
		{
			bool valid = false;
			string id = item.GetItemId();
			TerjeXmlObject options = null;
			TerjeXmlObject respawn = m_respawnsXml.GetChildByAttrPair("Respawn", "id", id);
			if (respawn != null)
			{
				valid = respawn.EqualAttribute("$valid", "1");
				options = respawn.GetChildByNodeName("Options");
			}
			
			m_infoActionPanel.Show(valid);
			m_infoAlertPanel.Show(!valid);
			m_selectedRespawnId = id;
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenMapView(respawn, options));
		}
	}
	
	protected void OnCommandMapView(TerjeWidgetCommand_TerjeStartScreenMapView viewCommand)
	{
		string attrValue;
		TerjeXmlObject option;
		TerjeXmlObject options = viewCommand.m_options;
		if (options != null)
		{
			option = options.GetChildByNodeName("MapImage");
			if ((option != null) && (option.FindAttribute("path", attrValue)))
			{
				SetMapImageImmediately(attrValue);
				return;
			}
			
			option = options.GetChildByNodeName("MapRender");
			if (option != null)
			{
				float scale;
				if (option.FindAttribute("zoom", attrValue))
				{
					scale = attrValue.ToFloat();
				}
				else
				{
					scale = 1;
				}
				
				SetMapRenderImmediately(TerjeVectorHelper.XmlToVector(option), scale, viewCommand.m_respawn, option);
				return;
			}
		}
		
		m_mapRender.Show(false);
		m_mapImage.Show(false);
	}
	
	protected void SetMapImageImmediately(string imgPath)
	{
		m_mapRender.Show(false);
		m_mapImage.LoadImageFile(0, TerjeStringHelper.FixTexturePath(imgPath));
		m_mapImage.Show(true);
	}
	
	protected void SetMapRenderImmediately(vector pos, float scale, TerjeXmlObject actualRespawn, TerjeXmlObject actualRender)
	{
		m_mapImage.Show(false);
		m_mapRender.Show(true);
		
		if (m_mapRenderAutozoom)
		{
			m_mapRender.SetScale(scale);
			m_mapRender.SetMapPos(pos);
		}
		
		m_mapRender.ClearUserMarks();
		
		if (m_respawnsXml != null)
		{
			for (int i = 0; i < m_respawnsXml.GetChildrenCount(); i++)
			{
				TerjeXmlObject respawnXml = m_respawnsXml.GetChild(i);
				if (respawnXml != null)
				{
					TerjeXmlObject optionsXml = respawnXml.GetChildByNodeName("Options");
					if (optionsXml != null)
					{
						TerjeXmlObject renderXml = optionsXml.GetChildByNodeName("MapRender");
						if (renderXml != null && renderXml != actualRender)
						{
							SetMapMarksImmediately(respawnXml, renderXml, false);
						}
					}
				}
			}
		}
		
		SetMapMarksImmediately(actualRespawn, actualRender, true);
		
		if (actualRender.EqualAttribute("allowInteraction", "1"))
		{
			m_mapRender.ClearFlags(WidgetFlags.IGNOREPOINTER);
		}
		else
		{
			m_mapRender.SetFlags(WidgetFlags.IGNOREPOINTER);
		}
		
		if (m_mapRenderAutozoom)
		{
			// Double update required, bug in vanilla MapWidget
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenMapRender(pos, scale));
		}
		
		m_mapRenderAutozoom = true;
	}
	
	protected void SetMapMarksImmediately(TerjeXmlObject respawn, TerjeXmlObject render, bool selected)
	{
		// Points
		string attrValue;
		bool showPoints = false;
		if (render.FindAttribute("showPoints", attrValue))
		{
			if (attrValue == "active")
			{
				showPoints = selected;
			}
			else if (attrValue == "always")
			{
				showPoints = true;
			}
		}
		
		if (showPoints)
		{
			int pointsColor;
			if (selected)
			{
				if (render.FindAttribute("activePointsColor", attrValue))
				{
					pointsColor = attrValue.HexToInt();
				}
				else
				{
					pointsColor = ARGB(255, 180, 0, 0);
				}
			}
			else
			{
				if (render.FindAttribute("inactivePointsColor", attrValue))
				{
					pointsColor = attrValue.HexToInt();
				}
				else
				{
					pointsColor = ARGB(255, 25, 25, 25);
				}
			}
		
			string pointsIcon = "TerjeStartScreen/Textures/dot.paa";
			if (render.FindAttribute("pointsPath", attrValue))
			{
				pointsIcon = attrValue;
			}
			
			TerjeXmlObject pointsXml = respawn.GetChildByNodeName("Points");
			if (pointsXml != null)
			{
				for (int pointId = 0; pointId < pointsXml.GetChildrenCount(); pointId++)
				{
					TerjeXmlObject pointXml = pointsXml.GetChild(pointId);
					if (pointXml != null)
					{
						vector pointPos = TerjeVectorHelper.XmlToVector(pointXml);
						if ((pointPos[0] != 0) && (pointPos[2] != 0))
						{
							m_mapRender.AddUserMark(pointPos, string.Empty, pointsColor, TerjeStringHelper.FixTexturePath(pointsIcon));
						}
					}
				}
			}
		}
		
		// Marker
		bool showMarker = false;
		if (render.FindAttribute("showMarker", attrValue))
		{
			if (attrValue == "active")
			{
				showMarker = selected;
			}
			else if (attrValue == "always")
			{
				showMarker = true;
			}
		}
		
		if (showMarker)
		{
			string markerName = string.Empty;
			if (render.EqualAttribute("showMarkerName", "1") && respawn.FindAttribute("displayName", attrValue))
			{
				markerName = attrValue;
			}
			
			int markerColor;
			if (selected)
			{
				if (render.FindAttribute("activeMarkerColor", attrValue))
				{
					markerColor = attrValue.HexToInt();
				}
				else
				{
					markerColor = ARGB(255, 180, 0, 0);
				}
			}
			else
			{
				if (render.FindAttribute("inactiveMarkerColor", attrValue))
				{
					markerColor = attrValue.HexToInt();
				}
				else
				{
					markerColor = ARGB(255, 25, 25, 25);
				}
			}
		
			string markerIcon = "TerjeStartScreen/Textures/marker.paa";
			if (render.FindAttribute("markerPath", attrValue))
			{
				markerIcon = attrValue;
			}
			
			vector markerPos = TerjeVectorHelper.XmlToVector(render);
			if ((markerPos[0] != 0) && (markerPos[2] != 0))
			{
				m_mapRender.AddUserMark(markerPos, markerName, markerColor, TerjeStringHelper.FixTexturePath(markerIcon));
			}
		}
	}
}

class TerjeWidgetCommand_TerjeStartScreenMapRefresh : TerjeWidgetCommand
{
	ref TerjeXmlObject m_respawns;
	
	void TerjeWidgetCommand_TerjeStartScreenMapRefresh(TerjeXmlObject respawns)
	{
		m_respawns = respawns;
	}
}

class TerjeWidgetCommand_TerjeStartScreenMapView : TerjeWidgetCommand
{
	ref TerjeXmlObject m_respawn;
	ref TerjeXmlObject m_options;
	
	void TerjeWidgetCommand_TerjeStartScreenMapView(TerjeXmlObject respawn, TerjeXmlObject options)
	{
		m_respawn = respawn;
		m_options = options;
	}
}

class TerjeWidgetCommand_TerjeStartScreenMapRender : TerjeWidgetCommand
{
	vector m_pos;
	float m_scale;
	
	void TerjeWidgetCommand_TerjeStartScreenMapRender(vector pos, float scale)
	{
		m_pos = pos;
		m_scale = scale;
	}
}