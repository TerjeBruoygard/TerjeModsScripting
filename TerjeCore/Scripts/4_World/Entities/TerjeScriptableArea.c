// <copyright file="TerjeScriptableArea.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeScriptableArea : House
{
	private int m_terjeLocalIndex;
	private vector m_terjeStaticPos;
	protected bool m_terjeInitialized = false;
	protected float m_terjeInnerRadius = 0;
	protected float m_terjeOuterRadius = 0;
	protected float m_terjeHeightMin = 0;
	protected float m_terjeHeightMax = 0;
	protected float m_terjePower = 0;
	
	void TerjeScriptableArea()
	{
		RegisterNetSyncVariableBool("m_terjeInitialized");
		RegisterNetSyncVariableFloat("m_terjeInnerRadius", 0, 0, 2);
		RegisterNetSyncVariableFloat("m_terjeOuterRadius", 0, 0, 2);
		RegisterNetSyncVariableFloat("m_terjeHeightMin", 0, 0, 2);
		RegisterNetSyncVariableFloat("m_terjeHeightMax", 0, 0, 2);
		RegisterNetSyncVariableFloat("m_terjePower", 0, 0, 2);
	}
	
	float GetTerjeRadius()
	{
		return m_terjeOuterRadius;
	}
	
	string GetTerjeScriptableAreaType()
	{
		return "";
	}
	
	void SetTerjeFilterServer(string filter)
	{
		SetTerjeFilter(filter);
	}
	
	void SetTerjeFilter(string filter)
	{
	
	}
	
	void SetTerjeParametersServer(map<string, float> parameters)
	{
		if (GetGame().IsDedicatedServer())
		{
			SetTerjeParameters(parameters);
			m_terjeInitialized = true;
			SetSynchDirty();
		}
	}
	
	void SetTerjeParameters(map<string, float> parameters)
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
	}
	
	void LoadTerjeConfigParameters()
	{
		m_terjeInnerRadius = ConfigGetFloat("terjeInnerRadius");
		m_terjeOuterRadius = ConfigGetFloat("terjeOuterRadius");
		m_terjeHeightMin = ConfigGetFloat("terjeHeightMin");
		m_terjeHeightMax = ConfigGetFloat("terjeHeightMax");
		m_terjePower = ConfigGetFloat("terjePower");
	}
	
	override void EEInit()
	{
		super.EEInit();
		m_terjeLocalIndex = GetTerjeScriptableAreas().RegisterScriptableArea(this);
		m_terjeStaticPos = GetWorldPosition();
		
		if (!m_terjeInitialized && GetGame().IsDedicatedServer())
		{
			LoadTerjeConfigParameters();
			
			string filter = ConfigGetStringRaw("terjeFilter");
			if (filter != "")
			{
				SetTerjeFilter(filter);
			}
			
			m_terjeInitialized = true;
			SetSynchDirty();
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		GetTerjeScriptableAreas().UnregisterScriptableArea(m_terjeLocalIndex, this);
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
	
	float CalculateTerjeEffectValue(EntityAI source, vector targetPos)
	{
		float result;
		if (TryCalculateTerjeEffectValue(source, targetPos, "", result))
		{
			return result;
		}
		
		return 0;
	}
	
	bool TryCalculateTerjeEffectValue(EntityAI source, vector targetPos, string filterEntry, out float result)
	{
		vector areaPos = GetWorldPosition();
		if (m_terjeStaticPos != areaPos)
		{
			areaPos = m_terjeStaticPos;
			SetPosition(m_terjeStaticPos);
			TerjeLog_Error("Terje scripted area " + this + " is a static object and cannot be moved.");
		}
		
		if (m_terjeInitialized && targetPos[1] >= (areaPos[1] + m_terjeHeightMin) && targetPos[1] <= (areaPos[1] + m_terjeHeightMax))
		{
			vector areaPos2d = Vector(areaPos[0], 0, areaPos[2]);
			vector targetPos2d = Vector(targetPos[0], 0, targetPos[2]);
			float distance2d = vector.Distance(areaPos2d, targetPos2d);
			if (distance2d < m_terjeOuterRadius)
			{
				if (distance2d <= m_terjeInnerRadius)
				{
					result = m_terjePower;
					return TryCalculateTerjeEffectFilter(source, filterEntry);
				}
				else
				{
					float ringsDistance = (m_terjeOuterRadius - m_terjeInnerRadius);
					if (ringsDistance > 0)
					{
						result = (1.0 - ((distance2d - m_terjeInnerRadius) / ringsDistance)) * m_terjePower;
						return TryCalculateTerjeEffectFilter(source, filterEntry);
					}
					else
					{
						result = m_terjePower;
						return TryCalculateTerjeEffectFilter(source, filterEntry);
					}
				}
			}
		}
		
		result = 0;
		return false;
	}
	
	bool TryCalculateTerjeEffectFilter(EntityAI source, string filterEntry)
	{
		return true;
	}
}