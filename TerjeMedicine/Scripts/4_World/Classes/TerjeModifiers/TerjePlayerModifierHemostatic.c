// <copyright file="TerjePlayerModifierHemostatic.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerModifierHemostatic : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 3;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float hemostaticValue = 0;
		float hemostaticTimer = 0;
		if (player.GetTerjeStats().GetHemostatic(hemostaticValue, hemostaticTimer))
		{			
			if (hemostaticTimer > 0)
			{
				player.GetTerjeStats().SetHemostatic(hemostaticValue, hemostaticTimer - deltaTime);
			}
			else if (hemostaticValue > 0)
			{
				player.GetTerjeStats().SetHemostatic(0, 0);
			}
		}
	}
}