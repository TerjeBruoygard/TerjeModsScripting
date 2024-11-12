// <copyright file="TerjeCustomLiquids.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class InspectMenuNew
{
	override void SetItem(EntityAI item)
	{
		super.SetItem(item);
		
		if (item && layoutRoot)
		{
			UpdateItemInfoTerjeCustomLiquidType(layoutRoot, item);
		}
	}
	
	static void UpdateItemInfoTerjeCustomLiquidType(Widget root_widget, EntityAI item)
	{
		ItemBase itemBase = ItemBase.Cast(item);
		if (itemBase && root_widget)
		{
			int vanillaLiquidType = itemBase.GetLiquidType();
			int terjeLiquidType = itemBase.GetTerjeLiquidType();
			if (vanillaLiquidType == LIQUID_TERJE_CUSTOM && terjeLiquidType > 0)
			{
				ref LiquidInfo liquidInfo;
				if (TerjeCustomLiquids.GetInstance().m_LiquidInfosByType.Find(terjeLiquidType, liquidInfo))
				{
					InspectMenuNew.WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", liquidInfo.m_LiquidDisplayName, Colors.COLOR_LIQUID);
				}
			}
		}
	}
};

modded class ItemManager
{
	override void PrepareTooltip(EntityAI item, int x = 0, int y = 0)
	{
		super.PrepareTooltip(item, x, y);
		
		if (item && m_TooltipWidget && !IsDragging())
		{
			InspectMenuNew.UpdateItemInfoTerjeCustomLiquidType(m_TooltipWidget, item);
		}
	}
};
