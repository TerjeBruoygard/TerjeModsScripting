// <copyright file="TerjeStartScreenContextFace.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenContextFace : TerjeStartScreenContextBase
{
	ref TerjeXmlObject m_inputFacesXml = new TerjeXmlObject;
	ref TerjeXmlObject m_selectedFaceXml = new TerjeXmlObject;
	
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
		
		if (!m_selectedFaceXml.Binarize(ctx))
			return false;
		
		return true;
	}
	
	override bool Deserialize(Serializer ctx)
	{
		if (!super.Deserialize(ctx))
			return false;
		
		if (!m_inputFacesXml.Unbinarize(ctx))
			return false;
		
		if (!m_selectedFaceXml.Unbinarize(ctx))
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
		
		string classname;
		if (!m_selectedFaceXml.FindAttribute("classname", classname))
		{
			return;
		}
		
		TerjeXmlObject conditionsXml = m_selectedFaceXml.GetChildByNodeName("Conditions");
		if (conditionsXml != null)
		{
			TerjePlayerConditions playerConds = TerjePlayerConditions.GetInstance();
			for (int condId = 0; condId < conditionsXml.GetChildrenCount(); condId++)
			{
				TerjeXmlObject condXml = conditionsXml.GetChild(condId);
				if (condXml != null && condXml.IsObjectNode())
				{
					playerConds.ApplyCondition(player, condXml);
				}
			}
		}
		
		if (player && player.GetTerjeProfile() != null)
		{
			player.GetTerjeProfile().SetCharacterClassname(classname);
			player.m_terjeStartScreenParams = null;
			player.SetTerjeServerStartScreenImmunity(false);
			player.SetTerjeMaintenanceMode(true);
			player.SetHealth("", "", 0);
		}
	}
}