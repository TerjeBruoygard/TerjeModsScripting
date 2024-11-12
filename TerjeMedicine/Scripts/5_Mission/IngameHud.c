// <copyright file="IngameHud.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class IngameHud
{
	int TERJE_NOTIFIER_SLEEPING = -1;
	int TERJE_NOTIFIER_MIND = -1;
	
	int TERJE_BADGE_BULLETWOUND = -1;
	int TERJE_BADGE_VISCERA = -1;
	int TERJE_BADGE_RADIATION = -1;
	int TERJE_BADGE_PAIN = -1;
	int TERJE_BADGE_OVERDOSE = -1;
	int TERJE_BADGE_STUBWOUND = -1;
	int TERJE_BADGE_HEMATOMA = -1;
	int TERJE_BADGE_CONTUSION = -1;
	int TERJE_BADGE_ZVIRUS = -1;
	int TERJE_BADGE_SEPSIS = -1;
	int TERJE_BADGE_INFLUENZA = -1;
	int TERJE_BADGE_POISON = -1;
	int TERJE_BADGE_BIOHAZARD = -1;
	int TERJE_BADGE_RABIES = -1;
	
	int TERJE_BADGE_UNIVERSALMED = -1;
	int TERJE_BADGE_ANTIPOISON = -1;
	int TERJE_BADGE_SALVE = -1;
	int TERJE_BADGE_ANTIRAD = -1;
	int TERJE_BADGE_PAINKILLER = -1;
	int TERJE_BADGE_HEMOSTATIC = -1;
	int TERJE_BADGE_BLOODREGEN = -1;
	int TERJE_BADGE_DISINFECTED = -1;
	int TERJE_BADGE_BANDAGED_CLEAN = -1;
	int TERJE_BADGE_BANDAGED_DIRTY = -1;
	int TERJE_BADGE_SUTURES_CLEAN = -1;
	int TERJE_BADGE_SUTURES_DIRTY = -1;
	int TERJE_BADGE_ANTIDEPRESANT = -1;
	int TERJE_BADGE_ANTIBIOTIC = -1;
	int TERJE_BADGE_ANTISEPSIS = -1;
	int TERJE_BADGE_Z_ANTIDOT = -1;
	int TERJE_BADGE_ADRENALIN = -1;
	int TERJE_BADGE_CONTUSSIONHEAL = -1;
	int TERJE_BADGE_ANTIBIOHAZARD = -1;
	int TERJE_BADGE_VACINA_A = -1;
	int TERJE_BADGE_VACINA_B = -1;
	int TERJE_BADGE_VACINA_C = -1;
	int TERJE_BADGE_RABIES_CURE = -1;
	
	override void InitBadgesAndNotifiers()
	{
		super.InitBadgesAndNotifiers();
		
		// Change default icons
		ref ImageWidget defaultBleedingIcon = ImageWidget.Cast( m_HudPanelWidget.FindAnyWidget("Bleeding") );
		if (defaultBleedingIcon)
		{
			defaultBleedingIcon.LoadImageFile(0, "set:TerjeMedicine_icon image:tm_scratch");
		}
		
		// Notifiers
		TERJE_NOTIFIER_SLEEPING = RegisterTerjeNotifierWidget("set:TerjeMedicine_icon image:tm_sleeping_{ID}", "TerjeSleeping");
		TERJE_NOTIFIER_MIND = RegisterTerjeNotifierWidget("set:TerjeMedicine_icon image:tm_mind_{ID}", "TerjeMind");
		
		// Badges
		TERJE_BADGE_BULLETWOUND = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_bullethit", "TerjeBullethit", TerjeBadgeType.COUNTER);
		TERJE_BADGE_VISCERA = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_viscera", "TerjeViscera", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_RADIATION = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_radiation", "TerjeRadiation", TerjeBadgeType.LEVELED);
		TERJE_BADGE_PAIN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_pain", "TerjePain", TerjeBadgeType.LEVELED);
		TERJE_BADGE_OVERDOSE = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_overdosed", "TerjeOverdosed", TerjeBadgeType.LEVELED);
		TERJE_BADGE_STUBWOUND = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_wound", "TerjeKnifeHit", TerjeBadgeType.COUNTER);
		TERJE_BADGE_HEMATOMA = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_hematoma", "TerjeHematoma", TerjeBadgeType.COUNTER);
		TERJE_BADGE_CONTUSION = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_concussion", "TerjeConcussion", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_ZVIRUS = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_virusz", "TerjeZVirus", TerjeBadgeType.LEVELED);
		TERJE_BADGE_SEPSIS = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_sepsis", "TerjeSepsis", TerjeBadgeType.LEVELED);
		TERJE_BADGE_INFLUENZA = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_influenza", "TerjeInfluenza", TerjeBadgeType.LEVELED);
		TERJE_BADGE_POISON = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_poison", "TerjePoison", TerjeBadgeType.LEVELED);
		TERJE_BADGE_BIOHAZARD = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_biohazard", "TerjeBiohazard", TerjeBadgeType.LEVELED);
		TERJE_BADGE_RABIES = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_rabies", "TerjeRabies", TerjeBadgeType.LEVELED);
		
		TERJE_BADGE_UNIVERSALMED = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_tablets", "TerjeUniversalMed", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_ANTIPOISON = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antipoison", "TerjeAntipoison", TerjeBadgeType.LEVELED);
		TERJE_BADGE_SALVE = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_salve", "TerjeSalve", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_ANTIRAD = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antirad", "TerjeAntirad", TerjeBadgeType.LEVELED);
		TERJE_BADGE_PAINKILLER = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_painkiller", "TerjePainkiller", TerjeBadgeType.LEVELED);
		TERJE_BADGE_HEMOSTATIC = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_hemostatic", "TerjeHemostatic", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_BLOODREGEN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_bloodregen", "TerjeBloodRegen", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_DISINFECTED = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_disinfected_2", "TerjeDisinfected", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_BANDAGED_CLEAN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_bandagedclean_2", "TerjeBandagedClean", TerjeBadgeType.COUNTER);
		TERJE_BADGE_BANDAGED_DIRTY = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_bandageddirty_2", "TerjeBandagedDirty", TerjeBadgeType.COUNTER);
		TERJE_BADGE_SUTURES_CLEAN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_protectingwound", "TerjeSuturesClean", TerjeBadgeType.COUNTER);
		TERJE_BADGE_SUTURES_DIRTY = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_protectingwoundseps", "TerjeSuturesDirty", TerjeBadgeType.COUNTER);
		TERJE_BADGE_ANTIDEPRESANT = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antidepresant", "TerjeAntidepresant", TerjeBadgeType.LEVELED);
		TERJE_BADGE_ANTIBIOTIC = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antibiotic", "TerjeAntibiotic", TerjeBadgeType.LEVELED);
		TERJE_BADGE_ANTISEPSIS = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antisepsis", "TerjeAntisepsis", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_Z_ANTIDOT = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antidotz", "TerjeZAntidot", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_ADRENALIN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_adrenalin", "TerjeAdrenalin", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_CONTUSSIONHEAL = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_concussionheal", "TerjeConcussionHeal", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_ANTIBIOHAZARD = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_biohazardheal", "TerjeBiohazardHeal", TerjeBadgeType.LEVELED);
		TERJE_BADGE_VACINA_A = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_vacina_a", "TerjeVacinaA", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_VACINA_B = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_vacina_b", "TerjeVacinaB", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_VACINA_C = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_vacina_c", "TerjeVacinaC", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_RABIES_CURE = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_rabies_cure", "TerjeRabiesCure", TerjeBadgeType.LEVELED);
	}
	
	int GetBadgeColor( int key, int value )
	{
		bool colorizedHudBadges;
		int badgetColor = ARGB( 255, 220, 220, 220 );
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_COLORIZED_HUD_BADGES, colorizedHudBadges) && colorizedHudBadges)
		{
			int yellowColor = ARGB( 255, 220, 220, 0 );
			int redColor = ARGB( 255, 220, 0, 0 );
			if (key == NTFKEY_FRACTURE || key == NTFKEY_BLEEDISH)
			{
				badgetColor = redColor;
			}
			else if (key == NTFKEY_SICK || key == NTFKEY_POISONED || key == NTFKEY_LEGS || key == TERJE_BADGE_CONTUSION || key == TERJE_BADGE_BANDAGED_DIRTY || key == TERJE_BADGE_SUTURES_DIRTY)
			{
				badgetColor = yellowColor;
			}
			else if (key == TERJE_BADGE_BULLETWOUND || key == TERJE_BADGE_VISCERA || key == TERJE_BADGE_STUBWOUND || key == TERJE_BADGE_ZVIRUS)
			{
				badgetColor = redColor;
			}
			else if (key == TERJE_BADGE_RADIATION || key == TERJE_BADGE_BIOHAZARD || key == TERJE_BADGE_PAIN || key == TERJE_BADGE_OVERDOSE || key == TERJE_BADGE_SEPSIS || key == TERJE_BADGE_INFLUENZA || key == TERJE_BADGE_POISON || key == TERJE_BADGE_RABIES)
			{
				if (value <= 2)
				{
					badgetColor = yellowColor;
				}
				else
				{
					badgetColor = redColor;
				}
			}
			else if (key == TERJE_BADGE_HEMATOMA)
			{
				if (value <= 8)
				{
					badgetColor = yellowColor;
				}
				else
				{
					badgetColor = redColor;
				}
			}
		}
		
		return badgetColor;
	}
	
	override void DisplayBadge( int key, int value )
	{
		super.DisplayBadge(key, value);
		
		string badgeName;
		if (m_BadgesWidgetNames.Find(key, badgeName))
		{
			int badgetColor = GetBadgeColor(key, value);
			ref ImageWidget badgeImage = ImageWidget.Cast( m_Badges.FindAnyWidget( badgeName ) );
			if (badgeImage)
			{
				badgeImage.SetColor(badgetColor);
			}
			
			ref TextWidget badgeText = TextWidget.Cast( m_Badges.FindAnyWidget( badgeName + "_TerjeCounter" ) );
			if (badgeText)
			{
				badgeText.SetColor(badgetColor);
			}
		}
	}
};
