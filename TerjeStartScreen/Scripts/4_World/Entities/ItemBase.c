// <copyright file="ItemBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ItemBase
{
	protected ref TerjeRespawnObjectData m_terjeRespawnData = null;
	
	bool HasTerjeRespawnOwner()
	{
		return (m_terjeRespawnData != null) && (m_terjeRespawnData.ValidatePosition(GetWorldPosition()));
	}
	
	bool ValidateTerjeRespawnOwner(PlayerBase player)
	{
		if (HasTerjeRespawnOwner())
		{
			return m_terjeRespawnData.ValidateOwner(player);
		}
		
		return false;
	}
	
	bool CheckTerjeRespawnOwner(PlayerBase player)
	{
		if (HasTerjeRespawnOwner())
		{
			return m_terjeRespawnData.ValidateOwner(player);
		}
		
		return true;
	}
	
	void SetTerjeRespawnOwner(PlayerBase player)
	{
		if (player && player.GetIdentity())
		{
			m_terjeRespawnData = new TerjeRespawnObjectData;
			m_terjeRespawnData.m_Owner = player.GetIdentity().GetId();
			m_terjeRespawnData.m_Position = GetWorldPosition();
		}
		else
		{
			m_terjeRespawnData = null;
		}
	}
	
	void ResetTerjeRespawnOwner(string uid)
	{
		if ((m_terjeRespawnData != null) && (m_terjeRespawnData.m_Owner == uid))
		{
			m_terjeRespawnData = null;
		}
	}
	
	override void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		super.OnTerjeStoreSave(ctx);
		
		if ((m_terjeRespawnData != null) && m_terjeRespawnData.ValidatePosition(GetWorldPosition()))
		{
			ctx.WriteBool("tss.respobj", true);
			m_terjeRespawnData.OnTerjeStoreSave(ctx);
		}
	}
	
	override void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		super.OnTerjeStoreLoad(ctx);
		
		bool hasTerjeRespawnObjectData = false;
		if (ctx.ReadBool("tss.respobj", hasTerjeRespawnObjectData) && hasTerjeRespawnObjectData)
		{
			m_terjeRespawnData = new TerjeRespawnObjectData;
			if (!m_terjeRespawnData.OnTerjeStoreLoad(ctx))
			{
				m_terjeRespawnData = null;
			}
		}
	}
}