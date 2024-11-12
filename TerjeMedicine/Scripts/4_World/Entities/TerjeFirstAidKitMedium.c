// <copyright file="TerjeFirstAidKitMedium.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeFirstAidKitMedium : Container_Base
{
	override bool CanReceiveItemIntoCargo( EntityAI item )
	{
		if (!super.CanReceiveItemIntoCargo(item))
			return false;
		
		return item && item.ConfigGetBool("medicalItem");
	}
	
	override bool CanLoadItemIntoCargo( EntityAI item )
	{
		if (!super.CanLoadItemIntoCargo(item))
			return false;
		
		return item && item.ConfigGetBool("medicalItem");
	}
};