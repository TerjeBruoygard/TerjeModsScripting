// <copyright file="TerjePlayerModifierContusion.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierContusion : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 3;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float healValue = player.GetTerjeStats().GetContusionHealValue();
		if (healValue > 0)
		{
			player.GetTerjeStats().SetContusionHealValue(healValue - deltaTime);
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_CONTUSION_ENABLED) == false)
		{
			player.GetTerjeStats().SetContusionValue(0);
			return;
		}
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		float contusionValue = player.GetTerjeStats().GetContusionValue();
		if (contusionValue > 0)
		{
			int contusionIntOrig = (int)contusionValue;
			float contusionHealModifier = 1;
			float contusionDecPerSec = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CONTUSION_DEC_PER_SEC, contusionDecPerSec);	

			if (healValue > 0)
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CONTUSION_HEAL_MODIFIER, contusionHealModifier);
			}
			
			contusionValue = contusionValue - (contusionDecPerSec * contusionHealModifier * deltaTime);
			player.GetTerjeStats().SetContusionValue(contusionValue);
			
			if (contusionValue > 1)
			{
				if (GetPlayerShock(player) > PlayerConstants.UNCONSCIOUS_THRESHOLD + 25)
				{
					DecreasePlayerShock(player, TerjeDamageSource.CONTUSION, 20);
				}
			}
			
			if (contusionValue > 2)
			{
				float contusionUnconsciousChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CONTUSION_UNCONSCIOUS_CHANCE, contusionUnconsciousChance);
				if (Math.RandomFloat01() < contusionUnconsciousChance)
				{
					SetPlayerShock(player, TerjeDamageSource.CONTUSION, 0);
				}
			}
			
			if (contusionIntOrig > 0 && contusionValue < 1)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_CONTUSION_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
				}
			}
		}
	}
}
