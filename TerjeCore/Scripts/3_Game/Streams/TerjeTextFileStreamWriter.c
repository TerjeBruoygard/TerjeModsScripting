// <copyright file="TerjeTextFileStreamWriter.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeTextFileStreamWriter : TerjeTextStreamWriter
{
	FileHandle m_Handle;
	
	void TerjeTextFileStreamWriter(string path)
	{
		m_Handle = OpenFile(path, FileMode.WRITE);
	}
	
	override void Write(string data)
	{
		FPrint(m_Handle, data);
	}
	
	override void WriteLine(string data)
	{
		FPrintln(m_Handle, data);
	}
	
	override bool IsOpen()
	{
		return m_Handle != 0;
	}
	
	override void Close()
	{
		if (IsOpen())
		{
			CloseFile(m_Handle);
		}
	}
}