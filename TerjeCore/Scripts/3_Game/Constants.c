// <copyright file="Constants.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

const int LIQUID_TERJE_CUSTOM = LIQUID_SOLUTION;

enum TerjeERPC {
	TerjeRPC_FIRST = -281200,
	TerjeRPC_SYNCH_PLAYER_STATS,
	TerjeRPC_CUSTOM_CALL
};

int ClampInt(int value, int min, int max)
{
	if (value < min)
	{
		value = min;
	}
	if (value > max)
	{
		value = max;
	}
	return value;
};