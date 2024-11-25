// <copyright file="TerjeRecord.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

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
	
	void CopyValue(ref TerjeRecordBase from);
	void WriteValue(ParamsWriteContext ctx);
	bool ReadValue(ParamsReadContext ctx);
	string DebugValue();
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
	
	override void CopyValue(ref TerjeRecordBase from)
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
	
	override void CopyValue(ref TerjeRecordBase from)
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
	
	override void CopyValue(ref TerjeRecordBase from)
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
	
	override void CopyValue(ref TerjeRecordBase from)
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
}