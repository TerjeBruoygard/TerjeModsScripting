// <copyright file="TerjeStartScreenItemFace.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenItemFace : TerjeWidgetBase
{
	protected ImageWidget m_buttonImage;
	protected Widget m_buttonBackground;
	protected Widget m_buttonForeground;
	protected Widget m_buttonActor;
	
	// void ScriptInvoker(TerjeStartScreenItemFace widget)
	ref ScriptInvoker OnClickEvent = new ScriptInvoker;
	
	override void OnInit()
	{
		super.OnInit();
		m_buttonImage = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeFaceItemImg"));
		m_buttonBackground = GetNativeWidget().FindAnyWidget("TerjeFaceItemBac");
		m_buttonForeground = GetNativeWidget().FindAnyWidget("TerjeFaceItemFor");
		m_buttonActor = GetNativeWidget().FindAnyWidget("TerjeFaceItemBtn");
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/ItemFace.layout";
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_ItemPageSelect))
		{
			if (TerjeWidgetCommand_ItemPageSelect.Cast(command).m_state)
			{
				m_buttonBackground.SetColor(ARGB(255, 60, 113, 84));
				m_buttonForeground.SetColor(ARGB(255, 60, 113, 84));
			}
			else
			{
				m_buttonBackground.SetColor(ARGB(255, 80, 80, 80));
				m_buttonForeground.SetColor(ARGB(255, 80, 80, 80));
			}
			
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_Clicked))
		{
			OnClickEvent.Invoke(this);
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_Image))
		{
			string imgPath = TerjeStringHelper.FixTexturePath(TerjeWidgetCommand_Image.Cast(command).m_path);
			if ((imgPath.Length() > 0) && (FileExist(imgPath)))
			{
				m_buttonImage.LoadImageFile(0, imgPath);
			}
			else
			{
				m_buttonImage.LoadImageFile(0, "TerjeStartScreen\\Faces\\Unknown.paa");
			}
			
			return;
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if ((m_buttonActor != null) && (w == m_buttonActor) && (button == 0))
		{
			PushCommand(new TerjeWidgetCommand_Clicked(button));
			return true;
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	void SetSelected(bool state)
	{
		PushCommand(new TerjeWidgetCommand_ItemPageSelect(state));
	}
	
	void SetImage(string path)
	{
		PushCommand(new TerjeWidgetCommand_Image(path));
	}
}

class TerjeWidgetCommand_ItemPageSelect : TerjeWidgetCommand
{
	bool m_state;
	
	void TerjeWidgetCommand_ItemPageSelect(bool state)
	{
		m_state = state;
	}
}