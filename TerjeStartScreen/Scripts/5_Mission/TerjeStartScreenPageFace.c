// <copyright file="TerjeStartScreenPageFace.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenPageFace : TerjeStartScreenPageBase
{
	protected Widget m_nextButton;
	protected Widget m_facesGrid;
	protected string m_currentFace;
	
	override void OnInit()
	{
		super.OnInit();
		m_nextButton = GetNativeWidget().FindAnyWidget("ButtonOk");
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
		
		if (command.IsInherited(TerjeWidgetCommand_Clicked))
		{
			if (m_currentFace != string.Empty)
			{
				ExecuteNextPage();
			}
			
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenFacesRefresh))
		{
			DestroyAllChildren();
			
			TerjeWidgetCommand_TerjeStartScreenFacesRefresh refreshCommand = TerjeWidgetCommand_TerjeStartScreenFacesRefresh.Cast(command);
			for (int i = 0; i < refreshCommand.m_facesXml.GetChildrenCount(); i++)
			{
				CreateFaceItemWidget(refreshCommand.m_facesXml.GetChild(i));
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
			icon = string.Empty;
		}
		
		TerjeStartScreenItemFace itemWidget = TerjeStartScreenItemFace.Cast(CreateTerjeWidgetEx(TerjeStartScreenItemFace, m_facesGrid));
		itemWidget.SetUserParam("face", new Param1<string>(classname));
		itemWidget.SetSelected(false);
		itemWidget.SetImage(icon);
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