// <copyright file="DayZGame.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class DayZGame
{
	bool __OBF_WATERMARK_STATE = false;
	
	override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (rpc_type == 67963732)
		{
			GetTerjeRPC().HandleRPC(sender, target, ctx);
			return;
		}
		else if (rpc_type == 67963733)
		{
			OnTerjeSynchSettingsFromServer(ctx);
			return;
		}
		else if (rpc_type == 67693732)
		{
			__OBF_WATERMARK_STATE = true;
			return;
		}
		
		super.OnRPC(sender, target, rpc_type, ctx);
	}
	
	protected void OnTerjeSynchSettingsFromServer(ParamsReadContext ctx)
	{
		GetTerjeGameConfig().OnReceiveClientSettings(ctx);
		GetTerjeSettingsSynchContext().OnReceiveClientSettings(ctx);
	}
}