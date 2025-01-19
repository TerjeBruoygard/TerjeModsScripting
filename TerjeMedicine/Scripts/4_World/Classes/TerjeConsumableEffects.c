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
			float overdosedIncrement = GetGame().ConfigGetFloat( classname + " overdosedIncrement" );
			if (overdosedIncrement > 0)
			{
				player.GetTerjeStats().SetOverdoseValue(player.GetTerjeStats().GetOverdoseValue() + (overdosedIncrement * amount));
			}
			
			float biohazardIncrement = GetGame().ConfigGetFloat( classname + " biohazardIncrement" );
			if (biohazardIncrement > 0)
			{
				player.GetTerjeStats().SetBiohazardValue(player.GetTerjeStats().GetBiohazardValue() + (biohazardIncrement * amount));
			}
			
			int medPainkillerLevel = GetGame().ConfigGetInt( classname + " medPainkillerLevel" );
			if (medPainkillerLevel > 0)
			{
				if (medPainkillerLevel < 3 && player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkLevel("med", "anestlog") > 0)
				{
					medPainkillerLevel = medPainkillerLevel + 1;
				}
				
				int activePainkillerLevel = 0;
				float activePainkillerTime = 0;
				player.GetTerjeStats().GetPainkiller(activePainkillerLevel, activePainkillerTime);
				
				float medPainkillerTimeSec = GetGame().ConfigGetFloat( classname + " medPainkillerTimeSec" );
				if (medPainkillerLevel >= activePainkillerLevel && medPainkillerTimeSec > 0)
				{
					int medPainkillerMaxTimeSec = GetGame().ConfigGetInt( classname + " medPainkillerMaxTimeSec" );
					if (medPainkillerMaxTimeSec <= 0)
					{
						medPainkillerMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetPainkiller(medPainkillerLevel, Math.Min(medPainkillerMaxTimeSec, activePainkillerTime + (medPainkillerTimeSec * amount * timeModifier)));
				}
			}
			
			int medAntipoisonLevel = GetGame().ConfigGetInt( classname + " medAntipoisonLevel" );
			if (medAntipoisonLevel > 0)
			{
				int activeAntipoisonLevel = 0;
				float activeAntipoisonTime = 0;
				player.GetTerjeStats().GetAntipoison(activeAntipoisonLevel, activeAntipoisonTime);
				
				float medAntipoisonTimeSec = GetGame().ConfigGetFloat( classname + " medAntipoisonTimeSec" );
				if (medAntipoisonLevel >= activeAntipoisonLevel && medAntipoisonTimeSec > 0)
				{
					int medAntipoisonMaxTimeSec = GetGame().ConfigGetInt( classname + " medAntipoisonMaxTimeSec" );
					if (medAntipoisonMaxTimeSec <= 0)
					{
						medAntipoisonMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetAntipoison(medAntipoisonLevel, Math.Min(medAntipoisonMaxTimeSec, activeAntipoisonTime + (medAntipoisonTimeSec * amount * timeModifier)));
				}
			}
			
			int medAntibiohazardLevel = GetGame().ConfigGetInt( classname + " medAntibiohazardLevel" );
			if (medAntibiohazardLevel > 0)
			{
				int activeAntibiohazardLevel = 0;
				float activeAntibiohazardTime = 0;
				player.GetTerjeStats().GetAntibiohazard(activeAntibiohazardLevel, activeAntibiohazardTime);
				
				float medAntibiohazardTimeSec = GetGame().ConfigGetFloat( classname + " medAntibiohazardTimeSec" );
				if (medAntibiohazardLevel >= activeAntibiohazardLevel && medAntibiohazardTimeSec > 0)
				{
					int medAntibiohazardMaxTimeSec = GetGame().ConfigGetInt( classname + " medAntibiohazardMaxTimeSec" );
					if (medAntibiohazardMaxTimeSec <= 0)
					{
						medAntibiohazardMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetAntibiohazard(medAntibiohazardLevel, Math.Min(medAntibiohazardMaxTimeSec, activeAntibiohazardTime + (medAntibiohazardTimeSec * amount * timeModifier)));
				}
			}
			
			int medAntibioticLevel = GetGame().ConfigGetInt( classname + " medAntibioticLevel" );
			if (medAntibioticLevel > 0)
			{
				if (medAntibioticLevel < 3 && player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkLevel("med", "expantib") > 0)
				{
					medAntibioticLevel = medAntibioticLevel + 1;
				}
				
				int activeAntibioticLevel = 0;
				float activeAntibioticTime = 0;
				player.GetTerjeStats().GetAntibiotic(activeAntibioticLevel, activeAntibioticTime);
							
				float medAntibioticsTimeSec = GetGame().ConfigGetFloat( classname + " medAntibioticsTimeSec" );
				if (medAntibioticLevel >= activeAntibioticLevel && medAntibioticsTimeSec > 0)
				{
					int medAntibioticsMaxTimeSec = GetGame().ConfigGetInt( classname + " medAntibioticsMaxTimeSec" );
					if (medAntibioticsMaxTimeSec <= 0)
					{
						medAntibioticsMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetAntibiotic(medAntibioticLevel, Math.Min(medAntibioticsMaxTimeSec, activeAntibioticTime + (medAntibioticsTimeSec * amount * timeModifier)));
				}			
			}
			
			int medRabiesAntibioticLevel = GetGame().ConfigGetInt( classname + " medRabiesAntibioticLevel" );
			if (medRabiesAntibioticLevel > 0)
			{
				if (medRabiesAntibioticLevel < 3 && player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkLevel("med", "expantib") > 0)
				{
					medRabiesAntibioticLevel = medRabiesAntibioticLevel + 1;
				}
				
				int activeRabiesAntibioticLevel = 0;
				float activeRabiesAntibioticTime = 0;
				player.GetTerjeStats().GetRabiesCure(activeRabiesAntibioticLevel, activeRabiesAntibioticTime);
							
				float medRabiesAntibioticsTimeSec = GetGame().ConfigGetFloat( classname + " medRabiesAntibioticTimeSec" );
				if (medRabiesAntibioticLevel >= activeRabiesAntibioticLevel && medRabiesAntibioticsTimeSec > 0)
				{
					int medRabiesAntibioticsMaxTimeSec = GetGame().ConfigGetInt( classname + " medRabiesAntibioticMaxTimeSec" );
					if (medRabiesAntibioticsMaxTimeSec <= 0)
					{
						medRabiesAntibioticsMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetRabiesCure(medRabiesAntibioticLevel, Math.Min(medRabiesAntibioticsMaxTimeSec, activeRabiesAntibioticTime + (medRabiesAntibioticsTimeSec * amount * timeModifier)));
				}			
			}
			
			float medZAntidotTimeSec = GetGame().ConfigGetFloat( classname + " medZAntidotTimeSec" );
			if (medZAntidotTimeSec > 0)
			{
				int medZAntidotMaxTimeSec = GetGame().ConfigGetInt( classname + " medZAntidotMaxTimeSec" );
				if (medZAntidotMaxTimeSec <= 0)
				{
					medZAntidotMaxTimeSec = 1800;
				}
				
				player.GetTerjeStats().SetZAntidotValue(Math.Min(medZAntidotMaxTimeSec, player.GetTerjeStats().GetZAntidotValue() + (medZAntidotTimeSec * amount * timeModifier)));
			}
			
			float medAntisepsis = GetGame().ConfigGetFloat( classname + " medAntisepsisTimeSec" );
			if (medAntisepsis > 0)
			{
				int medAntisepsisMaxTimeSec = GetGame().ConfigGetInt( classname + " medAntisepsisMaxTimeSec" );
				if (medAntisepsisMaxTimeSec <= 0)
				{
					medAntisepsisMaxTimeSec = 1800;
				}
				
				player.GetTerjeStats().SetAntisepsisValue(Math.Min(medAntisepsisMaxTimeSec, player.GetTerjeStats().GetAntisepsisValue() + (medAntisepsis * amount * timeModifier)));
			}
			
			float medConcussionHealTime = GetGame().ConfigGetFloat( classname + " medConcussionHealTimeSec" );
			if (medConcussionHealTime > 0)
			{
				int medConcussionHealMaxTimeSec = GetGame().ConfigGetInt( classname + " medConcussionHealMaxTimeSec" );
				if (medConcussionHealMaxTimeSec <= 0)
				{
					medConcussionHealMaxTimeSec = 1800;
				}
				
				player.GetTerjeStats().SetContusionHealValue(Math.Min(medConcussionHealMaxTimeSec, player.GetTerjeStats().GetContusionHealValue() + (medConcussionHealTime * amount * timeModifier)));
			}
			
			float medBloodHemostaticValue = GetGame().ConfigGetInt( classname + " medBloodHemostaticValue" );
			if (medBloodHemostaticValue > 0)
			{
				int activeHemostaticValue = 0;
				float activeHemostaticTime = 0;
				player.GetTerjeStats().GetHemostatic(activeHemostaticValue, activeHemostaticTime);
							
				float medHemostaticTimeSec = GetGame().ConfigGetFloat( classname + " medBloodHemostaticTimeSec" );
				if (medBloodHemostaticValue >= activeHemostaticValue && medHemostaticTimeSec > 0)
				{
					int medHemostaticMaxTimeSec = GetGame().ConfigGetInt( classname + " medBloodHemostaticMaxTimeSec" );
					if (medHemostaticMaxTimeSec <= 0)
					{
						medHemostaticMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetHemostatic(medBloodHemostaticValue, Math.Min(medHemostaticMaxTimeSec, activeHemostaticTime + (medHemostaticTimeSec * amount * timeModifier)));
				}	
			}
			
			float medBloodRegenValue = GetGame().ConfigGetInt( classname + " medBloodRegenValue" );
			if (medBloodRegenValue > 0)
			{
				int activeRegenValue = 0;
				float activeRegenTime = 0;
				player.GetTerjeStats().GetBloodRegen(activeRegenValue, activeRegenTime);
							
				float medRegenTimeSec = GetGame().ConfigGetFloat( classname + " medBloodRegenTimeSec" );
				if (medBloodRegenValue >= activeRegenValue && medRegenTimeSec > 0)
				{
					int medRegenMaxTimeSec = GetGame().ConfigGetInt( classname + " medBloodRegenMaxTimeSec" );
					if (medRegenMaxTimeSec <= 0)
					{
						medRegenMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetBloodRegen(medBloodRegenValue, Math.Min(medRegenMaxTimeSec, activeRegenTime + (medRegenTimeSec * amount * timeModifier)));
				}	
			}
			
			float medHematomaHealTimeSec = GetGame().ConfigGetInt( classname + " medHematomaHealTimeSec" );
			if (medHematomaHealTimeSec > 0)
			{
				int medHematomaHealMaxTimeSec = GetGame().ConfigGetInt( classname + " medHematomaHealMaxTimeSec" );
				if (medHematomaHealMaxTimeSec <= 0)
				{
					medHematomaHealMaxTimeSec = 1800;
				}
				
				player.GetTerjeStats().SetSalveValue(Math.Min(medHematomaHealMaxTimeSec, player.GetTerjeStats().GetSalveValue() + (medHematomaHealTimeSec * amount * timeModifier)));
			}
			
			float medAdrenalinTimeSec = GetGame().ConfigGetFloat( classname + " medAdrenalinTimeSec" );
			if (medAdrenalinTimeSec > 0)
			{
				int medAdrenalinMaxTimeSec = GetGame().ConfigGetInt( classname + " medAdrenalinMaxTimeSec" );
				if (medAdrenalinMaxTimeSec <= 0)
				{
					medAdrenalinMaxTimeSec = 1800;
				}
				
				player.GetTerjeStats().SetAdrenalinValue(Math.Min(medAdrenalinMaxTimeSec, player.GetTerjeStats().GetAdrenalinValue() + (medAdrenalinTimeSec * amount * timeModifier)));
				player.GetStaminaHandler().SetStamina( player.GetStaminaHandler().GetStaminaMax() );
			}
			
			int medAntidepLevel = GetGame().ConfigGetInt( classname + " medAntidepresantLevel" );
			if (medAntidepLevel > 0)
			{
				int activeAntidepValue = 0;
				float activeAntidepTime = 0;
				player.GetTerjeStats().GetAntidepresant(activeAntidepValue, activeAntidepTime);
				
				float medAntidepTimeSec = GetGame().ConfigGetFloat( classname + " medAntidepresantTimer" );
				if (medAntidepLevel >= activeAntidepValue && medAntidepTimeSec > 0)
				{
					int medAntidepMaxTimeSec = GetGame().ConfigGetInt( classname + " medAntidepresantMaxTimer" );
					if (medAntidepMaxTimeSec <= 0)
					{
						medAntidepMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetAntidepresant(medAntidepLevel, Math.Min(medAntidepMaxTimeSec, activeAntidepTime + (medAntidepTimeSec * amount * timeModifier)));
				}
			}
			
			float medMindDegradationForce = GetGame().ConfigGetFloat( classname + " medMindDegradationForce" );
			if (medMindDegradationForce > 0)
			{
				float medMindDegradationTime = GetGame().ConfigGetFloat( classname + " medMindDegradationTime" );
				if (medMindDegradationTime > 0)
				{
					player.GetTerjeStats().AddMindDegradation(medMindDegradationForce, medMindDegradationTime * amount);
				}
			}
			
			float medSleepingIncTime = GetGame().ConfigGetFloat( classname + " medSleepingIncrementTimeSec" );
			if (medSleepingIncTime > 0)
			{
				float medSleepingIncValue = GetGame().ConfigGetFloat( classname + " medSleepingIncrementValue" );
				if (medSleepingIncValue > 0)
				{
					player.GetTerjeStats().AddSleepingIncrement(medSleepingIncValue, medSleepingIncTime * amount);
				}
				else if (medSleepingIncValue < 0)
				{
					player.GetTerjeStats().AddSleepingDecrement(Math.AbsFloat(medSleepingIncValue), medSleepingIncTime * amount);
				}
			}
			
			float medInfluenzaVacineTime = GetGame().ConfigGetFloat( classname + " medInfluenzaVacineTime" );
			if (medInfluenzaVacineTime > 0)
			{
				player.GetTerjeStats().SetInfluenzaVacineValue(medInfluenzaVacineTime * amount * timeModifier);
			}
			
			float medZVirusVacineTime = GetGame().ConfigGetFloat( classname + " medZVirusVacineTime" );
			if (medZVirusVacineTime > 0)
			{
				player.GetTerjeStats().SetZVirusVacineValue(medZVirusVacineTime * amount * timeModifier);
			}
			
			float medRabiesVacineTime = GetGame().ConfigGetFloat( classname + " medRabiesVacineTime" );
			if (medRabiesVacineTime > 0)
			{
				player.GetTerjeStats().SetRabiesVacineValue(medRabiesVacineTime * amount * timeModifier);
			}
		}
	}
	
	override string Describe(EntityAI entity, string classname)
	{
		string result = super.Describe(entity, classname);
		float overdosedIncrement = GetGame().ConfigGetFloat( classname + " overdosedIncrement" );
		if (overdosedIncrement > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_OVERDOSE <color rgba='198,59,64,255'>+" + (int)(overdosedIncrement * 100) + "%</color><br/>";
		}
		
		float biohazardIncrement = GetGame().ConfigGetFloat( classname + " biohazardIncrement" );
		if (biohazardIncrement > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_BIOHAZARD <color rgba='198,59,64,255'>+" + (int)(biohazardIncrement * 100) + "%</color><br/>";
		}
		
		int medPainkillerLevel = GetGame().ConfigGetInt( classname + " medPainkillerLevel" );
		float medPainkillerTimeSec = GetGame().ConfigGetFloat( classname + " medPainkillerTimeSec" );
		if (medPainkillerLevel > 0 && medPainkillerTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_PAINKILLER <color rgba='97,215,124,255'>" + medPainkillerLevel + "</color> (" + (int)(medPainkillerTimeSec) + "sec)<br/>";
		}
		
		int medAntipoisonLevel = GetGame().ConfigGetInt( classname + " medAntipoisonLevel" );
		float medAntipoisonTimeSec = GetGame().ConfigGetFloat( classname + " medAntipoisonTimeSec" );
		if (medAntipoisonLevel > 0 && medAntipoisonTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_ANTIPOISON <color rgba='97,215,124,255'>" + medAntipoisonLevel + "</color> (" + (int)(medAntipoisonTimeSec) + "sec)<br/>";
		}
		
		int medAntibiohazardLevel = GetGame().ConfigGetInt( classname + " medAntibiohazardLevel" );
		float medAntibiohazardTimeSec = GetGame().ConfigGetFloat( classname + " medAntibiohazardTimeSec" );
		if (medAntibiohazardLevel > 0 && medAntibiohazardTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_ANTIBIOHAZARD <color rgba='97,215,124,255'>" + medAntibiohazardLevel + "</color> (" + (int)(medAntibiohazardTimeSec) + "sec)<br/>";
		}
		
		int medAntibioticLevel = GetGame().ConfigGetInt( classname + " medAntibioticLevel" );
		float medAntibioticsTimeSec = GetGame().ConfigGetFloat( classname + " medAntibioticsTimeSec" );
		if (medAntibioticLevel > 0 && medAntibioticsTimeSec > 0)
		{			
			result = result + "#STR_TERJEMED_EFFECT_ANTIBIOTIC <color rgba='97,215,124,255'>" + medAntibioticLevel + "</color> (" + (int)(medAntibioticsTimeSec) + "sec)<br/>";			
		}
		
		int medRabiesAntibioticLevel = GetGame().ConfigGetInt( classname + " medRabiesAntibioticLevel" );
		float medRabiesAntibioticsTimeSec = GetGame().ConfigGetFloat( classname + " medRabiesAntibioticTimeSec" );
		if (medRabiesAntibioticLevel > 0 && medRabiesAntibioticsTimeSec > 0)
		{			
			result = result + "#STR_TERJEMED_EFFECT_RABIESCURE <color rgba='97,215,124,255'>" + medRabiesAntibioticLevel + "</color> (" + (int)(medRabiesAntibioticsTimeSec) + "sec)<br/>";			
		}
		
		float medZAntidotTimeSec = GetGame().ConfigGetFloat( classname + " medZAntidotTimeSec" );
		if (medZAntidotTimeSec > 0)
		{
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_ZANTIDOT</color> (" + (int)(medZAntidotTimeSec) + "sec)<br/>";
		}
		
		float medAntisepsis = GetGame().ConfigGetFloat( classname + " medAntisepsisTimeSec" );
		if (medAntisepsis > 0)
		{			
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_ANTISEPSIS</color> (" + (int)(medAntisepsis) + "sec)<br/>";
		}
		
		float medConcussionHealTime = GetGame().ConfigGetFloat( classname + " medConcussionHealTimeSec" );
		if (medConcussionHealTime > 0)
		{
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_CONTUSIONCURE</color> (" + (int)(medConcussionHealTime) + "sec)<br/>";
		}
		
		float medBloodHemostaticValue = GetGame().ConfigGetInt( classname + " medBloodHemostaticValue" );
		float medHemostaticTimeSec = GetGame().ConfigGetFloat( classname + " medBloodHemostaticTimeSec" );
		if (medBloodHemostaticValue > 0 && medHemostaticTimeSec > 0)
		{
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_HEMOSTATIC</color> (" + (int)(medHemostaticTimeSec) + "sec)<br/>";
		}
		
		float medBloodRegenValue = GetGame().ConfigGetInt( classname + " medBloodRegenValue" );
		float medRegenTimeSec = GetGame().ConfigGetFloat( classname + " medBloodRegenTimeSec" );
		if (medBloodRegenValue > 0 && medRegenTimeSec > 0)
		{
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_BLOODREGEN</color> (" + (int)(medRegenTimeSec) + "sec)<br/>";
		}
		
		float medHematomaHealTimeSec = GetGame().ConfigGetInt( classname + " medHematomaHealTimeSec" );
		if (medHematomaHealTimeSec > 0)
		{
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_HEMATOMA</color> (+" + (int)(medHematomaHealTimeSec) + "sec)<br/>";
		}
		
		float medAdrenalinTimeSec = GetGame().ConfigGetFloat( classname + " medAdrenalinTimeSec" );
		if (medAdrenalinTimeSec > 0)
		{
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_ADRENALIN</color> (" + (int)(medAdrenalinTimeSec) + "sec)<br/>";
		}
		
		int medAntidepLevel = GetGame().ConfigGetInt( classname + " medAntidepresantLevel" );
		float medAntidepTimeSec = GetGame().ConfigGetFloat( classname + " medAntidepresantTimer" );
		if (medAntidepLevel > 0 && medAntidepTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_ANTIDEPRESANT <color rgba='97,215,124,255'>" + medAntidepLevel + "</color> (" + (int)(medAntidepTimeSec) + "sec)<br/>";			
		}
		
		float medInfluenzaVacineTime = GetGame().ConfigGetFloat( classname + " medInfluenzaVacineTime" );
		if (medInfluenzaVacineTime > 0)
		{
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_INFVACINE</color> (" + (int)(medInfluenzaVacineTime) + "sec)<br/>";
		}
		
		float medZVirusVacineTime = GetGame().ConfigGetFloat( classname + " medZVirusVacineTime" );
		if (medZVirusVacineTime > 0)
		{
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_ZEDVACINE</color> (" + (int)(medZVirusVacineTime) + "sec)<br/>";
		}
		
		float rabiesVacineTime = GetGame().ConfigGetFloat( classname + " medRabiesVacineTime" );
		if (rabiesVacineTime > 0)
		{
			result = result + "<color rgba='255,215,0,255'>#STR_TERJEMED_EFFECT_RABIESVACCINE</color> (" + (int)(rabiesVacineTime) + "sec)<br/>";
		}
		
		return result;
	}
}