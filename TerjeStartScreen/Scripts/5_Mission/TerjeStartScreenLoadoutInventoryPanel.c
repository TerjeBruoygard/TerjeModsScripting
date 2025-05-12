// <copyright file="TerjeStartScreenLoadoutInventoryPanel.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenLoadoutInventoryPanel : TerjeWidgetStackArea
{
	protected PlayerBase m_player;
	protected bool m_isInventoryDirty = false;
	
	void TerjeStartScreenLoadoutInventoryPanel()
	{
		m_player = PlayerBase.Cast(GetGame().GetPlayer());
		if (m_player && m_player.OnTerjeAttachmentChangedEvent)
		{
			m_player.OnTerjeAttachmentChangedEvent.Insert(InventoryLayoutMarkDirty);
		}
	}
	
	void ~TerjeStartScreenLoadoutInventoryPanel()
	{
		if (m_player && m_player.OnTerjeAttachmentChangedEvent)
		{
			m_player.OnTerjeAttachmentChangedEvent.Remove(InventoryLayoutMarkDirty);
		}
	}
	
	override void OnInit()
	{
		super.OnInit();
		m_isInventoryDirty = true;
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		if (m_isInventoryDirty)
		{
			m_isInventoryDirty = false;
			Clear();
			BuildLayout();
			RecalculateLayout();
		}
	}
	
	protected void InventoryLayoutMarkDirty(string slotName, EntityAI entity, bool state)
	{
		if (state && entity)
		{
			m_isInventoryDirty = true;
		}
	}
	
	protected void BuildLayout()
	{
		TerjeWidgetEntityInventory entityInvWidget;
		if (m_player)
		{
			string title = "#STR_TERJESTARTSCREEN_PAGE_LOADOUT_TITLE2";
			entityInvWidget = TerjeWidgetEntityInventory.Cast(CreateChildWidget(TerjeWidgetEntityInventory));
			entityInvWidget.SetEntityImmediately(m_player, TerjeWidgetEntityInvHeaderType.PLAYER, title);
			
			if (m_player.GetItemInHands())
			{
				entityInvWidget = TerjeWidgetEntityInventory.Cast(CreateChildWidget(TerjeWidgetEntityInventory));
				entityInvWidget.SetEntityImmediately(m_player.GetItemInHands(), TerjeWidgetEntityInvHeaderType.DEFAULT);
			}
			
			int attCount = m_player.GetInventory().AttachmentCount();
			for ( int attIdx = 0; attIdx < attCount; attIdx++ )
			{
				EntityAI attachment = m_player.GetInventory().GetAttachmentFromIndex(attIdx);
				if (IsDisplayableAttachment(attachment))
				{
					entityInvWidget = TerjeWidgetEntityInventory.Cast(CreateChildWidget(TerjeWidgetEntityInventory));
					entityInvWidget.SetEntityImmediately(attachment, TerjeWidgetEntityInvHeaderType.DEFAULT);
				}
			}
		}
	}
	
	protected bool IsDisplayableAttachment(EntityAI attachment)
	{
		if (attachment && attachment.GetInventory())
		{
			if (attachment.GetInventory().AttachmentCount() > 0)
			{
				return true;
			}
			
			if (attachment.GetInventory().GetCargo() && attachment.GetInventory().GetCargo().GetItemCount() > 0)
			{
				return true;
			}
		}
		
		return false;
	}
}