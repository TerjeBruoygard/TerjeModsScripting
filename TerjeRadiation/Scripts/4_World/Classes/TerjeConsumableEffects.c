// <copyright file="TerjeConsumableEffects.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeConsumableEffects
{
	override void Apply(EntityAI entity, string classname, PlayerBase player, float amount)
	{
		super.Apply(entity, classname, player, amount);
		
		float timeModifier;
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("med", "pharmac", timeModifier))
		{
			timeModifier = 1.0 + timeModifier;
		}
		else
		{
			timeModifier = 1.0;
		}
		
		if (player && player.GetTerjeStats())
		{
			int medRadprotectLevel = GetGame().ConfigGetInt( classname + " medAntiradLevel" );
			if (medRadprotectLevel > 0)
			{
				int activeAntiradValue = 0;
				float activeAntiradTime = 0;
				player.GetTerjeStats().GetAntirad(activeAntiradValue, activeAntiradTime);
				
				float medRadprotectTimeSec = GetGame().ConfigGetFloat( classname + " medAntiradTimer" );
				if (medRadprotectLevel >= activeAntiradValue && medRadprotectTimeSec > 0)
				{
					int medRadprotectMaxTimeSec = GetGame().ConfigGetInt( classname + " medAntiradMaxTimer" );
					if (medRadprotectMaxTimeSec <= 0)
					{
						medRadprotectMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetAntirad(medRadprotectLevel, Math.Min(medRadprotectMaxTimeSec, activeAntiradTime + (medRadprotectTimeSec * amount * timeModifier)));
				}
			}
			
			float medRadiationIncrement = GetGame().ConfigGetFloat( classname + " medRadiationIncrement" );
			if (medRadiationIncrement != 0)
			{
				player.GetTerjeStats().SetRadiationValue(player.GetTerjeStats().GetRadiationValue() + (medRadiationIncrement * amount));
			}
		}
	}
	
	override string Describe(EntityAI entity, string classname)
	{
		string result = super.Describe(entity, classname);
		float medRadprotectTimeSec = GetGame().ConfigGetFloat( classname + " medAntiradTimer" );
		int medRadprotectLevel = GetGame().ConfigGetInt( classname + " medAntiradLevel" );
		if (medRadprotectLevel > 0 && medRadprotectTimeSec > 0)
		{
			result = result + "#STR_TERJERAD_EFFECT_RADPROTECT <color rgba='97,215,124,255'>" + medRadprotectLevel + "</color> (" + (int)(medRadprotectTimeSec) + "sec)<br/>";			
		}
		
		float medRadiationIncrement = GetGame().ConfigGetFloat( classname + " medRadiationIncrement" );
		if (medRadiationIncrement > 0)
		{
			result = result + "#STR_TERJERAD_EFFECT_RADIATION <color rgba='97,215,124,255'>+" + (int)(medRadiationIncrement) + "%</color><br/>";
		}
		else if (medRadiationIncrement < 0)
		{
			result = result + "#STR_TERJERAD_EFFECT_RADIATION <color rgba='198,59,64,255'>" + (int)(medRadiationIncrement) + "%</color><br/>";
		}
		
		return result;
	}
}