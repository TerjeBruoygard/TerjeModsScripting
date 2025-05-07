// <copyright file="TerjeWidgetPadding.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetPadding : TerjeWidgetBase
{
	override void OnInit()
	{
		super.OnInit();
		CreateTerjeWidget(TerjeWidgetEmpty);
	}
	
	void SetPadding(float top, float right, float bottom, float left)
	{
		PushCommand(new TerjeWidgetCommand_Padding(top, right, bottom, left));
	}
	
	void SetPaddingImmediately(float top, float right, float bottom, float left)
	{
		float ownerTop;
		float ownerLeft;
		float ownerWidth;
		float ownerHeight;
		float paddingWidth = left + right;
		float paddingHeight = top + bottom;
		Widget nativeOwner = GetNativeWidget();
		Widget nativeChild = GetChild(0).GetNativeWidget();
		nativeOwner.GetScreenPos(ownerLeft, ownerTop);
		nativeOwner.GetScreenSize(ownerWidth, ownerHeight);
		nativeChild.SetScreenPos(Math.Round(ownerLeft + left), Math.Round(ownerTop + top));
		nativeChild.SetScreenSize(Math.Round(ownerWidth - paddingWidth), Math.Round(ownerHeight - paddingHeight));
	}
	
	void SetPaddingAll(float value)
	{
		PushCommand(new TerjeWidgetCommand_Padding(value, value, value, value));
	}
	
	void SetPaddingAllImmadiately(float value)
	{
		SetPaddingImmediately(value, value, value, value);
	}
	
	void SetPaddingProportional(float horizontal, float vertical)
	{
		PushCommand(new TerjeWidgetCommand_Padding(horizontal, vertical, horizontal, vertical));
	}
	
	void SetPaddingProportionalImmediately(float horizontal, float vertical)
	{
		SetPaddingImmediately(horizontal, vertical, horizontal, vertical);
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		TerjeWidgetCommand_Padding paddingCmd = TerjeWidgetCommand_Padding.Cast(command);
		if (paddingCmd != null)
		{
			SetPaddingImmediately(paddingCmd.m_top, paddingCmd.m_right, paddingCmd.m_bottom, paddingCmd.m_left);
			return;
		}
		
		super.OnCommand(command, timeslice);
	}
	
	TerjeWidgetBase CreateContentWidget(typename name)
	{
		return GetChild(0).CreateTerjeWidget(name);
	}
}

class TerjeWidgetCommand_Padding : TerjeWidgetCommand
{
	float m_top;
	float m_right;
	float m_bottom;
	float m_left;
	
	void TerjeWidgetCommand_Padding(float top, float right, float bottom, float left)
	{
		m_top = top;
		m_right = right;
		m_bottom = bottom;
		m_left = left;
	}
}