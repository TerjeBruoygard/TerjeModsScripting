// <copyright file="TerjeRecord.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

bool TerjeReadUnknownRecord(string typeId, ParamsReadContext ctx)
{
	ref TerjeRecordBase record;
	if (typeId == "str")
	{
		record = new TerjeRecordString("", true);
		return record.ReadValue(ctx);
	}
	
	if (typeId == "int")
	{
		record = new TerjeRecordInt(0, true);
		return record.ReadValue(ctx);
	}
	
	if (typeId == "num")
	{
		record = new TerjeRecordFloat(0, true);
		return record.ReadValue(ctx);
	}
	
	if (typeId == "bool")
	{
		record = new TerjeRecordBool(false, true);
		return record.ReadValue(ctx);
	}
	
	if (typeId == "arrstr")
	{
		record = new TerjeRecordStringArray(true);
		return record.ReadValue(ctx);
	}
	
	if (typeId == "arrint")
	{
		record = new TerjeRecordIntArray(true);
		return record.ReadValue(ctx);
	}
	
	if (typeId == "arrnum")
	{
		record = new TerjeRecordFloatArray(true);
		return record.ReadValue(ctx);
	}
	
	if (typeId == "mapstr")
	{
		record = new TerjeRecordStringMap(true);
		return record.ReadValue(ctx);
	}
	
	if (typeId == "mapint")
	{
		record = new TerjeRecordIntMap(true);
		return record.ReadValue(ctx);
	}
	
	if (typeId == "mapnum")
	{
		record = new TerjeRecordFloatMap(true);
		return record.ReadValue(ctx);
	}
	
	return false;
}

class TerjeRecordBase
{
	private bool m_serverOnly = true;
	private bool m_isDirty = false;
	
	protected void SetServerOnly(bool serverOnly)
	{
		m_serverOnly = serverOnly;
	}
	
	bool IsServerOnly()
	{
		return m_serverOnly;
	}
	
	bool IsDirty()
	{
		return m_isDirty;
	}
	
	void MarkDirty()
	{
		m_isDirty = true;
	}
	
	void ClearDirty()
	{
		m_isDirty = false;
	}
	
	void CopyValue(TerjeRecordBase from)
	{
	}
	
	void WriteValue(ParamsWriteContext ctx)
	{
	}
	
	bool ReadValue(ParamsReadContext ctx)
	{
	}
	
	string DebugValue()
	{
		return "";
	}
	
	string GetRecordTypeId()
	{
		return "err";
	}
	
	string SerializeValue()
	{
		return "";
	}
	
	void DeserializeValue(string value)
	{
	}
}

class TerjeRecordString : TerjeRecordBase
{
	private string m_value;
	
	void TerjeRecordString(string value, bool serverOnly)
	{
		m_value = value;
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		ctx.Write(GetValue());
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		string value;
		if (ctx.Read(value))
		{
			SetValue(value);
			return true;
		}
		
		return false;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordString fromRecord = TerjeRecordString.Cast(from);
		if (fromRecord)
		{
			SetValue(fromRecord.GetValue());
		}
	}
	
	void SetValue(string value)
	{
		if (m_value != value)
		{
			MarkDirty();
		}
		
		m_value = value;
	}
	
	string GetValue()
	{
		return m_value;
	}
	
	override string DebugValue()
	{
		return m_value;
	}
	
	override string GetRecordTypeId()
	{
		return "str";
	}
	
	override string SerializeValue()
	{
		return TerjeStringHelper.EncodeToHex(GetValue());
	}
	
	override void DeserializeValue(string value)
	{
		SetValue(TerjeStringHelper.DecodeFromHex(value));
	}
}

class TerjeRecordInt : TerjeRecordBase
{
	private int m_value;
	
