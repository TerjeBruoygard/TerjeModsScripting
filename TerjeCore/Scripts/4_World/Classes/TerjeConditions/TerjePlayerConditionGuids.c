// <copyright file="TerjePlayerConditionGuids.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjePlayerConditionGuids : TerjePlayerConditionBase
{
	override bool Validate(PlayerBase player, TerjeXmlObject condition)
	{
		if (player && player.GetIdentity())
		{
			string playerSteamId = player.GetIdentity().GetId();
			string playerPlainId = player.GetIdentity().GetPlainId();
			for (int specificPlayerId = 0; specificPlayerId < condition.GetChildrenCount(); specificPlayerId++)
			{
				TerjeXmlObject specificPlayerNode = condition.GetChild(specificPlayerId);
				if (specificPlayerNode.IsObjectNode() && (specificPlayerNode.GetName() == "SpecificPlayer"))
				{
					string steamGUID;
					if (specificPlayerNode.FindAttribute("steamGUID", steamGUID))
					{
						if ((playerSteamId == steamGUID) || (playerPlainId == steamGUID))
						{
							return true;
						}
					}
				}
			}
		}
		
		return false;
	}
	
	override string GetText(PlayerBase player, TerjeXmlObject condition)
	{
		return "#STR_TERJECORE_COND_SP";
	}
}