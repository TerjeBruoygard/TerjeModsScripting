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
				
		EntityAI entityKiller = EntityAI.Cast(killer);
		if (entityKiller)
		{
			PlayerBase killerPlayer = PlayerBase.Cast(entityKiller.GetHierarchyRootPlayer());
			if (killerPlayer && killerPlayer.GetTerjeStats())
			{
				float safeDist = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_KILLING_MIND_DEG_SAFEDIST);
				if (vector.Distance(killerPlayer.GetWorldPosition(), this.GetWorldPosition()) < safeDist)
				{
					float mindDegValue = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_KILLING_MIND_DEG_VALUE);
					float mindDegTime = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_ZOMBIE_KILLING_MIND_DEG_TIME);
					killerPlayer.GetTerjeStats().AddMindDegradation(mindDegValue, mindDegTime);
				}
			}
		}
	}
}