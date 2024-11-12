// <copyright file="TerjePlayerRecordsBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerRecordsBase
{
	protected bool m_dirtySynch = false;
	protected ref map<string, ref TerjeRecordBase> m_records = new map<string, ref TerjeRecordBase>;
	protected ref array<ref TerjeRecordBase> m_orderedRecords = new array<ref TerjeRecordBase>;
	
	void OnInit();
	
	bool IsDirtySynch()
	{
		return m_dirtySynch;
	}
	
	protected void MarkDirty()
	{
		m_dirtySynch = true;
	}
	
	protected int RegisterRecordString(string id, string defaultValue, bool serverOnly)
	{
		return RegisterRecord(id, new TerjeRecordString(defaultValue, serverOnly));
	}
	
	protected int RegisterRecordInt(string id, int defaultValue, bool serverOnly)
	{
		return RegisterRecord(id, new TerjeRecordInt(defaultValue, serverOnly));
	}
	
	protected int RegisterRecordFloat(string id, float defaultValue, bool serverOnly)
	{
		return RegisterRecord(id, new TerjeRecordFloat(defaultValue, serverOnly));
	}
	
	protected int RegisterRecordBool(string id, bool defaultValue, bool serverOnly)
	{
		return RegisterRecord(id, new TerjeRecordBool(defaultValue, serverOnly));
	}
	
	protected int RegisterRecord(string id, ref TerjeRecordBase defaultValue)
	{
		if (!GetGame().IsDedicatedServer() && defaultValue.IsServerOnly())
		{
			return -1;
		}
		
		if (m_records.Contains(id))
		{
			TerjeLog_Error("Record with ID " + id + " already registered.");
			return -1;
		}
		
		m_records.Insert(id, defaultValue);
		return m_orderedRecords.Insert(defaultValue);
	};
	
	string GetStringValue(int id)
	{
		return TerjeRecordString.Cast(m_orderedRecords.Get(id)).GetValue();
	};
	
	void SetStringValue(int id, string value)
	{
		ref TerjeRecordBase record = m_orderedRecords.Get(id);
		TerjeRecordString.Cast(record).SetValue(value);
		if (record.IsDirty())
		{
			MarkDirty();
		}
	};
	
	int GetIntValue(int id)
	{
		return TerjeRecordInt.Cast(m_orderedRecords.Get(id)).GetValue();
	};
	
	void SetIntValue(int id, int value)
	{
		ref TerjeRecordBase record = m_orderedRecords.Get(id);
		TerjeRecordInt.Cast(record).SetValue(value);
		if (record.IsDirty())
		{
			MarkDirty();
		}
	};
	
	float GetFloatValue(int id)
	{
		return TerjeRecordFloat.Cast(m_orderedRecords.Get(id)).GetValue();
	};
	
	void SetFloatValue(int id, float value)
	{
		ref TerjeRecordBase record = m_orderedRecords.Get(id);
		TerjeRecordFloat.Cast(record).SetValue(value);
		if (record.IsDirty())
		{
			MarkDirty();
		}
	};
	
	bool GetBoolValue(int id)
	{
		return TerjeRecordBool.Cast(m_orderedRecords.Get(id)).GetValue();
	};
	
	void SetBoolValue(int id, bool value)
	{
		ref TerjeRecordBase record = m_orderedRecords.Get(id);
		TerjeRecordBool.Cast(record).SetValue(value);
		if (record.IsDirty())
		{
			MarkDirty();
		}
	};
	
	bool TryGetStringValue(string id, out string value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			value = TerjeRecordString.Cast(record).GetValue();
			return true;
		}
		
		return false;
	};
	
	bool TrySetStringValue(string id, string value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			ref TerjeRecordString recordStr = TerjeRecordString.Cast(record);
			if (recordStr)
			{
				recordStr.SetValue(value);
				if (recordStr.IsDirty())
				{
					MarkDirty();
				}
				
				return true;
			}
		}
		
		return false;
	};
	
	bool TryGetIntValue(string id, out int value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			value = TerjeRecordInt.Cast(record).GetValue();
			return true;
		}
		
		return false;
	};
	
	bool TrySetIntValue(string id, int value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			ref TerjeRecordInt recordInt = TerjeRecordInt.Cast(record);
			if (recordInt)
			{
				recordInt.SetValue(value);
				if (recordInt.IsDirty())
				{
					MarkDirty();
				}
				
				return true;
			}
		}
		
		return false;
	};
	
	bool TryGetFloatValue(string id, out float value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			value = TerjeRecordFloat.Cast(record).GetValue();
			return true;
		}
		
		return false;
	};
	
	bool TrySetFloatValue(string id, float value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			ref TerjeRecordFloat recordFloat = TerjeRecordFloat.Cast(record);
			if (recordFloat)
			{
				recordFloat.SetValue(value);
				if (recordFloat.IsDirty())
				{
					MarkDirty();
				}
				
				return true;
			}
		}
		
		return false;
	};
	
	bool TryGetBoolValue(string id, out bool value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			value = TerjeRecordBool.Cast(record).GetValue();
			return true;
		}
		
		return false;
	};
	
	bool TrySetBoolValue(string id, bool value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			ref TerjeRecordBool recordBool = TerjeRecordBool.Cast(record);
			if (recordBool)
			{
				recordBool.SetValue(value);
				if (recordBool.IsDirty())
				{
					MarkDirty();
				}
				
				return true;
			}
		}
		
		return false;
	};
};