// <copyright file="PPERequesterBank.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PPERequesterBank
{
	static const int REQ_TERJEMED_CONCUSSION = RegisterRequester(PPERequester_TerjeMedConcussion);
	static const int REQ_TERJEMED_OVERDOSE = RegisterRequester(PPERequester_TerjeMedOverdose);
	static const int REQ_TERJEMED_PAIN = RegisterRequester(PPERequester_TerjeMedPain);
	static const int REQ_TERJEMED_SLEEPING = RegisterRequester(PPERequester_TerjeMedSleeping);
	static const int REQ_TERJEMED_PSYONIC = RegisterRequester(PPERequester_TerjeMedPsyonic);
}