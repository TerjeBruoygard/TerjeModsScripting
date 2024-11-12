// <copyright file="TerjePlayerProfile.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerProfile : TerjePlayerRecordsBase
{
	private bool m_dirtyStorage = false;
	
	override void OnInit()
	{
		RegisterRecordString("core", "1.0.0", true);
	};
	
	bool IsDirtyStorage()
	{
		return m_dirtyStorage;
	}
	
	override protected void MarkDirty()
	{
		super.MarkDirty();
		m_dirtyStorage = true;
	}
	
	void SendToClient(PlayerIdentity identity, bool forceSynchAll)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void ApplyFromServer(ref map<string, string> context)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void OnStoreSave(string path)
	{
		FileSerializer ctx = new FileSerializer();
		ctx.Open(path + ".temp", FileMode.WRITE);
		if (ctx.IsOpen())
		{
			ctx.Write(m_records.Count());
			foreach (string id, ref TerjeRecordBase record : m_records)	
			{
				ctx.Write(id);
				ctx.Write(record.GetStringValue());
			}		
			
			ctx.Close();
			CopyFile(path + ".temp", path);
			DeleteFile(path + ".temp");
		}
		
		m_dirtyStorage = false;
	}
	
	bool OnStoreLoad(string path)
	{
		if (!FileExist(path))
		{
			// Skip when profile is not exist. (New player)
			return true;
		}
		
		FileSerializer ctx = new FileSerializer();
		ctx.Open(path, FileMode.READ);
		if (!ctx.IsOpen())
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
		
		ctx.Close();
		return true;
	}
};