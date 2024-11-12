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
	
	void SetStringValue(string value);
	string GetStringValue();
};

class TerjeRecordString : TerjeRecordBase
{
	private string m_value;
	
	void TerjeRecordString(string value, bool serverOnly)
	{
		m_value = value;
		SetServerOnly(serverOnly);
	}
	
	override void SetStringValue(string value)
	{
		m_value = value;
	}
	
	override string GetStringValue()
	{
		return m_value;
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
};

class TerjeRecordInt : TerjeRecordBase
{
	private int m_value;
	
	void TerjeRecordInt(int value, bool serverOnly)
	{
		m_value = value;
		SetServerOnly(serverOnly);
	}
	
	override void SetStringValue(string value)
	{
		m_value = value.ToInt();
	}
	
	override string GetStringValue()
	{
		return m_value.ToString();
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
};

class TerjeRecordFloat : TerjeRecordBase
{
	private float m_value;
	
	void TerjeRecordFloat(float value, bool serverOnly)
	{
		m_value = value;
		SetServerOnly(serverOnly);
	}
	
	override void SetStringValue(string value)
	{
		m_value = value.ToFloat();
	}
	
	override string GetStringValue()
	{
		return m_value.ToString();
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
};

class TerjeRecordBool : TerjeRecordBase
{
	private bool m_value;
	
	void TerjeRecordBool(bool value, bool serverOnly)
	{
		m_value = value;
		SetServerOnly(serverOnly);
	}
	
	override void SetStringValue(string value)
	{
		bool boolValue = false;
		if (value == "+")
		{
			boolValue = true;
		}
		
		m_value = boolValue;
	}
	
	override string GetStringValue()
	{
		if (m_value)
		{
			return "+";
		}
		else
		{
			return "-";
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
};