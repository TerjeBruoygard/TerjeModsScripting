// <copyright file="TerjeStartScreenContextOverview.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenContextOverview : TerjeStartScreenContextBase
{
	bool m_allowDeletion = false;
	bool m_showSouls = false;
	string m_characterName;
	int m_soulsCount;
	
	override string GetPageName()
	{
		return "overview";
	}
	
	override bool Serialize(Serializer ctx)
	{
		if (!super.Serialize(ctx))
			return false;
		
		if (!ctx.Write(m_allowDeletion))
			return false;
		
		if (!ctx.Write(m_showSouls))
			return false;
		
		if (!ctx.Write(m_characterName))
			return false;
		
		if (!ctx.Write(m_soulsCount))
			return false;
		
		return true;
	}
	
	override bool Deserialize(Serializer ctx)
	{
		if (!super.Deserialize(ctx))
			return false;
		
		if (!ctx.Read(m_allowDeletion))
			return false;
		
		if (!ctx.Read(m_showSouls))
			return false;
		
		if (!ctx.Read(m_characterName))
			return false;
		
		if (!ctx.Read(m_soulsCount))
			return false;
		
		return true;
	}
	
	override void Build(PlayerBase player)
	{
		super.Build(player);
		
		m_allowDeletion = GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_OVERVIEW_PAGE_DEL);
		m_characterName = player.GetTerjeCharacterName();
		
		if ((player.GetTerjeSouls() != null) && (player.GetTerjeSouls().IsEnabled()))
		{
			m_showSouls = true;
			m_soulsCount = player.GetTerjeSouls().GetCount();
		}
	}
	
	override void Apply(PlayerBase player)
	{
		super.Apply(player);
	}
}