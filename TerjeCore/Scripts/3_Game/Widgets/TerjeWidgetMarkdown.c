// <copyright file="TerjeWidgetMarkdown.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetMarkdown : TerjeWidgetBase
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdown.layout";
	}
	
	void Clear()
	{
		DestroyAllChildren();
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_MarkdownSetContent))
		{
			TerjeWidgetCommand_MarkdownSetContent setCmd = TerjeWidgetCommand_MarkdownSetContent.Cast(command);
			SetContentImmediately(setCmd.m_width, setCmd.m_content);
			return;
		}
	}
	
	void SetContent(float width, array<string> lines)
	{
		PushCommand(new TerjeWidgetCommand_MarkdownSetContent(width, lines));
	}
	
	void SetContentImmediately(float width, array<string> lines)
	{
		DestroyAllChildren();
		SetWidthImmediately(width, true);
		width = width - 16;
		
		bool insideCode = false;
		TerjeWidgetSpacerH spacerWidget;
		foreach (string rawLine : lines)
		{
			string line = rawLine.Trim();
			
			if (TerjeStringHelper.StartsWith(line, "```"))
			{
				insideCode = !insideCode;
				continue;
			}
			
			if (insideCode)
			{
				TerjeWidgetText codeWidget = TerjeWidgetText.Cast(CreateTerjeWidget(TerjeWidgetMarkdownCode));
				codeWidget.SetWidthImmediately(width, true);
				codeWidget.SetTextImmediately(line);
				continue;
			}
			
			if (line == string.Empty)
			{
				spacerWidget = TerjeWidgetSpacerH.Cast(CreateTerjeWidget(TerjeWidgetSpacerH));
				spacerWidget.SetWidthImmediately(width, true);
				spacerWidget.SetSpacingImmediately(8);
				continue;
			}
			
			if (TerjeStringHelper.StartsWith(line, "---"))
			{
				TerjeWidgetMarkdownLineBreak breaklineWidget = TerjeWidgetMarkdownLineBreak.Cast(CreateTerjeWidget(TerjeWidgetMarkdownLineBreak));
				breaklineWidget.SetWidthImmediately(width, true);
				continue;
			}
			
			if (TerjeStringHelper.StartsWith(line, "["))
			{
				int linkTextEndIdx = line.IndexOf("]");
				if ((linkTextEndIdx > 0) && (line.Length() > (linkTextEndIdx + 2)) && (line.Get(linkTextEndIdx + 1) == "("))
				{
					int linkDataEndIdx = line.IndexOfFrom(linkTextEndIdx + 1, ")");
					if (linkDataEndIdx != -1)
					{
						int linkDataLng = (linkDataEndIdx - linkTextEndIdx) - 2;
						string linkText = line.Substring(1, linkTextEndIdx - 1);
						string linkData = line.Substring(linkTextEndIdx + 2, linkDataLng);
						TerjeWidgetMarkdownLink linkWidget = TerjeWidgetMarkdownLink.Cast(CreateTerjeWidget(TerjeWidgetMarkdownLink));
						linkWidget.SetWidthImmediately(width, true);
						linkWidget.SetLink(linkData, linkText);
						continue;
					}
				}
			}
			
			if (TerjeStringHelper.StartsWith(line, "!["))
			{
				int imgTextEndIdx = line.IndexOf("]");
				if ((imgTextEndIdx > 1) && (line.Length() > (imgTextEndIdx + 2)) && (line.Get(imgTextEndIdx + 1) == "("))
				{
					int imgDataEndIdx = line.IndexOfFrom(imgTextEndIdx + 1, ")");
					if (imgDataEndIdx != -1)
					{
						int imgDataLng = (imgDataEndIdx - imgTextEndIdx) - 2;
						string imgText = line.Substring(2, imgTextEndIdx - 1);
						string imgData = line.Substring(imgTextEndIdx + 2, imgDataLng);
						TerjeWidgetMarkdownImage imageWidget = TerjeWidgetMarkdownImage.Cast(CreateTerjeWidget(TerjeWidgetMarkdownImage));
						imageWidget.SetWidthImmediately(width, true);
						imageWidget.SetImageImmediately(imgData, imgText);
						continue;
					}
				}
			}
			
			if (TerjeStringHelper.StartsWith(line, "# ") && line.Length() > 2)
			{
				spacerWidget = TerjeWidgetSpacerH.Cast(CreateTerjeWidget(TerjeWidgetSpacerH));
				spacerWidget.SetWidthImmediately(width, true);
				spacerWidget.SetSpacingImmediately(8);
				
				TerjeWidgetText header1Widget = TerjeWidgetText.Cast(CreateTerjeWidget(TerjeWidgetMarkdownHeader1));
				header1Widget.SetWidthImmediately(width, true);
				header1Widget.SetTextImmediately(ProcessTextLine(line.Substring(2, line.Length() - 2)));
				
				spacerWidget = TerjeWidgetSpacerH.Cast(CreateTerjeWidget(TerjeWidgetSpacerH));
				spacerWidget.SetWidthImmediately(width, true);
				spacerWidget.SetSpacingImmediately(8);
				continue;
			}
			
			if (TerjeStringHelper.StartsWith(line, "## ") && line.Length() > 3)
			{
				spacerWidget = TerjeWidgetSpacerH.Cast(CreateTerjeWidget(TerjeWidgetSpacerH));
				spacerWidget.SetWidthImmediately(width, true);
				spacerWidget.SetSpacingImmediately(8);
				
				TerjeWidgetText header2Widget = TerjeWidgetText.Cast(CreateTerjeWidget(TerjeWidgetMarkdownHeader2));
				header2Widget.SetWidthImmediately(width, true);
				header2Widget.SetTextImmediately(ProcessTextLine(line.Substring(3, line.Length() - 3)));
				
				spacerWidget = TerjeWidgetSpacerH.Cast(CreateTerjeWidget(TerjeWidgetSpacerH));
				spacerWidget.SetWidthImmediately(width, true);
				spacerWidget.SetSpacingImmediately(8);
				continue;
			}
			
			if (TerjeStringHelper.StartsWith(line, "### ") && line.Length() > 4)
			{
				spacerWidget = TerjeWidgetSpacerH.Cast(CreateTerjeWidget(TerjeWidgetSpacerH));
				spacerWidget.SetWidthImmediately(width, true);
				spacerWidget.SetSpacingImmediately(8);
				
				TerjeWidgetText header3Widget = TerjeWidgetText.Cast(CreateTerjeWidget(TerjeWidgetMarkdownHeader3));
				header3Widget.SetWidthImmediately(width, true);
				header3Widget.SetTextImmediately(ProcessTextLine(line.Substring(4, line.Length() - 4)));
				continue;
			}
			
			if (TerjeStringHelper.StartsWith(line, "> ") && line.Length() > 2)
			{
				TerjeWidgetMarkdownBlock blockWidget = TerjeWidgetMarkdownBlock.Cast(CreateTerjeWidget(TerjeWidgetMarkdownBlock));
				blockWidget.SetWidthImmediately(width, true);
				blockWidget.SetTextImmediately(ProcessTextLine(line.Substring(2, line.Length() - 2)));
				continue;
			}
			
			if (TerjeStringHelper.StartsWith(line, "- ") && line.Length() > 2)
			{
				int listOffsetSize = rawLine.IndexOf("-");
				string listOffset = string.Empty;
				for (int i = 0; i < listOffsetSize; i++)
				{
					listOffset += rawLine.Get(i);
				}
				
				string listMarker = " • ";
				if (listOffsetSize > 0)
				{
					listMarker = " › ";
				}
				
				line = listOffset + listMarker + line.Substring(2, line.Length() - 2);
			}
			
			TerjeWidgetText textWidget = TerjeWidgetText.Cast(CreateTerjeWidget(TerjeWidgetMarkdownText));
			textWidget.SetWidthImmediately(width, true);
			textWidget.SetTextImmediately(ProcessTextLine(line));
		}
		
		spacerWidget = TerjeWidgetSpacerH.Cast(CreateTerjeWidget(TerjeWidgetSpacerH));
		spacerWidget.SetWidthImmediately(width, true);
		spacerWidget.SetSpacingImmediately(16);
		
		GetNativeWidget().Update();
	}
	
	protected string ProcessTextLine(string input)
	{
		input = ProcessTextLineTag(input, "***", "<b><i>", "</i></b>");
		input = ProcessTextLineTag(input, "**", "<b>", "</b>");
		input = ProcessTextLineTag(input, "*", "<i>", "</i>");
		return input;
	}
	
	protected string ProcessTextLineTag(string input, string mdTag, string htmlTagOpen, string htmlTagClose)
	{
		if (input == string.Empty)
		{
			return input;
		}
		
		bool state = false;
		while (true)
		{
			int index = input.IndexOfFrom(index, mdTag);
			if (index == -1)
				break;
			
			string tag;
			if (state)
			{
				tag = htmlTagClose;
			}
			else
			{
				tag = htmlTagOpen;
			}
			
			input = input.Substring(0, index) + tag + input.Substring(index + mdTag.Length(), (input.Length() - index) - mdTag.Length());
			state = !state;
		}
		
		return input;
	}
}

