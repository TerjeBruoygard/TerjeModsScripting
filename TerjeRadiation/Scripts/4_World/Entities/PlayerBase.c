// <copyright file="PlayerBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PlayerBase
{
	private int m_terjeRadiationSynch = 0;
	private int m_terjeAbsoluteRadProtection = -1;
	
	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableInt("m_terjeRadiationSynch", 0, TerjeRadiationConstants.RADIATION_PLAYER_ACCUMULATOR_SYNCH_MAX);
	}
	
	override void OnTerjeRegisterModifiers(ref array<ref TerjePlayerModifierBase> modifiers)
	{
		super.OnTerjeRegisterModifiers(modifiers);
		
		modifiers.Insert(new TerjePlayerModifierRadioactiveScriptableAreas());
		modifiers.Insert(new TerjePlayerModifierRadiation());
	}
	
	override bool HasTerjeHealings()
	{
		if (super.HasTerjeHealings())
		{
			return true;
		}
		else if (GetTerjeStats() != null && GetTerjeStats().GetAntiradLevel())
		{
			return true;
		}
		
		return false;
	}
	
	override bool HasTerjeDisease()
	{
		if (super.HasTerjeDisease())
		{
			return true;
		}
		else if (GetTerjeStats() != null && GetTerjeStats().GetRadiationLevel())
		{
			return true;
		}
		
		return false;
	}
	
	override bool AddTerjeRadiation(float rAmount)
	{
		return AddTerjeRadiationAdvanced(rAmount, -1, false);
	}
	
	override bool AddTerjeRadiationAdvanced(float rAmount, float environmentRadiation, bool ignoreProtection)
	{
		if (GetGame().IsDedicatedServer() && IsAlive() && GetTerjeStats() != null)
		{
			if (m_terjeAbsoluteRadProtection == -1)
			{
				PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
				if (plugin && plugin.HasAbsoluteCustomProtectionOfType(this, "radiation"))
				{
					m_terjeAbsoluteRadProtection = 1;
				}
				else
				{
					m_terjeAbsoluteRadProtection = 0;
				}
			}
			
			if (m_terjeAbsoluteRadProtection == 1)
			{
				return false;
			}
			
			if (rAmount > 0 && !ignoreProtection)
			{
				rAmount *= (1.0 - Math.Clamp(GetTerjeRadiationProtection(environmentRadiation), 0, 1));
			}
			
			if (rAmount != 0)
			{
				GetTerjeStats().SetRadiationAccumulated(GetTerjeStats().GetRadiationAccumulated() + rAmount);
			}
			
			return true;
		}
		
		return super.AddTerjeRadiationAdvanced(rAmount, environmentRadiation, ignoreProtection);
	}
	
	override float GetTerjeRadiation()
	{
		if (IsAlive() && GetTerjeStats() != null)
		{
			if (GetGame().IsDedicatedServer())
			{
				return GetTerjeStats().GetRadiationAccumulated();
			}
			else
			{
				return m_terjeRadiationSynch * TerjeRadiationConstants.RADIATION_PLAYER_ACCUMULATOR_SYNCH_DIVIDER;
			}
		}
		
		return super.GetTerjeRadiation();
	}
	
	override float GetTerjeRadiationAdvanced(bool body, bool itemInHands, bool equipment)
	{
		float result = 0;
		if (body)
		{
			result += GetTerjeRadiation();
		}
		
		if (itemInHands)
		{
			ItemBase inHands = GetItemInHands();
			if (inHands)
			{
				result += inHands.GetTerjeRadiation();
			}
		}
		
		if (equipment)
		{
			ItemBase attachment;
			int attCount = GetInventory().AttachmentCount();
			for ( int attIdx = 0; attIdx < attCount; attIdx++ )
			{
				if (ItemBase.CastTo(attachment, GetInventory().GetAttachmentFromIndex( attIdx )) && attachment)
				{
					result += attachment.GetTerjeRadiation();
				}
			}
		}
		
		return result;
	}
	
	override float GetTerjeRadiationProtection(float environmentRadiation)
	{
		float protection = GetTerjeScriptableAreas().CalculatePlayerBodyProtection(this, "radiation", environmentRadiation);
		float perkRadresMod;
		if (GetTerjeSkills() && GetTerjeSkills().GetPerkValue("immunity", "radres", perkRadresMod))
		{
			protection = protection + ((1.0 - protection) * perkRadresMod);
		}
		
		return Math.Clamp(protection, 0, 1);
	}

	override bool HasTerjeSicknesOrInjures()
	{
		if (super.HasTerjeSicknesOrInjures())
		{
			return true;
		}
		
		if (GetTerjeStats() != null)
		{
			if (GetTerjeStats().GetRadiationLevel() > 0) 
			{
				return true;
			}
		}
		
		return false;
	}

	void UpdateTerjeRadiationAccumulated()
	{
		if (GetGame().IsDedicatedServer() && IsAlive() && GetTerjeStats() != null)
		{
			int newValue = (int)Math.Round(GetTerjeStats().GetRadiationAccumulated() / TerjeRadiationConstants.RADIATION_PLAYER_ACCUMULATOR_SYNCH_DIVIDER);
			if (m_terjeRadiationSynch != newValue)
			{
				m_terjeRadiationSynch = newValue;
				SetSynchDirty();
			}
		}
	}
}
