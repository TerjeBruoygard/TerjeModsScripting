// <copyright file="TerjeTextFileStreamReader.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeTextFileStreamReader : TerjeTextStreamReader
{
	private FileHandle m_Handle;
	private string m_LineData;
	private int m_LineNumber;
	
	void TerjeTextFileStreamReader(string path)
	{
		m_Handle = OpenFile(path, FileMode.READ);
		m_LineData = string.Empty;
		m_LineNumber = 0;
	}
	
	override bool ReadToken(out string token, out int type)
	{
		if (m_LineData.Length() == 0)
		{
			if (!ReadLine(m_LineData))
			{
				return false;
			}
			
			if (m_LineNumber > 1)
			{
				type = 5;
				token = "\n";
				return true;
			}
		}
		
		type = m_LineData.ParseStringEx(token);
		if (type == 0)
		{
			if ((m_LineData.Length() > 0) && (m_LineData.Get(0) == "?"))
			{
				// Fix parser error
				m_LineData = m_LineData.Substring(1, m_LineData.Length() - 1);
				type = 1;
				token = "?";
			}
			else
			{
				m_LineData = string.Empty;
				return ReadToken(token, type);
			}
		}
		
		return true;
	}
	
	override bool ReadLine(out string line)
	{
		if (FGets(m_Handle, line) != -1)
		{
			m_LineNumber = m_LineNumber + 1;
			return true;
		}
		
		return false;
	}
	
	override bool ReadTo(string separator, out string data)
	{
		string nextLine;
		int index = m_LineData.IndexOf(separator);
		while (index == -1)
		{
			if (!ReadLine(nextLine))
			{
				return false;
			}
			
			m_LineData = m_LineData + "\n" + nextLine;
			index = m_LineData.IndexOf(separator);
		}
		
		data = m_LineData.Substring(0, index);
		m_LineData = m_LineData.Substring(index, m_LineData.Length() - index);
		return true;
	}
	
	override int GetLineNumber()
	{
		return m_LineNumber;
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