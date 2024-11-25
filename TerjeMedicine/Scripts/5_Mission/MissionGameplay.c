// <copyright file="MissionGameplay.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class MissionGameplay
{
	private float m_terjeScriptableAreaRecalculate;
	
	override void OnMissionStart()
	{
		super.OnMissionStart();
		m_terjeScriptableAreaRecalculate = 0;
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_CONCUSSION).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_OVERDOSE).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_PAIN).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_SLEEPING).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_PSYONIC).Start();
		
		// Fix PPEffect to 1
		GameOptions gameOptions = new GameOptions();
		if (gameOptions)
		{
			gameOptions.Initialize();
			ListOptionsAccess ppOption = ListOptionsAccess.Cast( gameOptions.GetOptionByType( OptionAccessType.AT_POSTPROCESS_EFFECTS ) );
			if (ppOption && ppOption.GetIndex() == 0)
			{
				ppOption.SetIndex( 1 );
				gameOptions.Apply();
			}
		}
	}
	
	override void OnMissionFinish()
	{
		super.OnMissionFinish();
		
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_CONCUSSION).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_OVERDOSE).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_PAIN).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_SLEEPING).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_PSYONIC).Stop();
	}
	
	override void OnUpdateTerjeCustomBadges(PlayerBase player, bool detailedDiseaseHudBadges, bool detailedHealingHudBadges)
	{
		super.OnUpdateTerjeCustomBadges(player, detailedDiseaseHudBadges, detailedHealingHudBadges);
		
		// Notifiers
		if (m_Hud.TERJE_NOTIFIER_SLEEPING != -1)
		{
			m_Hud.DisplayNotifier(m_Hud.TERJE_NOTIFIER_SLEEPING, player.GetTerjeStats().GetSleepingTendency(), player.GetTerjeStats().GetSleepingLevel());
		}
		
		if (m_Hud.TERJE_NOTIFIER_MIND != -1)
		{
			m_Hud.DisplayNotifier(m_Hud.TERJE_NOTIFIER_MIND, player.GetTerjeStats().GetMindTendency(), player.GetTerjeStats().GetMindLevel());
		}
		
		// Badges (Deseases)
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_HEMATOMA, player.GetTerjeStats().GetHematomasCount());
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_BULLETWOUND, player.GetTerjeStats().GetBulletWounds());
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_STUBWOUND, player.GetTerjeStats().GetStubWounds());
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_CONTUSION, (int)player.GetTerjeStats().GetContusion());
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_VISCERA, (int)player.GetTerjeStats().GetViscera());
		
		if (detailedDiseaseHudBadges)
		{
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_PAIN, player.GetTerjeStats().GetPainLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_OVERDOSE, player.GetTerjeStats().GetOverdoseLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_ZVIRUS, player.GetTerjeStats().GetZVirusLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_SEPSIS, player.GetTerjeStats().GetSepsisLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_INFLUENZA, player.GetTerjeStats().GetInfluenzaLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_POISON, player.GetTerjeStats().GetPoisonLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_BIOHAZARD, player.GetTerjeStats().GetBiohazardLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_RABIES, player.GetTerjeStats().GetRabiesLevel());
		}
		
		// Badges (Medicine)
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_DISINFECTED, (int)player.GetTerjeStats().GetDisinfected());
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_BANDAGED_CLEAN, player.GetTerjeStats().GetBandagesClean() + player.GetTerjeStats().GetSuturesBandagedClean());
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_BANDAGED_DIRTY, player.GetTerjeStats().GetBandagesDirty() + player.GetTerjeStats().GetSuturesBandagedDirty());
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_SUTURES_CLEAN, player.GetTerjeStats().GetSuturesClean());
		m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_SUTURES_DIRTY, player.GetTerjeStats().GetSuturesDirty());
		
		if (detailedHealingHudBadges)
		{
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_ANTIPOISON, player.GetTerjeStats().GetAntipoisonLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_SALVE, (int)player.GetTerjeStats().GetSalve());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_PAINKILLER, player.GetTerjeStats().GetPainkillerLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_HEMOSTATIC, (int)player.GetTerjeStats().GetHemostatic());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_BLOODREGEN, (int)player.GetTerjeStats().GetBloodRegen());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_ANTIDEPRESANT, player.GetTerjeStats().GetAntidepresantLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_ANTIBIOTIC, player.GetTerjeStats().GetAntibioticLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_ANTISEPSIS, (int)player.GetTerjeStats().GetAntisepsis());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_Z_ANTIDOT, (int)player.GetTerjeStats().GetZAntidot());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_ADRENALIN, (int)player.GetTerjeStats().GetAdrenalin());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_CONTUSSIONHEAL, (int)player.GetTerjeStats().GetContusionHeal());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_ANTIBIOHAZARD, player.GetTerjeStats().GetAntibiohazardLevel());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_VACINA_A, (int)player.GetTerjeStats().GetInfluenzaVacine());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_VACINA_B, (int)player.GetTerjeStats().GetZVirusVacine());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_VACINA_C, (int)player.GetTerjeStats().GetRabiesVacine());
			m_Hud.DisplayBadge(m_Hud.TERJE_BADGE_RABIES_CURE, (int)player.GetTerjeStats().GetRabiesCureLevel());
		}
	}
	
	override void OnUpdateTerjeCustomGUI(PlayerBase player, float deltaTime)
	{
		super.OnUpdateTerjeCustomGUI(player, deltaTime);
		float overdosedEffect = Math.Clamp(((float)player.GetTerjeStats().GetOverdoseLevel() - 0.5) * 0.1, 0, 0.3);
		PPERequester_TerjeMedOverdose.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_OVERDOSE)).SetOverdosedEffect(overdosedEffect);
		
		float painEffect = Math.Clamp((float)player.GetTerjeStats().GetPainLevel() * 0.1, 0, 0.3);
		PPERequester_TerjeMedPain.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_PAIN)).SetPainEffect(painEffect);
		
		float concussionEffect = Math.Clamp(((int)player.GetTerjeStats().GetContusion()) * 0.1, 0, 0.1);
		PPERequester_TerjeMedConcussion.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_CONCUSSION)).SetConcussionEffect(concussionEffect);
		
		int sleepingLevel = player.GetTerjeStats().GetSleepingLevel() - 4;
		int sleepingState = player.GetTerjeStats().GetSleepingState();
		float sleepingValue = Math.Max(Math.Clamp(sleepingLevel, 0, 0.6), Math.Clamp(sleepingState, 0, 0.98));
		PPERequester_TerjeMedSleeping.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_SLEEPING)).SetSleepingEffect(sleepingValue);
		
		m_terjeScriptableAreaRecalculate = m_terjeScriptableAreaRecalculate - deltaTime;
		if (m_terjeScriptableAreaRecalculate < 0)
		{
			m_terjeScriptableAreaRecalculate = 1.0 / 30.0;
			float psionicEffect = GetTerjeScriptableAreas().CalculateTerjeEffectValue(player, "psi");
			PPERequester_TerjeMedPsyonic.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_PSYONIC)).SetPsyonicEffect(psionicEffect);
		}
		
		int mindStateLevel = player.GetTerjeStats().GetMindLevel();
		if (mindStateLevel >= 4)
		{
			float randomCheck = 0.05;
			if (mindStateLevel >= 5)
			{
				randomCheck = 0.25;
			}
			
			if (Math.RandomFloat01() < deltaTime * randomCheck)
			{
				int action = Math.RandomInt(0, 8);
				if (action == 0)
				{
					Weapon_Base weapon;
					WeaponEventBase weapon_event = new WeaponEventTrigger;
					if ( Weapon_Base.CastTo(weapon, player.GetItemInHands()) )
					{
						weapon.ProcessWeaponEvent(weapon_event);
					}
				}
				else if (action == 1)
				{
					if (player.GetEmoteManager().CanPlayEmote(EmoteConstants.ID_EMOTE_SUICIDE))
					{
						player.GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_SUICIDE);
					}
				}
				else
				{
					int emotesCount = player.GetEmoteManager().GetTotalEmotesCount();
					int emoteId = Math.RandomInt(0, emotesCount);
					int emoteKey = player.GetEmoteManager().GetEmoteKeyById(emoteId);
					if (player.GetEmoteManager().CanPlayEmote(emoteKey))
					{
						player.GetEmoteManager().CreateEmoteCBFromMenu(emoteKey);
					}
				}
			}
		}
		
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_CONCUSSION).SetRequesterUpdating(true);
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_OVERDOSE).SetRequesterUpdating(true);
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_PAIN).SetRequesterUpdating(true);
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_SLEEPING).SetRequesterUpdating(true);
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_TERJEMED_PSYONIC).SetRequesterUpdating(true);
	}
}
