// <copyright file="TerjeModalDialog.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeModalDialog : UIScriptedMenu
{
	private static ref TerjeModalDialog m_Instance = null;
	static ref UIScriptedMenu GetInstance(string title, string message, Class callbackClass, string callbackFnc)
	{
		if (m_Instance == null)
		{
			m_Instance = new TerjeModalDialog();
		}
		
		m_Instance.SetMetadata(title, message, callbackClass, callbackFnc);
		return m_Instance;
	}
	
	private string m_Title = "";
	private string m_Message = "";
	private ref Param2<Class, string> m_Callback = null; 
	
	void CloseAndHandleModal(bool result)
	{
		Close();
		
		if (m_Callback != null)
		{
			if (m_Callback.param1)
			{
				auto invokeData = new Param1<bool>(result);
				GetGame().GameScript.CallFunctionParams(m_Callback.param1, m_Callback.param2, null, invokeData);
			}
			else
			{
				TerjeLog_Error("TerjeModalDialog::CloseAndHandleModal CLASS INSTANCE IS NULL FOR FUNCTION " + m_Callback.param2);
			}
			
			m_Callback = null;
		}
	}
	
	void SetMetadata(string title, string message, Class callbackClass, string callbackFnc)
	{
		m_Title = title;
		m_Message = message;
		m_Callback = new ref Param2<Class, string>(callbackClass, callbackFnc);
	}
	
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("TerjeCore/Layouts/ModalDialogYesNo.layout");
		TextWidget.Cast(layoutRoot.FindAnyWidget("Caption")).SetText(m_Title);
		TextWidget.Cast(layoutRoot.FindAnyWidget("Text")).SetText(m_Message);
		return layoutRoot;
	}
	
	override void LockControls()
	{
		super.LockControls();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_INVENTORYBLUR).Start();
		SetFocus( layoutRoot.FindAnyWidget("bNo") );
	}
	
	override void UnlockControls()
	{
		super.UnlockControls();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_INVENTORYBLUR).Stop();
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (w.GetUserID() == 1)
		{
			CloseAndHandleModal(true);
			return true;
		}
		else
		{
			CloseAndHandleModal(false);
			return true;
		}
	
		return super.OnClick(w, x, y, button);
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		if (key == KeyCode.KC_ESCAPE)
		{
			CloseAndHandleModal(false);
			return true;
		}
		else if (key == KeyCode.KC_RETURN)
		{
			CloseAndHandleModal(true);
			return true;
		}
		
		return super.OnKeyPress(w, x, y, key);
	}
};