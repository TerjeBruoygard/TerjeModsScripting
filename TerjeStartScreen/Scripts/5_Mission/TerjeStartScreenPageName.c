// <copyright file="TerjeStartScreenPageName.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenPageName : TerjeStartScreenPageBase
{
	protected Widget m_windowGrid;
	protected EditBoxWidget m_firstName;
	protected EditBoxWidget m_lastName;
	protected TextWidget m_infoText;
	protected Widget m_nextButton;
	protected bool m_inputBlocked = false;
	protected bool m_lastNameRequired = false;
	
	protected string m_outputFirstName = "";
	protected string m_outputLastName = "";
	protected string m_nameFilter = "";
	protected int m_nameLengthMin = 3;
	protected int m_nameLengthMax = 16;
	
	override void OnInit()
	{
		super.OnInit();
		
		m_windowGrid = GetNativeWidget().FindAnyWidget("TextInputDialogWindow");
		m_firstName = EditBoxWidget.Cast(GetNativeWidget().FindAnyWidget("PrimaryEditBox"));
		m_lastName = EditBoxWidget.Cast(GetNativeWidget().FindAnyWidget("SecondEditBox"));
		m_infoText = TextWidget.Cast(GetNativeWidget().FindAnyWidget("MessageText"));
		m_nextButton = GetNativeWidget().FindAnyWidget("ButtonOk");
		GetTerjeRPC().RegisterHandler("startscreen.name.verify", this, "OnTerjeStartScreenNameVerifyCallback");
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/PageName.layout";
	}
	
	override void InitInputContext(TerjeStartScreenContextBase context)
	{
		super.InitInputContext(context);
		
		TerjeStartScreenContextName nameContext = TerjeStartScreenContextName.Cast(context);
		if (nameContext != null)
		{
			m_nameFilter = nameContext.m_inputAllowedCharacters;
			m_nameFilter.ToUpper();
			
			m_outputFirstName = string.Empty;
			m_outputLastName = string.Empty;
			m_nameLengthMin = nameContext.m_inputLengthMin;
			m_nameLengthMax = nameContext.m_inputLengthMax;
			m_lastNameRequired = nameContext.m_inputLastNameEnabled;
			
			SetInfoMessage("");
		}
	}
	
	override void InitOutputContext(TerjeStartScreenContextBase context)
	{
		super.InitOutputContext(context);
		
		TerjeStartScreenContextName nameContext = TerjeStartScreenContextName.Cast(context);
		if (nameContext != null)
		{
			nameContext.m_outputFirstName = m_outputFirstName;
			nameContext.m_outputLastName = m_outputLastName;
		}
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_Clicked))
		{
			if (!m_inputBlocked)
			{
				m_inputBlocked = true;
				if (m_lastNameRequired)
				{
					if (VerifyNameString(m_firstName.GetText(), m_outputFirstName) && VerifyNameString(m_lastName.GetText(), m_outputLastName))
					{
						GetTerjeRPC().SendToServer("startscreen.name.verify", new Param1<string>(m_outputFirstName + " " + m_outputLastName));
					}
					else
					{
						m_inputBlocked = false;
					}
				}
				else
				{
					if (VerifyNameString(m_firstName.GetText(), m_outputFirstName))
					{
						GetTerjeRPC().SendToServer("startscreen.name.verify", new Param1<string>(m_outputFirstName));
					}
					else
					{
						m_inputBlocked = false;
					}
				}
			}
			
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_Text))
		{
			string infoText = TerjeWidgetCommand_Text.Cast(command).m_text;
			if (infoText == string.Empty)
			{
				m_infoText.Show(false);
			}
			else
			{
				m_infoText.Show(true);
				m_infoText.SetText(infoText);
			}
			
			m_windowGrid.FindAnyWidget("PanelWidgetLastName").Show(m_lastNameRequired);
			m_windowGrid.Update();
			return;
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if ((m_nextButton != null) && (w == m_nextButton) && (button == 0) && (!m_inputBlocked))
		{
			PushCommand(new TerjeWidgetCommand_Clicked(button));
			return true;
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	void SetInfoMessage(string text)
	{
		PushCommand(new TerjeWidgetCommand_Text(text));
	}
	
	protected bool VerifyNameString(string input, out string output)
	{
		output = string.Empty;
		
		int length = input.LengthUtf8();
		if (length < m_nameLengthMin)
		{
			SetInfoMessage(string.Format(GetNativeWidget().TranslateString("#STR_TERJESTARTSCREEN_PAGE_NAME_ERR1"), m_nameLengthMin));
			return false;
		}
		
		if (length > m_nameLengthMax)
		{
			SetInfoMessage(string.Format(GetNativeWidget().TranslateString("#STR_TERJESTARTSCREEN_PAGE_NAME_ERR2"), m_nameLengthMax));
			return false;
		}
		
		for (int i = 0; i < length; i++)
		{
			string symbol = input.SubstringUtf8(i, 1);
			symbol.ToUpper();
			
			if (m_nameFilter.IndexOf(symbol) == -1)
			{
				SetInfoMessage("#STR_TERJESTARTSCREEN_PAGE_NAME_ERR3 '" + symbol + "'");
				return false;
			}
			
			if (i > 0)
			{
				symbol.ToLower();
			}
			
			output += symbol;
		}
		
		return true;
	}
	
	protected void OnTerjeStartScreenNameVerifyCallback(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param1<bool> data;
		if (!ctx.Read(data))
		{
			return;
		}
		
		if (data.param1)
		{
			ExecuteNextPage();
		}
		else
		{
			SetInfoMessage("#STR_TERJESTARTSCREEN_PAGE_NAME_ERR4");
		}
		
		m_inputBlocked = false;
	}
}