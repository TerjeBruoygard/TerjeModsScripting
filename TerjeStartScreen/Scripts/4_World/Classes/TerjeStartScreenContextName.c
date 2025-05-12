// <copyright file="TerjeStartScreenContextName.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenContextName : TerjeStartScreenContextBase
{
	int m_inputLengthMin;
	int m_inputLengthMax;
	string m_inputAllowedCharacters;
	
	string m_outputFirstName;
	string m_outputLastName;
	
	override string GetPageName()
	{
		return "name";
	}
	
	override bool Serialize(Serializer ctx)
	{
		if (!super.Serialize(ctx))
			return false;
		
		if (!ctx.Write(m_inputLengthMin))
			return false;
		
		if (!ctx.Write(m_inputLengthMax))
			return false;
		
		if (!ctx.Write(m_inputAllowedCharacters))
			return false;
		
		if (!ctx.Write(m_outputFirstName))
			return false;
		
		if (!ctx.Write(m_outputLastName))
			return false;
		
		return true;
	}
	
	override bool Deserialize(Serializer ctx)
	{
		if (!super.Deserialize(ctx))
			return false;
		
		if (!ctx.Read(m_inputLengthMin))
			return false;
		
		if (!ctx.Read(m_inputLengthMax))
			return false;
		
		if (!ctx.Read(m_inputAllowedCharacters))
			return false;
		
		if (!ctx.Read(m_outputFirstName))
			return false;
		
		if (!ctx.Read(m_outputLastName))
			return false;
		
		return true;
	}
	
	override void Build(PlayerBase player)
	{
		super.Build(player);
		
		m_inputAllowedCharacters = GetPluginTerjeStartScreen().GetGeneralXmlValue("NamePageFilter", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		m_inputLengthMin = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_NAME_PAGE_LENGTH_MIN);
		m_inputLengthMax = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_NAME_PAGE_LENGTH_MAX);
	}
	
	override void Apply(PlayerBase player)
	{
		super.Apply(player);
		
		if (player && player.GetTerjeProfile() != null)
		{
			player.GetTerjeProfile().SetFirstName(m_outputFirstName);
			player.GetTerjeProfile().SetLastName(m_outputLastName);
			if (player.GetIdentity())
			{
				GetPluginTerjeStartScreen().CreateCharacterNameIndex(m_outputFirstName + " " + m_outputLastName, player.GetIdentity().GetId());
			}
			
			// Update synch cached name
			player.GetTerjeCharacterName();
		}
	}
}