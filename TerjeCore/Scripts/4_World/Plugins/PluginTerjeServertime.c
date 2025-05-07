// <copyright file="PluginTerjeServertime.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeServertime extends PluginBase
{
	private const int SERVERTIME_VERSION = 1;
	private const string SERVERTIME_FILE = "$mission:terje_storage\\servertime.dat";
	
	private int m_serverSeconds;
	
	private float m_calcTimer;
	private float m_saveTimer;
	
	int GetTimestamp()
	{
		return m_serverSeconds;
	}
	
	override void OnInit()
	{
		m_calcTimer = 0;
		m_saveTimer = 0;
		
		if (GetGame().IsDedicatedServer())
		{
			bool loadedSuccess = false;
			if (FileExist(SERVERTIME_FILE))
			{
				FileSerializer file = new FileSerializer();
				if (file.Open(SERVERTIME_FILE, FileMode.READ))
				{
					if (LoadServertime(file))
					{
						loadedSuccess = true;
					}
					
					file.Close();
				}
			}
			
			if (!loadedSuccess)
			{
				m_serverSeconds = 0;
			}
		}
	}
	
	override void OnUpdate(float delta_time)
	{
		super.OnUpdate(delta_time);
		
		if (GetGame().IsDedicatedServer())
		{
			m_calcTimer += delta_time;
			if (m_calcTimer > 1.0)
			{
				float calcSeconds = Math.Floor(m_calcTimer);
				m_serverSeconds += (int)calcSeconds;
				m_calcTimer -= calcSeconds;
			}
			
			m_saveTimer += delta_time;
			if (m_saveTimer > 180)
			{
				m_saveTimer = 0;
				SaveServertime();
			}
		}
	}
	
	private bool LoadServertime(FileSerializer file)
	{
		int version;
		if (!file.Read(version))
			return false;
		
		if (version != SERVERTIME_VERSION)
			return false;
		
		if (!file.Read(m_serverSeconds))
			return false;
		
		return true;
	}
	
	private void SaveServertime()
	{
		if (GetGame().IsDedicatedServer())
		{
			FileSerializer file = new FileSerializer();
			if (file.Open(SERVERTIME_FILE, FileMode.WRITE))
			{
				file.Write(SERVERTIME_VERSION);
				file.Write(m_serverSeconds);
				file.Close();
			}
		}
	}
}

PluginTerjeServertime GetTerjeServertime() 
{
	return PluginTerjeServertime.Cast(GetPlugin(PluginTerjeServertime));
}
