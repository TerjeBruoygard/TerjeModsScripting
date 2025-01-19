// <copyright file="TerjePlayerModifierRadioactiveScriptableAreas.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierRadioactiveScriptableAreas : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
		if (!plugin)
		{
			return;
		}
		
		
		// Calculate radiation zones
		float playerRadiation = player.GetTerjeRadiation();
		float environmentRadiation = plugin.CalculateTerjeEffectValue(player, "rad");
		if (environmentRadiation > 0)
		{
			float radioactiveGlobalModifier = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_AREAS_POWER_MOD);
			float rAmount = environmentRadiation * radioactiveGlobalModifier;
			float maxAccumulatedRadLimit = rAmount * GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_ZONE_POWER_TO_RAD_LIMIT);
			if (playerRadiation < maxAccumulatedRadLimit)
			{
				float rIncrement = Math.Clamp(rAmount * deltaTime, 0, maxAccumulatedRadLimit - playerRadiation);
				player.AddTerjeRadiationAdvanced(rIncrement, environmentRadiation, false);
			}
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_TRANSFER_WITH_PARENT))
		{
			float transferThreshold = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_TRANSFER_THRESHOLD);
			float transferAmount = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_TRANSFER_PER_SECOND) * deltaTime;
			
			ItemBase attachment;
			playerRadiation = player.GetTerjeRadiation();
			int attCount = player.GetInventory().AttachmentCount();
			for ( int attIdx = 0; attIdx < attCount; attIdx++ )
			{
				if (ItemBase.CastTo(attachment, player.GetInventory().GetAttachmentFromIndex( attIdx )) && attachment)
				{
					TransferRadiationWithEntity(player, attachment, playerRadiation, transferThreshold, transferAmount);
				}
			}
			
			ItemBase inHands = player.GetItemInHands();
			if (inHands != null)
			{
				TransferRadiationWithEntity(player, inHands, playerRadiation, transferThreshold, transferAmount);
			}
			
			EntityAI parent = EntityAI.Cast(player.GetParent());
			if (parent != null)
			{
				TransferRadiationWithEntity(player, parent, playerRadiation, transferThreshold, transferAmount);
			}
		}
	}
	
	void TransferRadiationWithEntity(PlayerBase player, EntityAI entity, float playerRadiation, float transferThreshold, float transferAmount)
	{
		if (!player)
		{
			return;
		}
		
		if (!entity)
		{
			return;
		}
		
		PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
		if (!plugin)
		{
			return;
		}
		
		float maxTransferAmount;
		float finalTransferAmount;
		float entityRadiation = plugin.GetTerjeRadiationFromEntity(entity);
		if (playerRadiation * transferThreshold > entityRadiation)
		{
			maxTransferAmount = Math.Max(0, (playerRadiation * transferThreshold) - entityRadiation);
			finalTransferAmount = Math.Clamp(transferAmount, 0, maxTransferAmount);
			plugin.AddTerjeRadiationToEntity(entity, finalTransferAmount);
		}
		else if (entityRadiation * transferThreshold > playerRadiation)
		{
			maxTransferAmount = Math.Max(0, (entityRadiation * transferThreshold) - playerRadiation);
			finalTransferAmount = Math.Clamp(transferAmount, 0, maxTransferAmount);
			player.AddTerjeRadiationAdvanced(finalTransferAmount, entityRadiation, false);
		}
	}
}