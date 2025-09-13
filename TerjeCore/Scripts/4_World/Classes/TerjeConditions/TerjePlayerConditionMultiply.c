// <copyright file="TerjePlayerConditionMultiply.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditionMultiply : TerjePlayerConditionBase
{
	override bool Validate(PlayerBase player, TerjeXmlObject condition)
	{
		return true;
	}
	
	override void Apply(PlayerBase player, TerjeXmlObject condition)
	{
		string name;
		string value;
		string attrValue;
		if (player && condition && condition.FindAttribute("name", name) && condition.FindAttribute("value", value))
		{
			int min = int.MIN;
			if (condition.FindAttribute("min", attrValue))
			{
				min = attrValue.ToInt();
			}
			
			int max = int.MAX;
			if (condition.FindAttribute("max", attrValue))
			{
				max = attrValue.ToInt();
			}
			
			if (condition.EqualAttribute("persist", "1"))
			{
				if (player.GetTerjeProfile() != null)
				{
					player.GetTerjeProfile().SetUserVariableInt(name, TerjeMathHelper.ClampInt((player.GetTerjeProfile().GetUserVariableInt(name)) * (EvaluateValueParameter(player, value)), min, max));
				}
			}
			else
			{
				if (player.GetTerjeStats() != null)
				{
					player.GetTerjeStats().SetUserVariableInt(name, TerjeMathHelper.ClampInt((player.GetTerjeStats().GetUserVariableInt(name)) * (EvaluateValueParameter(player, value)), min, max));
				}
			}
		}
	}
}