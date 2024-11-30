// <copyright file="ActionSkinning.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ActionSkinning
{
	override void HandlePlayerBody(ActionData action_data)
	{
		super.HandlePlayerBody(action_data);
		
		PlayerBase body;
		if (Class.CastTo(body, action_data.m_Target.GetObject()))
		{
			if (action_data.m_Player && action_data.m_Player.GetTerjeStats())
			{
				float mindDegValue = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PLAYER_SKINNING_MIND_DEG_VALUE);
				float mindDegTime = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PLAYER_SKINNING_MIND_DEG_TIME);
				action_data.m_Player.GetTerjeStats().AddMindDegradation(mindDegValue, mindDegTime);
			}
		}
	}
}