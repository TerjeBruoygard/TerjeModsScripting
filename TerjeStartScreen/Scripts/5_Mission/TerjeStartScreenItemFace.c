// <copyright file="TerjeStartScreenItemFace.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenItemFace : TerjeWidgetBase
{
	protected ImageWidget m_buttonImage;
	protected ImageWidget m_buttonBackground;
	protected ImageWidget m_buttonForeground;
	protected ImageWidget m_buttonLocked;
	protected Widget m_buttonActor;
	protected bool m_valid;
	
	// void ScriptInvoker(TerjeStartScreenItemFace widget)
	ref ScriptInvoker OnClickEvent = new ScriptInvoker;
	
	override void OnInit()
	{
		super.OnInit();
		m_buttonImage = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeFaceItemImg"));
		m_buttonBackground = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeFaceItemBac"));
		m_buttonForeground = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeFaceItemFor"));
		m_buttonLocked = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeFaceItemLock"));
		m_buttonActor = GetNativeWidget().FindAnyWidget("TerjeFaceItemBtn");
		m_valid = false;
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/ItemFace.layout";
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_FaceSelect))
		{
			if (!m_valid)
			{
				m_buttonBackground.SetColor(ARGB(255, 112, 60, 60));
				m_buttonForeground.SetColor(ARGB(255, 112, 60, 60));
			}
			else if (TerjeWidgetCommand_FaceSelect.Cast(command).m_state)
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
		else if (command.IsInherited(TerjeWidgetCommand_FaceIcon))
		{
			m_buttonImage.LoadImageFile(0, TerjeStringHelper.FixTexturePath(TerjeWidgetCommand_FaceIcon.Cast(command).m_path));
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_FaceBackground))
		{
			m_buttonBackground.LoadImageFile(0, TerjeStringHelper.FixTexturePath(TerjeWidgetCommand_FaceBackground.Cast(command).m_path));
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_FaceValid))
		{
			bool isValid = TerjeWidgetCommand_FaceValid.Cast(command).m_state;
			m_buttonLocked.Show(!isValid);
			m_buttonLocked.SetColor(ARGB(50, 255, 255, 255));
			return;
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if ((m_buttonActor != null) && (w == m_buttonActor) && (button == 0) && m_valid)
		{
			PushCommand(new TerjeWidgetCommand_Clicked(button));
			return true;
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	void SetSelected(bool state)
	{
		PushCommand(new TerjeWidgetCommand_FaceSelect(state));
	}
	
	void SetIcon(string path)
	{
		PushCommand(new TerjeWidgetCommand_FaceIcon(path));
	}
	
	void SetBackground(string path)
	{
		PushCommand(new TerjeWidgetCommand_FaceBackground(path));
	}
	
	void SetValid(bool state)
	{
		m_valid = state;
		PushCommand(new TerjeWidgetCommand_FaceValid(state));
	}
}

class TerjeWidgetCommand_FaceIcon : TerjeWidgetCommand_Image {}
class TerjeWidgetCommand_FaceBackground : TerjeWidgetCommand_Image {}
class TerjeWidgetCommand_FaceSelect : TerjeWidgetCommand
{
	bool m_state;
	
	void TerjeWidgetCommand_FaceSelect(bool state)
	{
		m_state = state;
	}
}

class TerjeWidgetCommand_FaceValid : TerjeWidgetCommand
{
	bool m_state;
	
	void TerjeWidgetCommand_FaceValid(bool state)
	{
		m_state = state;
	}
}

