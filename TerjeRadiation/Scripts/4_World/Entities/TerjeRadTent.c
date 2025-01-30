// <copyright file="TerjeRadTent.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeRadTent extends TentBase
{
	protected const int TERJE_SHOWERS_COUNT = 5;
	protected EffectSound m_PumpSoundEffect;
	protected ref array<EffectSound> m_ShowerSoundEffects = null;
	protected ref array<Particle> m_ShowerParticleEffects = null;
	
	void TerjeRadTent()
	{
		m_ShowAnimationsWhenPitched.Insert( "Body" );
		m_ShowAnimationsWhenPitched.Insert( "Pack" );
		m_ShowAnimationsWhenPacked.Insert( "Inventory" );
		
		m_HalfExtents = Vector(1.8, 0.33, 3.4);
	}
		
	override bool HasClutterCutter()
	{
		return false;
	}

	override bool IsDeployable()
	{
		return true;
	}
	
	override string GetDeploySoundset()
	{
		return "placeCarTent_SoundSet";
	}
	
	override string GetLoopDeploySoundset()
	{
		return "cartent_deploy_SoundSet";
	}
	
	override bool CanBePacked()
	{
		if (GetState() == PITCHED)
		{
			if (GetInventory().AttachmentCount() == 0)
			{
				return true;
			}
		}
		
		return false;
	}
	
	bool IsValidTerjeRadTentToWork()
	{
		if (GetState() == PITCHED)
		{
			ItemBase canister = ItemBase.Cast(GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("TerjeCanisterGasoline")));
			ItemBase shower = ItemBase.Cast(GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("TerjeShower")));
			ItemBase pump = ItemBase.Cast(GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("TerjePump")));
			ItemBase battery = ItemBase.Cast(GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("CarBattery")));
			
			bool isValidCanister = (canister && !canister.IsRuined() && canister.GetQuantity() > canister.GetQuantityMin());
			bool isValidShower = (shower && !shower.IsRuined());
			bool isValidPump = (pump && !pump.IsRuined());
			bool isValidBattery = (battery && !battery.IsRuined() && battery.GetQuantity() > battery.GetQuantityMin());
			return isValidBattery && isValidPump && isValidShower && isValidCanister;
		}
		
		return false;
	}
	
	void TerjeUpdateVisuals()
	{
		bool picthed = false;
		if (GetState() == PITCHED)
		{
			picthed = true;
		}
		
		EntityAI canister = GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("TerjeCanisterGasoline"));
		EntityAI shower = GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("TerjeShower"));
		EntityAI pump = GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("TerjePump"));
		EntityAI battery = GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("CarBattery"));
		
		if (shower && picthed)
		{
			SetAnimationPhase("Shower", 0);
		}
		else
		{
			SetAnimationPhase("Shower", 1);
		}
		
		if (pump && picthed)
		{
			SetAnimationPhase("Cord_folded", 0);
			
			if (canister)
			{
				SetAnimationPhase("Canistre_plug", 0);
			}
			else
			{
				SetAnimationPhase("Canistre_plug", 1);
			}
			
			if (battery && HasEnergyManager() && GetCompEM().IsSwitchedOn())
			{
				SetAnimationPhase("Cord_plugged", 0);
			}
			else
			{
				SetAnimationPhase("Cord_plugged", 1);
			}
		}
		else
		{
			SetAnimationPhase("Cord_folded", 1);
			SetAnimationPhase("Cord_plugged", 1);
			SetAnimationPhase("Canistre_plug", 1);
		}
	}
	
	void TerjeDestroyVisualEffects()
	{
		if (GetGame().IsClient())
		{			
			if (m_ShowerSoundEffects != null)
			{
				foreach (EffectSound soundEffect : m_ShowerSoundEffects)
				{
					if (soundEffect)
					{
						SEffectManager.DestroyEffect(soundEffect);
					}
				}
				
				m_ShowerSoundEffects = null;
			}
			
			if (m_ShowerParticleEffects != null)
			{
				foreach (Particle particleEffect : m_ShowerParticleEffects)
				{
					if (particleEffect)
					{
						particleEffect.Stop();
					}
				}
				
				m_ShowerParticleEffects = null;
			}
		}
	}
	
	override bool IsTerjeRadiationAccumulated()
	{
		return false;
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		TerjeUpdateVisuals();
	}
	
	override void RefreshAttachements()
	{
		super.RefreshAttachements();
		TerjeUpdateVisuals();
	}
	
	override void EOnInit(IEntity other, int extra)
	{
		super.EOnInit(other, extra);
		TerjeUpdateVisuals();
	}
	
	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);
		TerjeUpdateVisuals();
	}
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		TerjeUpdateVisuals();
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);		
		TerjeDestroyVisualEffects();
		
		if (m_PumpSoundEffect)
		{
			SEffectManager.DestroyEffect(m_PumpSoundEffect);
		}
	}
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		TerjeUpdateVisuals();
		
		if (GetGame().IsClient())
		{
			PlaySoundSetAtMemoryPointLoopedSafe(m_PumpSoundEffect, "TerjeRadTentPump_SoundSet", "sound_pump", 1, 1);
		}
	}
	
	override void OnWork( float consumed_energy )
	{
		super.OnWork(consumed_energy);
		if (GetGame().IsDedicatedServer())
		{
			if (IsValidTerjeRadTentToWork())
			{
				OnWorkTerjeServerLogic();
			}
			else
			{
				if (HasEnergyManager() && GetCompEM().CanSwitchOff())
				{
					GetCompEM().SwitchOff();
				}
			}
		}
		else if (GetGame().IsClient())
		{
			if (m_ShowerSoundEffects == null)
			{
				m_ShowerSoundEffects = new array<EffectSound>;
				for (int soundIndex = 1; soundIndex <= TERJE_SHOWERS_COUNT; soundIndex++)
				{
					EffectSound effectSound;
					PlaySoundSetAtMemoryPointLoopedSafe(effectSound, "TerjeRadTentShower_SoundSet", "particle_shower_" + soundIndex, 1, 1);
					m_ShowerSoundEffects.Insert(effectSound);
				}
			}
			
			if (m_ShowerParticleEffects == null)
			{
				m_ShowerParticleEffects = new array<Particle>;
				for (int particleIndex = 1; particleIndex <= TERJE_SHOWERS_COUNT; particleIndex++)
				{
					m_ShowerParticleEffects.Insert(ParticleManager.GetInstance().PlayOnObject(ParticleList.TERJE_RADIATION_SHOWER_EFFECT, this, GetMemoryPointPos("particle_shower_" + particleIndex)));
				}
			}
		}
	}
	
	void OnWorkTerjeServerLogic()
	{
		ItemBase canister = ItemBase.Cast(GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("TerjeCanisterGasoline")));
		if (canister && HasEnergyManager() && GetCompEM().IsSwitchedOn())
		{
			float consumeAmount = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_RADTENT_CONSUME_LIQUID);
			if (consumeAmount > 0)
			{
				canister.AddQuantity(-consumeAmount);
			}
			
			float cleanupForce = ActionWashRadioactiveItems.GetTerjeRadiationCleanupForce(canister);
			float cleanupModifier = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_RADTENT_EFFICIENCY_MOD);
			float cleanupTotal = cleanupForce * cleanupModifier;
			if (cleanupTotal > 0)
			{
				TerjeDecontaminateEntitiesInside(cleanupTotal);
			}
		}
	}
	
	void TerjeDecontaminateEntitiesInside(float cleanupForce)
	{
		ref PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
		if (!plugin)
		{
			return;
		}
		
		bool decontaminatePlayers = GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_RADTENT_DECONTAMINATE_PLAYERS);
		ref set<EntityAI> cleanedItems = new set<EntityAI>;
		ref array<Object> nearestObjects = new array<Object>;
		for (int pointIndex = 1; pointIndex <= TERJE_SHOWERS_COUNT; pointIndex++)
		{
			vector memPointPos = GetMemoryPointPos("particle_shower_" + pointIndex);
			vector worldPos = ModelToWorld(Vector(memPointPos[0], 0, memPointPos[2]));
			
			GetGame().GetObjectsAtPosition3D(worldPos, m_HalfExtents[0], nearestObjects, null);
			foreach (Object obj : nearestObjects)
			{
				if (!obj)
				{
					continue;
				}
				
				if (obj == this)
				{
					continue;
				}
				
				if (!decontaminatePlayers && obj.IsInherited(PlayerBase))
				{
					continue;
				}
				
				EntityAI currentEntity = EntityAI.Cast(obj);
				if (currentEntity && cleanedItems.Find(currentEntity) == -1)
				{
					cleanedItems.Insert(currentEntity);
					plugin.CleanTerjeRadiationFromEntity(currentEntity, cleanupForce, true, true);
				}
			}
			
			nearestObjects.Clear();
		}
	}
		
	override void OnWorkStop()
	{
		super.OnWorkStop();
		TerjeUpdateVisuals();
		TerjeDestroyVisualEffects();
		
		if (m_PumpSoundEffect)
		{
			SEffectManager.DestroyEffect(m_PumpSoundEffect);
		}
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionTurnOnTerjeRadTent);		
		AddAction(ActionTurnOffTerjeRadTent);
	}
	
	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		return super.CanDisplayAttachmentSlot(slot_id) && GetState() == PITCHED;
	}
	
	override bool CanDisplayAttachmentCategory( string category_name )
	{
		return super.CanDisplayAttachmentCategory(category_name) && GetState() == PITCHED;
	}
}