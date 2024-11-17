// <copyright file="PPERequester_TerjeMedPsyonic.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PPERequester_TerjeMedPsyonic : PPERequester_GameplayBase
{
	private EffectSound m_psiEffectSound;
	private ref array<float> m_psiEffectColors = new array<float>();
	private float m_psiEffectValue = 0;
	
	void SetPsyonicEffect(float value)
	{
		m_psiEffectValue = Math.Clamp(value, 0, 1);
	}
	
	override protected void OnStart(Param par = null)
	{
		super.OnStart(par);
		m_psiEffectColors.Insert(0.0);
		m_psiEffectColors.Insert(0.0);
		m_psiEffectColors.Insert(0.0);
		m_psiEffectColors.Insert(0.0);
	}
	
	override protected void OnStop(Param par = null)
	{
		super.OnStop();
		m_psiEffectValue = 0;
		m_psiEffectColors[0] = 0.0;
		m_psiEffectColors[1] = 0.0;
		m_psiEffectColors[2] = 0.0;
		m_psiEffectColors[3] = 0.0;
		SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_psiEffectColors,PPEGlow.L_PSI,PPOperators.SUBSTRACT);
		
		if (m_psiEffectSound)
		{
			m_psiEffectSound.Stop();
			m_psiEffectSound = null;
		}
	}
	
	override void OnUpdate(float delta)
	{
		super.OnUpdate(delta);
				
		if (m_psiEffectValue > 0.33)
		{
			if (!m_psiEffectSound)
			{
				m_psiEffectSound = SEffectManager.CreateSound("psyonicWaveTerje_SoundSet", GetGame().GetPlayer().GetPosition(), 1, 1, true);
				m_psiEffectSound.SetParent(GetGame().GetPlayer());
				m_psiEffectSound.SetLocalPosition( vector.Zero );
				m_psiEffectSound.SetAutodestroy(false);
			}
			
			m_psiEffectSound.SetSoundVolume(m_psiEffectValue - 0.33);
			
			if (!m_psiEffectSound.IsPlaying())
			{
				m_psiEffectSound.Start();
			}
		}
		else if (m_psiEffectSound)
		{
			m_psiEffectSound.Stop();
			m_psiEffectSound = null;
		}
		
		m_psiEffectColors[0] = m_psiEffectValue * 0.8;
		m_psiEffectColors[1] = m_psiEffectValue * 0.8;
		m_psiEffectColors[2] = 0.0;
		m_psiEffectColors[3] = 0.0;
		SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_psiEffectColors,PPEGlow.L_PSI,PPOperators.SUBSTRACT);
	}
};