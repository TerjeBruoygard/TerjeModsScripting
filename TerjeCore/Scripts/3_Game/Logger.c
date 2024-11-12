// <copyright file="Logger.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

void TerjeLog_Info(string message)
{
	Print("[TERJE CORE](INFO): " + message);
}

void TerjeLog_Warning(string message)
{
	Print("[TERJE CORE](WARNING): " + message);
}

void TerjeLog_Error(string message)
{
	Print("[TERJE CORE](ERROR): " + message);
}