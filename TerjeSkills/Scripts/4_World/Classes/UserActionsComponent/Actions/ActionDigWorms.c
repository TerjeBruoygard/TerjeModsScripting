// <copyright file="ActionDigWorms.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionDigWorms
{
	override void OnFinishProgressServer(ActionData action_data)
	{	
		super.OnFinishProgressServer(action_data);
		
		ItemBase worms;
		float perkValue;
		int count = action_data.m_MainItem.GetOnDigWormsAmount();
		if (action_data.m_Player && action_data.m_Player.GetTerjeSkills() && action_data.m_Player.GetTerjeSkills().GetPerkValue("fish", "wormhunt", perkValue))
		{
			count = (int)Math.Round((float)count * perkValue);
			for (int i = 0; i < count; i++)
			{
				Class.CastTo(worms,  GetGame().CreateObjectEx("Worm", action_data.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
			}
		}
	}
}