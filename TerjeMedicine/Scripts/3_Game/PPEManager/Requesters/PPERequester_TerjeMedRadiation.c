// <copyright file="PPERequester_TerjeMedRadiation.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PPERequester_TerjeMedRadiation : PPERequester_GameplayBase
{
	private float m_RadiationEffect = 0;
	private float m_RadiationValue = 0;
	private ref array<float> m_RadEffectColors = new array<float>();
	
	void SetRadiationEffect(float value)
	{
		m_RadiationEffect = value;
	}
	
	override protected void OnStart(Param par = null)
	{
		super.OnStart(par);
		m_RadEffectColors.Insert(0.0);
		m_RadEffectColors.Insert(0.0);
		m_RadEffectColors.Insert(0.0);
		m_RadEffectColors.Insert(0.0);
	}
	
	override protected void OnStop(Param par = null)
	{
		super.OnStop();
		m_RadiationEffect = 0;
		m_RadiationValue = 0;
		m_RadEffectColors[0] = 0.0;
		m_RadEffectColors[1] = 0.0;
		m_RadEffectColors[2] = 0.0;
		m_RadEffectColors[3] = 0.0;
		
		SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_RadEffectColors,PPEGlow.L_RADIATION,PPOperators.SUBSTRACT);
	}
	
	override void OnUpdate(float delta)
	{
		super.OnUpdate(delta);
		
		float newRadValue = m_RadiationValue;
		if (m_RadiationEffect > 0)
		{
			newRadValue = Math.Clamp(m_RadiationValue + (delta * 0.1), 0, m_RadiationEffect);
		}
		else
		{
			newRadValue = Math.Max(m_RadiationValue - (delta * 0.1), 0);
		}
		
		if (newRadValue != m_RadiationValue)
		{
			m_RadiationValue = newRadValue;
			float radColorValue = Math.Clamp(m_RadiationValue, 0, 1);
			m_RadEffectColors[0] = radColorValue * 0.1;
			m_RadEffectColors[1] = radColorValue * 0.1;
			m_RadEffectColors[2] = radColorValue * 0.25;
			m_RadEffectColors[3] = 0.0;
		}
		
		float grainMod = Math.Clamp(m_RadiationValue, 0, 1);
		SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_RadEffectColors,PPEGlow.L_RADIATION,PPOperators.SUBSTRACT);
		
		// TODO: ADD FILMFRAIN EFFECT
		//SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,10.0,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.HIGHEST);
		//SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,1.0,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.LOWEST);
	}
};