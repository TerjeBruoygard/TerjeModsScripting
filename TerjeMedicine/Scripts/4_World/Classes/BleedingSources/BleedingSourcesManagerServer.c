// <copyright file="BleedingSourcesManagerServer.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class BleedingSourcesManagerServer
{	
	bool TerjeAttemptRemoveBleedingSource(int component)
	{
		int bit = GetBitFromSelectionID(component);
		
		if ( bit == 0 )
		{
			return false;
		}
		
		return RemoveBleedingSource(bit);
	}
	
	override void RemoveMostSignificantBleedingSource()
	{
		if (m_Player.GetTerjeStats().GetStubWounds() > 0)
		{
			m_Player.GetTerjeStats().SetStubWounds(m_Player.GetTerjeStats().GetStubWounds() - 1);
			m_Player.GetTerjeStats().SetBandagesClean(m_Player.GetTerjeStats().GetBandagesClean() + 1);
		}
		else if (m_Player.GetTerjeStats().GetSuturesClean() > 0)
		{
			m_Player.GetTerjeStats().SetSuturesClean(m_Player.GetTerjeStats().GetSuturesClean() - 1);
			m_Player.GetTerjeStats().SetSuturesBandagedClean(m_Player.GetTerjeStats().GetSuturesBandagedClean() + 1);
		}
		else if (m_Player.GetTerjeStats().GetSuturesDirty() > 0)
		{
			m_Player.GetTerjeStats().SetSuturesDirty(m_Player.GetTerjeStats().GetSuturesDirty() - 1);
			m_Player.GetTerjeStats().SetSuturesBandagedClean(m_Player.GetTerjeStats().GetSuturesBandagedClean() + 1);
		}
		else
		{
			super.RemoveMostSignificantBleedingSource();
		}
	}
	
	override void ProcessHit(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
		// Call super.ProcessHit to compatibility with other mods
		super.ProcessHit(damage, source, component, zone, ammo, modelPos);
		
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	};
};