	void TerjeRecordInt(int value, bool serverOnly)
	{
		m_value = value;
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		ctx.Write(GetValue());
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		int value;
		if (ctx.Read(value))
		{
			SetValue(value);
			return true;
		}
		
		return false;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordInt fromRecord = TerjeRecordInt.Cast(from);
		if (fromRecord)
		{
			SetValue(fromRecord.GetValue());
		}
	}
	
	void SetValue(int value)
	{
		if (m_value != value)
		{
			MarkDirty();
		}
		
		m_value = value;
	}
	
	int GetValue()
	{
		return m_value;
	}
	
	override string DebugValue()
	{
		return m_value.ToString();
	}
	
	override string GetRecordTypeId()
	{
		return "int";
	}
	
	override string SerializeValue()
	{
		return m_value.ToString();
	}
	
	override void DeserializeValue(string value)
	{
		SetValue(value.ToInt());
	}
}

class TerjeRecordFloat : TerjeRecordBase
{
	private float m_value;
	
	void TerjeRecordFloat(float value, bool serverOnly)
	{
		m_value = value;
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		ctx.Write(GetValue());
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		float value;
		if (ctx.Read(value))
		{
			SetValue(value);
			return true;
		}
		
		return false;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordFloat fromRecord = TerjeRecordFloat.Cast(from);
		if (fromRecord)
		{
			SetValue(fromRecord.GetValue());
		}
	}
	
	void SetValue(float value)
	{
		if (m_value != value)
		{
			MarkDirty();
		}
		
		m_value = value;
	}
	
	float GetValue()
	{
		return m_value;
	}
	
	override string DebugValue()
	{
		return m_value.ToString();
	}
	
	override string GetRecordTypeId()
	{
		return "num";
	}
	
	override string SerializeValue()
	{
		return m_value.ToString();
	}
	
	override void DeserializeValue(string value)
	{
		SetValue(value.ToFloat());
	}
}

class TerjeRecordBool : TerjeRecordBase
{
	private bool m_value;
	
	void TerjeRecordBool(bool value, bool serverOnly)
	{
		m_value = value;
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		ctx.Write(GetValue());
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		bool value;
		if (ctx.Read(value))
		{
			SetValue(value);
			return true;
		}
		
		return false;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordBool fromRecord = TerjeRecordBool.Cast(from);
		if (fromRecord)
		{
			SetValue(fromRecord.GetValue());
		}
	}
	
	void SetValue(bool value)
	{
		if (m_value != value)
		{
			MarkDirty();
		}
		
		m_value = value;
	}
	
	bool GetValue()
	{
		return m_value;
	}
	
	override string DebugValue()
	{
		if (m_value)
		{
			return "true";
		}
		
		return "false";
	}
	
	override string GetRecordTypeId()
	{
		return "bool";
	}
	
	override string SerializeValue()
	{
		if (m_value)
		{
			return "1";
		}
		
		return "0";
	}
	
	override void DeserializeValue(string value)
	{
		if (value == "1")
		{
			SetValue(true);
		}
		else
		{
			SetValue(false);
		}
	}
}

class TerjeRecordArray : TerjeRecordBase
{
	int GetValuesCount()
	{
		return 0;
	}
	
	void ClearValues()
	{

	}
	
	void RemoveValue(int index)
	{

	}
}

class TerjeRecordStringArray : TerjeRecordArray
{
	private ref array<string> m_value = new array<string>;
	
	void TerjeRecordStringArray(bool serverOnly)
	{
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		int count = GetValuesCount();
		ctx.Write(count);
		for (int i = 0; i < count; i++)
		{
			ctx.Write(GetValue(i));
		}
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		ClearValues();
		
		int count;
		if (!ctx.Read(count))
			return false;
		
		for (int i = 0; i < count; i++)
		{
			string item;
			if (!ctx.Read(item))
				return false;
			
			AddValue(item);
		}
		
		return true;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordStringArray fromRecord = TerjeRecordStringArray.Cast(from);
		if (fromRecord)
		{
			ClearValues();
			for (int i = 0; i < fromRecord.GetValuesCount(); i++)
			{
				AddValue(fromRecord.GetValue(i));
			}
		}
	}
	
