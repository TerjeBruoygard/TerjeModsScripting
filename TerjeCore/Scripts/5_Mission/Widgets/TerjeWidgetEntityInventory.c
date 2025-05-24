// <copyright file="TerjeWidgetEntityInventory.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetEntityInventory : TerjeWidgetBase
{
	protected Widget m_widgetHeaderPanel1;
	protected Widget m_widgetHeaderPanel2;
	protected TextWidget m_widgetHeaderText1;
	protected TextWidget m_widgetHeaderText2;
	protected ItemPreviewWidget m_widgetHeaderPreview2;
	protected WrapSpacerWidget m_widgetAttachmentsPanel;
	protected WrapSpacerWidget m_widgetCargoPanel;
	
	override void OnInit()
	{
		super.OnInit();
		m_widgetHeaderPanel1 = GetNativeWidget().FindAnyWidget("TerjeWidgetHeaderPanel1");
		m_widgetHeaderPanel2 = GetNativeWidget().FindAnyWidget("TerjeWidgetHeaderPanel2");
		m_widgetHeaderText1 = TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetHeaderText1"));
		m_widgetHeaderText2 = TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetHeaderText2"));
		m_widgetHeaderPreview2 = ItemPreviewWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetHeaderRender2"));
		m_widgetAttachmentsPanel = WrapSpacerWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetAttchPanel"));
		m_widgetCargoPanel = WrapSpacerWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeWidgetCargoPanel"));
	}
	
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetEntityInventory.layout";
	}
	
	void SetEntity(EntityAI entity, TerjeWidgetEntityInvHeaderType headerType, string title = "")
	{
		PushCommand(new TerjeWidgetCommand_SetEntityInv(entity, headerType, title));
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_SetEntityInv))
		{
			TerjeWidgetCommand_SetEntityInv setCmd = TerjeWidgetCommand_SetEntityInv.Cast(command);
			SetEntityImmediately(setCmd.m_entity, setCmd.m_headerType, setCmd.m_title);
			return;
		}
	}
	
	void SetEntityImmediately(EntityAI entity, TerjeWidgetEntityInvHeaderType headerType, string title = "")
	{
		ResetInternal();
		
		if (headerType == TerjeWidgetEntityInvHeaderType.PLAYER)
		{
			m_widgetAttachmentsPanel.SetColor(ARGB(204, 128, 128, 128));
			m_widgetHeaderPanel1.Show(true); 
		}
		else if (headerType == TerjeWidgetEntityInvHeaderType.DEFAULT)
		{
			m_widgetHeaderPanel2.Show(true); 
		}
		
		if (entity)
		{
			if (title == string.Empty)
			{
				title = entity.GetDisplayName();
			}
			
			m_widgetHeaderText1.SetText(title);
			m_widgetHeaderText2.SetText(title);
			m_widgetHeaderPreview2.SetItem(entity);
			SetAttachmentsInternal(entity);
			SetCargoInternal(entity);
		}
		
		GetNativeWidget().Update();
	}
	
	protected void ResetInternal()
	{
		m_widgetHeaderText1.SetText("");
		m_widgetHeaderText2.SetText("");
		m_widgetHeaderPreview2.SetItem(null);
		m_widgetHeaderPanel1.Show(false);
		m_widgetHeaderPanel2.Show(false);
		m_widgetAttachmentsPanel.Show(false);
		m_widgetAttachmentsPanel.SetColor(ARGB(70, 0, 0, 0));
		m_widgetCargoPanel.Show(false);
		
		while (m_widgetAttachmentsPanel.GetChildren())
		{
			m_widgetAttachmentsPanel.RemoveChild(m_widgetAttachmentsPanel.GetChildren());
		}
		
		while (m_widgetCargoPanel.GetChildren())
		{
			m_widgetCargoPanel.RemoveChild(m_widgetCargoPanel.GetChildren());
		}
	}
	
	protected void SetAttachmentsInternal(EntityAI entity)
	{
		bool displayAttachments = false;
		if (entity && entity.GetInventory())
		{
			TerjeWidgetEntityIcon icon;
			array<string> attachmentSlotNames();
			GetEntityAttachmentsSlots(entity, attachmentSlotNames);
			foreach(string attachmentSlotName : attachmentSlotNames)
			{
				int slotId = InventorySlots.GetSlotIdFromString(attachmentSlotName);
				if (entity.CanDisplayAttachmentSlot(slotId))
				{
					icon = TerjeWidgetEntityIcon.Cast(CreateTerjeWidgetEx(TerjeWidgetEntityIconMedium, m_widgetAttachmentsPanel));
					icon.SetHighlightable(true);
					icon.DisplayTooltip(true);
					
					EntityAI attachment = entity.GetInventory().FindAttachment(slotId);
					if (attachment)
					{
						icon.SetEntityImmediately(attachment);
					}
					else
					{
						string ghostIcon = GetGame().ConfigGetTextOut("CfgSlots Slot_" + attachmentSlotName + " ghostIcon");
						string slotIcon = StaticGUIUtils.VerifyIconImageString(StaticGUIUtils.IMAGESETGROUP_INVENTORY, ghostIcon);
						string slotName = InventorySlots.GetSlotDisplayName(slotId);
						icon.SetSlotIconImmediately(slotIcon, slotName, string.Empty);
					}
					
					displayAttachments = true;
				}
			}
		}
		
		m_widgetAttachmentsPanel.Show(displayAttachments);
	}
	
	protected void SetCargoInternal(EntityAI entity)
	{
		if (entity && entity.GetInventory() && entity.GetInventory().GetCargo())
		{
			CargoBase cargo = entity.GetInventory().GetCargo();
			int cargoWidth = cargo.GetWidth();
			int cargoHeight = cargo.GetHeight();
			
			if ((cargoWidth > 0) && (cargoHeight > 0))
			{
				array<TerjeWidgetCargoRow> rows();
				TerjeWidgetCargoFooter footer;
				TerjeWidgetCargoRow rowWidget;
				m_widgetCargoPanel.Show(true);
				
				for (int row = 0; row < cargoHeight; row++)
				{
					rowWidget = TerjeWidgetCargoRow.Cast(CreateTerjeWidgetEx(TerjeWidgetCargoRow, m_widgetCargoPanel));
					rowWidget.SetRowWidthImmediately(cargoWidth);
					rows.Insert(rowWidget);
				}
				
				footer = TerjeWidgetCargoFooter.Cast(CreateTerjeWidgetEx(TerjeWidgetCargoFooter, m_widgetCargoPanel));
				footer.SetRowWidthImmediately(cargoWidth);
				
				for (int entityId = 0; entityId < cargo.GetItemCount(); entityId++)
				{
					EntityAI entityItem;
					int itemRow;
					int itemCol;
					int itemWidth;
					int itemHeight;
					bool itemFlip;
					if (GetEntityInCargoInfo(cargo, entityId, entityItem, itemRow, itemCol, itemWidth, itemHeight, itemFlip))
					{
						if ((itemRow >= 0) && (itemRow < rows.Count()))
						{
							rows.Get(itemRow).SetEntityIconImmediately(entityItem, itemRow, itemCol, itemWidth, itemHeight, itemFlip);
						}
					}
				}
			}
		}
	}
	
	protected bool GetEntityInCargoInfo(CargoBase cargo, int index, out EntityAI entity, out int row, out int col, out int width, out int height, out bool flip)
	{
		entity = cargo.GetItem(index);
		if (GetGame() && entity && entity.GetInventory())
		{
			InventoryLocation invloc = new InventoryLocation;
			entity.GetInventory().GetCurrentInventoryLocation(invloc);
			GetGame().GetInventoryItemSize(InventoryItem.Cast(entity), width, height);
			if (entity.GetInventory().GetFlipCargo())
			{
				row = invloc.GetCol();
				col = invloc.GetRow();
				flip = true;
			}
			else
			{
				col = invloc.GetCol();
				row = invloc.GetRow();
				flip = false;
			}
			
			return true;
		}
		
		return false;
	}
	
	protected void GetEntityAttachmentsSlots(EntityAI entity, array<string> slots)
	{
		entity.ConfigGetTextArray("attachments", slots);
		if (entity.IsWeapon() && (!entity.ConfigIsExisting("DisplayMagazine") || entity.ConfigGetBool("DisplayMagazine")))
		{
			slots.Insert("magazine");
		}
	}
}

class TerjeWidgetCommand_SetEntityInv : TerjeWidgetCommand
{
	EntityAI m_entity;
	TerjeWidgetEntityInvHeaderType m_headerType;
	string m_title;
	
	void TerjeWidgetCommand_SetEntityInv(EntityAI entity, TerjeWidgetEntityInvHeaderType headerType, string title)
	{
		m_entity = entity;
		m_headerType = headerType;
		m_title = title;
	}
}

enum TerjeWidgetEntityInvHeaderType
{
	NONE, DEFAULT, PLAYER
}