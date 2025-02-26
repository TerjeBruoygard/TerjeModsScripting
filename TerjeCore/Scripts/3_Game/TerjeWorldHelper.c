// <copyright file="TerjeWorldHelper.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWorldHelper
{
	static bool IsOutOfMap(EntityAI entity)
	{
		if (entity && GetGame() && GetGame().GetWorld())
		{
			vector worldPos = entity.GetWorldPosition();
			int worldSize = GetGame().GetWorld().GetWorldSize();

			if ((worldPos[0] < 0) || (worldPos[0] > worldSize) || (worldPos[2] < 0) || (worldPos[2] > worldSize))
			{
				return true;
			}
		}
		
		return false;
	}
}