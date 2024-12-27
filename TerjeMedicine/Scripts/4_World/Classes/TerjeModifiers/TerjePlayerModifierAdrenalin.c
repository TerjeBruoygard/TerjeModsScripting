// <copyright file="TerjePlayerModifierAdrenalin.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierAdrenalin : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ADRENALIN_ENABLED) == false)
		{
			player.GetTerjeStats().SetAdrenalinValue(0);
			return;
		}
		
		float adrenalineTimer = player.GetTerjeStats().GetAdrenalinValue();
		if (adrenalineTimer > 0)
		{
			player.GetTerjeStats().SetAdrenalinValue(adrenalineTimer - deltaTime);
			
			if (!player.GetModifiersManager().IsModifierActive(eModifiers.MDF_EPINEPHRINE))
			{
				player.GetModifiersManager().ActivateModifier( eModifiers.MDF_EPINEPHRINE );
			}
			
			if (!player.GetStaminaHandler().ContainsDepletionModifier(EStaminaMultiplierTypes.EPINEPHRINE))
			{
				player.GiveShock(100);
				player.GetStaminaHandler().SetStamina(100);
				player.GetStaminaHandler().ActivateDepletionModifier(EStaminaMultiplierTypes.EPINEPHRINE);
			}
		}
		else
		{
			if (player.GetStaminaHandler().ContainsDepletionModifier(EStaminaMultiplierTypes.EPINEPHRINE))
			{
				player.GetStaminaHandler().DeactivateDepletionModifier(EStaminaMultiplierTypes.EPINEPHRINE);
			}
			
			if (player.GetModifiersManager().IsModifierActive(eModifiers.MDF_EPINEPHRINE))
			{
				player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_EPINEPHRINE );
			}
		}
	}
}

modded class StaminaHandler
{
	bool ContainsDepletionModifier(EStaminaMultiplierTypes type)
	{
		return m_ActiveDepletionModifiers.Find(type) != -1;
	}
	
	bool ContainsRecoveryModifier(EStaminaMultiplierTypes type)
	{
		return m_ActiveRecoveryModifiers.Find(type) != -1;
	}
}