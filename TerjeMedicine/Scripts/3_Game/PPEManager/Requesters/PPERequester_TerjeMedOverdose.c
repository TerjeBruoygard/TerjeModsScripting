// <copyright file="PPERequester_TerjeMedOverdose.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PPERequester_TerjeMedOverdose : PPERequester_GameplayBase
{
	private EffectSound m_hearthbitSound;
	private float m_OverdosedOffset = 0;
	private float m_OverdosedValue = 0;
	
	void SetOverdosedEffect(float value)
	{
		m_OverdosedValue = value;
	}
	
	override protected void OnStop(Param par = null)
	{
		super.OnStop();
		m_OverdosedOffset = 0;
		m_OverdosedValue = 0;
		SetTargetValueFloat(PostProcessEffectType.GaussFilter,PPEGaussFilter.PARAM_INTENSITY,false,0,PPEGaussFilter.L_OVERDOSE,PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.ChromAber,PPEChromAber.PARAM_POWERX,false,0,PPEChromAber.L_OVERDOSE,PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.ChromAber,PPEChromAber.PARAM_POWERY,false,0,PPEChromAber.L_OVERDOSE,PPOperators.HIGHEST);
	}
	
	override void OnUpdate(float delta)
	{
		super.OnUpdate(delta);
		
		float matChromaOffset = 0;
		float blurEffect = 0;
		if (m_OverdosedValue > 0)
		{
			m_OverdosedOffset = m_OverdosedOffset + (delta * 6);
			if (m_OverdosedOffset >= 12)
			{
				m_OverdosedOffset = 0;
				GetGame().GetPlayer().PlaySoundSet(m_hearthbitSound, "hearthbit_SoundSet", 0, 0);
			}
			
			float sinusVal = Math.Clamp(m_OverdosedOffset, 0, 12);
			if (sinusVal >= 2) sinusVal = Math.Cos((sinusVal - 2) * Math.PI_HALF * 0.1);
			else sinusVal = Math.AbsFloat( Math.Sin( sinusVal * Math.PI * 0.75 ) );
			
			matChromaOffset = matChromaOffset + (sinusVal * m_OverdosedValue * 0.25);
			blurEffect = blurEffect + (m_OverdosedValue + (sinusVal * 0.1));
		}
		
		matChromaOffset = Math.Clamp(matChromaOffset, 0, 1);
		blurEffect = Math.Clamp(blurEffect, 0, 1);
		SetTargetValueFloat(PostProcessEffectType.GaussFilter,PPEGaussFilter.PARAM_INTENSITY,false,blurEffect,PPEGaussFilter.L_OVERDOSE,PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.ChromAber,PPEChromAber.PARAM_POWERX,false,matChromaOffset,PPEChromAber.L_OVERDOSE,PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.ChromAber,PPEChromAber.PARAM_POWERY,false,matChromaOffset,PPEChromAber.L_OVERDOSE,PPOperators.HIGHEST);
	}
};