class TerjeWidgetCommand_MarkdownSetContent : TerjeWidgetCommand
{
	float m_width;
	ref array<string> m_content = new array<string>;
	
	void TerjeWidgetCommand_MarkdownSetContent(float width, array<string> content)
	{
		m_width = width;
		m_content.Copy(content);
	}
}

class TerjeWidgetMarkdownText : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdownText.layout";
	}
}

class TerjeWidgetMarkdownHeader1 : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdownHeader1.layout";
	}
}

class TerjeWidgetMarkdownHeader2 : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdownHeader2.layout";
	}
}

class TerjeWidgetMarkdownHeader3 : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdownHeader3.layout";
	}
}

class TerjeWidgetMarkdownLineBreak : TerjeWidgetBase
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdownLineBreak.layout";
	}
}

class TerjeWidgetMarkdownCode : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdownCode.layout";
	}
	
	override void SetTextImmediately(string text)
	{
		TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetText")).SetText(text);
		GetNativeWidget().Update();
	}
}

class TerjeWidgetMarkdownBlock : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdownBlock.layout";
	}
	
	override void SetTextImmediately(string text)
	{
		TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetText")).SetText(text);
		GetNativeWidget().Update();
	}
}

class TerjeWidgetMarkdownLink : TerjeWidgetText
{
	string m_linkUrl;
	
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdownLink.layout";
	}
	
	override void SetTextImmediately(string text)
	{
		TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetText")).SetText(text);
		GetNativeWidget().Update();
	}
	
	void SetLink(string link, string text)
	{
		m_linkUrl = link;
		SetText(text);
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_Clicked))
		{
			int button = TerjeWidgetCommand_Clicked.Cast(command).m_button;
			if (button == 0)
			{
				GetGame().OpenURL(m_linkUrl);
			}
			else
			{
				GetGame().CopyToClipboard(m_linkUrl);
			}
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		PushCommand(new TerjeWidgetCommand_Clicked(button));
		return true;
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		GetNativeWidget().FindAnyWidget("SeparatorPanel").Show(true);
		return true;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		GetNativeWidget().FindAnyWidget("SeparatorPanel").Show(false);
		return true;
	}
}

class TerjeWidgetMarkdownImage : TerjeWidgetText
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/Markdown/TerjeWidgetMarkdownImage.layout";
	}
	
	void SetImage(string path, string data)
	{
		PushCommand(new TerjeWidgetCommand_MarkdownImage(path, data));
	}
	
	void SetImageImmediately(string path, string data)
	{
		ImageWidget image = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetImage"));
		image.LoadImageFile(0, TerjeStringHelper.FixTexturePath(path));
		
		array<string> parts();
		data.Split("x", parts);
		if (parts.Count() == 2)
		{
			image.SetScreenSize(parts.Get(0).ToInt(), parts.Get(1).ToInt());
		}
		
		GetNativeWidget().Update();
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_MarkdownImage))
		{
			TerjeWidgetCommand_MarkdownImage imageCommand = TerjeWidgetCommand_MarkdownImage.Cast(command);
			SetImageImmediately(imageCommand.m_path, imageCommand.m_data);
			return;
		}
	}
}

class TerjeWidgetCommand_MarkdownImage : TerjeWidgetCommand
{
	string m_path;
	string m_data;
	
	void TerjeWidgetCommand_MarkdownImage(string path, string data)
	{
		m_path = path;
		m_data = data;
	}
}