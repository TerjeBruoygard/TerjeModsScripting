// <copyright file="TerjeSurgicalTool_ColorBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSurgicalTool_ColorBase extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionSewTarget);
		AddAction(ActionSewSelf);
	}
	
	override bool CanBeDisinfected()
	{
		return true;
	}
	
	override float GetInfectionChance(int system = 0, Param param = null)
	{
		if(m_Cleanness == 1)
		{
			return 0;
		}
		else
		{
			return 0.8;
		}
	}
};