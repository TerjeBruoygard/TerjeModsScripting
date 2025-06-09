// <copyright file="PluginTerjeRespawnObjects.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeRespawnObjects : PluginBase 
{
	protected ref set<string> m_idsCollection = new set<string>;
	protected ref map<string, ref map<string, TerjeXmlObject>> m_idsToXmlObjects = new map<string, ref map<string, TerjeXmlObject>>;
	protected ref map<string, ref set<string>> m_idsToClassname = new map<string, ref set<string>>;
	protected ref map<string, ref set<string>> m_classnameToIds = new map<string, ref set<string>>;
	protected ref map<string, ref map<string, ref TerjeRespawnObjectHandler>> m_customHandlers = new map<string, ref map<string, ref TerjeRespawnObjectHandler>>;
	protected Object m_lastLocalObject = null;
	
	override void OnInit()
	{
		if (GetGame().IsClient())
		{
			GetTerjeRPC().RegisterHandler("startscreen.tros", this, "OnTerjeStartScreenRespawnObjectsSynch");
		}
	}
	
	protected void OnTerjeStartScreenRespawnObjectsSynch(ParamsReadContext ctx, PlayerIdentity sender)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void RegisterRespawnObjects(string respawnId, TerjeXmlObject objects)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void SendToClient(PlayerIdentity identity)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
		
	void ResetRespawnObjectsOwner(string uid, TerjePlayerProfile profile)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void ResetRespawnObjectOwner(string respawnId, string uid, TerjePlayerProfile profile)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	bool FindAndValidateRespawnObject(PlayerBase player, string respawnId, out vector playerPos, out vector playerOri)
	{
		if (!GetGame() || !GetGame().IsDedicatedServer())
			return false;
		
		if (!player)
			return false;
		
		if (!player.GetTerjeProfile())
			return false;
		
		string classname;
		string metadata;
		vector objectPos;
		if (!player.GetTerjeProfile().FindRespawnObjectData(respawnId, classname, metadata, objectPos, playerPos, playerOri))
			return false;
		
		TerjeXmlObject xmlObject = FindTerjeXmlObjectServer(respawnId, classname);
		if (!xmlObject)
			return false;
		
		array<Object> objects();
		GetGame().GetObjectsAtPosition3D(objectPos, 0.1, objects, null);
		foreach (Object obj : objects)
		{
			if (obj && (obj.GetType() == classname) && (ValidateRespawnObject(obj, player, respawnId, xmlObject)))
			{
				return true;
			}
		}
		
		return false;
	}
	
	bool ValidateRespawnObject(Object object, PlayerBase player, string respawnId, TerjeXmlObject xmlObject)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (xmlObject.EqualAttribute("singleBind", "1"))
			{
				ItemBase objectItemBase;
				if (ItemBase.CastTo(objectItemBase, object) && !objectItemBase.ValidateTerjeRespawnOwner(player))
				{
					return false;
				}
			}
			
			TerjeRespawnObjectHandler handler;
			map<string, ref TerjeRespawnObjectHandler> handlersMap;
			if (m_customHandlers.Find(respawnId, handlersMap) && handlersMap.Find(object.GetType(), handler))
			{
				return handler.RespawnOnObject(player, object, respawnId);
			}
		}
		
		return true;
	}
	
	bool CanSetObjectAsRespawn(Object object, PlayerBase player)
	{
		if (!m_classnameToIds)
			return false;
		
		if (m_classnameToIds.Count() == 0)
			return false;
		
		if (!object)
			return false;
		
		if (!player)
			return false;
		
		EntityAI entityObj = EntityAI.Cast(object);
		if (entityObj && entityObj.GetHierarchyParent())
		{
			return false;
		}
		
		TentBase tentObj = TentBase.Cast(object);
		if (tentObj && (tentObj.GetState() == TentBase.PACKED) && (tentObj.GetState() == tentObj.GetStateLocal()))
		{
			return false;
		}
		
		string classname = object.GetType();
		if (classname == string.Empty)
			return false;
		
		return m_classnameToIds.Contains(classname);
	}
	
	bool SetObjectAsRespawn(Object object, PlayerBase player)
	{
		if (!CanSetObjectAsRespawn(object, player))
			return false;
		
		if (!player.GetTerjeProfile())
			return false;
		
		int result = 0;
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			set<string> respawnIds = null;
			string classname = object.GetType();
			if (!m_classnameToIds.Find(classname, respawnIds))
				return false;
			
			TerjeRespawnObjectHandler handler;
			map<string, ref TerjeRespawnObjectHandler> handlersMap;
			string metadata = GetObjectRespawnMetadata(object, player);
			vector objectPos = object.GetWorldPosition();
			vector playerPos = player.GetWorldPosition();
			vector playerOri = player.GetOrientation();
			foreach (string respawnId : respawnIds)
			{
				TerjeXmlObject xmlData = FindTerjeXmlObjectServer(respawnId, classname);
				if (xmlData)
				{
					bool valid = true;
					ItemBase objectItemBase = null;
					if (xmlData.EqualAttribute("singleBind", "1"))
					{
						if (ItemBase.CastTo(objectItemBase, object) && !objectItemBase.CheckTerjeRespawnOwner(player))
						{
							valid = false;
						}
					}
					
					if (valid && m_customHandlers.Find(respawnId, handlersMap) && handlersMap.Find(classname, handler))
					{
						if (!handler.SetAsRespawnObject(player, object, respawnId))
						{
							valid = false;
						}
					}
					
					if (valid)
					{
						ResetRespawnObjectOwner(respawnId, player.GetCachedID(), player.GetTerjeProfile());
						
						if (objectItemBase != null)
						{
							objectItemBase.SetTerjeRespawnOwner(player);
						}
						
						player.GetTerjeProfile().SetRespawnObjectData(respawnId, classname, metadata, objectPos, playerPos, playerOri);
						result += 1;
					}
				}
			}
		}
		
		return (result > 0);
	}
	
	string GetObjectRespawnMetadata(Object object, PlayerBase player)
	{
		return string.Empty;
	}
	
	void SetLastLocalObject(Object obj)
	{
		if (GetGame() && GetGame().IsClient())
		{
			m_lastLocalObject = obj;
		}
	}
	
	Object GetLastLocalObject()
	{
		if (GetGame() && GetGame().IsClient())
		{
			return m_lastLocalObject;
		}
		
		return null;
	}
	
	protected TerjeXmlObject FindTerjeXmlObjectServer(string respawnId, string classname)
	{
		TerjeXmlObject result;
		map<string, TerjeXmlObject> submap;
		if (m_idsToXmlObjects.Find(respawnId, submap))
		{
			if (submap && submap.Find(classname, result))
			{
				return result;
			}
		}
		
		return null;
	}
}

PluginTerjeRespawnObjects GetPluginTerjeRespawnObjects() 
{
	return PluginTerjeRespawnObjects.Cast(GetPlugin(PluginTerjeRespawnObjects));
}