// <copyright file="EmoteManager.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class EmoteManager
{
	int GetCurrentEmoteID()
	{
		return m_CurrentGestureID;
	}
	
	int GetTotalEmotesCount()
	{
		return m_NameEmoteMap.Count();
	}
	
	int GetEmoteKeyById(int emoteId)
	{
		return m_NameEmoteMap.GetKey(emoteId);
	}
	
	bool IsPlayerSleeping()
	{
		return GetCurrentEmoteID() == EmoteConstants.ID_EMOTE_LYINGDOWN;
	}
	
	override void Update( float deltaT )
	{
		super.Update(deltaT);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_MIND_USE_COMMIT_SUICIDE))
		{
			if ( m_Player && m_Callback && m_Player.GetTerjeStats() != null && !m_Player.IsRestrained() )
			{
				if (m_CurrentGestureID == EmoteConstants.ID_EMOTE_SUICIDE && m_Player.GetTerjeStats().GetMindLevel() == 5)
				{
					if (m_Callback.GetState() == m_Callback.STATE_LOOP_LOOP)
					{
						CommitSuicide();
					}
				}
			}
		}
	}
}