	override int GetValuesCount()
	{
		return m_value.Count();
	}
	
	override void ClearValues()
	{
		if (m_value.Count() > 0)
		{
			MarkDirty();
		}
		
		m_value.Clear();
	}
	
	void AddValue(string value)
	{
		MarkDirty();
		m_value.Insert(value);
	}
	
	override void RemoveValue(int index)
	{
		MarkDirty();
		m_value.Remove(index);
	}
	
	void SetValue(int index, string value)
	{
		if (m_value.Get(index) != value)
		{
			MarkDirty();
			m_value.Set(index, value);
		}
	}
	
	string GetValue(int index)
	{
		return m_value.Get(index);
	}
	
	override string DebugValue()
	{
		return "array<string>";
	}
	
	override string GetRecordTypeId()
	{
		return "arrstr";
	}
	
	override string SerializeValue()
	{
		string result = string.Empty;
		foreach (int index, string item : m_value)
		{
			if (index != 0) result += ",";
			string encoded = TerjeStringHelper.EncodeToHex(item);
			if (encoded != string.Empty)
			{
				result += encoded;
			}
			else
			{
				result += "_";
			}
		}
		
		return result;
	}
	
	override void DeserializeValue(string value)
	{
		ClearValues();
		
		array<string> parts();
		value.Split(",", parts);
		foreach (string item : parts)
		{
			if (item == "_")
			{
				AddValue(string.Empty);
			}
			else
			{
				AddValue(TerjeStringHelper.DecodeFromHex(item));
			}
		}
	}
}

class TerjeRecordIntArray : TerjeRecordArray
{
	private ref array<int> m_value = new array<int>;
	
	void TerjeRecordIntArray(bool serverOnly)
	{
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		int count = GetValuesCount();
		ctx.Write(count);
		for (int i = 0; i < count; i++)
		{
			ctx.Write(GetValue(i));
		}
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		ClearValues();
		
		int count;
		if (!ctx.Read(count))
			return false;
		
		for (int i = 0; i < count; i++)
		{
			int item;
			if (!ctx.Read(item))
				return false;
			
			AddValue(item);
		}
		
		return true;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordIntArray fromRecord = TerjeRecordIntArray.Cast(from);
		if (fromRecord)
		{
			ClearValues();
			for (int i = 0; i < fromRecord.GetValuesCount(); i++)
			{
				AddValue(fromRecord.GetValue(i));
			}
		}
	}
	
	override int GetValuesCount()
	{
		return m_value.Count();
	}
	
	override void ClearValues()
	{
		if (m_value.Count() > 0)
		{
			MarkDirty();
		}
		
		m_value.Clear();
	}
	
	void AddValue(int value)
	{
		MarkDirty();
		m_value.Insert(value);
	}
	
	override void RemoveValue(int index)
	{
		MarkDirty();
		m_value.Remove(index);
	}
	
	void SetValue(int index, int value)
	{
		if (m_value.Get(index) != value)
		{
			MarkDirty();
			m_value.Set(index, value);
		}
	}
	
	int GetValue(int index)
	{
		return m_value.Get(index);
	}
	
	override string DebugValue()
	{
		return "array<int>";
	}
	
	override string GetRecordTypeId()
	{
		return "arrint";
	}
	
	override string SerializeValue()
	{
		string result = string.Empty;
		foreach (int index, int item : m_value)
		{
			if (index != 0) result += ",";
			result += item.ToString();
		}
		
		return result;
	}
	
	override void DeserializeValue(string value)
	{
		ClearValues();
		
		array<string> parts();
		value.Split(",", parts);
		foreach (string item : parts)
		{
			AddValue(item.ToInt());
		}
	}
}

