// <copyright file="TerjeStorage.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

// This is a helper class for more safe handling of storage in DayZ to prevent crashes when storage is corrupted.
class TerjeStorageHelpers
{
	private static int m_TerjeStorageVersion = -1;
	
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
	
	static bool ReadMarker(ParamsReadContext ctx, out int marker)
	{
		return ctx.Read(marker);
	}
	
	static int GetServerInstanceId()
	{
		return GetGame().ServerConfigGetInt("instanceId");
	}
	
	static string GetServerStoragePath()
	{
		return "$mission:storage_" + GetServerInstanceId();
	}
	
	static int GetTerjeStorageVersion()
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	static void SetActualTerjeStorageVersion()
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
}

class TerjeStorageBaseContext
{
	
	protected ref map<string, bool> m_Booleans = null;
	protected ref map<string, float> m_Floats = null;
	protected ref map<string, int> m_Integers = null;
	protected ref map<string, string> m_Strings = null;
	protected ref map<string, ref TerjeStorageBaseContext> m_ChildCtxs = null;	
	
	void ~TerjeStorageBaseContext()
	{
		if (m_Booleans != null)
		{
			delete m_Booleans;
		}
		
		if (m_Floats != null)
		{
			delete m_Floats;
		}
		
		if (m_Integers != null)
		{
			delete m_Integers;
		}
		
		if (m_Strings != null)
		{
			delete m_Strings;
		}
		
		if (m_ChildCtxs != null)
		{
			delete m_ChildCtxs;
		}
	}
}

class TerjeStorageWritingContext : TerjeStorageBaseContext
{
	
	void OnStoreSave(ParamsWriteContext ctx)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void WriteBool(string id, bool value)
	{
		if (m_Booleans == null)
		{
			m_Booleans = new map<string, bool>;
		}
		
		m_Booleans.Set(id, value);
	}
	
	void WriteFloat(string id, float value)
	{
		if (m_Floats == null)
		{
			m_Floats = new map<string, float>;
		}
		
		m_Floats.Set(id, value);
	}
	
	void WriteInt(string id, int value)
	{
		if (m_Integers == null)
		{
			m_Integers = new map<string, int>;
		}
		
		m_Integers.Set(id, value);
	}
	
	void WriteString(string id, string value)
	{
		if (m_Strings == null)
		{
			m_Strings = new map<string, string>;
		}
		
		m_Strings.Set(id, value);
	}
	
	ref TerjeStorageWritingContext WriteSubcontext(string id)
	{
		if (m_ChildCtxs == null)
		{
			m_ChildCtxs = new map<string, ref TerjeStorageBaseContext>;
		}
		
		ref TerjeStorageWritingContext result = new TerjeStorageWritingContext;
		m_ChildCtxs.Set(id, result);
		return result;
	}
}

class TerjeStorageReadingContext : TerjeStorageBaseContext
{
	
	bool OnStoreLoad(ParamsReadContext ctx)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
		
		return false;
	}
	
	bool ReadBool(string id, out bool value, bool defaultValue = false)
	{
		if (m_Booleans != null && m_Booleans.Find(id, value))
		{
			return true;
		}
		
		value = defaultValue;
		return false;
	}
	
	bool ReadFloat(string id, out float value, float defaultValue = 0)
	{
		if (m_Floats != null && m_Floats.Find(id, value))
		{
			return true;
		}
		
		value = defaultValue;
		return false;
	}
	
	bool ReadInt(string id, out int value, int defaultValue = 0)
	{
		if (m_Integers != null && m_Integers.Find(id, value))
		{
			return true;
		}
		
		value = defaultValue;
		return false;
	}
	
	bool ReadString(string id, out string value, string defaultValue = "")
	{
		if (m_Strings != null && m_Strings.Find(id, value))
		{
			return true;
		}
		
		value = defaultValue;
		return false;
	}
	
	ref TerjeStorageReadingContext ReadSubcontext(string id)
	{
		ref TerjeStorageReadingContext value;
		if (m_ChildCtxs != null && m_ChildCtxs.Find(id, value))
		{
			return value;
		}
		
		return null;
	}
}