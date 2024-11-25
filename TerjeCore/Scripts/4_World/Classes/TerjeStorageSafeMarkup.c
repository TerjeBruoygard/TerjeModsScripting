// <copyright file="TerjeStorageSafeMarkup.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

// This is a helper class for more safe handling of storage in DayZ to prevent crashes when storage is corrupted.
class TerjeStorageSafeMarkup
{
	static void WriteMarker(ParamsWriteContext ctx, int marker)
	{
		ctx.Write(marker);
	}
	
	static bool VerifyMarker(ParamsReadContext ctx, int marker)
	{
		int storedValue;
		if (ctx.Read(storedValue) && storedValue == marker)
		{
			return true;
		}
		
		return false;
	}
}