// <copyright file="TerjeRadTentStatic.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeRadTentStatic extends House
{
	protected const int TERJE_SHOWERS_COUNT = 5;
	protected const int TERJE_SHOWERS_AUTOSTOP = 60;
	protected const float TERJE_CLEAN_RADIUS = 1.8;
	protected bool m_terjeRadTentActual = false;
	protected bool m_terjeRadTentLast = false;
	protected float m_terjeRadTentTimeout = 0;
	protected ref array<EffectSound> m_ShowerSoundEffects = null;
	protected ref array<Particle> m_ShowerParticleEffects = null;
	
	void TerjeRadTentStatic()
	{
		RegisterNetSyncVariableBool("m_terjeRadTentActual");
	}
	
	bool IsTerjeRadTentWorking()
	{
		return m_terjeRadTentActual;
	}
	
	void SetTerjeRadTentWorking(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			m_terjeRadTentActual = state;
			SetSynchDirty();
			
			if (m_terjeRadTentLast != m_terjeRadTentActual)
			{
				m_terjeRadTentLast = m_terjeRadTentActual;
				if (m_terjeRadTentActual)
				{
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.OnWorkTerjeServerLogic, 1000, true);
				}
				else
				{
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.OnWorkTerjeServerLogic);
				}
			}
		}
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if (GetGame() && GetGame().IsClient())
		{
			if (m_terjeRadTentLast != m_terjeRadTentActual)
			{
				m_terjeRadTentLast = m_terjeRadTentActual;
				if (m_terjeRadTentActual)
				{
					if (m_ShowerSoundEffects == null)
					{
						m_ShowerSoundEffects = new array<EffectSound>;
						for (int soundIndex = 1; soundIndex <= TERJE_SHOWERS_COUNT; soundIndex++)
						{
							EffectSound effectSound;
							PlaySoundSetAtMemoryPointLoopedSafe(effectSound, "TerjeRadTentShower_SoundSet", "particle_shower_" + soundIndex, 1, 1);
							m_ShowerSoundEffects.Insert(effectSound);
						}
					}
					
					if (m_ShowerParticleEffects == null)
					{
						m_ShowerParticleEffects = new array<Particle>;
						for (int particleIndex = 1; particleIndex <= TERJE_SHOWERS_COUNT; particleIndex++)
						{
							m_ShowerParticleEffects.Insert(ParticleManager.GetInstance().PlayOnObject(ParticleList.TERJE_RADIATION_SHOWER_EFFECT, this, GetMemoryPointPos("particle_shower_" + particleIndex)));
						}
					}
				}
				else
				{
					if (m_ShowerSoundEffects != null)
					{
						foreach (EffectSound soundEffect : m_ShowerSoundEffects)
						{
							if (soundEffect)
							{
								SEffectManager.DestroyEffect(soundEffect);
							}
						}
						
						m_ShowerSoundEffects = null;
					}
					
					if (m_ShowerParticleEffects != null)
					{
						foreach (Particle particleEffect : m_ShowerParticleEffects)
						{
							if (particleEffect)
							{
								particleEffect.Stop();
							}
						}
						
						m_ShowerParticleEffects = null;
					}
				}
			}
		}
	}
	
	protected void OnWorkTerjeServerLogic()
	{
		float cleanupForce = GetTerjeGameConfig().ConfigGetFloat("CfgTerjeCustomLiquids RadDesactivator terjeRadiationCleanupForce");
		float cleanupModifier = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_RADTENT_EFFICIENCY_MOD);
		float cleanupTotal = cleanupForce * cleanupModifier;
		if (cleanupTotal > 0)
		{
			PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
			if (plugin)
			{
				plugin.TerjeDecontaminateRadioactiveEntitiesInside(this, TERJE_CLEAN_RADIUS, TERJE_SHOWERS_COUNT, cleanupTotal);
			}
		}
		
		m_terjeRadTentTimeout = m_terjeRadTentTimeout + 1;
		if (m_terjeRadTentTimeout > TERJE_SHOWERS_AUTOSTOP)
		{
			m_terjeRadTentTimeout = 0;
			SetTerjeRadTentWorking(false);
		}
	}
}