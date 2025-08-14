// <copyright file="TerjePassport.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePassport : ItemBase
{
	protected ref TerjePassportData m_passportData = null;
	
	bool HasTerjePassportData()
	{
		return m_passportData != null;
	}
	
	TerjePassportData GetTerjePassportData()
	{
		return m_passportData;
	}
	
	void InitializeTerjePassportData(PlayerBase target)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (target && target.IsAlive() && target.GetIdentity())
			{
				m_passportData = new TerjePassportData;
				m_passportData.Init(target);
			}
		}
	}
	
	void OpenTerjePassportServer(PlayerBase player)
	{
		if ((m_passportData != null) && (player != null))
		{
			NotificationSystem.SendNotificationToPlayerExtended(player, m_passportData.GetNotificationTime(), m_passportData.GetNotificationTitle(), m_passportData.GetNotificationText(), m_passportData.GetNotificationIcon());
		}
	}
	
	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner)
	{
		super.OnItemLocationChanged(old_owner, new_owner);
		
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (new_owner && !HasTerjePassportData())
			{
				PlayerBase target = PlayerBase.Cast(new_owner);
				if (!target)
				{
					target = PlayerBase.Cast(new_owner.GetHierarchyRootPlayer());
				}
				
				if (target)
				{
					InitializeTerjePassportData(target);
				}
			}
		}
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionTerjePassportOpen);
	}
	
	override void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		super.OnTerjeStoreSave(ctx);
		
		if (m_passportData != null)
		{
			m_passportData.OnTerjeStoreSave(ctx.WriteSubcontext("passport"));
		}
	}
	
	override void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		super.OnTerjeStoreLoad(ctx);
		
		TerjeStorageReadingContext passportCtx = ctx.ReadSubcontext("passport");
		if (passportCtx != null)
		{
			m_passportData = new TerjePassportData;
			m_passportData.OnTerjeStoreLoad(passportCtx);
		}
	}
}

class TerjePassportData
{
	string m_Id;
	string m_Guid;
	string m_Name;
	string m_Icon;
	bool m_IsMale;
	
	void Init(PlayerBase player)
	{
		m_Id = Math.RandomInt(1000000, 9999999).ToString();
		m_Guid = player.GetCachedID();
		m_Name = player.GetTerjeCharacterName();
		m_IsMale = player.IsMale();
		
		if (!GetPluginTerjeStartScreen().FindCharacterIconByClassname(player.GetType(), m_Icon))
		{
			m_Icon = "TerjeStartScreen/Faces/Unknown.paa";
		}
	}
	
	string GetNotificationTitle()
	{
		return m_Name;
	}
	
	string GetNotificationText()
	{
		string result = string.Empty;
		if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_PASSPORT_SHOW_NUMBER))
		{
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_PASSPORT_UNIQ_NUMBER))
			{
				result += "<b>#STR_TERJESTARTSCREEN_PASS_ID: </b>" + m_Id + "<br/>";
			}
			else
			{
				int guidHash = m_Guid.Hash();
				if (guidHash < 0)
				{
					guidHash = guidHash * -1;
				}
				
				result += "<b>#STR_TERJESTARTSCREEN_PASS_ID: </b>" + guidHash + "<br/>";
			}
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_PASSPORT_SHOW_GENDER))
		{
			if (m_IsMale)
			{
				result += "<b>#STR_TERJESTARTSCREEN_PASS_SEX: </b>#STR_TERJESTARTSCREEN_PASS_MALE <br/>";
			}
			else
			{
				result += "<b>#STR_TERJESTARTSCREEN_PASS_SEX: </b>#STR_TERJESTARTSCREEN_PASS_FEMALE <br/>";
			}
		}
		
		return result;
	}
	
	string GetNotificationIcon()
	{
		return TerjeStringHelper.FixTexturePath(m_Icon);
	}
	
	float GetNotificationTime()
	{
		return 15;
	}
	
	void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		ctx.WriteString("id", m_Id);
		ctx.WriteString("guid", m_Guid);
		ctx.WriteString("name", m_Name);
		ctx.WriteString("icon", m_Icon);
		ctx.WriteBool("gender", m_IsMale);
	}
	
	void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		ctx.ReadString("id", m_Id);
		ctx.ReadString("guid", m_Guid);
		ctx.ReadString("name", m_Name);
		ctx.ReadString("icon", m_Icon);
		ctx.ReadBool("gender", m_IsMale);
	}
}
