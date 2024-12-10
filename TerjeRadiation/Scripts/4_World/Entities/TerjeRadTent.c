// <copyright file="TerjeRadTent.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeRadTent extends TentBase
{
	void TerjeRadTent()
	{
		m_ShowAnimationsWhenPitched.Insert( "Body" );
		m_ShowAnimationsWhenPitched.Insert( "Pack" );
		m_ShowAnimationsWhenPacked.Insert( "Inventory" );
		
		m_HalfExtents = Vector(1.8, 0.33, 3.4);
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
		return "placeCarTent_SoundSet";
	}
	
	override string GetLoopDeploySoundset()
	{
		return "cartent_deploy_SoundSet";
	}
}