// <copyright file="TerjePlayerConditionAny.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditionAny : TerjePlayerConditionBase
{
	override bool Validate(PlayerBase player, TerjeXmlObject condition)
	{
		if (player && condition)
		{
			TerjePlayerConditions filter = TerjePlayerConditions.GetInstance();
			for (int i = 0; i < condition.GetChildrenCount(); i++)
			{
				if (filter.ValidateCondition(player, condition.GetChild(i)))
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	override void Apply(PlayerBase player, TerjeXmlObject condition)
	{
		if (player && condition)
		{
			TerjePlayerConditions filter = TerjePlayerConditions.GetInstance();
			for (int i = 0; i < condition.GetChildrenCount(); i++)
			{
				TerjeXmlObject child = condition.GetChild(i);
				if (filter.ValidateCondition(player, child))
				{
					filter.ApplyCondition(player, child);
				}
			}
		}
	}
}