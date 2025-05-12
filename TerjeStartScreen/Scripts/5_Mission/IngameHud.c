// <copyright file="IngameHud.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class IngameHud
{
	int TERJE_BADGE_SOULS = -1;

	override void InitBadgesAndNotifiers()
	{
		super.InitBadgesAndNotifiers();
		
		TERJE_BADGE_SOULS = RegisterTerjeBadgetWidget(TerjePlayerSoulsAccessor.SOULS_BADGE, "TerjeSouls", TerjeBadgeType.COUNTER);
	}
}
