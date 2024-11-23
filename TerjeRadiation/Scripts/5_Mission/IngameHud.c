// <copyright file="IngameHud.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class IngameHud
{
	int TERJE_BADGE_RADIATION = -1;
	int TERJE_BADGE_ANTIRAD = -1;

	override void InitBadgesAndNotifiers()
	{
		super.InitBadgesAndNotifiers();
		TERJE_BADGE_RADIATION = RegisterTerjeBadgetWidget("set:TerjeRadiation_icon image:tr_rad_sickness", "TerjeRadiation", TerjeBadgeType.LEVELED);
		TERJE_BADGE_ANTIRAD = RegisterTerjeBadgetWidget("set:TerjeRadiation_icon image:tr_antirad", "TerjeAntirad", TerjeBadgeType.LEVELED);
	}
	
	override bool GetTerjeBadgeColor( int key, int value, out int outputColor )
	{
		if (super.GetTerjeBadgeColor(key, value, outputColor))
		{
			return true;
		}
		else if (key == TERJE_BADGE_RADIATION)
		{
			if (value <= 2)
			{
				outputColor = GetTerjeBadgeColorWarning();
				return true;
			}
			else
			{
				outputColor = GetTerjeBadgeColorCritical();
				return true;
			}
		}
		
		outputColor = GetTerjeBadgeColorDefault();
		return false;
	}
};
