// <copyright file="TerjeStreamRpc.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStreamRpc : ScriptRPC
{
	TerjeStreamRpc_Target m_Target = TerjeStreamRpc_Target.INVALID;
	PlayerIdentity m_Identity = null;
	
	void InitTerjeRpc(string id, PlayerIdentity identity, TerjeStreamRpc_Target target)
	{
		ref Param1<string> metaData = new Param1<string>(id);
		Write(metaData);
		
		m_Identity = identity;
		m_Target = target;
	}
	
	void Flush()
	{
		if (m_Target == TerjeStreamRpc_Target.TO_CLIENT)
		{
			if (m_Identity != null && GetGame().IsDedicatedServer())
			{
				Send(null, 67963732, true, m_Identity);
			}
		}
		else if (m_Target == TerjeStreamRpc_Target.TO_SERVER)
		{
			if (!GetGame().IsDedicatedServer())
			{
				Send(null, 67963732, true, null);
			}
		}
		else if (m_Target == TerjeStreamRpc_Target.TO_ALL)
		{
			if (GetGame().IsDedicatedServer())
			{
				Send(null, 67963732, true, null);
			}
		}
	}
}

enum TerjeStreamRpc_Target
{
	INVALID, TO_CLIENT, TO_SERVER, TO_ALL
}