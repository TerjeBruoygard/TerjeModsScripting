// <copyright file="TerjeDosimetrBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeDosimetrBase : Inventory_Base
{
	const string TERJE_NUMBERS_TEXTURE_PATH = "TerjeRadiation\\Dosimeter\\Numbers\\num";
	
	protected EffectSound m_DosimetrSoundEffect;
	protected int m_DosimeterSoundIndex = -1;
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (GetGame() && m_DosimetrSoundEffect)
		{
			SEffectManager.DestroyEffect(m_DosimetrSoundEffect);
		}
	}
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		
		if (GetGame().IsClient())
		{
			TerjeEnableDisplayClient();
			m_DosimeterSoundIndex = -1;
		}
	}
	
	override void OnWork( float consumed_energy )
	{
		super.OnWork(consumed_energy);
		
		if (GetGame().IsClient())
		{
			float radioactiveValue = Math.Clamp(CalculateTerjeEnvironmentRadiation() * TerjeGeigerRadiationModifier(), 0, TerjeGeigerMaxLimit());
			
			TerjeUpdateDisplayValueClient((int)radioactiveValue);
			
			if (radioactiveValue > 0)
			{
				int newSoundStages = TerjeGeigerSoundsCount() - 1;
				int newSoundIndex = ClampInt((int)((radioactiveValue / TerjeGeigerMaxLimit()) * newSoundStages), 0, newSoundStages);
				if (m_DosimeterSoundIndex != newSoundIndex)
				{
					m_DosimeterSoundIndex = newSoundIndex;
					StopSoundSet(m_DosimetrSoundEffect);
					PlaySoundSetLoop(m_DosimetrSoundEffect, TerjeGeigerGetSoundSet(newSoundIndex), 0, 0);
				}
			}
			else
			{
				if (m_DosimeterSoundIndex != -1)
				{
					m_DosimeterSoundIndex = -1;
					StopSoundSet(m_DosimetrSoundEffect);
				}
			}
		}
	}
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		
		if (GetGame().IsClient())
		{
			TerjeDisableDisplayClient();
			if (m_DosimeterSoundIndex != -1)
			{
				m_DosimeterSoundIndex = -1;
				StopSoundSet(m_DosimetrSoundEffect);
			}
		}
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
	}
	
	override void OnDebugSpawn()
	{
		Battery9V.Cast(GetInventory().CreateInInventory("Battery9V"));
	}
	
	float CalculateTerjeEnvironmentRadiation()
	{
		// Calculate is item inside the protection container (no radiation inside)
		float hierarhyProtection = 0;
		ItemBase hierarhyParentItem;
		EntityAI hierarhyParent = this.GetHierarchyParent();
		while (hierarhyParent)
		{
			if (ItemBase.CastTo(hierarhyParentItem, hierarhyParent))
			{
				hierarhyProtection += hierarhyParentItem.GetTerjeRadiationInventoryIsolation();
			}
			else
			{
				break;
			}
			
			hierarhyParent = hierarhyParent.GetHierarchyParent();
		}
		
		// Calculate radiation from environment
		float result = 0;
		hierarhyProtection = 1.0 - Math.Clamp(hierarhyProtection, 0, 1);
		PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
		if (plugin && hierarhyProtection > 0)
		{
			result = Math.Max(result, plugin.CalculateTerjeEffectValue(this, "rad") * hierarhyProtection);
			result = Math.Max(result, plugin.CalculateTerjeRadiationFromNearestEntities(this, GetTerjeSensitivityRadius(), true) * hierarhyProtection);
		}
		
		return result;
	}
	
	protected void TerjeEnableDisplayClient()
	{
	}
	
	protected void TerjeDisableDisplayClient()
	{
	}
	
	protected void TerjeUpdateDisplayValueClient(int value)
	{
	}
	
	protected int TerjeGeigerSoundsCount()
	{
		return 0;
	}
	
	protected int TerjeGeigerMaxLimit()
	{
		return 0;
	}
	
	protected float TerjeGeigerRadiationModifier()
	{
		return 0;
	}
	
	protected string TerjeGeigerGetSoundSet(int index)
	{
		return "";
	}
	
	protected string TerjeConvertNumberToTexture(int number)
	{
		if (number >= 0 && number < 10)
		{
			return TERJE_NUMBERS_TEXTURE_PATH + number + "_ca.paa";
		}
		
		return TERJE_NUMBERS_TEXTURE_PATH + "off_ca.paa";
	}
	
	protected int GetTerjeHiddenSelection(string selection)
	{	
		int idx = GetHiddenSelectionIndex(selection);
		if (idx != INDEX_NOT_FOUND)
		{
			return idx;
		}
		else
		{
			return 0;
		}
	}
	
	protected float GetTerjeSensitivityRadius()
	{
		return 0;
	}
	
	override bool IsTerjeRadiationAccumulated()
	{
		return false;
	}
	
	override float GetTerjeRadiationInventoryIsolation()
	{
		return 1;
	}
}