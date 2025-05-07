// <copyright file="TerjeArtifactFireBall.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeArtifactAntirad extends TerjeArtifactBase
{
	override void StartEffects()
	{
		super.StartEffects();

		if (GetGame() && GetGame().IsClient())
		{
			StopEffects();
			
			m_terjeArtIdleLight = TerjeArtifactAntiradLight.Cast(ScriptedLightBase.CreateLight(TerjeArtifactAntiradLight, GetPosition()));
			m_terjeArtIdleLight.AttachOnObject(this, Vector(0.0, 0.05, 0.0));
			m_terjeArtEffectIdle = Particle.PlayOnObject(ParticleList.TERJE_RADIATION_ARTFIREBALL_EFFECT, this, Vector(0.0, 0.05, 0.0));
		}
	}
}

class TerjeArtifactAntiradLight extends PointLightBase
{
	void TerjeArtifactAntiradLight()
	{
		SetVisibleDuringDaylight(true);
		SetRadiusTo( 0.6 );
		SetBrightnessTo( 1.6 );
		SetCastShadow(false);
		SetFadeOutTime(0.0);
		SetDiffuseColor(1.0, 0.4, 0.0);
		SetAmbientColor(1.0, 0.4, 0.0);
		SetFlareVisible(true);
		SetFlickerAmplitude(0.7);
		SetFlickerSpeed(1.8);
		SetDancingShadowsMovementSpeed(0.0);
		SetDancingShadowsAmplitude(0.0);
	}
}