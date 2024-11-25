// <copyright file="BitmaskHelper.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class BitmaskHelper
{
	static int SetBit(int bitmask, int index, bool bit)
	{
		if (index < 0 || index >= 32)
		{
			return bitmask; // ERROR
		}
		else if (bit == true)
		{
			bitmask |= 1 << index;
		}
		else
		{
			bitmask &= ~(1 << index);
		}
		
		return bitmask;
	}
	
	static bool GetBit(int bitmask, int index)
	{
		if (index < 0 || index >= 32)
		{
			return false; // ERROR
		}
		
		return (bitmask & (1 << index)) != 0;
	}
}