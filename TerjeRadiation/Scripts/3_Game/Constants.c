// <copyright file="Constants.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeRadiationConstants
{
	const float RADIATION_MAX_VALUE = 5;

	const int RADIATION_PLAYER_ACCUMULATOR_SERVER_MAX = 5000;
	const int RADIATION_PLAYER_ACCUMULATOR_SYNCH_MAX = 50;
	const float RADIATION_PLAYER_ACCUMULATOR_SYNCH_DIVIDER = 100;
	
	const int RADIATION_ITEMS_ACCUMULATOR_SERVER_MAX = 500;
	const int RADIATION_ITEMS_ACCUMULATOR_SYNCH_MAX = 50;
	const float RADIATION_ITEMS_ACCUMULATOR_SYNCH_DIVIDER = 10;
	
	const int RADIATION_ANIMALS_ACCUMULATOR_SERVER_MAX = 5000;
	const int RADIATION_ANIMALS_ACCUMULATOR_SYNCH_MAX = 50;
	const float RADIATION_ANIMALS_ACCUMULATOR_SYNCH_DIVIDER = 100;
	const float RADIATION_ANIMALS_DAMAGE_THRESHOLD = 1000;
	const float RADIATION_ANIMALS_DAMAGE_PER_SEC = 1;
	
	const int RADIATION_ZOMBIE_ACCUMULATOR_SERVER_MAX = 5000;
	const int RADIATION_ZOMBIE_ACCUMULATOR_SYNCH_MAX = 50;
	const float RADIATION_ZOMBIE_ACCUMULATOR_SYNCH_DIVIDER = 100;
	const float RADIATION_ZOMBIE_DAMAGE_THRESHOLD = 1000;
	const float RADIATION_ZOMBIE_DAMAGE_PER_SEC = 1;
	
	const int RADIATION_VEHICLE_ACCUMULATOR_SERVER_MAX = 500;
	const int RADIATION_VEHICLE_ACCUMULATOR_SYNCH_MAX = 50;
	const float RADIATION_VEHICLE_ACCUMULATOR_SYNCH_DIVIDER = 10;
}