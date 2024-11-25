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
		return 5.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
		if (!plugin)
		{
			return;
		}
		
		// Calculate radiation zones
		float currentRadiation = player.GetTerjeRadiation();
		float environmentRadiation = plugin.CalculateTerjeEffectValue(player, "rad");
		float additionalRadiation = environmentRadiation;
		if (additionalRadiation > 0)
		{
			additionalRadiation *= GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_AREAS_POWER_MOD);
		}
		
		// Calculate contaminated with radiation player's gear
		float environmentWetDelta = 0;
		if (player.m_Environment != null)
		{
			Math.Clamp(player.m_Environment.GetWetDelta(), 0, 1) * deltaTime;
		}
		
		float radiationGearTransferMod = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_TRANSFER_GEAR);
		if (radiationGearTransferMod > 0)
		{
			ItemBase attachment;
			float transferAmount = radiationGearTransferMod * deltaTime;
			int attCount = player.GetInventory().AttachmentCount();
			for ( int attIdx = 0; attIdx < attCount; attIdx++ )
			{
				if (ItemBase.CastTo(attachment, player.GetInventory().GetAttachmentFromIndex( attIdx )) && attachment)
				{
					if (environmentWetDelta > 0)
					{
						attachment.AddTerjeRadiation(-environmentWetDelta);
					}
					
					float itemRadiation = attachment.GetTerjeRadiation();
					if (currentRadiation > transferAmount || itemRadiation > transferAmount)
					{
						if (currentRadiation > itemRadiation * 2)
						{
							attachment.AddTerjeRadiation(transferAmount);
						}
						else if (itemRadiation > currentRadiation * 2)
						{
							additionalRadiation += radiationGearTransferMod;
						}
					}
				}
			}
			
			ItemBase inHands = player.GetItemInHands();
			if (inHands != null)
			{
				if (environmentWetDelta > 0)
				{
					inHands.AddTerjeRadiation(-environmentWetDelta);
				}
				
				float inHandsRadiation = plugin.GetTerjeRadiationFromEntity(inHands);
				if (currentRadiation > inHandsRadiation * 2)
				{
					plugin.AddTerjeRadiationToEntity(inHands, transferAmount);
				}
				else if (inHandsRadiation > currentRadiation * 2)
				{
					additionalRadiation += radiationGearTransferMod;
				}
			}
			
			EntityAI parent = player.GetHierarchyParent();
			if (parent != null)
			{
				float parentRadiation = plugin.GetTerjeRadiationFromEntity(parent);
				if (currentRadiation > transferAmount || parentRadiation > transferAmount)
				{
					if (currentRadiation > parentRadiation * 2)
					{
						plugin.AddTerjeRadiationToEntity(parent, transferAmount);
					}
					else if (parentRadiation > currentRadiation * 2)
					{
						additionalRadiation += radiationGearTransferMod;
					}
				}
			}
		}
		
		// Apply additional radiation
		if (additionalRadiation > 0)
		{
			player.AddTerjeRadiationAdvanced(additionalRadiation * deltaTime, environmentRadiation, false);
		}
	}
}