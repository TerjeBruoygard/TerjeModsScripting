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
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_RadiationAccum("terjeRadiationAccum", "Rad-buffer", "set:TerjeMedicine_icon image:tm_radiation", 0, TerjeMedicineConstants.RADIATION_PLAYER_ACCUMULATOR_SERVER_MAX));
		RegisterPlayerStat(new TerjeAdmintoolSupport_PlayerStat_RadiationSick("terjeRadiationSick", "Rad-sickness", "set:TerjeMedicine_icon image:tm_radiation", 0, TerjeMedicineConstants.RADIATION_MAX_VALUE));
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
			player.GetTerjeStats().SetRadiationAccumulated(0);
			player.GetTerjeStats().SetRadiationValue(0);
			player.GetTerjeStats().SetPoisonValue(0);
			player.GetTerjeStats().SetBiohazardValue(0);
			player.GetTerjeStats().SetRabiesValue(0);
			player.GetTerjeStats().SetMindValue(TerjeMedicineConstants.MIND_MAX_VALUE);
			player.GetTerjeStats().SetSleepingValue(TerjeMedicineConstants.SLEEPING_MAX_VALUE);
		}
	}
};

class TerjeAdmintoolSupport_PlayerStat_Sleeping : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetSleepingValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetSleepingValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Mind : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetMindValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetMindValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_BC : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetBandagesClean();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetBandagesClean((int)value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_BD : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetBandagesDirty();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetBandagesDirty((int)value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_BCS : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetSuturesBandagedClean();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetSuturesBandagedClean((int)value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_BDS : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetSuturesBandagedDirty();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetSuturesBandagedDirty((int)value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_CS : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetSuturesClean();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetSuturesClean((int)value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_DS : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetSuturesDirty();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetSuturesDirty((int)value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Hematomas : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetHematomas();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetHematomas(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Stubs : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetStubWounds();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetStubWounds((int)value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Bullets : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetBulletWounds();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetBulletWounds((int)value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_ZVirus : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetZVirusValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetZVirusValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Sepsis : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetSepsisValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetSepsisValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Pain : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetPainValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetPainValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Influenza : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetInfluenzaValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetInfluenzaValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Overdose : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetOverdoseValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetOverdoseValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_RadiationAccum : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetRadiationAccumulated();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetRadiationAccumulated(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_RadiationSick : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetRadiationValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetRadiationValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Poison : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetPoisonValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetPoisonValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Biohazard : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetBiohazardValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetBiohazardValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Contusion : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetContusionValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetContusionValue(value);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Viscera : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		if (player.GetTerjeStats().GetViscera())
			return 1;
		return 0;
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetViscera(value > 0.5);
	}
};

class TerjeAdmintoolSupport_PlayerStat_Rabies : TerjeAdmintoolSupport_PlayerStat
{
	override float GetValue(PlayerBase player)
	{
		return player.GetTerjeStats().GetRabiesValue();
	}
	
	override void SetValue(PlayerBase player, float value)
	{
		player.GetTerjeStats().SetRabiesValue(value);
	}
};