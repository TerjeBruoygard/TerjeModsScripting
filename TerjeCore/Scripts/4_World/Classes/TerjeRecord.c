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
		string result = "";
		int length = m_value.Length();
		for (int i = 0; i < length; i++)
		{
			result = result + m_value.Get(i).ToAscii().ToString() + ".";
		}
		
		return result;
	}
	
	override void DeserializeValue(string value)
	{
		string result = "";
		int length = value.Length();
		for (int i = 0; i < length; i++)
		{
			int newIndex = value.IndexOfFrom(i, ".");
			if (newIndex != -1)
			{
				result = result + value.Substring(i, newIndex - i).ToInt().AsciiToString();
				i = newIndex;
			}
		}
		
		SetValue(result);
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