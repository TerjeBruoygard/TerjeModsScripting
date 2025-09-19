// <copyright file="PluginTerjeScriptableAreas.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PluginTerjeScriptableAreas
{
	override bool GetTerjeRadiationZonePowerToRadLimit(out float result)
	{
		return GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_ZONE_POWER_TO_RAD_LIMIT, result);
	}
	
	override void WriteScriptableAreasWiki(FileHandle file)
	{
		super.WriteScriptableAreasWiki(file);
		
		FPrintln(file, "### Radioactive area (TerjeRadioactiveScriptableArea)");
		FPrintln(file, "");
		FPrintln(file, "**Classname:** TerjeRadioactiveScriptableArea");
		FPrintln(file, "");
		FPrintln(file, "This type of zone contaminate all items, vehicles, zombies, animals and players within it with radiation. The zone has a power gradient between the inner and outer radiuses.");
		FPrintln(file, "");
		FPrintln(file, "*IMPORTANT: It is recommended that the area size should be less then network synchronization bubble size (1200m by default) for the client-side logic of dosimeters works correctly.*");
		FPrintln(file, "");
		FPrintln(file, "Supported `Data` parameters:");
		FPrintln(file, "");
		FPrintln(file, "- `HeightMin`: The area is represented by a cylinder. The minimum height parameter defines the lower boundary of the area.");
		FPrintln(file, "- `HeightMax`: The area is represented by a cylinder. The maximum height parameter defines the upper boundary of the area.");
		FPrintln(file, "- `OuterRadius`: Outer radius of the area. The power will linearly lerped between the outer and inner radiuses.");
		FPrintln(file, "- `InnerRadius`: Inner radius of the area. Inside this radius, the power is constant.");
		FPrintln(file, "- `Power`: The power with which the area will affect the player. (recommended value is from 1 to 5).");
		FPrintln(file, "");
		FPrintln(file, "");
	}
	
	override void RegisterCustomProtection(TerjeCustomProtectionTypes customProtectionTypes)
	{
		super.RegisterCustomProtection(customProtectionTypes);
		customProtectionTypes.Insert("radiation");
	}
	
	float GetEnvironmentRainRadioactivity()
	{
		float rainRadiation = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_RADRAIN_POWER);
		if (rainRadiation > 0)
		{
			Weather weather = GetGame().GetWeather();
			if (weather != null)
			{
				float effectPower = 0;
				Rain rain = weather.GetRain();
				if (rain != null)
				{
					effectPower = Math.Max(effectPower, rain.GetActual());
				}
				
				Snowfall snowfall = weather.GetSnowfall();
				if (snowfall != null)
				{
					effectPower = Math.Max(effectPower, snowfall.GetActual());
				}
				
				return effectPower * rainRadiation;
			}
		}
		
		return 0;
	}
	
	void TerjeDecontaminateRadioactiveEntitiesInside(Object parent, float radius, int mempointsCount, float cleanupForce)
	{
		bool decontaminatePlayers = GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_RADTENT_DECONTAMINATE_PLAYERS);
		ref set<EntityAI> cleanedItems = new set<EntityAI>;
		ref array<Object> nearestObjects = new array<Object>;
		for (int pointIndex = 1; pointIndex <= mempointsCount; pointIndex++)
		{
			vector memPointPos = parent.GetMemoryPointPos("particle_shower_" + pointIndex);
			vector worldPos = parent.ModelToWorld(Vector(memPointPos[0], 0, memPointPos[2]));
			
			GetGame().GetObjectsAtPosition3D(worldPos, radius, nearestObjects, null);
			foreach (Object obj : nearestObjects)
			{
				if (!obj)
				{
					continue;
				}
				
				if (obj == this)
				{
					continue;
				}
				
				if (!decontaminatePlayers && obj.IsInherited(PlayerBase))
				{
					continue;
				}
				
				EntityAI currentEntity = EntityAI.Cast(obj);
				if (currentEntity && cleanedItems.Find(currentEntity) == -1)
				{
					cleanedItems.Insert(currentEntity);
					CleanTerjeRadiationFromEntity(currentEntity, cleanupForce, true, true);
				}
			}
			
			nearestObjects.Clear();
		}
	}
}