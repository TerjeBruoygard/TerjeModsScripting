// <copyright file="TerjeSleepingBag.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSleepingBag extends TentBase
{
	const float PARAM_FULL_HEAT_RADIUS 				= 0.5;		//! radius in which objects are fully heated by fire
	const float PARAM_HEAT_RADIUS 					= 1.0;		//! radius in which objects are heated by fire
	const float PARAM_MAX_TRANSFERED_TEMPERATURE	= 5;		//! maximum value for temperature that will be transfered to player (environment)
	
	protected ref UniversalTemperatureSource m_UTSource;
	protected ref UniversalTemperatureSourceSettings m_UTSSettings;
	protected ref UniversalTemperatureSourceLambdaConstant m_UTSLConstant;
	
	void TerjeSleepingBag()
	{
		m_ShowAnimationsWhenPitched.Insert( "Body" );
		m_ShowAnimationsWhenPacked.Insert( "Bags" );
		m_HalfExtents = Vector(0.25, 0.1, 0.75);
	}

	override bool HasClutterCutter()
	{
		return false;
	}

	override bool IsDeployable()
	{
		return true;
	}
	
	override string GetDeploySoundset()
	{
		return "TerjeSleepingDeploy_SoundSet";
	}
	
	override string GetLoopDeploySoundset()
	{
		return "mediumtent_deploy_SoundSet";
	}
	
	override bool CanBePacked()
	{		
		return GetState() == PITCHED;
	}
	
	override void HideAllAnimationsAndProxyPhysics(bool hide_animations = true, bool hide_physics = true)
	{
		super.HideAllAnimationsAndProxyPhysics(hide_animations, false);
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		RemoveAction(ActionToggleTentOpen);
		RemoveAction(ActionPackTent);
		
		AddAction(ActionPackTerjeSleepingBag);
	}
	
	override void Pack(bool update_navmesh, bool init = false)
	{
		super.Pack(update_navmesh, init);
		
		if (GetGame().IsDedicatedServer())
		{
			if (m_UTSource)
			{
				m_UTSource.SetActive(false);
			}
		}
	}

	override void Pitch(bool update_navmesh, bool init = false)
	{
		super.Pitch(update_navmesh, init);
		
		if (GetGame().IsDedicatedServer())
		{
			if (!m_UTSource)
			{
	 			m_UTSSettings 						= new UniversalTemperatureSourceSettings();
				m_UTSSettings.m_Updateable			= true;
				m_UTSSettings.m_UpdateInterval		= 2.5;
				m_UTSSettings.m_TemperatureItemCap 	= GameConstants.ITEM_TEMPERATURE_NEUTRAL_ZONE_MIDDLE;
				m_UTSSettings.m_TemperatureCap		= PARAM_MAX_TRANSFERED_TEMPERATURE;
				m_UTSSettings.m_RangeFull			= PARAM_FULL_HEAT_RADIUS;
				m_UTSSettings.m_RangeMax			= PARAM_HEAT_RADIUS;
				
				m_UTSLConstant						= new UniversalTemperatureSourceLambdaConstant();
				m_UTSource							= new UniversalTemperatureSource(this, m_UTSSettings, m_UTSLConstant);
			}
			
			if (m_UTSource)
			{
				m_UTSource.SetActive(true);
			}
		}
	}
}