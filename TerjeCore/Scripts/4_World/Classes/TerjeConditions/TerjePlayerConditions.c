// <copyright file="TerjePlayerConditions.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditions
{
	protected static ref TerjePlayerConditions m_instance = null;
	protected ref map<string, ref TerjePlayerConditionBase> m_conditions = new map<string, ref TerjePlayerConditionBase>;
	
	static TerjePlayerConditions GetInstance()
	{
		if (m_instance == null)
		{
			m_instance = new TerjePlayerConditions;
			
			if (GetGame() && GetGame().IsDedicatedServer())
			{
				m_instance.OnInit();
			}
			else
			{
				TerjeLog_Error("TerjePlayerConditions initialization is not allowed on client.");
			}
		}
		
		return m_instance;
	}
	
	protected void OnInit()
	{
		RegisterCondition("Set",				TerjePlayerConditionSet);
		RegisterCondition("Sum",				TerjePlayerConditionSum);
		RegisterCondition("Subtract",			TerjePlayerConditionSubtract);
		RegisterCondition("Multiply",			TerjePlayerConditionMultiply);
		RegisterCondition("Divide",				TerjePlayerConditionDivide);
		
		RegisterCondition("Equal",				TerjePlayerConditionEqual);
		RegisterCondition("NotEqual",			TerjePlayerConditionNotEqual);
		RegisterCondition("LessThen",			TerjePlayerConditionLessThen);
		RegisterCondition("GreaterThen",		TerjePlayerConditionGreaterThen);
		RegisterCondition("LessOrEqual",		TerjePlayerConditionLessOrEqual);
		RegisterCondition("GreaterOrEqual",		TerjePlayerConditionGreaterOrEqual);
		
		RegisterCondition("All",				TerjePlayerConditionAll);
		RegisterCondition("Any",				TerjePlayerConditionAny);
		RegisterCondition("One",				TerjePlayerConditionOne);
		RegisterCondition("Fail",				TerjePlayerConditionFail);
		
		RegisterCondition("SpecificPlayers",	TerjePlayerConditionGuids);
		RegisterCondition("Timeout",			TerjePlayerConditionTimeout);
		RegisterCondition("CustomCondition",	TerjePlayerConditionCustom);
		RegisterCondition("SkillLevel",			TerjePlayerConditionSkill);
		RegisterCondition("SkillPerk",			TerjePlayerConditionPerk);
	}
	
	protected void RegisterCondition(string name, typename type)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (type && type.IsInherited(TerjePlayerConditionBase))
			{
				ref TerjePlayerConditionBase value = TerjePlayerConditionBase.Cast(type.Spawn());
				if (value != null)
				{
					m_conditions.Set(name, value);
				}
			}
		}
	}
	
	bool ProcessCondition(PlayerBase player, TerjeXmlObject condition, out string displayText)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && (condition != null) && (condition.IsObjectNode()))
		{
			bool result = ValidateCondition(player, condition);
			if (result)
			{
				if (condition.FindAttribute("successText", displayText))
				{
					return true;
				}
			}
			else
			{
				if (condition.FindAttribute("failText", displayText))
				{
					return false;
				}
			}
			
			displayText = GetConditionText(player, condition);
			return result;
		}
		
		return false;
	}
	
	bool ValidateCondition(PlayerBase player, TerjeXmlObject condition)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			TerjePlayerConditionBase result;
			if ((condition != null) && (condition.IsObjectNode()) && (m_conditions.Find(condition.GetName(), result)) && (result != null))
			{
				return result.Validate(player, condition);
			}
		}
		
		return false;
	}
	
	void ApplyCondition(PlayerBase player, TerjeXmlObject condition)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			TerjePlayerConditionBase result;
			if ((condition != null) && (condition.IsObjectNode()) && (m_conditions.Find(condition.GetName(), result)) && (result != null))
			{
				result.Apply(player, condition);
			}
		}
	}
	
	string GetConditionText(PlayerBase player, TerjeXmlObject condition)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			TerjePlayerConditionBase result;
			if ((condition != null) && (condition.IsObjectNode()))
			{
				string displayText;
				if (condition.FindAttribute("displayText", displayText))
				{
					return displayText;
				}
				else if ((m_conditions.Find(condition.GetName(), result)) && (result != null))
				{
					return result.GetText(player, condition);
				}
			}
		}
		
		return "Unknown condition '" + condition.GetName() + "'";
	}
}