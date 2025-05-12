// <copyright file="TerjeStartScreenLoadoutSelectionsPanel.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenLoadoutSelectionsPanel : TerjeWidgetStackArea
{
	ref ScriptInvoker OnChangedEvent = new ScriptInvoker;
	
	void SetLoadoutData(TerjeXmlObject loadout)
	{
		Clear();
		BuildLayout(loadout);
		RecalculateLayout();
	}
	
	protected void BuildLayout(TerjeXmlObject loadout)
	{
		if (!loadout)
			return;
		
		TerjeXmlObject itemsXml = loadout.GetChildByNodeName("Items");
		if (itemsXml == null)
			return;
		
		bool isHeaderCreated = false;
		for (int i = 0; i < itemsXml.GetChildrenCount(); i++)
		{
			TerjeXmlObject selectorXml = itemsXml.GetChild(i);
			if (selectorXml != null && selectorXml.IsObjectNode() && (selectorXml.GetName() == "Selector") && selectorXml.EqualAttribute("$visible", "1"))
			{
				if (!isHeaderCreated)
				{
					isHeaderCreated = true;
					TerjeWidgetHeaderPanel panel = TerjeWidgetHeaderPanel.Cast(CreateChildWidget(TerjeWidgetPrimaryHeaderPanel));
					panel.SetHeaderTextImmediately("#STR_TERJESTARTSCREEN_PAGE_LOADOUT_TITLE3");
				}
				
				BuildSelectorLayout(selectorXml);
			}
		}
		
		TerjeWidgetSpacer.Cast(CreateChildWidget(TerjeWidgetSpacerH)).SetSpacingImmediately(8);
	}
	
	protected void BuildSelectorLayout(TerjeXmlObject selector)
	{
		string displayName;
		if (!selector.FindAttribute("displayName", displayName))
		{
			displayName = string.Empty;
		}
		
		TerjeWidgetHeaderPanel panel = TerjeWidgetHeaderPanel.Cast(CreateChildWidget(TerjeWidgetSecondaryHeaderPanel));
		panel.SetHeaderTextImmediately(displayName);
		
		TerjeXmlObject selectorItem;
		TerjeWidgetListItem listItem;
		TerjeWidgetStackList stackList = TerjeWidgetStackList.Cast(panel.CreateContentWidget(TerjeWidgetStackList));
		stackList.SetUserParam("xml", new Param1<TerjeXmlObject>(selector));
		stackList.OnItemSelectedEvent.Insert(OnSelectorItemChanged);
		
		if (selector.EqualAttribute("type", "MULTIPLE"))
		{
			stackList.AllowMultipleSelections(true);
		}
		
		bool usePoints = false;
		string pointsStr = string.Empty;
		TerjeWidgetLoadoutPoints pointsWidget;
		if (selector.FindAttribute("$points", pointsStr))
		{
			string pointsIcon = string.Empty;
			if (!selector.FindAttribute("pointsIcon", pointsIcon) || (pointsIcon == string.Empty))
			{
				pointsIcon = "set:TerjeStartScreen_icons image:tss_point";
			}
			
			pointsIcon = TerjeStringHelper.FixTexturePath(pointsIcon);
			pointsWidget = TerjeWidgetLoadoutPoints.Cast(panel.CreateHeaderWidget(TerjeWidgetLoadoutPoints));
			pointsWidget.SetPointsData(pointsIcon, pointsStr.ToInt());
			stackList.SetUserParam("pwidget", new Param1<TerjeWidgetLoadoutPoints>(pointsWidget));
			usePoints = true;
		}
		
		for (int i = 0; i < selector.GetChildrenCount(); i++)
		{
			selectorItem = selector.GetChild(i);
			listItem = stackList.CreateItemWidget(i.ToString(), selectorItem.EqualAttribute("$selected", "1"));
			BuildSelectorItem(listItem, selectorItem, usePoints);
		}
	}
	
	protected void BuildSelectorItem(TerjeWidgetListItem listItem, TerjeXmlObject selectorItem, bool usePoints)
	{
		int costValue = 0;
		string costStr;
		if (usePoints && selectorItem.FindAttribute("cost", costStr))
		{
			costValue = costStr.ToInt();
			listItem.SetUserParam("cost", new Param1<int>(costValue));
		}
		
		string classname;
		string displayName;
		TerjeWidgetEntityLocalRow entityRow;
		if (selectorItem.GetName() == "Group")
		{
			TerjeWidgetStackArea groupStack = TerjeWidgetStackArea.Cast(listItem.CreateChildWidget(TerjeWidgetStackArea));
			for (int i = 0; i < selectorItem.GetChildrenCount(); i++)
			{
				TerjeXmlObject selectorSubitem = selectorItem.GetChild(i);
				if (!selectorSubitem.FindAttribute("displayName", displayName))
				{
					displayName = string.Empty;
				}
				
				if (selectorSubitem.FindAttribute("classname", classname))
				{
					entityRow = TerjeWidgetEntityLocalRow.Cast(groupStack.CreateChildWidget(TerjeWidgetEntityLocalRow));
					entityRow.SetLocalEntityImmediately(classname, displayName);
					if (usePoints && (i == 0))
					{
						BuildSelectorItemCost(entityRow, costValue);
					}
				}
			}
		}
		else if (selectorItem.GetName() == "Item")
		{
			if (!selectorItem.FindAttribute("displayName", displayName))
			{
				displayName = string.Empty;
			}
			
			if (selectorItem.FindAttribute("classname", classname))
			{
				entityRow = TerjeWidgetEntityLocalRow.Cast(listItem.CreateChildWidget(TerjeWidgetEntityLocalRow));
				entityRow.SetLocalEntityImmediately(classname, displayName);
				if (usePoints)
				{
					BuildSelectorItemCost(entityRow, costValue);
				}
			}
		}
	}
	
	protected void BuildSelectorItemCost(TerjeWidgetEntityLocalRow entityRow, int pointsCost)
	{
		TerjeWidgetText textWidget = TerjeWidgetText.Cast(entityRow.CreateAdditionalContentWidget(TerjeWidgetLoadoutItemPoints));
		textWidget.SetTextImmediately(pointsCost.ToString());
	}
	
	protected void OnSelectorItemChanged(TerjeWidgetStackList parent, TerjeWidgetListItem item, bool state)
	{
		TerjeXmlObject selector = (Param1<TerjeXmlObject>.Cast(parent.GetUserParam("xml"))).param1;
		if (selector != null)
		{
			int index = item.GetItemId().ToInt();
			TerjeXmlObject selectorItem = selector.GetChild(index);
			if (selectorItem != null)
			{
				string actualState;
				if (!selectorItem.FindAttribute("$selected", actualState))
				{
					actualState = "0";
				}
				
				string pointsStr;
				if (selector.FindAttribute("$points", pointsStr))
				{
					int pointsInt = pointsStr.ToInt();
					Param1<TerjeWidgetLoadoutPoints> pointsWidgetParam = Param1<TerjeWidgetLoadoutPoints>.Cast(parent.GetUserParam("pwidget"));
					if (pointsWidgetParam != null && pointsWidgetParam.param1 != null)
					{
						for (int i = 0; i < parent.GetChildrenCount(); i++)
						{
							TerjeWidgetListItem iterWidget = TerjeWidgetListItem.Cast(parent.GetChild(i));
							if (iterWidget != null)
							{
								Param1<int> iterCost = Param1<int>.Cast(iterWidget.GetUserParam("cost"));
								if (iterCost != null && iterWidget.IsSelected())
								{
									pointsInt -= iterCost.param1;
								}
							}
						}
						
						if (pointsInt >= 0)
						{
							pointsWidgetParam.param1.SetPointsData(string.Empty, pointsInt);
						}
						else if (state)
						{
							item.SetSelected(false);
							return;
						}
					}
				}
				
				if (state)
				{
					if (actualState != "1")
					{
						selectorItem.SetAttribute("$selected", "1");
						OnChangedEvent.Invoke();
					}
				}
				else
				{
					if (actualState != "0")
					{
						selectorItem.SetAttribute("$selected", "0");
						OnChangedEvent.Invoke();
					}
				}
			}
		}
	}
}