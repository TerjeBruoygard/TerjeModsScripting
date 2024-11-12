// <copyright file="TerjePlayerStats.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerStats : TerjePlayerRecordsBase
{
	private int m_LifetimeStat;
	private const string STORE_BEGIN_RW_MARKER = "Qe#bz21PklVUo%EuPJ^x";
	private const string STORE_END_RW_MARKER = "Sb3&NO@SD0kAN&oLLAdV";
	
	override void OnInit()
	{
		m_LifetimeStat = RegisterRecordInt("lifetime", 0, true);
	};
	
	void ApplyFromServer(ref map<string, string> context)
	{
		foreach (string id, string value : context)
		{
			TerjeRecordBase record;
			if (m_records.Find(id, record))
			{
				record.SetStringValue(value);
			}
		}
	};
	
	void FillSynchContext(ref map<string, string> context, bool forceSynchAll)
	{
		if (GetGame().IsDedicatedServer())
		{
			if (forceSynchAll || IsDirtySynch())
			{
				foreach (string id, ref TerjeRecordBase record : m_records)
				{
					if (!record.IsServerOnly())
					{
						if (forceSynchAll || record.IsDirty())
						{
							context.Insert(id, record.GetStringValue());
							record.ClearDirty();
						}
					}
				}
				
				m_dirtySynch = false;
			}
		}
	};
	
	bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		string rwMarkerBegin;
		if (!ctx.Read(rwMarkerBegin) || rwMarkerBegin != STORE_BEGIN_RW_MARKER)
		{
			return false;
		}
		
		int count;
		if (!ctx.Read(count))
		{
			return false;
		}
		
		for (int i = 0; i < count; i++)
		{
			string id;
			if (!ctx.Read(id))
			{
				return false;
			}
			
			string data;
			if (!ctx.Read(data))
			{
				return false;
			}
			
			TerjeRecordBase record;
			if (m_records.Find(id, record))
			{
				record.SetStringValue(data);
			}
		}
		
		string rwMarkerEnd;
		if (!ctx.Read(rwMarkerEnd) || rwMarkerEnd != STORE_END_RW_MARKER)
		{
			return false;
		}
		
		MarkDirty();
		return true;
	}
	
	void OnStoreSave(ParamsWriteContext ctx)
	{
		ctx.Write(STORE_BEGIN_RW_MARKER);
		ctx.Write(m_records.Count());
		foreach (string id, ref TerjeRecordBase record : m_records)	
		{
			ctx.Write(id);
			ctx.Write(record.GetStringValue());
		}
		
		ctx.Write(STORE_END_RW_MARKER);
	}
	
	int IncrementLifetime()
	{
		int result = GetIntValue(m_LifetimeStat) + 1;
		SetIntValue(m_LifetimeStat, result);
		return result;
	};
	
	int GetLifetime()
	{
		return GetIntValue(m_LifetimeStat);
	};
};