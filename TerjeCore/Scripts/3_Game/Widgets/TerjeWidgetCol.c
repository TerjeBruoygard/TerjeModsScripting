// <copyright file="TerjeWidgetCol.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetCol : TerjeWidgetBase
{
	private ref array<float> m_elementsWeight = new array<float>;
	private float m_totalWeight = 0;
	
	override void OnInit()
	{
		super.OnInit();
		RecalculateLayout();
	}
	
	void RecalculateLayout()
	{
		PushPostCommand(new TerjeWidgetCommand_ColRecalc());
	}
	
	void RecalculateLayoutImmediately()
	{
		float ownerTop;
		float ownerLeft;
		float ownerWidth;
		float ownerHeight;
		Widget nativeOwner = GetNativeWidget();
		nativeOwner.GetScreenPos(ownerLeft, ownerTop);
		nativeOwner.GetScreenSize(ownerWidth, ownerHeight);
		
		float offset = 0;
		int count = GetChildrenCount();
		for (int i = 0; i < count; i++)
		{
			Widget nativeChild = GetChild(i).GetNativeWidget();
			if (nativeChild != null)
			{
				float weight = m_elementsWeight.Get(i);
				float height = ownerHeight * (weight / m_totalWeight);
				nativeChild.SetScreenPos(ownerLeft, ownerTop + offset);
				nativeChild.SetScreenSize(ownerWidth, height);
				offset = offset + height;
			}
		}
	}
	
	TerjeWidgetBase CreateChildWidget(typename name, float weight)
	{
		TerjeWidgetBase element = CreateTerjeWidget(name);
		if (element != null)
		{
			m_totalWeight = m_totalWeight + weight;
			m_elementsWeight.Insert(weight);
		}
		
		return element;
	}
	
	override void DestroyAllChildren()
	{
		m_elementsWeight.Clear();
		m_totalWeight = 0;
		super.DestroyAllChildren();
	}
	
	override void DestroyTerjeWidget(TerjeWidgetBase widget)
	{
		if (widget)
		{
			int index = m_terjeWidgets.Find(widget);
			if (index != -1)
			{
				m_elementsWeight.Remove(index);
			}
		}
		
		super.DestroyTerjeWidget(widget);
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_ColRecalc) && m_totalWeight > 0)
		{
			RecalculateLayoutImmediately();
		}
	}
}

class TerjeWidgetCommand_ColRecalc : TerjeWidgetCommand
{
}