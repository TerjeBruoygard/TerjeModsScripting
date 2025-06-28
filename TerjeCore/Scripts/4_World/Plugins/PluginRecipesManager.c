// <copyright file="PluginRecipesManager.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PluginRecipesManager
{
	private const string TERJE_CUSTOM_CRAFTS_DIR = "$profile:TerjeSettings\\CustomCrafting";
	ref TerjeXmlObject m_TerjeCustomRecipesData = null;
	
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
					// TODO: Remove later
					MigrateTerjeCustomRecipesData(xmlPath);
				}
				
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
						m_TerjeCustomRecipesData = xmlDocument.GetChildByNodeName("Recipes");
						RegisterTerjeCustomRecipes();
					}
				}
			}
		}
		else
		{
			GetTerjeRPC().RegisterHandlerEx("core.crafts", ScriptCaller.Create(this.OnReceiveClientTerjeCustomRecipes));
		}
	}
	
	void SendTerjeCustomRecipesToClient(PlayerIdentity identity)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if ((m_TerjeCustomRecipesData != null) && (m_TerjeCustomRecipesData.GetChildrenCount() > 0))
			{
				TerjeStreamRpc stream;
				GetTerjeRPC().StreamToClient("core.crafts", identity, stream);
				m_TerjeCustomRecipesData.Binarize(stream);
				stream.Flush();
			}
		}
	}
	
	void OnReceiveClientTerjeCustomRecipes(ParamsReadContext ctx, PlayerIdentity sender)
	{
		if (GetGame() && GetGame().IsClient())
		{
			m_TerjeCustomRecipesData = new TerjeXmlObject;
			m_TerjeCustomRecipesData.Unbinarize(ctx);
			RegisterTerjeCustomRecipes();
		}
	}
	
	void RegisterTerjeCustomRecipes()
	{
		if ((m_TerjeCustomRecipesData != null) && (m_TerjeCustomRecipesData.GetChildrenCount() > 0))
		{
			int counter = 0;
			for (int i = 0; i < m_TerjeCustomRecipesData.GetChildrenCount(); i++)
			{
				TerjeXmlObject recipeDataXml = m_TerjeCustomRecipesData.GetChild(i);
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
	
	bool MigrateTerjeCustomRecipeData(TerjeXmlObject migratedRecipes, string path)
	{
		// Migrate custom recipes from jsons
		// TODO: Remove in the future
		if (FileExist(path))
		{
			string errorMessage = "";
			TerjeCustomRecipeData result();
			if (JsonFileLoader<ref TerjeCustomRecipeData>.LoadFile(path, result, errorMessage))
			{
				TerjeXmlObject xmlRecipe = migratedRecipes.CreateChild("Recipe");
				xmlRecipe.SetAttribute("displayName", result.Name);
				
				if (result.Enabled)
				{
					xmlRecipe.SetAttribute("enabled", "1");
				}
				else
				{
					xmlRecipe.SetAttribute("enabled", "0");
				}
				
				if (!result.IsInstaRecipe && result.AnimationLength > 0)
				{
					xmlRecipe.SetAttribute("time", result.AnimationLength.ToString());
				}
				
				MigrateTerjeCustomRecipesDataIngredient(xmlRecipe.CreateChild("FirstIngredient"), result.FirstIngredient);
				MigrateTerjeCustomRecipesDataIngredient(xmlRecipe.CreateChild("SecondIngredient"), result.SecondIngredient);
				
				TerjeXmlObject xmlResults = xmlRecipe.CreateChild("CraftingResults");
				if (result.CraftingResults)
				{
					foreach (TerjeCustomRecipeResult jsonResult : result.CraftingResults)
					{
						MigrateTerjeCustomRecipesDataResult(xmlResults.CreateChild("Result"), jsonResult);
					}
				}
				
				DeleteFile(path);
				return true;
			}
		}
		
		return false;
	}
	
	void MigrateTerjeCustomRecipesDataIngredient(TerjeXmlObject xmlIngredient, TerjeCustomRecipeIngredient jsonIngredient)
	{
		// Migrate custom recipes from jsons
		// TODO: Remove in the future
		if (jsonIngredient.Items != null)
		{
			foreach (string item : jsonIngredient.Items)
			{
				xmlIngredient.CreateChild("Item").SetValue(item);
			}
		}
		
		if (jsonIngredient.DeleteRequired)
		{
			xmlIngredient.SetAttribute("singleUse", "1");
		}
		
		if (jsonIngredient.MinQuantity >= 0)
		{
			xmlIngredient.SetAttribute("minQuantity", jsonIngredient.MinQuantity.ToString());
		}
		
		if (jsonIngredient.MaxQuantity >= 0)
		{
			xmlIngredient.SetAttribute("maxQuantity", jsonIngredient.MaxQuantity.ToString());
		}
		
		if (jsonIngredient.MinDamage >= 0)
		{
			xmlIngredient.SetAttribute("minDamage", ((int)jsonIngredient.MinDamage).ToString());
		}
		
		if (jsonIngredient.MaxDamage >= 0)
		{
			xmlIngredient.SetAttribute("maxDamage", ((int)jsonIngredient.MaxDamage).ToString());
		}
		
		if (jsonIngredient.AddHealth > 0)
		{
			xmlIngredient.SetAttribute("addHealth", jsonIngredient.AddHealth.ToString());
		}
		
		if (jsonIngredient.SetHealth >= 0)
		{
			xmlIngredient.SetAttribute("setHealth", jsonIngredient.SetHealth.ToString());
		}
		
		if (jsonIngredient.AddQuantity > 0)
		{
			xmlIngredient.SetAttribute("addQuantity", jsonIngredient.AddQuantity.ToString());
		}
	}
	
	void MigrateTerjeCustomRecipesDataResult(TerjeXmlObject xmlResult, TerjeCustomRecipeResult jsonResult)
	{
		// Migrate custom recipes from jsons
		// TODO: Remove in the future
		
		if (jsonResult.SetFullQuantity)
		{
			xmlResult.SetAttribute("setFullQuantity", "1");
		}
		
		if (jsonResult.SetQuantity >= 0)
		{
			xmlResult.SetAttribute("setQuantity", jsonResult.SetQuantity.ToString());
		}
		
		if (jsonResult.SetHealth >= 0)
		{
			xmlResult.SetAttribute("setHealth", jsonResult.SetHealth.ToString());
		}
		
		if (jsonResult.InheritsHealth != -1)
		{
			xmlResult.SetAttribute("inheritsHealth", jsonResult.InheritsHealth.ToString());
		}
		
		if (jsonResult.InheritsColor != -1)
		{
			xmlResult.SetAttribute("inheritsColor", jsonResult.InheritsColor.ToString());
		}
		
		if (jsonResult.ToInventory != -2)
		{
			xmlResult.SetAttribute("spawnMode", jsonResult.ToInventory.ToString());
		}
		
		xmlResult.SetValue(jsonResult.Item);
	}
	
	void MigrateTerjeCustomRecipesData(string xmlPath)
	{
		// Migrate custom recipes from jsons
		// TODO: Remove in the future
		int counter = 0;
		TerjeXmlDocument migratedXmlDoc();
		if (!migratedXmlDoc.DeserializeFromFile("TerjeCore\\Templates\\Recipes.xml"))
		{
			return;
		}
		
		TerjeXmlObject migratedRecipes = migratedXmlDoc.GetChildByNodeName("Recipes");
		if (!migratedRecipes)
		{
			return;
		}
		
		migratedRecipes.ClearChildren();
		
		ref TerjeCustomRecipeData recipe;
		string rootPath = TERJE_CUSTOM_CRAFTS_DIR + "\\*.json";
		string fileName;
		FileAttr fileAttrs;
		FindFileHandle findHandle = FindFile(rootPath, fileName, fileAttrs, FindFileFlags.DIRECTORIES);
		if (findHandle != 0)
		{
			if (fileName.Length() > 0)
			{
				if (MigrateTerjeCustomRecipeData(migratedRecipes, TERJE_CUSTOM_CRAFTS_DIR + "\\" + fileName))
				{
					counter++;
				}
				
				while (FindNextFile(findHandle, fileName, fileAttrs))
				{
					if ((fileName.Length() > 0) && MigrateTerjeCustomRecipeData(migratedRecipes, TERJE_CUSTOM_CRAFTS_DIR + "\\" + fileName))
					{
						counter++;
					}
				}
			}
			
			CloseFindFile(findHandle);
		}
		
		if (counter > 0)
		{
			migratedXmlDoc.SerializeToFile(xmlPath);
			DeleteFile(TERJE_CUSTOM_CRAFTS_DIR + "\\README.md");
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