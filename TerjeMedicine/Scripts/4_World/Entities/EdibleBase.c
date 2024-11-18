// <copyright file="EdibleBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Edible_Base
{
	override bool Consume(float amount, PlayerBase consumer)
	{
		if (super.Consume(amount, consumer))
		{
			float itemRadiation = GetTerjeRadiation();
			if (itemRadiation > 0)
			{
				if (HasQuantity() && GetQuantityMax() > 0)
				{
					consumer.AddTerjeRadiationAdvanced((itemRadiation / GetQuantityMax()) * amount, true);
				}
				else
				{
					consumer.AddTerjeRadiationAdvanced(itemRadiation * amount, true);
				}
			}
			
			return true;
		}
		
		return false;
	};
}