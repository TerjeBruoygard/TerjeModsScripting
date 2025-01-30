// <copyright file="PluginTerjeRpc.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class PluginTerjeRpc : PluginBase 
{
	private ref map<string, ref Param2<Class, string>> m_RegisteredRPCs = new map<string, ref Param2<Class, string>>;
	
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

	void SendToClient(string id, PlayerIdentity identity, ref Param params) 
	{
		if (GetGame().IsDedicatedServer())
		{
			auto sendData = new ref array< ref Param >;
			sendData.Insert(new ref Param1<string>( id ));
			sendData.Insert(params);
			GetGame().RPC(null, 67963732, sendData, true, identity);
		}
	}
	
	void SendToServer(string id, ref Param params) 
	{
		if (!GetGame().IsDedicatedServer())
		{
			auto sendData = new ref array< ref Param >;
			sendData.Insert(new ref Param1<string>( id ));
			sendData.Insert(params);
			GetGame().RPC(null, 67963732, sendData, true, null);
		}
	}
	
	void SendToAll(string id, ref Param params) 
	{
		if (GetGame().IsDedicatedServer())
		{
			auto sendData = new ref array< ref Param >;
			sendData.Insert(new ref Param1<string>( id ));
			sendData.Insert(params);
			GetGame().RPC(null, 67963732, sendData, true, null);
		}
	}
}

PluginTerjeRpc GetTerjeRPC() 
{
	return PluginTerjeRpc.Cast(GetPlugin(PluginTerjeRpc));
}