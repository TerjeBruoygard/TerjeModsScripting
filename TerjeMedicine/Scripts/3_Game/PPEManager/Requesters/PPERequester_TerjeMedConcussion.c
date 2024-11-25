// <copyright file="PPERequester_TerjeMedConcussion.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PPERequester_TerjeMedConcussion : PPERequester_GameplayBase
{
	private float m_ConcussionValue = 0;
	private float m_ConcussionOffset = 0;
	
	void SetConcussionEffect(float value)
	{
		m_ConcussionValue = value;
	}
	
	override protected void OnStop(Param par = null)
	{
		super.OnStop();
		m_ConcussionValue = 0;
		m_ConcussionOffset = 0;
		SetTargetValueFloat(PostProcessEffectType.GaussFilter,PPEGaussFilter.PARAM_INTENSITY,false,0,PPEGaussFilter.L_CONCUSSION,PPOperators.HIGHEST);
	}
	
	override void OnUpdate(float delta)
	{
		super.OnUpdate(delta);
		
		float blurEffect = 0;
		if (m_ConcussionValue > 0)
		{
			m_ConcussionOffset = m_ConcussionOffset + (delta * 0.1);
			if (m_ConcussionOffset >= Math.PI2) m_ConcussionOffset = 0;
			float sinusVal = Math.Clamp( Math.Sin(m_ConcussionOffset) * 0.05, 0, 0.05) ;
			blurEffect = blurEffect + (m_ConcussionValue + sinusVal);
		}
		
		blurEffect = Math.Clamp(blurEffect, 0, 1);
		SetTargetValueFloat(PostProcessEffectType.GaussFilter,PPEGaussFilter.PARAM_INTENSITY,false,blurEffect,PPEGaussFilter.L_CONCUSSION,PPOperators.HIGHEST);
	}
}