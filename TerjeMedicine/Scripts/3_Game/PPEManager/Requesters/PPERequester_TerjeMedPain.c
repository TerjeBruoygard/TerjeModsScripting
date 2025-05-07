// <copyright file="PPERequester_TerjeMedPain.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PPERequester_TerjeMedPain : PPERequester_GameplayBase
{
	private float m_PainValue = 0;
	private float m_PainOffset = 0;
	private float m_PainMod = 1;
	private float m_camShake = 0;
	
	void SetPainEffect(float value, float mod)
	{
		m_PainValue = value;
		m_PainMod = mod;
	}
	
	override protected void OnStop(Param par = null)
	{
		super.OnStop();
		m_PainValue = 0;
		m_PainOffset = 0;
		m_camShake = 0;
		SetTargetValueFloat(PostProcessEffectType.GaussFilter,PPEGaussFilter.PARAM_INTENSITY,false,0,PPEGaussFilter.L_SYBPAIN,PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.ChromAber,PPEChromAber.PARAM_POWERX,false,0,PPEChromAber.L_SYBPAIN,PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.ChromAber,PPEChromAber.PARAM_POWERY,false,0,PPEChromAber.L_SYBPAIN,PPOperators.HIGHEST);
	}
	
	override void OnUpdate(float delta)
	{
		super.OnUpdate(delta);

		float matChromaOffset = 0;
		float blurEffect = 0;
		if (m_PainValue > 0)
		{
			m_PainOffset = m_PainOffset + (delta * 0.5);
			if (m_PainOffset >= Math.PI2) m_PainOffset = 0;
			
			float sinusVal = Math.Clamp( Math.Sin(m_PainOffset), 0, 1);
			if (m_PainValue >= 0.2 && sinusVal >= 0.9 && m_camShake <= 0)
			{
				m_camShake = 1;
			}
			
			sinusVal = ((m_PainValue - 0.1) + (sinusVal * 0.05));
			sinusVal = Math.Clamp(sinusVal, 0, 1);
			
			matChromaOffset = matChromaOffset + sinusVal;
			
			if (m_PainValue >= 0.3)
			{
				blurEffect = blurEffect + sinusVal;
			}
		}
		
		matChromaOffset = Math.Clamp(matChromaOffset * m_PainMod, 0, 1);
		blurEffect = Math.Clamp(blurEffect * m_PainMod, 0, 1);
		SetTargetValueFloat(PostProcessEffectType.GaussFilter,PPEGaussFilter.PARAM_INTENSITY,false,blurEffect,PPEGaussFilter.L_SYBPAIN,PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.ChromAber,PPEChromAber.PARAM_POWERX,false,matChromaOffset,PPEChromAber.L_SYBPAIN,PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.ChromAber,PPEChromAber.PARAM_POWERY,false,matChromaOffset,PPEChromAber.L_SYBPAIN,PPOperators.HIGHEST);
		
		if (m_camShake == 1)
		{
			if (GetGame() && GetGame().GetPlayer())
			{
				GetGame().GetPlayer().GetCurrentCamera().SpawnCameraShake();
			}
		}
		if (m_camShake > 0)
		{
			m_camShake = m_camShake - delta;
		}
	}
}