// <copyright file="TerjePlayerConditionCustom.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditionCustom : TerjePlayerConditionBase
{
	override bool Validate(PlayerBase player, TerjeXmlObject condition)
	{
		string classname;
		if (condition.FindAttribute("classname", classname) && (classname != string.Empty))
		{
			typename type = classname.ToType();
			if (type && type.IsInherited(TerjeCustomConditionHandler))
			{
				TerjeCustomConditionHandler customCondition = TerjeCustomConditionHandler.Cast(type.Spawn());
				if (customCondition != null)
				{
					return customCondition.CheckCondition(player, condition);
				}
			}
			else
			{
				TerjeLog_Warning("Class '" + classname + "' not found or not inherited TerjeCustomConditionHandler.");
			}
		}
		else
		{
			TerjeLog_Warning("Attribute 'classname' is required for 'CustomCondition'.");
		}
		
		return false;
	}
	
	override void Apply(PlayerBase player, TerjeXmlObject condition)
	{
		string classname;
		if (condition.FindAttribute("classname", classname) && (classname != string.Empty))
		{
			typename type = classname.ToType();
			if (type && type.IsInherited(TerjeCustomConditionHandler))
			{
				TerjeCustomConditionHandler customCondition = TerjeCustomConditionHandler.Cast(type.Spawn());
				if (customCondition != null)
				{
					customCondition.ApplyCondition(player, condition);
				}
			}
		}
	}
	
	override string GetText(PlayerBase player, TerjeXmlObject condition)
	{
		string classname;
		if (condition.FindAttribute("classname", classname) && (classname != string.Empty))
		{
			typename type = classname.ToType();
			if (type && type.IsInherited(TerjeCustomConditionHandler))
			{
				TerjeCustomConditionHandler customCondition = TerjeCustomConditionHandler.Cast(type.Spawn());
				if (customCondition != null)
				{
					return customCondition.GetConditionText(player, condition);
				}
			}
		}
		
		return string.Empty;
	}
}