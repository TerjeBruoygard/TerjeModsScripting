// <copyright file="TerjeAdmintoolSupport.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeAdmintoolSupport
{
	override void OnInit()
	{
		super.OnInit();
		
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Sleeping("terjeSleep", "Sleeping", "set:TerjeMedicine_icon image:tm_sleeping_4", 0, TerjeMedicineConstants.SLEEPING_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Mind("terjeMind", "Mind", "set:TerjeMedicine_icon image:tm_mind_4", 0, TerjeMedicineConstants.MIND_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_BC("terjeBC", "(C) Bandages", "set:TerjeMedicine_icon image:tm_bandagedclean_2", 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_BD("terjeBD", "(D) Bandages", "set:TerjeMedicine_icon image:tm_bandageddirty_2", 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_BCS("terjeBCS", "(BC) Sutures", "set:TerjeMedicine_icon image:tm_bandagedclean_2", 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_BDS("terjeBDS", "(BD) Sutures", "set:TerjeMedicine_icon image:tm_bandageddirty_2", 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_CS("terjeCS", "(C) Sutures", "set:TerjeMedicine_icon image:tm_protectingwound", 0, TerjeMedicineConstants.SUTURES_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_DS("terjeDS", "(D) Sutures", "set:TerjeMedicine_icon image:tm_protectingwoundseps", 0, TerjeMedicineConstants.SUTURES_MAX_VALUE));	
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Hematomas("terjeHematomas", "Hematomas", "set:TerjeMedicine_icon image:tm_hematoma", 0, TerjeMedicineConstants.HEMATOMAS_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Stubs("terjeStubs", "Stubs", "set:TerjeMedicine_icon image:tm_wound", 0, TerjeMedicineConstants.STUBWOUND_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Bullets("terjeBullets", "Bullets", "set:TerjeMedicine_icon image:tm_bullethit", 0, TerjeMedicineConstants.BULLETWOUND_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_ZVirus("terjeZVirus", "Z-Virus", "set:TerjeMedicine_icon image:tm_virusz", 0, TerjeMedicineConstants.ZOMBIE_VIRUS_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Sepsis("terjeSepsis", "Sepsis", "set:TerjeMedicine_icon image:tm_sepsis", 0, TerjeMedicineConstants.SEPSIS_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Pain("terjePain", "Pain", "set:TerjeMedicine_icon image:tm_pain", 0, TerjeMedicineConstants.PAIN_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Influenza("terjeInfluenza", "Influenza", "set:TerjeMedicine_icon image:tm_influenza", 0, TerjeMedicineConstants.INFLUENZA_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Overdose("terjeOverdose", "Overdose", "set:TerjeMedicine_icon image:tm_overdosed", 0, TerjeMedicineConstants.OVERDOSE_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Poison("terjePoison", "Poison", "set:TerjeMedicine_icon image:tm_poison", 0, TerjeMedicineConstants.POISON_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Biohazard("terjeBiohazard", "Biohazard", "set:TerjeMedicine_icon image:tm_biohazard", 0, TerjeMedicineConstants.BIOHAZARD_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Contusion("terjeContusion", "Contusion", "set:TerjeMedicine_icon image:tm_concussion", 0, TerjeMedicineConstants.CONTUSION_MAX_VALUE));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Viscera("terjeViscera", "Viscera", "set:TerjeMedicine_icon image:tm_viscera", 0, 1));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_Rabies("terjeRabies", "Rabies", "set:TerjeMedicine_icon image:tm_rabies", 0, TerjeMedicineConstants.RABIES_MAX_VALUE));
	}
	
	override void OnHeal(PlayerBase player)
	{
		super.OnHeal(player);
		
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetBandagesClean(0);
			player.GetTerjeStats().SetBandagesDirty(0);
			player.GetTerjeStats().SetSuturesBandagedClean(0);
			player.GetTerjeStats().SetSuturesBandagedDirty(0);
			player.GetTerjeStats().SetSuturesClean(0);
			player.GetTerjeStats().SetSuturesDirty(0);
			player.GetTerjeStats().SetHematomas(0);
			player.GetTerjeStats().SetBulletWounds(0);
			player.GetTerjeStats().SetStubWounds(0);
			player.GetTerjeStats().SetContusionValue(0);
			player.GetTerjeStats().SetZVirusValue(0);
			player.GetTerjeStats().SetViscera(false);
			player.GetTerjeStats().SetPainValue(0);
			player.GetTerjeStats().SetInfluenzaValue(0);
			player.GetTerjeStats().SetSepsisValue(0);
			player.GetTerjeStats().SetOverdoseValue(0);
			player.GetTerjeStats().SetPoisonValue(0);
			player.GetTerjeStats().SetBiohazardValue(0);
			player.GetTerjeStats().SetRabiesValue(0);
			player.GetTerjeStats().SetMindValue(TerjeMedicineConstants.MIND_MAX_VALUE);
			player.GetTerjeStats().SetSleepingValue(TerjeMedicineConstants.SLEEPING_MAX_VALUE);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Sleeping : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetSleepingValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetSleepingValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Mind : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetMindValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetMindValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_BC : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetBandagesClean();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetBandagesClean((int)value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_BD : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetBandagesDirty();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetBandagesDirty((int)value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_BCS : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetSuturesBandagedClean();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetSuturesBandagedClean((int)value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_BDS : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetSuturesBandagedDirty();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetSuturesBandagedDirty((int)value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_CS : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetSuturesClean();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetSuturesClean((int)value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_DS : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetSuturesDirty();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetSuturesDirty((int)value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Hematomas : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetHematomas();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetHematomas(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Stubs : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetStubWounds();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetStubWounds((int)value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Bullets : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetBulletWounds();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetBulletWounds((int)value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_ZVirus : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetZVirusValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetZVirusValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Sepsis : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetSepsisValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetSepsisValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Pain : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetPainValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetPainValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Influenza : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetInfluenzaValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetInfluenzaValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Overdose : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetOverdoseValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetOverdoseValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Poison : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetPoisonValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetPoisonValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Biohazard : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetBiohazardValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetBiohazardValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Contusion : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetContusionValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetContusionValue(value);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Viscera : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			if (player.GetTerjeStats().GetViscera())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetViscera(value > 0.5);
		}
	}
}

class TerjeAdmintoolSupport_PlayerStat_Rabies : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats())
		{
			return player.GetTerjeStats().GetRabiesValue();
		}
		else
		{
			return GetMin();
		}
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		if (player.GetTerjeStats())
		{
			player.GetTerjeStats().SetRabiesValue(value);
		}
	}
}