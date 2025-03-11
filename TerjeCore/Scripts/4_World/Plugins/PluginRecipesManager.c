// <copyright file="PluginRecipesManager.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class PluginRecipesManager
{
	private const string TERJE_CUSTOM_CRAFTS_DIR = "$profile:TerjeSettings\\CustomCrafting";
	ref array<ref TerjeCustomRecipeData> m_TerjeCustomRecipesData = null;
	
	override void OnInit()
	{
		super.OnInit();
		
		if (GetGame())
		{
			if (GetGame().IsDedicatedServer())
			{
				if (GetTerjeSettingBool(TerjeSettingsCollection.CORE_USE_CUSTOM_CRAFT_CONFIGS))
				{
					m_TerjeCustomRecipesData = new array<ref TerjeCustomRecipeData>;
					MakeDirectory(TERJE_CUSTOM_CRAFTS_DIR);
					ReadTerjeCustomRecipesData();
					
					if (m_TerjeCustomRecipesData.Count() == 0)
					{
						// Create default recipe
						ref TerjeCustomRecipeResult exampleResult = new TerjeCustomRecipeResult;
						exampleResult.Item = "UnknownFoodCan";
						
						ref TerjeCustomRecipeData exampleCraft = new TerjeCustomRecipeData;
						exampleCraft.Enabled = true;
						exampleCraft.Name = "Example craft";
						exampleCraft.FirstIngredient.Items.Insert("Apple");
						exampleCraft.SecondIngredient.Items.Insert("DuctTape");
						exampleCraft.CraftingResults.Insert(exampleResult);
						WriteTerjeCustomRecipeData(TERJE_CUSTOM_CRAFTS_DIR + "\\Example.json", exampleCraft);
						m_TerjeCustomRecipesData.Insert(exampleCraft);
					}
					
					RegisterTerjeCustomRecipes(m_TerjeCustomRecipesData);
					
					string wikiPath = TERJE_CUSTOM_CRAFTS_DIR + "\\README.md";
					if (FileExist(wikiPath))
					{
						DeleteFile(wikiPath);
					}
					
					FileHandle wikiFile = OpenFile(wikiPath, FileMode.WRITE);
					if (wikiFile != 0)
					{
						WriteTerjeCustomRecipesWiki(wikiFile);
						CloseFile(wikiFile);
					}
				}
			}
			else
			{
				GetTerjeRPC().RegisterHandler("core.crafts", this, "OnReceiveClientTerjeCustomRecipes");
			}
		}
	}
	
	void WriteTerjeCustomRecipesWiki(FileHandle file)
	{
		FPrintln(file, "# General");
		FPrintln(file, "You can create your own craft recipes on the server using this system.");
		FPrintln(file, "Each individual craft recipe must be in a separate file in this folder. The file names do not matter, but must have the `.json` extension.");
		FPrintln(file, "");
		FPrintln(file, "## Crafting recipes format");
		FPrintln(file, "");
		FPrintln(file, "> **Name**");
		FPrintln(file, "> The name of the recipe that will be displayed in the game. It is allowed to use localization tags defined in your `stringtable.csv`.");
		FPrintln(file, "");
		FPrintln(file, "> **Enabled**");
		FPrintln(file, "> Determines whether this recipe is enabled on the server. (0 - disabled, 1 - enabled)");
		FPrintln(file, "");
		FPrintln(file, "> **IsInstaRecipe**");
		FPrintln(file, "> Determines whether this recipe should be instant (0 - no, 1 - yes)");
		FPrintln(file, "");
		FPrintln(file, "> **AnimationLength**");
		FPrintln(file, "> Determines the time in seconds (floating number) required for the player to make this recipe (when `IsInstaRecipe` is off).");
		FPrintln(file, "");
		FPrintln(file, "> **FirstIngredient** and **SecondIngredient**");
		FPrintln(file, "> Two ingredients that must be combined in the game to produce a craft.");
		FPrintln(file, "> ");
		FPrintln(file, ">> **Items**");
		FPrintln(file, ">> List of class names of items that can be used as an ingredient. It is allowed to use base classes when needed.");
		FPrintln(file, ">");
		FPrintln(file, ">> **DeleteRequired**");
		FPrintln(file, ">> Determines whether the ingredient will be deleted after the end of the craft (0 - no, 1 - yes)");
		FPrintln(file, ">");
		FPrintln(file, ">> **MinQuantity**");
		FPrintln(file, ">> The minimum amount of the quantity needed to start crafting. Floating number equal or greater then 0. Use -1 to disable the check.");
		FPrintln(file, ">");
		FPrintln(file, ">> **MaxQuantity**");
		FPrintln(file, ">> The maximum possbile amount of the quantity to start crafting. Floating number equal or greater then 0. Use -1 to disable the check.");
		FPrintln(file, ">");
		FPrintln(file, ">> **MinDamage**");
		FPrintln(file, ">> The minimum damage of the ingredient needed to start crafting. Floating number equal or greater then 0. Use -1 to disable the check.");
		FPrintln(file, ">> *Important: this is not a health of the ingredient, but its state, where 0 is pristine, 1 is worn, 2 is damaged, 3 is badly damaged, 4 is ruined.*");
		FPrintln(file, ">");
		FPrintln(file, ">> **MaxDamage**");
		FPrintln(file, ">> The maximum possbile damage of the ingredient to start crafting. Floating number equal or greater then 0. Use -1 to disable the check.");
		FPrintln(file, ">> *Important: this is not a health of the ingredient, but its state, where 0 is pristine, 1 is worn, 2 is damaged, 3 is badly damaged, 4 is ruined.*");
		FPrintln(file, ">");
		FPrintln(file, ">> **AddHealth**");
		FPrintln(file, ">> Determines how much health will be added to the ingredient after the crafting is complete. Can be used to repair items if `DeleteRequired` is turned off. Floating number equal or greater then 0.");
		FPrintln(file, ">");
		FPrintln(file, ">> **SetHealth**");
		FPrintln(file, ">> Determines how much health will be set to the ingredient after the crafting is complete. Can be used to repair items if `DeleteRequired` is turned off. Floating number equal or greater then 0. Use -1 to disable this behaviour.");
		FPrintln(file, ">");
		FPrintln(file, ">> **AddQuantity**");
		FPrintln(file, ">> Determines how many units of quantity will be added to the ingredient after crafting is completed. Can be used to repair items if `DeleteRequired` is turned off. Floating number equal or greater then 0.");
		FPrintln(file, "");
		FPrintln(file, "> **CraftingResults**");
		FPrintln(file, "> List with crafting results (can be empty if necessary)");
		FPrintln(file, ">");
		FPrintln(file, ">> **Item**");
		FPrintln(file, ">> Class name of resulted item to be spawned.");
		FPrintln(file, ">");
		FPrintln(file, ">> **SetFullQuantity**");
		FPrintln(file, ">> Use 1 to set full quantity or 0 to do nothing.");
		FPrintln(file, ">");
		FPrintln(file, ">> **SetQuantity**");
		FPrintln(file, ">> Sets the specific quantity for the resulted item. Floating number equal or greater then 0. Use -1 to disable this behaviour.");
		FPrintln(file, ">");
		FPrintln(file, ">> **SetHealth**");
		FPrintln(file, ">> Sets the specific number of health for the resulted item. Floating number equal or greater then 0. Use -1 to disable this behaviour.");
		FPrintln(file, ">");
		FPrintln(file, ">> **InheritsHealth**");
		FPrintln(file, ">> Sets the specific behaviour for resulted items health. Use -1 to do nothing. Use -2 to this result will inherit health from all ingredients averaged. Or use 0 (first ingredient) or 1 (second ingredient) to this result will inherit health from the specific ingredient. ");
		FPrintln(file, ">");
		FPrintln(file, ">> **InheritsColor**");
		FPrintln(file, ">> Sets the specific behaviour for resulted items color. Use -1 to do nothing. Or use 0 (first ingredient) or 1 (second ingredient) to composite result classname for this result item and config value 'color' of ingredient.");
		FPrintln(file, ">");
		FPrintln(file, ">> **ToInventory**");
		FPrintln(file, ">> Sets the specific behaviour to determine spawning position for the resulting item. Use -2 to spawn result on the ground. Use -1 to place anywhere in the players inventory. Or use 0 (first ingredient) or 1 (second ingredient) to switch position with specific ingredient.");
		FPrintln(file, ">");
		FPrintln(file, ">> **ReplacesIngredient**");
		FPrintln(file, ">> Sets the specific behavior for determining the spawn properties for the resulting item. Use -1 to do nothing or use 0 (first ingredient) or 1 (second ingredient) to transfer item properties, attachments etc.. from an specific ingredient to this resulted item.");
	}
	
	void SendTerjeCustomRecipesToClient(PlayerIdentity identity)
	{
		if (m_TerjeCustomRecipesData != null && m_TerjeCustomRecipesData.Count() > 0)
		{
			GetTerjeRPC().SendToClient("core.crafts", identity, new Param1<ref array<ref TerjeCustomRecipeData>>(m_TerjeCustomRecipesData));
		}
	}
	
	void OnReceiveClientTerjeCustomRecipes(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param1<ref array<ref TerjeCustomRecipeData>> clientData;
		if (!ctx.Read(clientData))
		{
			return;
		}
		
		ref array<ref TerjeCustomRecipeData> recipes = clientData.param1;
		RegisterTerjeCustomRecipes(recipes);
	}
	
	void RegisterTerjeCustomRecipes(array<ref TerjeCustomRecipeData> recipes)
	{
		if (recipes != null && recipes.Count() > 0)
		{
			foreach (ref TerjeCustomRecipeData recipeData : recipes)
			{
				ref TerjeCustomRecipe terjeCustomRecipe = new TerjeCustomRecipe();
				terjeCustomRecipe.InitTerjeCustomRecipeData(recipeData);
				RegisterRecipe(terjeCustomRecipe);
			}
			
			GenerateRecipeCache();
			TerjeLog_Info("Registered " + recipes.Count() + " custom recipes.");
		}
	}
	
	void WriteTerjeCustomRecipeData(string path, TerjeCustomRecipeData data)
	{
		string errorMessage = "";
		if (!JsonFileLoader<TerjeCustomRecipeData>.SaveFile(path, data, errorMessage))
		{
			TerjeLog_Error("Failed to save json file " + path + "; Error: " + errorMessage);
		}
	}
	
	ref TerjeCustomRecipeData ReadTerjeCustomRecipeData(string path)
	{
		if (FileExist(path))
		{
			string errorMessage = "";
			ref TerjeCustomRecipeData result = new TerjeCustomRecipeData;
			if (JsonFileLoader<ref TerjeCustomRecipeData>.LoadFile(path, result, errorMessage))
			{
				return result;
			}
			else
			{
				TerjeLog_Error("Failed to load json file " + path + "; Error: " + errorMessage);
			}
		}
		else
		{
			TerjeLog_Error("File not found: " + path);
		}
		
		return null;
	}
	
	void ReadTerjeCustomRecipesData()
	{
		// Read custom recipes from disk
		ref TerjeCustomRecipeData recipe;
		string rootPath = TERJE_CUSTOM_CRAFTS_DIR + "\\*.json";
		string fileName;
		FileAttr fileAttrs;
		FindFileHandle findHandle = FindFile(rootPath, fileName, fileAttrs, FindFileFlags.DIRECTORIES);
		if (fileName.Length() > 0)
		{
			recipe = ReadTerjeCustomRecipeData(TERJE_CUSTOM_CRAFTS_DIR + "\\" + fileName);
			if (recipe != null && recipe.Enabled)
			{
				m_TerjeCustomRecipesData.Insert(recipe);
			}
		}
		
		while (FindNextFile(findHandle, fileName, fileAttrs))
		{
			if (fileName.Length() > 0)
			{
				recipe = ReadTerjeCustomRecipeData(TERJE_CUSTOM_CRAFTS_DIR + "\\" + fileName);
				if (recipe != null && recipe.Enabled)
				{
					m_TerjeCustomRecipesData.Insert(recipe);
				}
			}
		}
		
		CloseFindFile(findHandle);
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