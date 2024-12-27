// <copyright file="TerjeExperienceModScriptableArea.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeExperienceModScriptableArea : TerjeScriptableArea
{
	protected ref set<string> m_SkillFilters = null;
	
	override string GetTerjeScriptableAreaType()
	{
		return "exp";
	}
	
	override void SetTerjeFilter(string filter)
	{
		ref array<string> splitedParts = new array<string>;
		filter.Split(",", splitedParts);
		m_SkillFilters = new set<string>;
		foreach (string part : splitedParts)
		{
			m_SkillFilters.Insert(part.Trim());
		}
	}
	
	override void SetTerjeParameters(map<string, float> parameters)
	{
		super.SetTerjeParameters(parameters);
		
		if (parameters.Contains("Radius"))
		{
			m_terjeInnerRadius = parameters.Get("Radius");
			m_terjeOuterRadius = parameters.Get("Radius");
		}
	}
	
	override bool TryCalculateTerjeEffectFilter(string filterEntry)
	{
		if (filterEntry != "" && m_SkillFilters != null && m_SkillFilters.Count() > 0)
		{
			return m_SkillFilters.Find(filterEntry) != -1;
		}
		
		return super.TryCalculateTerjeEffectFilter(filterEntry);
	}
}