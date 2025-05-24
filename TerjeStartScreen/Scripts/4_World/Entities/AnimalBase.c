// <copyright file="AnimalBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class AnimalBase
{
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
					int soulsCount = ConfigGetInt("terjeOnKillSoulsCount");
					float soulsChance = ConfigGetFloat("terjeOnKillSoulsChance");
					if (soulsCount == 0)
					{
						soulsCount = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLANI_COUNT);
						soulsChance = GetTerjeSettingFloat(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLANI_CHANCE);
					}
					
					if ((soulsCount > 0) && (Math.RandomFloat01() < soulsChance))
					{
						killerPlayer.GetTerjeSouls().AddCount(soulsCount);
					}
				}
			}
		}
	}
}
