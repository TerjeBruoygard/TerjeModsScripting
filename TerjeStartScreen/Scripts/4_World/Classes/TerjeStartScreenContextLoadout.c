// <copyright file="TerjeStartScreenContextLoadout.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenContextLoadout : TerjeStartScreenContextBase
{
	ref TerjeXmlObject m_inputLoadouts = new TerjeXmlObject;
	ref TerjeXmlObject m_outputSelectedLoadout = new TerjeXmlObject;
	
	override string GetPageName()
	{
		return "loadout";
	}
	
	override bool Serialize(Serializer ctx)
	{
		if (!super.Serialize(ctx))
			return false;
		
		if (!m_inputLoadouts.Binarize(ctx))
			return false;
		
		if (!m_outputSelectedLoadout.Binarize(ctx))
			return false;
		
		return true;
	}
	
	override bool Deserialize(Serializer ctx)
	{
		if (!super.Deserialize(ctx))
			return false;
		
		if (!m_inputLoadouts.Unbinarize(ctx))
			return false;
		
		if (!m_outputSelectedLoadout.Unbinarize(ctx))
			return false;
		
		return true;
	}
	
	override void Build(PlayerBase player)
	{
		super.Build(player);
		GetPluginTerjeStartScreen().BuildLoadoutsForPlayer(player, m_inputLoadouts);
	}
	
	override void Apply(PlayerBase player)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
		
	protected void ApplyLoadoutSelectorHandler(PlayerBase player, string loadoutId, TerjeXmlObject selectorRoot, TerjeXmlObject selectorItem)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
}