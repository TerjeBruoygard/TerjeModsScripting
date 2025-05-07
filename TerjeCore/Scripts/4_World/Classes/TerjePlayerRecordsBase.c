// <copyright file="TerjePlayerRecordsBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerRecordsBase
{
	private const int STORE_BEGIN_RW_MARKER = -3539889261;
	private const int STORE_END_RW_MARKER = 1719232123;
	
	protected bool m_dirtySynch = false;
	protected bool m_dirtyServer = false;
	protected ref map<string, ref TerjeRecordBase> m_records = new map<string, ref TerjeRecordBase>;
	protected ref map<string, ref TerjeRecordBase> m_synchRecords = new map<string, ref TerjeRecordBase>;
	protected ref array<ref TerjeRecordBase> m_orderedRecords = new array<ref TerjeRecordBase>;
	protected ref map<string, int> m_timestampsCache = null;
	protected int m_timestampRecord;
	
	void OnInit()
	{
		m_timestampRecord = RegisterRecordString("timestamps", string.Empty, true);
	}
	
	bool IsDirtySynch()
	{
		return m_dirtySynch;
	}
	
	bool IsDirtyServer()
	{
		return m_dirtyServer;
	}
	
	void ClearDirtySynch()
	{
		m_dirtySynch = false;
	}
	
	void ClearDirtyServer()
	{
		m_dirtyServer = false;
	}
	
	protected void MarkDirtySynch()
	{
		m_dirtySynch = true;
	}
	
	protected void MarkDirtyServer()
	{
		m_dirtyServer = true;
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
	
	protected int RegisterRecord(string id, TerjeRecordBase defaultValue)
	{
		if (!GetGame().IsDedicatedServer() && defaultValue.IsServerOnly())
		{
			return -1;
		}
		
		if (id.Length() == 0 || id.Contains(":") || id.Contains(";"))
		{
			TerjeLog_Error("Invalid record ID '" + id + "' format.");
			return -1;
		}
		
		if (m_records.Contains(id))
		{
			TerjeLog_Error("Record with ID " + id + " already registered.");
			return -1;
		}
		
		m_records.Insert(id, defaultValue);
		
		if (!defaultValue.IsServerOnly())
		{
			m_synchRecords.Insert(id, defaultValue);
		}
		
		return m_orderedRecords.Insert(defaultValue);
	}
	
	string GetStringValue(int id)
	{
		return TerjeRecordString.Cast(m_orderedRecords.Get(id)).GetValue();
	}
	
	void SetStringValue(int id, string value)
	{
		ref TerjeRecordBase record = m_orderedRecords.Get(id);
		TerjeRecordString.Cast(record).SetValue(value);
		if (record.IsDirty())
		{
			MarkDirtyServer();
			if (!record.IsServerOnly())
			{
				MarkDirtySynch();
			}
		}
	}
	
	int GetIntValue(int id)
	{
		return TerjeRecordInt.Cast(m_orderedRecords.Get(id)).GetValue();
	}
	
	void SetIntValue(int id, int value)
	{
		ref TerjeRecordBase record = m_orderedRecords.Get(id);
		TerjeRecordInt.Cast(record).SetValue(value);
		if (record.IsDirty())
		{
			MarkDirtyServer();
			if (!record.IsServerOnly())
			{
				MarkDirtySynch();
			}
		}
	}
	
	float GetFloatValue(int id)
	{
		return TerjeRecordFloat.Cast(m_orderedRecords.Get(id)).GetValue();
	}
	
	void SetFloatValue(int id, float value)
	{
		ref TerjeRecordBase record = m_orderedRecords.Get(id);
		TerjeRecordFloat.Cast(record).SetValue(value);
		if (record.IsDirty())
		{
			MarkDirtyServer();
			if (!record.IsServerOnly())
			{
				MarkDirtySynch();
			}
		}
	}
	
	bool GetBoolValue(int id)
	{
		return TerjeRecordBool.Cast(m_orderedRecords.Get(id)).GetValue();
	}
	
	void SetBoolValue(int id, bool value)
	{
		ref TerjeRecordBase record = m_orderedRecords.Get(id);
		TerjeRecordBool.Cast(record).SetValue(value);
		if (record.IsDirty())
		{
			MarkDirtyServer();
			if (!record.IsServerOnly())
			{
				MarkDirtySynch();
			}
		}
	}
	
	bool TryGetStringValue(string id, out string value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			value = TerjeRecordString.Cast(record).GetValue();
			return true;
		}
		
		return false;
	}
	
	bool TrySetStringValue(string id, string value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			ref TerjeRecordString recordStr = TerjeRecordString.Cast(record);
			if (recordStr)
			{
				recordStr.SetValue(value);
				if (record.IsDirty())
				{
					MarkDirtyServer();
					if (!record.IsServerOnly())
					{
						MarkDirtySynch();
					}
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	bool TryGetIntValue(string id, out int value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			value = TerjeRecordInt.Cast(record).GetValue();
			return true;
		}
		
		return false;
	}
	
	bool TrySetIntValue(string id, int value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			ref TerjeRecordInt recordInt = TerjeRecordInt.Cast(record);
			if (recordInt)
			{
				recordInt.SetValue(value);
				if (record.IsDirty())
				{
					MarkDirtyServer();
					if (!record.IsServerOnly())
					{
						MarkDirtySynch();
					}
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	bool TryGetFloatValue(string id, out float value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			value = TerjeRecordFloat.Cast(record).GetValue();
			return true;
		}
		
		return false;
	}
	
	bool TrySetFloatValue(string id, float value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			ref TerjeRecordFloat recordFloat = TerjeRecordFloat.Cast(record);
			if (recordFloat)
			{
				recordFloat.SetValue(value);
				if (record.IsDirty())
				{
					MarkDirtyServer();
					if (!record.IsServerOnly())
					{
						MarkDirtySynch();
					}
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	bool TryGetBoolValue(string id, out bool value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			value = TerjeRecordBool.Cast(record).GetValue();
			return true;
		}
		
		return false;
	}
	
	bool TrySetBoolValue(string id, bool value)
	{
		ref TerjeRecordBase record;
		if (m_records.Find(id, record))
		{
			ref TerjeRecordBool recordBool = TerjeRecordBool.Cast(record);
			if (recordBool)
			{
				recordBool.SetValue(value);
				if (record.IsDirty())
				{
					MarkDirtyServer();
					if (!record.IsServerOnly())
					{
						MarkDirtySynch();
					}
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	string SerializeToString()
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void DeserializeFromString(string data)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void OnStoreCopy(TerjePlayerRecordsBase copyFrom)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	bool OnStoreLoad(ParamsReadContext ctx)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
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
	
	bool OnStoreSynch(ParamsWriteContext ctx, bool forceSynchAll)
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
	
	void SynchWithClient(PlayerBase player, bool forceSynchAll, int rpcId)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void SetTimestamp(string name, int value)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	bool GetTimestamp(string name, out int value)
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