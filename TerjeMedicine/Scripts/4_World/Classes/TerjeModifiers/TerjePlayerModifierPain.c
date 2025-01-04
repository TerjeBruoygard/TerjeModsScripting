// <copyright file="TerjePlayerModifierPain.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierPain : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	
	override float GetTimeout()
	{
		return 0.3;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_PAIN_ENABLED) == false)
		{
			player.GetTerjeStats().SetPainValue(0);
			player.GetTerjeStats().SetPainLevel(0);
			player.GetTerjeStats().SetPainkiller(0, 0);
			return;
		}
		
		float painValue = player.GetTerjeStats().GetPainValue();
		if (painValue < 3.1 && player.GetTerjeStats().GetViscera())
		{
			painValue = 3.2;
		}
		else if (painValue < 2.1 && (player.GetTerjeStats().GetStubWounds() || player.GetTerjeStats().GetBulletWounds() || player.GetTerjeStats().GetBandagesClean() || player.GetTerjeStats().GetBandagesDirty()))
		{
			painValue = 2.2;
		}
		else if (painValue < 1.1 && (player.GetTerjeStats().GetHematomasCount() >= TerjeMedicineConstants.HEMATOMAS_PAIN_COUNT || player.GetTerjeStats().GetSuturesClean() || player.GetTerjeStats().GetSuturesDirty()))
		{
			painValue = 1.2;
		}
		
		int painkillerLevel = 0;
		float painkillerTime = 0;
		if (player.GetTerjeStats().GetPainkiller(painkillerLevel, painkillerTime))
		{
			if (painkillerTime > 0)
			{
				player.GetTerjeStats().SetPainkiller(painkillerLevel, painkillerTime - deltaTime);
			}
			else if (painkillerLevel > 0)
			{
				player.GetTerjeStats().SetPainkiller(0, 0);
			}
			
			if (painkillerLevel > 0)
			{
				if (!player.GetModifiersManager().IsModifierActive(eModifiers.MDF_PAINKILLERS))
				{
					player.GetModifiersManager().ActivateModifier( eModifiers.MDF_PAINKILLERS );
				}
				
				if (painkillerLevel >= 3 && !player.GetModifiersManager().IsModifierActive(eModifiers.MDF_MORPHINE))
				{
					player.GetModifiersManager().ActivateModifier( eModifiers.MDF_MORPHINE );
				}
			}
			else
			{
				if (player.GetModifiersManager().IsModifierActive(eModifiers.MDF_PAINKILLERS))
				{
					player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_PAINKILLERS );
				}
				
				if (player.GetModifiersManager().IsModifierActive(eModifiers.MDF_MORPHINE))
				{
					player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_MORPHINE );
				}
			}
		}
		
		if (m_immunityInterval > 0)
		{
			m_immunityInterval = m_immunityInterval - deltaTime;
		}
		
		float immunityMod;
		if (player.GetTerjeSkills() && player.GetTerjeSkills().GetSkillModifierValue("immunity", "resdiseasesmod", immunityMod))
		{
			immunityMod = 1.0 + immunityMod;
		}
		else
		{
			immunityMod = 1.0;
		}
		
		float painSymtomChance = 0;
		int painLevel = (int)Math.Clamp(painValue, 0, 3);
		if (painLevel > 0 && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkLevel("immunity", "lowpain") > 0)
		{
			painLevel = painLevel - 1;
		}
		
		float painDecLevelValue = 0;
		if (painLevel == 0)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_DEC_LEVEL0, painDecLevelValue);
		}
		else if (painLevel == 1)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_DEC_LEVEL1, painDecLevelValue);
		}
		else if (painLevel == 2)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_DEC_LEVEL2, painDecLevelValue);
		}
		else if (painLevel == 3)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_DEC_LEVEL3, painDecLevelValue);
		}
		
		float newPainValue = painValue - (painDecLevelValue * immunityMod * deltaTime);
		player.GetTerjeStats().SetPainValue(newPainValue);
		player.GetTerjeStats().SetPainLevel(painLevel);
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (painkillerLevel >= painLevel)
		{
			painLevel = 0;
		}
		
		if (painLevel == 2)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_LIGHT_SYMPTOM_CHANCE, painSymtomChance);	
			if (Math.RandomFloat01() < painSymtomChance * deltaTime)
			{
				player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
			}
		}
		else if (painLevel == 3)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_HEAVY_SYMPTOM_CHANCE, painSymtomChance);	
			if (Math.RandomFloat01() < painSymtomChance * deltaTime)
			{
				player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			}
		}
		
		if (!player.IsUnconscious())
		{
			int currentShock = player.GetHealth("","Shock");
			if (painLevel == 3 && currentShock > PlayerConstants.UNCONSCIOUS_THRESHOLD + 25)
			{
				float uncChance = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_LEVEL3_UNCOUNCION_CHANCE);	
				if (Math.RandomFloat01() < uncChance * deltaTime)
				{
					player.SetHealth("", "Shock", 10);
				}
				else
				{
					player.DecreaseHealth("", "Shock", 20);
				}
			}
			else if ((player.GetTerjeStats().GetContusion() || painLevel == 2) && currentShock > PlayerConstants.UNCONSCIOUS_THRESHOLD + 35)
			{
				player.DecreaseHealth("","Shock",5);
			}
		}
		
		if (newPainValue < 1 && painValue >= 1 && m_immunityInterval <= 0)
		{
			float immunityExpGain = 0;
			GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_PAIN_EXP_GAIN, immunityExpGain);
			if (immunityExpGain > 0 && player.GetTerjeSkills())
			{
				player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
				m_immunityInterval = 300;
			}
		}
	}
}
