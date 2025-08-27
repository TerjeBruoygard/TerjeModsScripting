// <copyright file="ZombieBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ZombieBase
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
					int soulsCount = GetTerjeGameConfig().ConfigGetInt("CfgVehicles " + GetType() + " terjeOnKillSoulsCount");
					float soulsChance = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " terjeOnKillSoulsChance");
					if (soulsCount == 0)
					{
						soulsCount = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLZMB_COUNT);
						soulsChance = GetTerjeSettingFloat(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLZMB_CHANCE);
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
