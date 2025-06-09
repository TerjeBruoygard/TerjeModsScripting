// <copyright file="TerjeStartScreenLoadoutSelectionsPanel.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenLoadoutSelectionsPanel : TerjeWidgetStackArea
{
	protected ref array<TerjeWidgetStackList> m_selectors = new array<TerjeWidgetStackList>;
	
	ref ScriptInvoker OnChangedEvent = new ScriptInvoker;
	
	void SetLoadoutData(TerjeXmlObject loadout)
	{
		m_selectors.Clear();
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
			if (selectorItem.EqualAttribute("$visible", "1"))
			{
				TerjeWidgetListItem listItem = stackList.CreateItemWidget(i.ToString(), selectorItem.EqualAttribute("$selected", "1"));
				BuildSelectorItem(listItem, selectorItem, usePoints);
			}
		}
		
		m_selectors.Insert(stackList);
	}
	
	protected void BuildSelectorItem(TerjeWidgetListItem listItem, TerjeXmlObject selectorItem, bool usePoints)
	{
		int costValue = -1;
		string costStr;
		if (usePoints && selectorItem.FindAttribute("cost", costStr))
		{
			costValue = costStr.ToInt();
			if (costValue < 0)
			{
				costValue = 0;
			}
			
			listItem.SetUserParam("cost", new Param1<int>(costValue));
		}
		
		TerjeWidgetStackArea groupStack = TerjeWidgetStackArea.Cast(listItem.CreateChildWidget(TerjeWidgetStackArea));
		if (selectorItem.GetName() == "Group")
		{
			for (int i = 0; i < selectorItem.GetChildrenCount(); i++)
			{
				BuildSelectorItemRow(groupStack, selectorItem.GetChild(i), i, costValue);
			}
		}
		else if (selectorItem.GetName() == "Item")
		{
			BuildSelectorItemRow(groupStack, selectorItem, 0, costValue);
		}
		
		bool isValid = BuildSelectorItemHandler(groupStack, selectorItem);
		listItem.SetUserParam("valid", new Param1<bool>(isValid));
		listItem.SetUserParam("xml", new Param1<TerjeXmlObject>(selectorItem));
	}
	
	protected void BuildSelectorItemRow(TerjeWidgetStackArea groupStack, TerjeXmlObject selectorItem, int index, int cost)
	{
		string displayName;
		if (!selectorItem.FindAttribute("displayName", displayName))
		{
			displayName = string.Empty;
		}
		
		string classname;
		if (selectorItem.FindAttribute("classname", classname))
		{
			TerjeWidgetEntityLocalRow entityRow = TerjeWidgetEntityLocalRow.Cast(groupStack.CreateChildWidget(TerjeWidgetEntityLocalRow));
			entityRow.SetLocalEntityImmediately(classname, displayName);
			if ((cost >= 0) && (index == 0))
			{
				BuildSelectorItemCost(entityRow, cost);
			}
		}
	}
	
	protected bool BuildSelectorItemHandler(TerjeWidgetStackArea groupStack, TerjeXmlObject selectorItem)
	{
		bool result = true;
		string validStr;
		if (selectorItem.FindAttribute("$valid", validStr))
		{
			string handlerMsg;
			result = (validStr == "1");
			if (selectorItem.FindAttribute("$handlerMessage", handlerMsg))
			{
				TerjeWidgetText textWidget;
				TerjeWidgetSpacer.Cast(groupStack.CreateChildWidget(TerjeWidgetSpacerH)).SetSpacingImmediately(12);
				if (result)
				{
					textWidget = TerjeWidgetText.Cast(groupStack.CreateChildWidget(TerjeWidgetTextSmall));
				}
				else
				{
					textWidget = TerjeWidgetText.Cast(groupStack.CreateChildWidget(TerjeWidgetTextError));
				}
				
				textWidget.SetTextImmediately(handlerMsg);
				TerjeWidgetSpacer.Cast(groupStack.CreateChildWidget(TerjeWidgetSpacerH)).SetSpacingImmediately(24);
			}
		}
		
		return result;
	}
	
	protected void BuildSelectorItemCost(TerjeWidgetEntityLocalRow entityRow, int pointsCost)
	{
		TerjeWidgetText textWidget = TerjeWidgetText.Cast(entityRow.CreateAdditionalContentWidget(TerjeWidgetLoadoutItemPoints));
		textWidget.SetTextImmediately(pointsCost.ToString());
	}
	
	protected void OnSelectorItemChanged(TerjeWidgetStackList parent, TerjeWidgetListItem item, bool state)
	{
		Param1<TerjeXmlObject> selectorXmlParam = Param1<TerjeXmlObject>.Cast(parent.GetUserParam("xml"));
		if ((selectorXmlParam != null) && (selectorXmlParam.param1 != null))
		{
			TerjeXmlObject selectorXml = selectorXmlParam.param1;
			int index = item.GetItemId().ToInt();
			TerjeXmlObject selectorItem = selectorXml.GetChild(index);
			if (selectorItem != null)
			{
				string actualState;
				if (!selectorItem.FindAttribute("$selected", actualState))
				{
					actualState = "0";
				}
				
				string pointsStr;
				if (selectorXml.FindAttribute("$points", pointsStr))
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
	
	bool ValidateSelectors()
	{
		if (m_selectors != null)
		{
			foreach (TerjeWidgetStackList selector : m_selectors)
			{
				if (selector != null)
				{
					for (int i = 0; i < selector.GetChildrenCount(); i++)
					{
						TerjeWidgetListItem iterWidget = TerjeWidgetListItem.Cast(selector.GetChild(i));
						if ((iterWidget != null) && (iterWidget.IsSelected()))
						{
							Param1<bool> iterValid = Param1<bool>.Cast(iterWidget.GetUserParam("valid"));
							if ((iterValid != null) && (!iterValid.param1))
							{
								return false;
							}
						}
					}
				}
			}
		}
		
		return true;
	}
}