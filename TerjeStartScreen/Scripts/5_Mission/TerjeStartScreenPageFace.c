// <copyright file="TerjeStartScreenPageFace.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenPageFace : TerjeStartScreenPageBase
{
	protected Widget m_nextButtonPanel;
	protected Widget m_facesGrid;
	protected string m_currentFace;
	protected TerjeWidgetButton m_nextButton;
	
	override void OnInit()
	{
		super.OnInit();
		m_nextButtonPanel = GetNativeWidget().FindAnyWidget("PanelNextButton");
		m_facesGrid = GetNativeWidget().FindAnyWidget("FacesGrid");
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/PageFace.layout";
	}
	
	override void InitInputContext(TerjeStartScreenContextBase context)
	{
		super.InitInputContext(context);
		
		TerjeStartScreenContextFace faceContext = TerjeStartScreenContextFace.Cast(context);
		if (faceContext != null)
		{
			m_currentFace = string.Empty;
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenFacesRefresh(faceContext.m_inputFacesXml));
		}
	}
	
	override void InitOutputContext(TerjeStartScreenContextBase context)
	{
		super.InitOutputContext(context);
		
		TerjeStartScreenContextFace faceContext = TerjeStartScreenContextFace.Cast(context);
		if (faceContext != null)
		{
			faceContext.m_outputClassname = m_currentFace;
		}
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenFacesRefresh))
		{
			DestroyAllChildren();
			
			TerjeWidgetCommand_TerjeStartScreenFacesRefresh refreshCommand = TerjeWidgetCommand_TerjeStartScreenFacesRefresh.Cast(command);
			for (int i = 0; i < refreshCommand.m_facesXml.GetChildrenCount(); i++)
			{
				CreateFaceItemWidget(refreshCommand.m_facesXml.GetChild(i));
			}
			
			m_nextButton = TerjeWidgetButton.Cast(CreateTerjeWidgetEx(TerjeWidgetButton, m_nextButtonPanel));
			m_nextButton.SetText("#STR_USRACT_NEXT_ACTION");
			m_nextButton.SetEnabled(false);
			m_nextButton.OnClickEvent.Insert(OnClickNextButton);
		}
	}
	
	protected void OnClickNextButton(TerjeWidgetButton widget)
	{
		if (m_currentFace != string.Empty)
		{
			ExecuteNextPage();
		}
	}
	
	protected void CreateFaceItemWidget(TerjeXmlObject m_faceXml)
	{
		if (!m_faceXml)
			return;
		
		string classname;
		if (!m_faceXml.FindAttribute("classname", classname))
			return;
		
		string icon;
		if (!m_faceXml.FindAttribute("icon", icon))
		{
			return;
		}
		
		string background;
		TerjeStartScreenItemFace itemWidget = TerjeStartScreenItemFace.Cast(CreateTerjeWidgetEx(TerjeStartScreenItemFace, m_facesGrid));
		if (m_faceXml.FindAttribute("background", background))
		{
			itemWidget.SetBackground(background);
		}
		
		itemWidget.SetValid(m_faceXml.EqualAttribute("$valid", "1"));
		itemWidget.SetIcon(icon);
		itemWidget.SetSelected(false);
		itemWidget.SetUserParam("face", new Param1<string>(classname));
		itemWidget.OnClickEvent.Insert(OnFaceItemClick);
	}
	
	protected void OnFaceItemClick(TerjeStartScreenItemFace w)
	{
		w.SetSelected(true);
		for (int i = 0; i < GetChildrenCount(); i++)
		{
			TerjeStartScreenItemFace childItem = TerjeStartScreenItemFace.Cast(GetChild(i));
			if (childItem != null && childItem != w)
			{
				childItem.SetSelected(false);
			}
		}
		
		Param1<string> faceParam = Param1<string>.Cast(w.GetUserParam("face"));
		if (faceParam != null)
		{
			m_currentFace = faceParam.param1;
			if ((m_nextButton != null) && (m_currentFace != string.Empty))
			{
				m_nextButton.SetEnabled(true);
			}
		}
	}
}

class TerjeWidgetCommand_TerjeStartScreenFacesRefresh : TerjeWidgetCommand
{
	ref TerjeXmlObject m_facesXml;
	
	void TerjeWidgetCommand_TerjeStartScreenFacesRefresh(TerjeXmlObject facesXml)
	{
		m_facesXml = facesXml;
	}
}