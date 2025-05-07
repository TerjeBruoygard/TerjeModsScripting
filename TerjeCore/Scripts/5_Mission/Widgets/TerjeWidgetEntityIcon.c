// <copyright file="TerjeWidgetEntityIcon.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetEntityIcon : TerjeWidgetBase
{
	protected bool m_highlightable = false;
	protected bool m_colorable = false;
	protected bool m_displayToolstip = false;
	protected bool m_entityTooltipVisible = false;
	protected bool m_slotTooltipVisible = false;
	protected string m_slotName = string.Empty;
	protected string m_slotDesc = string.Empty;
	
	protected Widget m_colorWidget;
	protected ItemPreviewWidget m_widgetIcon;
	protected ImageWidget m_widgetSlot;
	protected Widget m_cursorWidget;
	
	protected Widget m_quantityPanel;
	protected TextWidget m_quantityItem;
	protected ProgressBarWidget m_quantityProgress;
	protected Widget m_quantityStack;
	
	override void OnInit()
	{
		super.OnInit();
		m_colorWidget = GetNativeWidget().FindAnyWidget("TerjeWidgetIconColor");
		m_widgetIcon = ItemPreviewWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetIconRender"));
		m_widgetSlot = ImageWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetIconGhost"));
		m_cursorWidget = GetNativeWidget().FindAnyWidget("TerjeWidgetIconCursor");
		
		m_quantityPanel = GetNativeWidget().FindAnyWidget("TerjeWidgetIconQuantityPanel");
		m_quantityItem = TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetIconQuantity"));
		m_quantityProgress = ProgressBarWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetIconQuantityBar"));
		m_quantityStack = GetNativeWidget().FindAnyWidget("TerjeWidgetIconQuantityStackPanel");
	}
	
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetEntityIcon.layout";
	}
	
	void SetEntity(EntityAI entity, bool flip = false)
	{
		PushCommand(new TerjeWidgetCommand_SetEntityIcon(entity, flip));
	}
	
	void SetSlotIcon(string icon, string name, string desc)
	{
		PushCommand(new TerjeWidgetCommand_SetSlotIcon(icon, name, desc));
	}
	
	void SetHighlightable(bool value)
	{
		m_highlightable = value;
	}
	
	void SetColorable(bool value)
	{
		m_colorable = value;
	}
	
	void DisplayTooltip(bool value)
	{
		m_displayToolstip = value;
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_SetEntityIcon))
		{
			TerjeWidgetCommand_SetEntityIcon entityCmd = TerjeWidgetCommand_SetEntityIcon.Cast(command);
			SetEntityImmediately(entityCmd.m_entity, entityCmd.m_flip);
			return;
		}
		else if (command.IsInherited(TerjeWidgetCommand_SetSlotIcon))
		{
			TerjeWidgetCommand_SetSlotIcon iconCmd = TerjeWidgetCommand_SetSlotIcon.Cast(command);
			SetSlotIconImmediately(iconCmd.m_icon, iconCmd.m_name, iconCmd.m_desc);
			return;
		}
	}
	
	void SetEntityImmediately(EntityAI entity, bool flip = false)
	{
		if (entity)
		{
			m_widgetSlot.Show(false);
			m_widgetIcon.Show(true);
			m_widgetIcon.SetForceFlipEnable(true);
			m_widgetIcon.SetForceFlip(flip);
			m_widgetIcon.SetItem(entity);
			m_widgetIcon.SetModelOrientation("0 0 0");
			m_widgetIcon.SetView(entity.GetViewIndex());
			
			m_colorWidget.Show(m_colorable);
			int quantityType = QUANTITY_HIDDEN;
			if (entity.IsInherited(InventoryItem))
			{
				quantityType = QuantityConversions.HasItemQuantity(entity);
			}
			
			if (quantityType == QUANTITY_COUNT)
			{
				string quantityText = QuantityConversions.GetItemQuantityText(entity);
				if (QuantityConversions.GetItemQuantityMax(InventoryItem.Cast(entity)) == 1 || quantityText == "")
				{
					m_quantityStack.Show(false);
				}
				else
				{
					m_quantityItem.SetText(quantityText);
					m_quantityStack.Show(true);
				}

				m_quantityProgress.Show(false);
			}
			else if (quantityType == QUANTITY_PROGRESS)
			{	
				int max = entity.GetQuantityMax();
				int count = entity.ConfigGetInt("count");
				float quantity = QuantityConversions.GetItemQuantity(InventoryItem.Cast(entity));
				if (count > 0)
				{
					max = count;
				}
				
				if (max > 0)
				{
					float value = Math.Round((quantity / max) * 100);
					m_quantityProgress.SetCurrent(value);
				}

				m_quantityStack.Show(false);
				m_quantityProgress.Show(true);
			}
			
			m_quantityPanel.Show(quantityType != QUANTITY_HIDDEN);
		}
	}
	
	void SetSlotIconImmediately(string icon, string name, string desc)
	{
		m_slotName = name;
		m_slotDesc = desc;
		m_widgetIcon.Show(false);
		m_widgetSlot.Show(true);
		m_widgetSlot.LoadImageFile(0, icon);
		m_colorWidget.Show(m_colorable);
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (m_highlightable)
		{
			m_cursorWidget.Show(true);
		}
		
		if (m_displayToolstip)
		{
			if (m_widgetIcon && m_widgetIcon.IsVisible())
			{
				TerjeUiManager.GetInstance().ShowGlobalTooltip("gui/layouts/inventory_new/day_z_inventory_new_tooltip.layout", ScriptCaller.Create(SetupEntityTooltip), x, y);
				m_entityTooltipVisible = true;
			}
			else if (m_widgetSlot && m_widgetSlot.IsVisible())
			{
				TerjeUiManager.GetInstance().ShowGlobalTooltip("gui/layouts/inventory_new/day_z_inventory_new_tooltip_slot.layout", ScriptCaller.Create(SetupSlotTooltip), x, y);
				m_slotTooltipVisible = true;
			}
		}
		
		return true;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		m_cursorWidget.Show(false);
		
		if (m_entityTooltipVisible)
		{
			TerjeUiManager.GetInstance().HideGlobalTooltip();
			m_entityTooltipVisible = false;
		}
		else if (m_slotTooltipVisible)
		{
			TerjeUiManager.GetInstance().HideGlobalTooltip();
			m_slotTooltipVisible = false;
		}
		
		return true;
	}
	
	protected void SetupEntityTooltip(Widget widget)
	{
		EntityAI entity = m_widgetIcon.GetItem();
		if (entity)
		{
			InspectMenuNew.UpdateItemInfo(widget, entity);
			ItemPreviewWidget previewFrame = ItemPreviewWidget.Cast(widget.FindAnyWidget("ItemFrameWidget"));
			if (previewFrame)
			{
				previewFrame.SetItem(entity);
				previewFrame.SetView(entity.GetViewIndex());
			}
		}
	}
	
	protected void SetupSlotTooltip(Widget widget)
	{
		InspectMenuNew.UpdateSlotInfo(widget, m_slotName, m_slotDesc);
	}
}

class TerjeWidgetEntityIconSmall : TerjeWidgetEntityIcon
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetEntityIconSmall.layout";
	}
}

class TerjeWidgetEntityIconMedium : TerjeWidgetEntityIcon
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetEntityIconMid.layout";
	}
}

class TerjeWidgetEntityIconLarge : TerjeWidgetEntityIcon
{
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetEntityIconBig.layout";
	}
}

class TerjeWidgetCommand_SetEntityIcon : TerjeWidgetCommand
{
	EntityAI m_entity;
	bool m_flip;
	
	void TerjeWidgetCommand_SetEntityIcon(EntityAI entity, bool flip)
	{
		m_entity = entity;
		m_flip = flip;
	}
}

class TerjeWidgetCommand_SetSlotIcon : TerjeWidgetCommand
{
	string m_icon;
	string m_name;
	string m_desc;
	
	void TerjeWidgetCommand_SetSlotIcon(string icon, string name, string desc)
	{
		m_icon = icon;
		m_name = name;
		m_desc = desc;
	}
}