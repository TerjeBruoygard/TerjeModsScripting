// <copyright file="PluginTerjeStartScreen.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeStartScreen : PluginBase 
{
	private const string SETTINGS_DIR = "$profile:TerjeSettings\\StartScreen";
	private const string NAMES_STORAGE_DIR = "$mission:terje_storage\\names_index";
	
	private ref TerjeXmlObject m_generalXml = new TerjeXmlObject;
	private ref TerjeXmlObject m_facesXml = new TerjeXmlObject;
	private ref TerjeXmlObject m_loadoutsList = new TerjeXmlObject;
	private ref map<string, int> m_loadoutsSearch = new map<string, int>;
	private ref array<int> m_loadoutsOrdered = new array<int>;
	
	private ref TerjeXmlObject m_respawnsList = new TerjeXmlObject;
	private ref map<string, int> m_respawnsSearch = new map<string, int>;
	private ref array<int> m_respawnsOrdered = new array<int>;
	
	private ref TerjeEntitySpawner m_entitySpawner = new TerjeEntitySpawner;
	
	override void OnInit()
	{
		if (GetGame().IsDedicatedServer())
		{
			MakeDirectory(SETTINGS_DIR);
			MakeDirectory(NAMES_STORAGE_DIR);
			LoadGeneralXml();
			LoadFacesList();
			LoadLoadoutsList();
			LoadRespawnsList();
			GetTerjeRPC().RegisterHandler("startscreen.apply", this, "OnTerjeStartScreenContextApply");
			GetTerjeRPC().RegisterHandler("startscreen.done", this, "OnTerjeStartScreenContextDone");
			GetTerjeRPC().RegisterHandler("startscreen.name.verify", this, "OnTerjeStartScreenNameVerify");
			GetTerjeRPC().RegisterHandler("startscreen.loadout.equip", this, "OnTerjeStartScreenLoadoutEquip");
			GetTerjeRPC().RegisterHandler("startscreen.overview.del", this, "OnTerjeStartScreenOverviewDel");
		}
	}
	
	string GetGeneralXmlValue(string name, string defaultValue)
	{
		if (m_generalXml != null)
		{
			string attrValue;
			TerjeXmlObject node = m_generalXml.GetChildByNodeName(name);
			
			if ((node != null) && (node.FindAttribute("value", attrValue)))
			{
				return attrValue;
			}
		}
		
		return defaultValue;
	}
	
	void DeleteCharacterNameIndex(string fullName)
	{
		string path = NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName);
		if (FileExist(path))
		{
			DeleteFile(path);
		}
	}
	
	bool HasCharacterWithName(string fullName)
	{
		return FileExist(NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName));
	}
	
	bool FindCharacterByName(string fullName, out string steamGUID)
	{
		string path = NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName);
		
		steamGUID = string.Empty;
		if (FileExist(path))
		{
			FileHandle file = OpenFile(path, FileMode.READ);
			if (file != 0)
			{
				FGets(file, steamGUID);
				CloseFile(file);
			}
			
			return steamGUID.Length() > 0;
		}
		
		return false;
	}
	
	bool CreateCharacterNameIndex(string fullName, string steamGUID)
	{
		string path = NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName);
		FileHandle file = OpenFile(path, FileMode.WRITE);
		if (file != 0)
		{
			FPrint(file, steamGUID);
			CloseFile(file);
			return true;
		}
		
		return false;
	}
	
	bool DeleteCharacterNameIndex(string fullName, string steamGUID)
	{
		return DeleteFile(NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName));
	}
	
	void BuildFacesForPlayer(PlayerBase player, out TerjeXmlObject result)
	{
		result = new TerjeXmlObject;
		m_facesXml.DeepCopy(result, true, false);
	}
	
	void BuildLoadoutsForPlayer(PlayerBase player, out TerjeXmlObject result)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void BuildRespawnsForPlayer(PlayerBase player, out TerjeXmlObject result)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	TerjeXmlObject GetLoadoutById(string id)
	{
		int result;
		if (m_loadoutsSearch.Find(id, result))
		{
			return m_loadoutsList.GetChild(result);
		}
		
		return null;
	}
	
	TerjeXmlObject GetRespawnById(string id)
	{
		int result;
		if (m_respawnsSearch.Find(id, result))
		{
			return m_respawnsList.GetChild(result);
		}
		
		return null;
	}
	
	private void SetLoadoutDefaultSelections(PlayerBase player, string loadoutId, TerjeXmlObject loadout, string lastLoadoutSelections)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	private bool SetLoadoutDefaultSelection(PlayerBase player, string loadoutId, int selectionIndex, TerjeXmlObject selector, string selectionPart)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	private bool SetLoadoutSelectionPoints(PlayerBase player, string loadoutId, int selectionIndex, TerjeXmlObject selector)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	private bool ValidateLoadoutNode(TerjeXmlObject loadout)
	{
		if (loadout == null)
		{
			return false;
		}
		
		if (!loadout.IsObjectNode())
		{
			return false;
		}
		
		if (loadout.GetName() != "Loadout")
		{
			return false;
		}
		
		if (!loadout.HasAttribute("id") || loadout.EqualAttribute("id", string.Empty))
		{
			TerjeLog_Error("Loadout 'id' attribute is missing.");
			return false;
		}
		
		if (!loadout.HasAttribute("displayName") || loadout.EqualAttribute("displayName", string.Empty))
		{
			TerjeLog_Error("Loadout 'displayName' attribute is missing.");
			return false;
		}
		
		return true;
	}
	
	private bool ValidateRespawnNode(TerjeXmlObject respawn)
	{
		if (respawn == null)
		{
			return false;
		}
		
		if (!respawn.IsObjectNode())
		{
			return false;
		}
		
		if (respawn.GetName() != "Respawn")
		{
			return false;
		}
		
		if (!respawn.HasAttribute("id") || respawn.EqualAttribute("id", string.Empty))
		{
			TerjeLog_Error("Respawn 'id' attribute is missing.");
			return false;
		}
		
		if (!respawn.HasAttribute("displayName") || respawn.EqualAttribute("displayName", string.Empty))
		{
			TerjeLog_Error("Respawn 'displayName' attribute is missing.");
			return false;
		}
		
		TerjeXmlObject objects = respawn.GetChildByNodeName("Objects");
		if (objects != null)
		{
			if (objects.GetChildrenCount() > 0)
			{
				return true;
			}
			else
			{
				TerjeLog_Error("'Objects' node cannot be empty.");
				return false;
			}
		}
		
		TerjeXmlObject points = respawn.GetChildByNodeName("Points");
		if (points != null)
		{
			if (points.GetChildrenCount() > 0)
			{
				return true;
			}
			else
			{
				TerjeLog_Error("'Points' node cannot be empty.");
				return false;
			}
		}
		
		TerjeLog_Error("Respawn must contain 'Points' or 'Objects' node.");
		return false;
	}
	
	private bool ProcessConditions(PlayerBase player, TerjeXmlObject conditions, out bool valid)
	{
		valid = true;
		if (conditions != null)
		{
			TerjePlayerConditions filter();
			for (int condId = 0; condId < conditions.GetChildrenCount(); condId++)
			{
				TerjeXmlObject condition = conditions.GetChild(condId);
				if (condition.IsObjectNode())
				{
					if (filter.ProcessCondition(player, condition))
					{
						condition.SetAttribute("$valid", "1");
					}
					else
					{
						valid = false;
						condition.SetAttribute("$valid", "0");
						if (condition.EqualAttribute("hideOwnerWhenFalse", "1"))
						{
							return false;
						}
					}
				}
			}
		}
		
		return true;
	}
	
	private void OnTerjeStartScreenNameVerify(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param1<string> received;
		if (!ctx.Read(received))
			return;
		
		string fullName = received.param1;
		bool result = !HasCharacterWithName(fullName);
		
		Param1<bool> payload = new Param1<bool>(result);
		GetTerjeRPC().SendToClient("startscreen.name.verify", sender, payload);
	}
	
	private void OnTerjeStartScreenOverviewDel(ParamsReadContext ctx, PlayerIdentity sender)
	{
		if (!sender)
			return;
		
		PlayerBase player = FindPlayerByIdentity(sender);
		if (!player)
			return;
		
		player.m_terjeStartScreenParams = null;
		player.SetTerjeServerStartScreenImmunity(false);
		player.SetTerjeMaintenanceMode(true);
		player.SetHealth("", "", 0);
		GetTerjeDatabase().DeletePlayerProfile(sender.GetId());
	}
	
	private void OnTerjeStartScreenLoadoutEquip(ParamsReadContext ctx, PlayerIdentity sender)
	{
		PlayerBase player = FindPlayerByIdentity(sender);
		if (!player)
			return;
		
		if (!player.m_terjeStartScreenParams)
			return;
		
		TerjeStartScreenContextLoadout loadoutContext = TerjeStartScreenContextLoadout.Cast(player.m_terjeStartScreenParams.GetContext(TerjeStartScreenContextLoadout));
		if (!loadoutContext)
			return;
		
		if (!loadoutContext.m_inputLoadouts)
			return;
		
		TerjeXmlObject clientLoadout();
		if (!clientLoadout.Unbinarize(ctx))
			return;
		
		string loadoutId;
		if (!clientLoadout.FindAttribute("id", loadoutId))
			return;
		
		TerjeXmlObject serverLoadout = loadoutContext.m_inputLoadouts.GetChildByAttrPair("Loadout", "id", loadoutId);
		if (!serverLoadout)
			return;
		
		if (!CompareClientAndServerLoadoutObjects(clientLoadout, serverLoadout))
		{
			TerjeLog_Warning("Server and client loadouts missmatch. Possible hacker: " + sender.GetId());
			GetGame().DisconnectPlayer(sender, sender.GetId());
			return;
		}
		
		TerjeXmlObject clientItems = clientLoadout.GetChildByNodeName("Items");
		if (!clientItems)
			return;
		
		TerjeXmlObject serverItems = serverLoadout.GetChildByNodeName("Items");
		if (!serverItems)
			return;
		
		clientItems.DeepCopy(serverItems, true, false);
		StartLoadoutItemsEquip(player, sender, serverItems);
	}
	
	private bool CompareClientAndServerLoadoutObjects(TerjeXmlObject clientLoadout, TerjeXmlObject serverLoadout)
	{
		if (clientLoadout.GetName() != serverLoadout.GetName())
		{
			return false;
		}
		
		if (!CompareClientAndServerXmlAttribute(clientLoadout, serverLoadout, "classname"))
		{
			return false;
		}
		
		if (!CompareClientAndServerXmlAttribute(clientLoadout, serverLoadout, "type"))
		{
			return false;
		}
		
		if (!CompareClientAndServerXmlAttribute(clientLoadout, serverLoadout, "cost"))
		{
			return false;
		}
		
		if (!CompareClientAndServerXmlAttribute(clientLoadout, serverLoadout, "$points"))
		{
			return false;
		}
		
		if (clientLoadout.GetChildrenCount() != serverLoadout.GetChildrenCount())
		{
			return false;
		}
		
		for (int i = 0; i < clientLoadout.GetChildrenCount(); i++)
		{
			if (!CompareClientAndServerLoadoutObjects(clientLoadout.GetChild(i), serverLoadout.GetChild(i)))
			{
				return false;
			}
		}
		
		return true;
	}
	
	private bool CompareClientAndServerXmlAttribute(TerjeXmlObject clientXml, TerjeXmlObject serverXml, string attrName)
	{
		string serverValue;
		if (serverXml.FindAttribute(attrName, serverValue))
		{
			string clientValue;
			if (!clientXml.FindAttribute(attrName, clientValue))
			{
				return false;
			}
			
			if (serverValue != clientValue)
			{
				return false;
			}
		}
		
		return true;
	}
	
	private void OnTerjeStartScreenContextApply(ParamsReadContext ctx, PlayerIdentity sender)
	{
		string type;
		if (!ctx.Read(type))
			return;
		
		ref TerjeStartScreenContextBase context = TerjeStartScreenContextBase.Cast(type.ToType().Spawn());
		if (context == null)
			return;
		
		if (!context.Deserialize(ctx))
			return;
		
		PlayerBase player = FindPlayerByIdentity(sender);
		if (player)
		{
			context.Apply(player);
		}
		
		Param1<int> payload = new Param1<int>(0);
		GetTerjeRPC().SendToClient("startscreen.apply.callback", sender, payload);
	}
	
	private void OnTerjeStartScreenContextDone(ParamsReadContext ctx, PlayerIdentity sender)
	{
		PlayerBase player = FindPlayerByIdentity(sender);
		if (player)
		{
			player.SetTerjeServerStartScreenImmunity(false);
			if (player.m_terjeStartScreenParams != null)
			{
				player.m_terjeStartScreenParams.OnServerDone(player);
			}
			
			player.m_terjeStartScreenParams = null;
			player.SetSynchDirty();
			
			if (player.GetTerjeStats() != null)
			{
				player.GetTerjeStats().SetStartScreenInProgress(false);
			}
			
			if (player.IsAlive())
			{
				TerjeStreamRpc stream;
				GetTerjeRPC().StreamToClient("startscreen.close", sender, stream);
				WriteTerjeStartScreenContextDone(player, stream);
				stream.Flush();
			}
		}
	}
	
	private void WriteTerjeStartScreenContextDone(PlayerBase player, TerjeStreamRpc stream)
	{
		stream.Write(player.GetPosition());
		stream.Write(player.GetOrientation());
	}
	
	private PlayerBase FindPlayerByIdentity(PlayerIdentity identity)
	{
		array<Man> players();
		GetGame().GetPlayers(players);
		foreach (Man man : players)
		{
			if (man && man.GetIdentity() && man.GetIdentity().GetId() == identity.GetId())
			{
				return PlayerBase.Cast(man);
			}
		}
		
		return null;
	}
	
	private void LoadGeneralXml()
	{
		string generalXmlPath = SETTINGS_DIR + "\\General.xml";
		if (!FileExist(generalXmlPath))
		{
			CopyFile("TerjeStartScreen\\Templates\\General.xml", generalXmlPath);
		}
		
		TerjeXmlDocument generalXmlDoc();
		if (generalXmlDoc.DeserializeFromFile(generalXmlPath))
		{
			generalXmlDoc.DeleteComments();
			
			int generalNodeIndex = generalXmlDoc.FindChildIndexByNodeName("General");
			if (generalNodeIndex != -1)
			{
				m_generalXml = generalXmlDoc.GetChild(generalNodeIndex);
			}
		}
	}
	
	private void LoadFacesList()
	{
		string facesXmlPath = SETTINGS_DIR + "\\Faces.xml";
		if (!FileExist(facesXmlPath))
		{
			CopyFile("TerjeStartScreen\\Templates\\Faces.xml", facesXmlPath);
		}
		
		TerjeXmlDocument facesXmlDoc();
		if (facesXmlDoc.DeserializeFromFile(facesXmlPath))
		{
			facesXmlDoc.DeleteComments();
			
			int facesNodeIndex = facesXmlDoc.FindChildIndexByNodeName("Faces");
			if (facesNodeIndex != -1)
			{
				m_facesXml = facesXmlDoc.GetChild(facesNodeIndex);
			}
			else
			{
				TerjeLog_Error("Failed to find 'Faces' root tag in " + facesXmlPath);
			}
		}
		else
		{
			TerjeLog_Error("Failed to load " + facesXmlPath);
		}
	}
	
	private void LoadLoadoutsList()
	{
		string loadoutsXmlPath = SETTINGS_DIR + "\\Loadouts.xml";
		if (!FileExist(loadoutsXmlPath))
		{
			CopyFile("TerjeStartScreen\\Templates\\Loadouts.xml", loadoutsXmlPath);
		}
		
		m_loadoutsSearch.Clear();
		m_loadoutsOrdered.Clear();
		TerjeXmlDocument loadoutsXmlDoc();
		if (loadoutsXmlDoc.DeserializeFromFile(loadoutsXmlPath))
		{
			loadoutsXmlDoc.DeleteComments();
			
			int nodeIndex = loadoutsXmlDoc.FindChildIndexByNodeName("Loadouts");
			if (nodeIndex != -1)
			{
				m_loadoutsList = loadoutsXmlDoc.GetChild(nodeIndex);
				
				for (int i = 0; i < m_loadoutsList.GetChildrenCount(); i++)
				{
					TerjeXmlObject loadoutObj = m_loadoutsList.GetChild(i);
					if (ValidateLoadoutNode(loadoutObj))
					{
						string loadoutId;
						if (loadoutObj.FindAttribute("id", loadoutId) && !m_loadoutsSearch.Contains(loadoutId))
						{
							m_loadoutsSearch.Insert(loadoutId, i);
							m_loadoutsOrdered.Insert(i);
						}
						else
						{
							TerjeLog_Error("Loadout id '" + loadoutId + "' duplicated.");
						}
					}
				}
			}
			else
			{
				TerjeLog_Error("Failed to find 'Loadouts' root tag in " + loadoutsXmlPath);
			}
		}
		else
		{
			TerjeLog_Error("Failed to load " + loadoutsXmlPath);
		}
	}
	
	private void LoadRespawnsList()
	{
		string respawnsXmlPath = SETTINGS_DIR + "\\Respawns.xml";
		if (!FileExist(respawnsXmlPath))
		{
			string worldName = GetGame().GetWorldName();
			if (FileExist("TerjeStartScreen\\Templates\\Respawns_" + worldName + ".xml"))
			{
				CopyFile("TerjeStartScreen\\Templates\\Respawns_" + worldName + ".xml", respawnsXmlPath);
			}
			else
			{
				CopyFile("TerjeStartScreen\\Templates\\Respawns_chernarusplus.xml", respawnsXmlPath);
			}
		}
		
		m_respawnsSearch.Clear();
		m_respawnsOrdered.Clear();
		TerjeXmlDocument respawnsXmlDoc();
		if (respawnsXmlDoc.DeserializeFromFile(respawnsXmlPath))
		{
			respawnsXmlDoc.DeleteComments();
			
			int nodeIndex = respawnsXmlDoc.FindChildIndexByNodeName("Respawns");
			if (nodeIndex != -1)
			{
				m_respawnsList = respawnsXmlDoc.GetChild(nodeIndex);
				
				for (int i = 0; i < m_respawnsList.GetChildrenCount(); i++)
				{
					TerjeXmlObject respawnObj = m_respawnsList.GetChild(i);
					if (ValidateRespawnNode(respawnObj))
					{
						string respawnId;
						if (respawnObj.FindAttribute("id", respawnId) && !m_respawnsSearch.Contains(respawnId))
						{
							m_respawnsSearch.Insert(respawnId, i);
							m_respawnsOrdered.Insert(i);
							
							TerjeXmlObject objects = respawnObj.GetChildByNodeName("Objects");
							if (objects != null)
							{
								GetPluginTerjeRespawnObjects().RegisterRespawnObjects(respawnId, objects);
							}
						}
						else
						{
							TerjeLog_Error("Respawn id '" + respawnId + "' duplicated.");
						}
					}
				}
			}
			else
			{
				TerjeLog_Error("Failed to find 'Respawns' root tag in " + respawnsXmlPath);
			}
		}
		else
		{
			TerjeLog_Error("Failed to load " + respawnsXmlPath);
		}
	}
	
	private void StartLoadoutItemsEquip(PlayerBase player, PlayerIdentity sender, TerjeXmlObject itemsObject)
	{
		if (!sender || !player || !player.IsAlive())
			return;
		
		if (itemsObject == null)
			return;
		
		if (player.m_terjeLoadoutProcessing)
			return;
		
		player.m_terjeLoadoutProcessing = true;
		player.ClearInventory();
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(EndLoadoutItemsEquip, player, sender, itemsObject);
	}
	
	private void EndLoadoutItemsEquip(PlayerBase player, PlayerIdentity sender, TerjeXmlObject itemsObject)
	{
		if (!sender || !player || !player.IsAlive())
			return;
		
		if (itemsObject == null)
			return;
		
		for (int i = 0; i < itemsObject.GetChildrenCount(); i++)
		{
			ProcessLoadoutItemEquip(itemsObject.GetChild(i), player, 0);
		}
		
		player.SetSynchDirty();
		player.m_terjeLoadoutProcessing = false;
		Param1<int> payload = new Param1<int>(0);
		GetTerjeRPC().SendToClient("startscreen.loadout.ready", sender, payload);
	}
	
	private bool ProcessLoadoutItemEquip(TerjeXmlObject xmlObject, EntityAI target, bool depth)
	{
		if ((xmlObject != null) && (xmlObject.IsObjectNode()))
		{
			if (xmlObject.GetName() == "Item")
			{
				return (m_entitySpawner.SpawnInInventoryFromXml(xmlObject, target) != null);
			}
			else if (xmlObject.GetName() == "Selector")
			{
				if ((xmlObject.GetChildrenCount() > 0) && (depth == 0))
				{
					return ProcessLoadoutSelectorEquip(xmlObject, target, depth + 1);
				}
			}
			else if (xmlObject.GetName() == "Group")
			{
				bool result = true;
				for (int groupChildId = 0; groupChildId < xmlObject.GetChildrenCount(); groupChildId++)
				{
					if (!ProcessLoadoutItemEquip(xmlObject.GetChild(groupChildId), target, depth + 1))
					{
						result = false;
					}
				}
				
				return result;
			}
		}
		
		return false;
	}
	
	private bool ProcessLoadoutSelectorEquip(TerjeXmlObject xmlObject, EntityAI target, bool depth)
	{
		if (xmlObject.EqualAttribute("type", "MULTIPLE"))
		{
			string pointsStr;
			if (xmlObject.FindAttribute("$points", pointsStr))
			{
				int pointsCount = pointsStr.ToInt();
				for (int multId = 0; multId < xmlObject.GetChildrenCount(); multId++)
				{
					string costStr;
					TerjeXmlObject multChild = xmlObject.GetChild(multId);
					if (multChild != null && multChild.EqualAttribute("$selected", "1") && multChild.FindAttribute("cost", costStr))
					{
						int costInt = costStr.ToInt();
						if (costInt >= 0)
						{
							pointsCount -= costInt;
							if (pointsCount >= 0)
							{
								ProcessLoadoutItemEquip(multChild, target, depth);
							}
						}
					}
				}
				
				return true;
			}
		}
		
		for (int singleId = 0; singleId < xmlObject.GetChildrenCount(); singleId++)
		{
			TerjeXmlObject singleChild = xmlObject.GetChild(singleId);
			if (singleChild != null && singleChild.EqualAttribute("$selected", "1"))
			{
				return ProcessLoadoutItemEquip(singleChild, target, depth);
			}
		}
		
		return false;
	}
}

PluginTerjeStartScreen GetPluginTerjeStartScreen() 
{
	return PluginTerjeStartScreen.Cast(GetPlugin(PluginTerjeStartScreen));
}