// <copyright file="TerjeGameConfig.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeGameConfig
{
	protected ref TerjeXmlDocument m_config = null;
	protected ref map<string, TerjeXmlObject> m_cache = null;
	
	void OnInit()
	{
		if (GetGame().IsDedicatedServer())
		{
			m_config = new TerjeXmlDocument;
			
			string dirpath = "$profile:TerjeSettings\\Core";
			MakeDirectory(dirpath);
			
			string filepath = dirpath + "\\GameOverrides.xml";
			if (!FileExist(filepath))
			{
				CopyFile("TerjeCore\\Templates\\GameOverrides.xml", filepath);
			}
			
			if (FileExist(filepath))
			{
				
				if (m_config.DeserializeFromFile(filepath))
				{
					m_config.DeleteComments(true);
					BuildCache();
				}
			}
		}
	}
	
	void Reset()
	{
		m_cache = null;
		m_config = null;
	}
	
	void SendSettingsToClient(ParamsWriteContext ctx)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void OnReceiveClientSettings(ParamsReadContext ctx)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	protected void BuildCache()
	{
		m_cache = new map<string, TerjeXmlObject>;
		if (m_config != null)
		{
			for (int i = 0; i < m_config.GetChildrenCount(); i++)
			{
				BuildCacheObject(m_config.GetChild(i), string.Empty, true);
			}
		}
		
		if (m_cache.Count() > 0)
		{
			TerjeLog_Info("Overrided " + m_cache.Count() + " values from config.cpp (including inherited classes)");
		}
	}
	
	protected void BuildCacheObject(TerjeXmlObject obj, string path, bool replace)
	{
		if ((obj != null) && (obj.IsObjectNode()) && (obj.GetName() != string.Empty))
		{
			string newPath;
			string objName = obj.GetName();
			objName.ToLower();
			
			if (obj.EqualAttribute("type", "[]"))
			{
				if (path != string.Empty)
				{
					newPath = path + " " + objName;
					if (replace || (!m_cache.Contains(newPath)))
					{
						m_cache.Set(newPath, obj);
					}
				}
			}
			else if (obj.HasChildren())
			{
				TStringArray classesList();
				classesList.Insert(objName);
				ConfigGetAllInheritedClasses(path, objName, classesList);
				for (int q = 0; q < classesList.Count(); q++)
				{
					if (path == string.Empty)
					{
						newPath = classesList.Get(q);
					}
					else
					{
						newPath = path + " " + classesList.Get(q);
					}
		
					for (int i = 0; i < obj.GetChildrenCount(); i++)
					{
						bool nextReplace = false;
						if (replace && (q == 0))
						{
							nextReplace = true;
						}
						
						BuildCacheObject(obj.GetChild(i), newPath, nextReplace);
					}
				}
			}
			else if ((obj.HasValue()) && (path != string.Empty))
			{
				newPath = path + " " + objName;
				if (replace || (!m_cache.Contains(newPath)))
				{
					m_cache.Set(newPath, obj);
				}
			}
		}
	}
	
	protected bool FindCacheValue(string path, out TerjeXmlObject result)
	{
		if (m_cache != null)
		{
			string key = path;
			key.ToLower();
			
			if ((m_cache.Find(key, result)) && (result != null))
			{
				return true;
			}
		}
		
		return false;
	}
	
	bool ConfigGetBool(string path)
	{
		return (this.ConfigGetInt(path) == 1);
	}
	
	float ConfigGetFloat(string path)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			return result.GetValue().ToFloat();
		}
		
		if (GetGame())
		{
			return GetGame().ConfigGetFloat(path);
		}
		
		return 0;
	}
	
	vector ConfigGetVector(string path)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			return result.GetValue().ToVector();
		}
		
		if (GetGame())
		{
			return GetGame().ConfigGetVector(path);
		}
		
		return vector.Zero;
	}
	
	int ConfigGetInt(string path)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			return result.GetValue().ToInt();
		}
		
		if (GetGame())
		{
			return GetGame().ConfigGetInt(path);
		}
		
		return 0;
	}
	
	bool ConfigGetText(string path, out string value)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			value = Widget.TranslateString(result.GetValue());
			return true;
		}
		
		if (GetGame())
		{
			return GetGame().ConfigGetText(path, value);
		}
		
		value = string.Empty;
		return false;
	}
	
	bool ConfigGetTextRaw(string path, out string value)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			value = result.GetValue();
			return true;
		}
		
		if (GetGame())
		{
			return GetGame().ConfigGetTextRaw(path, value);
		}
		
		value = string.Empty;
		return false;
	}
	
	string ConfigGetTextOut(string path)
	{
		string ret_s;
		this.ConfigGetText(path, ret_s);
		return ret_s;
	}
	
	string ConfigGetString(string path)
	{
		string ret_s;
		this.ConfigGetText(path, ret_s);
		return ret_s;
	}
	
	string ConfigGetStringRaw(string path)
	{
		string ret_s;
		this.ConfigGetTextRaw(path, ret_s);
		return ret_s;
	}
	
	void ConfigGetTextArray(string path, out TStringArray values)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			if (values == null)
			{
				values = new TStringArray;
			}
			
			for (int i = 0; i < result.GetChildrenCount(); i++)
			{
				values.Insert(Widget.TranslateString(result.GetChild(i).GetValue()));
			}
			
			return;
		}
		
		if (GetGame())
		{
			GetGame().ConfigGetTextArray(path, values);
			return;
		}
	}
	
	void ConfigGetTextArrayRaw(string path, out TStringArray values)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			if (values == null)
			{
				values = new TStringArray;
			}
			
			for (int i = 0; i < result.GetChildrenCount(); i++)
			{
				values.Insert(result.GetChild(i).GetValue());
			}
			
			return;
		}
		
		if (GetGame())
		{
			GetGame().ConfigGetTextArrayRaw(path, values);
			return;
		}
	}
	
	void ConfigGetFloatArray(string path, out TFloatArray values)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			if (values == null)
			{
				values = new TFloatArray;
			}
			
			for (int i = 0; i < result.GetChildrenCount(); i++)
			{
				values.Insert(result.GetChild(i).GetValue().ToFloat());
			}
			
			return;
		}
		
		if (GetGame())
		{
			GetGame().ConfigGetFloatArray(path, values);
			return;
		}
	}
	
	void ConfigGetIntArray(string path, out TIntArray values)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			if (values == null)
			{
				values = new TIntArray;
			}
			
			for (int i = 0; i < result.GetChildrenCount(); i++)
			{
				values.Insert(result.GetChild(i).GetValue().ToInt());
			}
			
			return;
		}
		
		if (GetGame())
		{
			GetGame().ConfigGetIntArray(path, values);
			return;
		}
	}
	
	bool ConfigIsExisting(string path)
	{
		TerjeXmlObject result;
		if (FindCacheValue(path, result))
		{
			return true;
		}
		
		return GetGame() && GetGame().ConfigIsExisting(path);
	}
		
	bool ConfigGetChildName(string path, int index, out string name)
	{
		return GetGame() && GetGame().ConfigGetChildName(path, index, name);
	}
	
	bool ConfigGetBaseName(string path, out string base_name)
	{
		return GetGame() && GetGame().ConfigGetBaseName(path, base_name);
	}
	
	int ConfigGetChildrenCount(string path)
	{
		if (GetGame())
		{
			return GetGame().ConfigGetChildrenCount(path);
		}
		
		return 0;
	}
	
	void ConfigGetAllInheritedClasses(string path, string baseclass, out TStringArray result)
	{
		if (path == string.Empty)
		{
			return;
		}
		
		if (result == null)
		{
			result = new TStringArray;
		}
		
		if (GetGame())
		{
			int count = GetGame().ConfigGetChildrenCount(path);
			for (int i = 0; i < count; i++)
			{
				string classname;
				if (GetGame().ConfigGetChildName(path, i, classname) && ConfigIsKindOf(path, classname, baseclass))
				{
					classname.ToLower();
					result.Insert(classname);
				}
			}
		}
	}
	
	bool ConfigIsKindOf(string path, string actualClass, string baseClass)
	{
		actualClass.ToLower();
		baseClass.ToLower();		
		if (GetGame() && (actualClass != baseClass))
		{
			string parentName = string.Empty;
			string value = path + " " + actualClass;
			while (GetGame().ConfigIsExisting(value) && GetGame().ConfigGetBaseName(value, parentName))
			{
				parentName.ToLower();
				if (parentName == actualClass)
				{
					return false;
				}
				
				if (parentName == baseClass)
				{
					return true;
				}
				
				value = path + " " + parentName;
				parentName = string.Empty;
			}
		}
		
		return false;
	}
}

TerjeGameConfig GetTerjeGameConfig()
{
	/*
	 This code block is private and was hidden before publishing on github.
	 
	 This repository does not provide full code of our mods need to be fully functional.
	 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
	 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
	 Copyright (c) TerjeMods. All rights reserved.
	*/
}