class TerjeRecordFloatArray : TerjeRecordArray
{
	private ref array<float> m_value = new array<float>;
	
	void TerjeRecordFloatArray(bool serverOnly)
	{
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		int count = GetValuesCount();
		ctx.Write(count);
		for (int i = 0; i < count; i++)
		{
			ctx.Write(GetValue(i));
		}
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		ClearValues();
		
		int count;
		if (!ctx.Read(count))
			return false;
		
		for (int i = 0; i < count; i++)
		{
			float item;
			if (!ctx.Read(item))
				return false;
			
			AddValue(item);
		}
		
		return true;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordFloatArray fromRecord = TerjeRecordFloatArray.Cast(from);
		if (fromRecord)
		{
			ClearValues();
			for (int i = 0; i < fromRecord.GetValuesCount(); i++)
			{
				AddValue(fromRecord.GetValue(i));
			}
		}
	}
	
	override int GetValuesCount()
	{
		return m_value.Count();
	}
	
	override void ClearValues()
	{
		if (m_value.Count() > 0)
		{
			MarkDirty();
		}
		
		m_value.Clear();
	}
	
	void AddValue(float value)
	{
		MarkDirty();
		m_value.Insert(value);
	}
	
	override void RemoveValue(int index)
	{
		MarkDirty();
		m_value.Remove(index);
	}
	
	void SetValue(int index, float value)
	{
		if (m_value.Get(index) != value)
		{
			MarkDirty();
			m_value.Set(index, value);
		}
	}
	
	float GetValue(int index)
	{
		return m_value.Get(index);
	}
	
	override string DebugValue()
	{
		return "array<float>";
	}
	
	override string GetRecordTypeId()
	{
		return "arrnum";
	}
	
	override string SerializeValue()
	{
		string result = string.Empty;
		foreach (int index, float item : m_value)
		{
			if (index != 0) result += ",";
			result += item.ToString();
		}
		
		return result;
	}
	
	override void DeserializeValue(string value)
	{
		ClearValues();
		
		array<string> parts();
		value.Split(",", parts);
		foreach (string item : parts)
		{
			AddValue(item.ToFloat());
		}
	}
}

class TerjeRecordMap : TerjeRecordBase
{
	void ClearValues()
	{

	}
	
	bool ContainsKey(string key)
	{

	}
	
	void RemoveValue(string key)
	{

	}
}

class TerjeRecordStringMap : TerjeRecordMap
{
	private ref map<string, string> m_value = new map<string, string>;
	
	void TerjeRecordStringMap(bool serverOnly)
	{
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		int count = m_value.Count();
		ctx.Write(count);
		foreach (string key, string val : m_value)
		{
			ctx.Write(key);
			ctx.Write(val);
		}
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		ClearValues();
		
		int count;
		if (!ctx.Read(count))
			return false;
		
		for (int i = 0; i < count; i++)
		{
			string key;
			if (!ctx.Read(key))
				return false;
			
			string value;
			if (!ctx.Read(value))
				return false;
			
			SetValue(key, value);
		}
		
		return true;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordStringMap fromRecord = TerjeRecordStringMap.Cast(from);
		if (fromRecord)
		{
			ClearValues();
			
			map<string, string> fromValues = fromRecord.GetValues();
			foreach (string key, string value : fromValues)
			{
				SetValue(key, value);
			}
		}
	}
	
	override void ClearValues()
	{
		if (m_value.Count() > 0)
		{
			MarkDirty();
		}
		
		m_value.Clear();
	}
	
	override bool ContainsKey(string key)
	{
		return m_value.Contains(key);
	}
	
	override void RemoveValue(string key)
	{
		if (m_value.Contains(key))
		{
			MarkDirty();
			m_value.Remove(key);
		}
	}
	
	map<string, string> GetValues()
	{
		return m_value;
	}
	
