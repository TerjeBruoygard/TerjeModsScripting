// <copyright file="TerjeTextStreamReader.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeTextStreamReader
{
	bool ReadToken(out string token, out int type)
	{
		return -1;
	}
	
	bool ReadLine(out string line)
	{
		return -1;
	}
	
	bool ReadTo(string separator, out string data)
	{
		return -1;
	}
	
	int GetLineNumber()
	{
		return 0;
	}
	
	bool IsOpen()
	{
		return false;
	}
	
	void Close()
	{
	
	}
}