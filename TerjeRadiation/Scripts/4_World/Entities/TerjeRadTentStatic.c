// <copyright file="TerjeRadTentStatic.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeRadTentStatic extends TerjeRadTent
{
	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(TerjeInitServerState);
		}
	}
	
	void TerjeInitServerState()
	{
		SetAllowDamage(false);
		Pitch(true, true);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(TerjeInitServerAttachments);
	}
	
	void TerjeInitServerAttachments()
	{
		GetInventory().CreateAttachment("TerjeShower");
		GetInventory().CreateAttachment("TerjePump");
		GetInventory().CreateAttachment("CarBattery");
		GetInventory().CreateAttachment("TerjeCanisterChemical");
		RefreshAttachements();
		SetSynchDirty();
	}
	
	override void OnWorkTerjeServerLogic()
	{
		if (GetGame() && HasEnergyManager() && GetCompEM().IsSwitchedOn())
		{
			float cleanupForce = GetGame().ConfigGetFloat("CfgTerjeCustomLiquids RadDesactivator terjeRadiationCleanupForce");
			float cleanupModifier = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_RADTENT_EFFICIENCY_MOD);
			float cleanupTotal = cleanupForce * cleanupModifier;
			if (cleanupTotal > 0)
			{
				TerjeDecontaminateEntitiesInside(cleanupTotal);
			}
		}
	}
	
	override void UpdateVisuals()
	{
		super.UpdateVisuals();
		SetAnimationPhase("Pack", 1);
	}
	
	override bool CanBePacked()
	{
		return false;
	}
	
	override bool IsValidTerjeRadTentToWork()
	{
		return true;
	}
	
	override void EEOnAfterLoad()
	{
		Delete();
	}
	
	override void SetActions()
	{
		// super is not needed here, not a mistake
		AddAction(ActionTurnOnTerjeRadTent);		
		AddAction(ActionTurnOffTerjeRadTent);
	}
	
	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		return false;
	}
	
	override bool CanDisplayAttachmentCategory( string category_name )
	{
		return false;
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}

	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}
	
	override bool CanBeManipulated()
	{
		return false;
	}
	
	override bool CanAttach(ItemBase item)
	{
		return false;
	}
}