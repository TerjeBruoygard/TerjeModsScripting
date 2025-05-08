// <copyright file="TerjeHeadgearPsiHelm.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeHeadgearPsiHelm : Clothing
{
	override float GetTerjeProtectionLevel(string protectionType)
	{
		if (GetCompEM().IsWorking())
		{
			return super.GetTerjeProtectionLevel(protectionType);
		}
		
		return 0;
	}
	
	override float GetTerjeProtectionAdvanced(string protectionType, float power)
	{
		if (GetCompEM().IsWorking())
		{
			return super.GetTerjeProtectionAdvanced(protectionType, power);
		}
		
		return 0;
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
	}
}