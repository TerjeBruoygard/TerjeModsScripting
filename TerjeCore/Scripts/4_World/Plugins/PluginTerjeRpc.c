// <copyright file="PluginTerjeRpc.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeRpc : PluginBase 
{
	private ref map<string, ref Param2<Class, string>> m_RegisteredRPCs = new map<string, ref Param2<Class, string>>;
	private ref map<string, ref ScriptCaller> m_RegisteredRPCsEx = new map<string, ref ScriptCaller>;
	
	void PluginTerjeRpc() 
	{
		GetDayZGame().Event_OnRPC.Insert(ServerRPCHandler);
	}

	void ~PluginTerjeRpc() 
	{
		GetDayZGame().Event_OnRPC.Remove(ServerRPCHandler);
	}

	private void ServerRPCHandler(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) 
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	void RegisterHandler(string id, Class instance, string fnc)
	{
		if (m_RegisteredRPCs.Contains(id))
		{
			m_RegisteredRPCs.Remove(id);
		}
		
		m_RegisteredRPCs.Insert(id, new Param2<Class, string>(instance, fnc));
	}
	
	void RegisterHandlerEx(string id, ScriptCaller callback)
	{
		if (m_RegisteredRPCsEx.Contains(id))
		{
			m_RegisteredRPCsEx.Remove(id);
		}
		
		m_RegisteredRPCsEx.Insert(id, callback);
	}

	void SendToClient(string id, PlayerIdentity identity, Param params) 
	{
		if (GetGame().IsDedicatedServer())
		{
			array<ref Param> sendData();
			sendData.Insert(new Param1<string>(id));
			
			if (params != null)
			{
				sendData.Insert(params);
			}
			
			GetGame().RPC(null, 67963732, sendData, true, identity);
		}
	}
	
	void StreamToClient(string id, PlayerIdentity identity, out TerjeStreamRpc stream)
	{
		stream = new TerjeStreamRpc();
		stream.InitTerjeRpc(id, identity, TerjeStreamRpc_Target.TO_CLIENT);
	}
	
	void SendToServer(string id, Param params) 
	{
		if (!GetGame().IsDedicatedServer())
		{
			array<ref Param> sendData();
			sendData.Insert(new Param1<string>(id));
			
			if (params != null)
			{
				sendData.Insert(params);
			}
			
			GetGame().RPC(null, 67963732, sendData, true, null);
		}
	}
	
	void StreamToServer(string id, out TerjeStreamRpc stream)
	{
		stream = new TerjeStreamRpc();
		stream.InitTerjeRpc(id, null, TerjeStreamRpc_Target.TO_SERVER);
	}
	
	void SendToAll(string id, Param params) 
	{
		if (GetGame().IsDedicatedServer())
		{
			array<ref Param> sendData();
			sendData.Insert(new Param1<string>(id));
			
			if (params != null)
			{
				sendData.Insert(params);
			}
			
			GetGame().RPC(null, 67963732, sendData, true, null);
		}
	}
	
	void StreamToAll(string id, out TerjeStreamRpc stream)
	{
		stream = new TerjeStreamRpc();
		stream.InitTerjeRpc(id, null, TerjeStreamRpc_Target.TO_ALL);
	}
}

PluginTerjeRpc GetTerjeRPC() 
{
	return PluginTerjeRpc.Cast(GetPlugin(PluginTerjeRpc));
}