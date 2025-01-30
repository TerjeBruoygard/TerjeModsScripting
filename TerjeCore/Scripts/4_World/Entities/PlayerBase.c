// <copyright file="PlayerBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PlayerBase
{
	private const int TERJE_CORE_STORE_BEGIN_MARKER_V1 = 133986254;
	private const int TERJE_CORE_STORE_END_MARKER_V1 = 1860587056;
	private int m_terjeModifierId = 0;
	private ref array<ref TerjePlayerModifierBase> m_terjeModifiers;
	private ref TerjePlayerProfile m_terjeProfile = null;
	private float m_terjeProfileSynchTimer = 0;
	private ref TerjePlayerStats m_terjeStats = null;
	private float m_terjeStatsSynchTimer = 0;
	private ref TerjePlayerSkillsAccessor m_terjePlayerSkillsAccessor = null;
	
	void OnTerjeProfileFirstCreation() {}
	
	void OnTerjeProfileChanged() {}
	
	void OnTerjeStatsChanged() {}
	
	void OnTerjeUpdateServerTick(float deltaTime) {}
	
	void OnTerjeRegisterModifiers(ref array<ref TerjePlayerModifierBase> modifiers)
	{
		modifiers.Insert(new TerjePlayerModifierLifetime());
	}
	
	ref TerjePlayerProfile GetTerjeProfile()
	{
		return m_terjeProfile;
	}
	
	ref TerjePlayerStats GetTerjeStats()
	{
		if (m_terjeStats == null && IsAlive() && GetIdentity())
		{
			if (GetGame().IsDedicatedServer() || IsTerjeLocalControlledPlayer())
			{
				m_terjeStats = new TerjePlayerStats;
				m_terjeStats.OnInit();
			}
		}
		
		return m_terjeStats;
	}
	
	ref TerjePlayerSkillsAccessor GetTerjeSkills()
	{
		if (m_terjePlayerSkillsAccessor == null && IsAlive() && GetIdentity())
		{
			if (GetGame().IsDedicatedServer() || IsTerjeLocalControlledPlayer())
			{
				m_terjePlayerSkillsAccessor = new TerjePlayerSkillsAccessor(this);
			}
		}
		
		return m_terjePlayerSkillsAccessor;
	}
	
	bool AddTerjeRadiation(float rAmount)
	{
		// Universal interface to insert radiation agents into the player body.
		// Implemented in TerjeRadiation mod.
		return false;
	}
	
	bool AddTerjeRadiationAdvanced(float rAmount, float environmentRadiation, bool ignoreProtection)
	{
		// Universal interface to insert radiation agents into the player body with extra parameters.
		// Implemented in TerjeRadiation mod.
		return false;
	}
	
	float GetTerjeRadiation()
	{
		// Universal interface to get radiation agents from the player body.
		// Implemented in TerjeRadiation mod.
		return 0;
	}
	
	float GetTerjeRadiationAdvanced(bool body, bool itemInHands, bool equipment)
	{
		// Universal interface to get radiation agents from the player with extended options.
		// Implemented in TerjeRadiation mod.
		return 0;
	}
	
	float GetTerjeRadiationProtection(float environmentRadiation)
	{
		// Universal interface to get radiation agents from the player body.
		// Implemented in TerjeRadiation mod.
		return 0;
	}
	
	bool IsTerjeLocalControlledPlayer()
	{
		return GetGame().IsClient() && (GetGame().GetPlayer() == this);
	}
	
	bool HasTerjeSicknesOrInjures()
	{
		if (GetStatWater() != null && GetStatWater().Get() < PlayerConstants.SL_WATER_LOW)
		{
			return true;
		}
		
		if (GetStatEnergy() != null && GetStatEnergy().Get() < PlayerConstants.SL_ENERGY_LOW)
		{
			return true;
		}
		
		return false;
	}
	
	override void Init()
	{
		super.Init();

		if (GetGame().IsDedicatedServer())
		{
			ref array<ref TerjePlayerModifierBase> terjeModifiers = new array<ref TerjePlayerModifierBase>;
			OnTerjeRegisterModifiers(terjeModifiers);
			m_terjeModifiers = terjeModifiers;
			m_terjeModifierId = 0;
		}
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
		{
			return false;
		}
		
		if (!TerjeStorageHelpers.VerifyMarker(ctx, TERJE_CORE_STORE_BEGIN_MARKER_V1))
		{
			return false;
		}
		
		if (GetGame().IsDedicatedServer() && GetTerjeStats() != null)
		{
			if (!GetTerjeStats().OnStoreLoad(ctx))
			{
				TerjeLog_Error("Failed to read player stats.");
				return false;
			}
		}
		
		if (!TerjeStorageHelpers.VerifyMarker(ctx, TERJE_CORE_STORE_END_MARKER_V1))
		{
			return false;
		}
		
		return true;
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		TerjeStorageHelpers.WriteMarker(ctx, TERJE_CORE_STORE_BEGIN_MARKER_V1);
		if (GetGame().IsDedicatedServer() && GetTerjeStats() != null)
		{
			GetTerjeStats().OnStoreSave(ctx);
		}
		
		TerjeStorageHelpers.WriteMarker(ctx, TERJE_CORE_STORE_END_MARKER_V1);
	}
	
	void OnTerjePlayerKilledEvent()
	{
	
	}
	
	override void EEKilled(Object killer)
	{		
		super.EEKilled(killer);
		OnTerjePlayerKilledEvent();
		m_terjeModifiers = null;
		m_terjeProfile = null;
		m_terjeStats = null;
		m_terjePlayerSkillsAccessor = null;
	}
	
	override bool HasHealings()
	{
		bool result = super.HasHealings();
		bool detailedHealingHudBadges = false;
		if (!result && GetTerjeStats() && GetTerjeSettingBool(TerjeSettingsCollection.CORE_DETAILED_HEALING_HUD_BADGES, detailedHealingHudBadges) && !detailedHealingHudBadges)
		{
			return HasTerjeHealings();
		}
		
		return result;
	}
	
	bool HasTerjeHealings()
	{
		return false;
	}
	
	override bool HasDisease()
	{
		bool result = super.HasDisease();
		bool detailedDiseaseHudBadges = false;
		if (!result && GetTerjeStats() && GetTerjeSettingBool(TerjeSettingsCollection.CORE_DETAILED_DISEASE_HUD_BADGES, detailedDiseaseHudBadges) && !detailedDiseaseHudBadges)
		{
			return HasTerjeDisease();
		}
		
		return result;
	}
	
	bool HasTerjeDisease()
	{
		return false;
	}
	
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);
		
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void OnTerjeRPC(PlayerIdentity sender, string id, ParamsReadContext ctx)
	{
		if (id == "~pse")
		{
			if (!GetGame() || !GetGame().IsClient())
			{
				return;
			}
			
			Param2<string, float> soundEventParams;
			if (!ctx.Read(soundEventParams))
			{
				return;		
			}
			
			EffectSound effectTerjeSound = SEffectManager.PlaySoundOnObject(soundEventParams.param1, this);
			if (effectTerjeSound)
			{
				effectTerjeSound.SetSoundVolume(soundEventParams.param2);
				effectTerjeSound.SetSoundMaxVolume(soundEventParams.param2);
				effectTerjeSound.SetAutodestroy(true);
			}
		}
	}
	
	void TerjeRPCSingleParam(string id, Param params, bool guaranteed, PlayerIdentity recipient = NULL)
	{
		auto sendData = new ref array< ref Param >;
		sendData.Insert(new ref Param1<string>( id ));
		sendData.Insert(params);
		this.RPC(TerjeERPC.TerjeRPC_CUSTOM_CALL, sendData, guaranteed, recipient);
	}
	
	void TerjeSendSoundEvent(string soundSet, string soundType, float volume)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && soundSet != "" && volume > 0)
		{
			Param2<string, float> params = new Param2<string, float>(soundSet, volume);
			TerjeRPCSingleParam("~pse", params, false);
		}
	}
	
	override void OnCommandVehicleStart()
	{
		// Hide weapon when player is inside the car (only visual change)
		super.OnCommandVehicleStart();
		TryHideEquipmentInsideCar(true);
	}
	
	override void OnCommandVehicleFinish()
	{
		// Show weapon when player get out from the car (only visual change)
		super.OnCommandVehicleFinish();
		TryHideEquipmentInsideCar(false);
	}
	
	
	void TryHideEquipmentInsideCar(bool state)
	{
		EntityAI weaponMelee = GetItemOnSlot("Melee");
		EntityAI weaponShoulder = GetItemOnSlot("Shoulder");
		
		if (weaponMelee)
		{
			if (state)
			{
				SetSimpleHiddenSelectionState(DayZPlayer.SIMPLE_SELECTION_MELEE_RIFLE,false);
				SetSimpleHiddenSelectionState(DayZPlayer.SIMPLE_SELECTION_MELEE_MELEE,false);
			}
			else
			{
				UpdateShoulderProxyVisibility(weaponMelee, "Melee");
			}
		}
		
		if (weaponShoulder)
		{
			if (state)
			{
				SetSimpleHiddenSelectionState(SIMPLE_SELECTION_SHOULDER_RIFLE,false);
				SetSimpleHiddenSelectionState(SIMPLE_SELECTION_SHOULDER_MELEE,false);
			}
			else
			{
				UpdateShoulderProxyVisibility(weaponShoulder, "Shoulder");
			}
		}
	}
	
	void OnTerjeCharacterLifetimeUpdated(int secondsSinceRespawn)
	{

	}
	
	void CallTerjeVomitSymptom(float duration, float drainForce)
	{
		SymptomBase symptom = GetSymptomManager().QueueUpPrimarySymptom( SymptomIDs.SYMPTOM_VOMIT );
		if( symptom )
		{
			symptom.SetDuration( duration );

			float waterDrainFromVomit = 70;
			GetTerjeSettingFloat(TerjeSettingsCollection.CORE_WATER_DRAIN_FROM_VOMIT, waterDrainFromVomit);
			
			float energyDrainFromVomit = 55;
			GetTerjeSettingFloat(TerjeSettingsCollection.CORE_ENERGY_DRAIN_FROM_VOMIT, energyDrainFromVomit);
			
			if ( GetStatWater().Get() > drainForce * waterDrainFromVomit )
			{
				GetStatWater().Add( -1.0 * drainForce * waterDrainFromVomit );
			}
			
			if ( GetStatEnergy().Get() > drainForce * energyDrainFromVomit )
			{
				GetStatEnergy().Add( -1.0 * drainForce * energyDrainFromVomit );
			}
			
			OnCallTerjeVomitSymptom(symptom, duration, drainForce);
		}
	}
	
	void OnCallTerjeVomitSymptom(SymptomBase symptom, float duration, float drainForce)
	{
	
	}
	
	override bool Consume(ItemBase source, float amount, EConsumeType consume_type)
	{
		bool result = super.Consume(source, amount, consume_type);
		if (result)
		{
			if (consume_type == EConsumeType.ENVIRO_POND || consume_type == EConsumeType.ENVIRO_WELL || consume_type == EConsumeType.ENVIRO_SNOW)
			{
				TerjeConsumableEffects medEffects = new TerjeConsumableEffects();
				medEffects.Apply(null, "CfgLiquidDefinitions " + Liquid.GetLiquidClassname(LIQUID_WATER), this, amount);
			}
			else if (consume_type == EConsumeType.ITEM_SINGLE_TIME || consume_type == EConsumeType.ITEM_CONTINUOUS)
			{
				Edible_Base edible_item = Edible_Base.Cast(source);
				if (edible_item && edible_item.IsLiquidContainer() && edible_item.GetLiquidType() == LIQUID_TERJE_CUSTOM)
				{
					int customLiquidId = edible_item.GetTerjeLiquidType();
					if (customLiquidId > 0)
					{
						ref NutritionalProfile nutProfile = TerjeCustomLiquids.GetInstance().GetNutritionalProfileByType(customLiquidId);
						if (nutProfile != null)
						{
							GetStatEnergy().Add((nutProfile.GetEnergy() / 100) * amount);
							GetStatWater().Add((nutProfile.GetWaterContent() / 100) * amount);
							m_PlayerStomach.DigestAgents(nutProfile.GetAgents(), amount);
						}
					}
				}
			}
		}
		
		return result;
	}
}
