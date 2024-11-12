// <copyright file="TrapSpawnBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TrapSpawnBase
{
	private bool m_terjeSkillCanCatchIndicator = true;
	
	override void SetupTrapPlayer( PlayerBase player, bool set_position = true )
	{
		super.SetupTrapPlayer(player, set_position);
		
		if ( GetGame().IsDedicatedServer() )
		{
			string terjeSkillName = "hunt";
			string terjePerkName = "trapexp";
			
			if (IsSurfaceWater( GetWorldPosition() ))
			{
				terjeSkillName = "fish";
				terjePerkName = "mastrap";
			}
			
			if (player && player.IsAlive() && player.GetTerjeSkills())
			{
				if (player.GetTerjeSkills().IsPerkRegistered(terjeSkillName, terjePerkName))
				{
					float perkValue;
					player.GetTerjeSkills().GetPerkValue(terjeSkillName, terjePerkName, perkValue);
					m_terjeSkillCanCatchIndicator = (Math.RandomFloat01() < perkValue);
				}
			}
		}
	}
	
	override bool SetCanCatch( out EntityAI bait )
	{
		return super.SetCanCatch(bait) && m_terjeSkillCanCatchIndicator;
	}
};