	void SetValue(string key, string value)
	{
		string oldValue;
		if (m_value.Find(key, oldValue))
		{
			if (oldValue != value)
			{
				MarkDirty();
				m_value.Set(key, value);
			}
		}
		else
		{
			MarkDirty();
			m_value.Set(key, value);
		}
	}
	
	bool FindValue(string key, out string value)
	{
		return m_value.Find(key, value);
	}
	
	override string DebugValue()
	{
		return "map<string>";
	}
	
	override string GetRecordTypeId()
	{
		return "mapstr";
	}
	
	override string SerializeValue()
	{
		int index = 0;
		string result = string.Empty;
		foreach (string key, string value : m_value)
		{
			if (index != 0)
			{
				result += ",";
			}
			
			if (key == string.Empty)
			{
				result += "_,";
			}
			else
			{
				result += TerjeStringHelper.EncodeToHex(key) + ",";
			}
			
			if (value == string.Empty)
			{
				result += "_";
			}
			else
			{
				result += TerjeStringHelper.EncodeToHex(value);
			}
			
			index += 1;
		}
		
		return result;
	}
	
	override void DeserializeValue(string value)
	{
		ClearValues();
		
		array<string> parts();
		value.Split(",", parts);
		for (int i = 0; (i + 1) < parts.Count(); i += 2)
		{
			string key = string.Empty;
			if (parts.Get(i) != "_")
			{
				key = TerjeStringHelper.DecodeFromHex(parts.Get(i));
			}
			
			string element = string.Empty;
			if (parts.Get(i + 1) != "_")
			{
				element = TerjeStringHelper.DecodeFromHex(parts.Get(i + 1));
			}
			
			SetValue(key, element);
		}
	}
}

class TerjeRecordIntMap : TerjeRecordMap
{
	private ref map<string, int> m_value = new map<string, int>;
	
	void TerjeRecordIntMap(bool serverOnly)
	{
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		int count = m_value.Count();
		ctx.Write(count);
		foreach (string key, int val : m_value)
		{
			ctx.Write(key);
			ctx.Write(val);
		}
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		ClearValues();
		
		int count;
		if (!ctx.Read(count))
			return false;
		
		for (int i = 0; i < count; i++)
		{
			string key;
			if (!ctx.Read(key))
				return false;
			
			int value;
			if (!ctx.Read(value))
				return false;
			
			SetValue(key, value);
		}
		
		return true;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordIntMap fromRecord = TerjeRecordIntMap.Cast(from);
		if (fromRecord)
		{
			ClearValues();
			
			map<string, int> fromValues = fromRecord.GetValues();
			foreach (string key, int value : fromValues)
			{
				SetValue(key, value);
			}
		}
	}
	
	override void ClearValues()
	{
		if (m_value.Count() > 0)
		{
			MarkDirty();
		}
		
		m_value.Clear();
	}
	
	override bool ContainsKey(string key)
	{
		return m_value.Contains(key);
	}
	
	override void RemoveValue(string key)
	{
		if (m_value.Contains(key))
		{
			MarkDirty();
			m_value.Remove(key);
		}
	}
	
	map<string, int> GetValues()
	{
		return m_value;
	}
	
	void SetValue(string key, int value)
	{
		int oldValue;
		if (m_value.Find(key, oldValue))
		{
			if (oldValue != value)
			{
				MarkDirty();
				m_value.Set(key, value);
			}
		}
		else
		{
			MarkDirty();
			m_value.Set(key, value);
		}
	}
	
	bool FindValue(string key, out int value)
	{
		return m_value.Find(key, value);
	}
	
	override string DebugValue()
	{
		return "map<int>";
	}
	
	override string GetRecordTypeId()
	{
		return "mapint";
	}
	
	override string SerializeValue()
	{
		int index = 0;
		string result = string.Empty;
		foreach (string key, int value : m_value)
		{
			if (index != 0)
			{
				result += ",";
			}
			
			if (key == string.Empty)
			{
				result += "_,";
			}
			else
			{
				result += TerjeStringHelper.EncodeToHex(key) + ",";
			}
			
			result += value.ToString();
			index += 1;
		}
		
		return result;
	}
	
