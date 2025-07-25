// <copyright file="PlayerBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PlayerBase
{
	ref TerjeStartScreenParams m_terjeStartScreenParams = null;
	bool m_terjeLoadoutProcessing = false;
	bool m_terjeStartScreenClientReady = false;
	string m_terjeStartScreenCharNameValue = string.Empty;
	
	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame() && (GetGame().IsClient()))
		{
			TerjeRPCSingleParam("tss.name.req", null, true);
		}
	}
	
	override void OnTerjePlayerRespawned()
	{
		super.OnTerjePlayerRespawned();
		
		if (GetIdentity() != null && GetTerjeProfile() != null)
		{
			m_terjeStartScreenParams = new TerjeStartScreenParams;
			m_terjeStartScreenParams.Build(this);
			m_terjeStartScreenParams.NextServerContext(this);
			
			if (m_terjeStartScreenParams.GetActualContext())
			{
				if (GetTerjeStats() != null)
				{
					GetTerjeStats().SetStartScreenInProgress(true);
				}
				
				TerjeStreamRpc terjeRpc;
				GetTerjeRPC().StreamToClient("startscreen.ctx", GetIdentity(), terjeRpc);
				m_terjeStartScreenParams.Serialize(terjeRpc);
				terjeRpc.Flush();
				SetTerjeServerStartScreenImmunity(true);
			}
			else
			{
				GetTerjeCharacterName();
				m_terjeStartScreenParams = null;
				GetTerjeRPC().SendToClient("startscreen.ready", GetIdentity(), null);
			}
		}
	}
	
	override void OnTerjePlayerLoaded()
	{
		super.OnTerjePlayerLoaded();
		
		if (GetIdentity() != null)
		{
			GetTerjeCharacterName();
			m_terjeStartScreenParams = null;
			GetTerjeRPC().SendToClient("startscreen.ready", GetIdentity(), null);
		}
	}
	
	override void OnTerjeUpdateServerTick(float deltaTime)
	{
		super.OnTerjeUpdateServerTick(deltaTime);
		
		if (m_terjeStartScreenParams != null)
		{
			m_terjeStartScreenParams.OnServerTick(this, deltaTime);
		}
	}
	
	override void OnTerjeCharacterLifetimeUpdated(int secondsSinceRespawn)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_SOULS_ENABLED))
		{
			float survTimePow = GetTerjeSettingFloat(TerjeSettingsCollection.STARTSCREEN_SOULS_SURVT_POW);
			int survTimeSlice = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_SURVT_TIME);
			if ((survTimePow >= 1) && (survTimeSlice > 0) && (GetTerjeStats() != null))
			{
				int counter = GetTerjeStats().GetSurvSoulsCounter();
				int timestamp = survTimeSlice + ((int)Math.Pow((survTimeSlice * counter), survTimePow));
				if (secondsSinceRespawn >= timestamp)
				{
					GetTerjeStats().IncrementSurvSoulsCounter();
					
					int soulsCount = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_SURVT_COUNT);
					float soulsChance = GetTerjeSettingFloat(TerjeSettingsCollection.STARTSCREEN_SOULS_SURVT_CHANCE);
					if ((soulsCount > 0) && (Math.RandomFloat01() < soulsChance))
					{
						GetTerjeSouls().AddCount(soulsCount);
					}
				}
			}
		}
	}
	
	override bool HasActiveTerjeStartScreen()
	{
		return m_terjeStartScreenParams != null;
	}
	
	override string GetTerjeCharacterName()
	{
		if (GetGame() && GetGame().IsDedicatedServer() && (GetTerjeProfile() != null))
		{
			string firstName = GetTerjeProfile().GetFirstName();
			string lastName = GetTerjeProfile().GetLastName();
			if (firstName != string.Empty && lastName != string.Empty)
			{
				m_terjeStartScreenCharNameValue = (firstName + " " + lastName);
			}
			else if (firstName != string.Empty)
			{
				m_terjeStartScreenCharNameValue = firstName;
			}
		}
		
		if (m_terjeStartScreenCharNameValue != string.Empty)
		{
			return m_terjeStartScreenCharNameValue;
		}
		
		return super.GetTerjeCharacterName();
	}
	
	override void OnTerjePlayerKilledEvent()
	{
		super.OnTerjePlayerKilledEvent();
		
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (GetTerjeProfile() != null)
			{
				GetTerjeProfile().SetRespawnLastDeathPoint(GetWorldPosition());
			}
			
			if ((GetTerjeProfile() != null) && (GetTerjeSouls() != null) && (GetTerjeSouls().IsEnabled()))
			{
				GetTerjeSouls().AddCount(-1);
				if ((GetTerjeSouls().GetCount() == 0) && (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_SOULS_AUTODEL)))
				{
					string id = string.Empty;
					if (GetIdentity() != null)
					{
						id = GetIdentity().GetId();
					}
					else if (GetCachedID() != string.Empty)
					{
						id = GetCachedID();
					}
					
					if (id != string.Empty)
					{
						GetTerjeDatabase().DeletePlayerProfile(id);
					}
				}
			}
		}
	}
	
	override void OnTerjeRPC(PlayerIdentity sender, string id, ParamsReadContext ctx)
	{
		super.OnTerjeRPC(sender, id, ctx);
		
		if (GetGame())
		{
			if (id == "tss.name.req")
			{
				if (GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_DISPLAY_PLAYER_NAMES_MODE) >= 0)
				{
					TerjeRPCSingleParam("tss.name.res", new Param1<string>(GetTerjeCharacterName()), true, sender);
				}
			}
			else if (id == "tss.name.res")
			{
				Param1<string> payload;
				if (!ctx.Read(payload))
					return;
				
				m_terjeStartScreenCharNameValue = payload.param1;
			}
		}
	}
	
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_SOULS_ENABLED))
		{
			EntityAI killerEntity = EntityAI.Cast(killer);
			if (killerEntity)
			{
				PlayerBase killerPlayer = PlayerBase.Cast(killerEntity);
				if (!killerPlayer)
				{
					killerPlayer = PlayerBase.Cast(killerEntity.GetHierarchyRootPlayer());
				}
				
				if (killerPlayer && killerPlayer.IsAlive() && killerPlayer.GetTerjeSouls() != null)
				{
					int soulsCount = 0;
					float soulsChance = 0;
					
					if (GetIdentity() != null)
					{
						soulsCount = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLPLAYER_COUNT);
						soulsChance = GetTerjeSettingFloat(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLPLAYER_CHANCE);
					}
					else
					{
						soulsCount = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLAI_COUNT);
						soulsChance = GetTerjeSettingFloat(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLAI_CHANCE);
					}
					
					if ((soulsCount > 0) && (Math.RandomFloat01() < soulsChance))
					{
						killerPlayer.GetTerjeSouls().AddCount(soulsCount);
					}
				}
			}
		}
	}
	
	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);
		AddAction(ActionTerjeSetRespawnPoint, InputActionMap);
	}
	
	void SetTerjeServerStartScreenImmunity(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_GOD_MODE))
			{
				SetTerjeGodMode(state);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_INDESTRUCTIBLE))
			{
				SetTerjeIndestructible(state);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_IGNORE_DAMAGE))
			{
				SetTerjeIgnoreDamage(state);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_INVISIBLE))
			{
				SetTerjeInvisibleMode(false, state);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_NOCLIP))
			{
				SetTerjeNoClipMode(state);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_NOTARGETING))
			{
				SetTerjeNoTargetMode(state);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_FREEZE))
			{
				SetTerjeFreezeMode(state);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_NOSIM))
			{
				SetTerjeNoSimulateMode(state);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_NOHEATCOMF))
			{
				SetTerjeDisableHeatComfort(state);
			}
		}
	}
}
