// <copyright file="TerjeStartScreenContextFace.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenContextFace : TerjeStartScreenContextBase
{
	ref TerjeXmlObject m_inputFacesXml = new TerjeXmlObject;
	
	string m_outputClassname;
	
	override string GetPageName()
	{
		return "face";
	}
	
	override bool Serialize(Serializer ctx)
	{
		if (!super.Serialize(ctx))
			return false;
		
		if (!m_inputFacesXml.Binarize(ctx))
			return false;
		
		if (!ctx.Write(m_outputClassname))
			return false;
		
		return true;
	}
	
	override bool Deserialize(Serializer ctx)
	{
		if (!super.Deserialize(ctx))
			return false;
		
		if (!m_inputFacesXml.Unbinarize(ctx))
			return false;
		
		if (!ctx.Read(m_outputClassname))
			return false;
		
		return true;
	}
	
	override void Build(PlayerBase player)
	{
		super.Build(player);
		
		GetPluginTerjeStartScreen().BuildFacesForPlayer(player, m_inputFacesXml);
	}
	
	override void Apply(PlayerBase player)
	{
		super.Apply(player);
		
		if (player && player.GetTerjeProfile() != null)
		{
			player.GetTerjeProfile().SetCharacterClassname(m_outputClassname);
			player.m_terjeStartScreenParams = null;
			player.SetTerjeServerStartScreenImmunity(false);
			
			if (player.GetTerjeSouls() != null)
			{
				// Lock souls to do not lose on force respawn
				player.GetTerjeSouls().SetLocked(true);
			}
			
			player.SetHealth("", "", 0);
		}
	}
}