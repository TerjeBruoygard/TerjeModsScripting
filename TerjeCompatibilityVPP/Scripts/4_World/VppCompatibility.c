// <copyright file="VppCompatibility.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PermissionManager
{
	override void OnInit()
	{
		AddPermissionType({"TerjePlayerManager"});
		super.OnInit();
	}
}

modded class PlayerManager
{
	override void HealPlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type == CallType.Server)
		{
			Param1<ref array<string>> data;
			if (!ctx.Read(data)) 
			{
				return;
			}
			
			string adminID  = sender.GetPlainId();
			if (GetPermissionManager().VerifyPermission(adminID, "PlayerManager:HealPlayers"))
			{
				foreach (string id : data.param1)
				{
					PlayerBase targetPlayer = GetPermissionManager().GetPlayerBaseByID(id);
					if (targetPlayer != null)
					{
						GetTerjeAdmintoolSupport().OnHeal(targetPlayer);
					}
				}
			}
			
			ScriptReadWriteContext copyctx = new ScriptReadWriteContext;
			copyctx.GetWriteContext().Write(data);
			super.HealPlayers(type, copyctx.GetReadContext(), sender, target);
		}
	}
}

modded class HealPlayerChatModule
{
	override void ExecuteCommand(PlayerBase caller, array<Man> targets, array<string> args)
	{
		super.ExecuteCommand(caller, targets, args);
		
		if (caller && caller.GetIdentity())
		{
			string adminID = caller.GetIdentity().GetPlainId();
			if (GetPermissionManager().VerifyPermission(adminID, "PlayerManager:HealPlayers"))
			{
				foreach (Man target : targets)
				{
					PlayerBase playerTarget = PlayerBase.Cast(target);
					if (playerTarget != null)
					{
						GetTerjeAdmintoolSupport().OnHeal(playerTarget);
					}
				}
			}
		}
	}
}