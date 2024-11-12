// <copyright file="TerjeScriptableArea.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeScriptableArea : House
{
	private int m_terjeLocalIndex;
	bool m_terjeInitialized = false;
	float m_terjeInnerRadius = 0;
	float m_terjeOuterRadius = 0;
	float m_terjeHeightMin = 0;
	float m_terjeHeightMax = 0;
	float m_terjePower = 0;
	
	void TerjeScriptableArea()
	{
		RegisterNetSyncVariableBool("m_terjeInitialized");
		RegisterNetSyncVariableFloat("m_terjeInnerRadius", 0, 0, 2);
		RegisterNetSyncVariableFloat("m_terjeOuterRadius", 0, 0, 2);
		RegisterNetSyncVariableFloat("m_terjeHeightMin", 0, 0, 2);
		RegisterNetSyncVariableFloat("m_terjeHeightMax", 0, 0, 2);
		RegisterNetSyncVariableFloat("m_terjePower", 0, 0, 2);
	}
	
	string GetTerjeScriptableAreaType()
	{
		return "";
	}
	
	void SetTerjeParameters(map<string, float> parameters)
	{
		if (GetGame().IsDedicatedServer())
		{
			if (parameters.Contains("InnerRadius"))
			{
				m_terjeInnerRadius = parameters.Get("InnerRadius");
			}
			
			if (parameters.Contains("OuterRadius"))
			{
				m_terjeOuterRadius = parameters.Get("OuterRadius");
			}
			
			if (parameters.Contains("HeightMin"))
			{
				m_terjeHeightMin = parameters.Get("HeightMin");
			}
			
			if (parameters.Contains("HeightMax"))
			{
				m_terjeHeightMax = parameters.Get("HeightMax");
			}
			
			if (parameters.Contains("Power"))
			{
				m_terjePower = parameters.Get("Power");
			}
			
			m_terjeInitialized = true;
			SetSynchDirty();
		}
	}
	
	override void EEInit()
	{
		super.EEInit();
		m_terjeLocalIndex = GetTerjeScriptableAreas().RegisterScriptableArea(this);
		
		if (!m_terjeInitialized && GetGame().IsDedicatedServer())
		{
			m_terjeInnerRadius = ConfigGetFloat("terjeInnerRadius");
			m_terjeOuterRadius = ConfigGetFloat("terjeOuterRadius");
			m_terjeHeightMin = ConfigGetFloat("terjeHeightMin");
			m_terjeHeightMax = ConfigGetFloat("terjeHeightMax");
			m_terjePower = ConfigGetFloat("terjePower");
			m_terjeInitialized = true;
			SetSynchDirty();
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		GetTerjeScriptableAreas().UnregisterScriptableArea(GetTerjeScriptableAreaType(), m_terjeLocalIndex);
	}
	
	override bool CanPutInCargo( EntityAI parent )
	{
		return false;
	}
	
	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
	
	override bool DisableVicinityIcon()
    {
        return true;
    }
	
	override bool CanBeTargetedByAI( EntityAI ai )
	{
		return false;
	}
	
	float CalculateTerjeEffectValue(vector targetPos)
	{
		float result = 0;
		vector areaPos = GetPosition();
		if (targetPos[1] >= (areaPos[1] + m_terjeHeightMin) && targetPos[1] <= (areaPos[1] + m_terjeHeightMax))
		{
			vector areaPos2d = Vector(areaPos[0], 0, areaPos[2]);
			vector targetPos2d = Vector(targetPos[0], 0, targetPos[2]);
			float distance2d = vector.Distance(areaPos2d, targetPos2d);
			if (distance2d < m_terjeOuterRadius)
			{
				if (distance2d <= m_terjeInnerRadius)
				{
					result = m_terjePower;
				}
				else
				{
					float ringsDistance = (m_terjeOuterRadius - m_terjeInnerRadius);
					if (ringsDistance > 0)
					{
						result = (1.0 - ((distance2d - m_terjeInnerRadius) / ringsDistance)) * m_terjePower;
					}
					else
					{
						result = m_terjePower;
					}
				}
			}
		}
		
		return result;
	}
};