	override void DeserializeValue(string value)
	{
		ClearValues();
		
		array<string> parts();
		value.Split(",", parts);
		for (int i = 0; (i + 1) < parts.Count(); i += 2)
		{
			string key = string.Empty;
			if (parts.Get(i) != "_")
			{
				key = TerjeStringHelper.DecodeFromHex(parts.Get(i));
			}
			
			int element = parts.Get(i + 1).ToInt();
			SetValue(key, element);
		}
	}
}

class TerjeRecordFloatMap : TerjeRecordMap
{
	private ref map<string, float> m_value = new map<string, float>;
	
	void TerjeRecordFloatMap(bool serverOnly)
	{
		SetServerOnly(serverOnly);
	}
	
	override void WriteValue(ParamsWriteContext ctx)
	{
		int count = m_value.Count();
		ctx.Write(count);
		foreach (string key, float val : m_value)
		{
			ctx.Write(key);
			ctx.Write(val);
		}
	}
	
	override bool ReadValue(ParamsReadContext ctx)
	{
		ClearValues();
		
		int count;
		if (!ctx.Read(count))
			return false;
		
		for (int i = 0; i < count; i++)
		{
			string key;
			if (!ctx.Read(key))
				return false;
			
			float value;
			if (!ctx.Read(value))
				return false;
			
			SetValue(key, value);
		}
		
		return true;
	}
	
	override void CopyValue(TerjeRecordBase from)
	{
		TerjeRecordFloatMap fromRecord = TerjeRecordFloatMap.Cast(from);
		if (fromRecord)
		{
			ClearValues();
			
			map<string, float> fromValues = fromRecord.GetValues();
			foreach (string key, float value : fromValues)
			{
				SetValue(key, value);
			}
		}
	}
	
	override void ClearValues()
	{
		if (m_value.Count() > 0)
		{
			MarkDirty();
		}
		
		m_value.Clear();
	}
	
	override bool ContainsKey(string key)
	{
		return m_value.Contains(key);
	}
	
	override void RemoveValue(string key)
	{
		if (m_value.Contains(key))
		{
			MarkDirty();
			m_value.Remove(key);
		}
	}
	
	map<string, float> GetValues()
	{
		return m_value;
	}
	
	void SetValue(string key, float value)
	{
		float oldValue;
		if (m_value.Find(key, oldValue))
		{
			if (oldValue != value)
			{
				MarkDirty();
				m_value.Set(key, value);
			}
		}
		else
		{
			MarkDirty();
			m_value.Set(key, value);
		}
	}
	
	bool FindValue(string key, out float value)
	{
		return m_value.Find(key, value);
	}
	
	override string DebugValue()
	{
		return "map<float>";
	}
	
	override string GetRecordTypeId()
	{
		return "mapnum";
	}
	
	override string SerializeValue()
	{
		int index = 0;
		string result = string.Empty;
		foreach (string key, float value : m_value)
		{
			if (index != 0)
			{
				result += ",";
			}
			
			if (key == string.Empty)
			{
				result += "_,";
			}
			else
			{
				result += TerjeStringHelper.EncodeToHex(key) + ",";
			}
			
			result += value.ToString();
			index += 1;
		}
		
		return result;
	}
	
	override void DeserializeValue(string value)
	{
		ClearValues();
		
		array<string> parts();
		value.Split(",", parts);
		for (int i = 0; (i + 1) < parts.Count(); i += 2)
		{
			string key = string.Empty;
			if (parts.Get(i) != "_")
			{
				key = TerjeStringHelper.DecodeFromHex(parts.Get(i));
			}
			
			float element = parts.Get(i + 1).ToFloat();
			SetValue(key, element);
		}
	}
}