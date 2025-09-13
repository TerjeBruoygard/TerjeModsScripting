// <copyright file="TerjePlayerConditionNotEqual.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditionNotEqual : TerjePlayerConditionBase
{
	override bool Validate(PlayerBase player, TerjeXmlObject condition)
	{
		string name;
		string value;
		if (player && condition && condition.FindAttribute("name", name) && condition.FindAttribute("value", value))
		{
			if (condition.EqualAttribute("persist", "1"))
			{
				if (player.GetTerjeProfile() != null)
				{
					return (player.GetTerjeProfile().GetUserVariableInt(name)) != (EvaluateValueParameter(player, value));
				}
			}
			else
			{
				if (player.GetTerjeStats() != null)
				{
					return (player.GetTerjeStats().GetUserVariableInt(name)) != (EvaluateValueParameter(player, value));
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
				filter.ApplyCondition(player, condition.GetChild(i));
			}
		}
	}
}