// <copyright file="PluginRecipesManager.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PluginRecipesManager
{
	private const string TERJE_CUSTOM_CRAFTS_DIR = "$profile:TerjeSettings\\CustomCrafting";
	ref TerjeXmlObject m_TerjeCustomServerRecipesData = null;
	ref TerjeXmlObject m_TerjeCustomClientRecipesData = null;
	
	override void OnInit()
	{
		super.OnInit();
		
		if (!GetGame())
			return;
		
		if (GetGame().IsDedicatedServer())
		{
			if (GetTerjeSettingBool(TerjeSettingsCollection.CORE_USE_CUSTOM_CRAFT_CONFIGS))
			{
				MakeDirectory(TERJE_CUSTOM_CRAFTS_DIR);
				
				string xmlPath = TERJE_CUSTOM_CRAFTS_DIR + "\\Recipes.xml";
				if (!FileExist(xmlPath))
				{
					CopyFile("TerjeCore\\Templates\\Recipes.xml", xmlPath);
				}
				
				if (FileExist(xmlPath))
				{
					TerjeXmlDocument xmlDocument();
					if (xmlDocument.DeserializeFromFile(xmlPath))
					{
						xmlDocument.DeleteComments(true);
						m_TerjeCustomServerRecipesData = xmlDocument.GetChildByNodeName("Recipes");
						m_TerjeCustomClientRecipesData = ConvertServerRecipesToClientRecipes(m_TerjeCustomServerRecipesData);
						RegisterTerjeCustomRecipes(m_TerjeCustomServerRecipesData);
					}
				}
			}
		}
		else
		{
			GetTerjeRPC().RegisterHandlerEx("core.crafts", ScriptCaller.Create(this.OnReceiveClientTerjeCustomRecipes));
		}
	}
	
	ref TerjeXmlObject ConvertServerRecipesToClientRecipes(TerjeXmlObject recipes)
	{
		if ((recipes != null) && (recipes.GetChildrenCount() > 0))
		{
			ref TerjeXmlObject result = new TerjeXmlObject;
			recipes.DeepCopy(result, true, false);
			for (int i = 0; i < result.GetChildrenCount(); i++)
			{
				TerjeXmlObject recipeNode = result.GetChild(i);
				if (recipeNode != null)
				{
					recipeNode.RemoveAllChildrenWithName("Conditions");
				}
			}
			
			return result;
		}
		
		return null;
	}
	
	void SendTerjeCustomRecipesToClient(PlayerIdentity identity)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if ((m_TerjeCustomClientRecipesData != null) && (m_TerjeCustomClientRecipesData.GetChildrenCount() > 0))
			{
				TerjeStreamRpc stream;
				GetTerjeRPC().StreamToClient("core.crafts", identity, stream);
				m_TerjeCustomClientRecipesData.Binarize(stream);
				stream.Flush();
			}
		}
	}
	
	void OnReceiveClientTerjeCustomRecipes(ParamsReadContext ctx, PlayerIdentity sender)
	{
		if (GetGame() && GetGame().IsClient() && (m_TerjeCustomClientRecipesData == null))
		{
			m_TerjeCustomClientRecipesData = new TerjeXmlObject;
			m_TerjeCustomClientRecipesData.Unbinarize(ctx);
			RegisterTerjeCustomRecipes(m_TerjeCustomClientRecipesData);
		}
	}
	
	void RegisterTerjeCustomRecipes(TerjeXmlObject recipes)
	{
		if ((recipes != null) && (recipes.GetChildrenCount() > 0))
		{
			int counter = 0;
			for (int i = 0; i < recipes.GetChildrenCount(); i++)
			{
				TerjeXmlObject recipeDataXml = recipes.GetChild(i);
				if ((recipeDataXml != null) && (recipeDataXml.IsObjectNode()) && (recipeDataXml.GetName() == "Recipe"))
				{
					ref TerjeCustomRecipe terjeCustomRecipe = new TerjeCustomRecipe();
					terjeCustomRecipe.InitTerjeCustomRecipeData(recipeDataXml);
					RegisterRecipe(terjeCustomRecipe);
					counter = counter + 1;
				}
			}
			
			GenerateRecipeCache();
			TerjeLog_Info("Registered " + counter + " custom recipes.");
		}
	}
	
	float GetTerjeRecipeTimeModifier(PlayerBase player, int recipe_id)
	{
		if ( m_RecipeList[recipe_id] )
		{
			return m_RecipeList[recipe_id].GetTerjeCraftingTimeModifier(player);
		}
		
		return 0;
	}
}

ref PluginRecipesManager GetTerjeCustomRecipesPlugin()
{
	return PluginRecipesManager.Cast(GetPlugin(PluginRecipesManager));
}