// <copyright file="TerjeCustomRecipe.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeCustomRecipe : RecipeBase
{	
	void InitTerjeIngredient(int index, TerjeCustomRecipeIngredient ingredient)
	{
		m_IngredientUseSoftSkills[index] = false;
		m_IngredientDestroy[index] = ingredient.DeleteRequired;
		m_MinDamageIngredient[index] = ingredient.MinDamage;
		m_MaxDamageIngredient[index] = ingredient.MaxDamage;
		m_MinQuantityIngredient[index] = ingredient.MinQuantity;
		m_MaxQuantityIngredient[index] = ingredient.MaxQuantity;
		m_IngredientAddHealth[index] = ingredient.AddHealth;
		m_IngredientSetHealth[index] = ingredient.SetHealth;
		m_IngredientAddQuantity[index] = ingredient.AddQuantity;
		
		if (ingredient.Items != null)
		{
			foreach (string item : ingredient.Items)
			{
				InsertIngredient(index, item);
			}
		}
	}
	
	void InitTerjeResult(TerjeCustomRecipeResult result)
	{
		int index = m_NumberOfResults;
		AddResult(result.Item);
		
		m_ResultSetFullQuantity[index] = result.SetFullQuantity;
		m_ResultSetQuantity[index] = result.SetQuantity;
		m_ResultSetHealth[index] = result.SetHealth;
		m_ResultInheritsHealth[index] = result.InheritsHealth;
		m_ResultInheritsColor[index] = result.InheritsColor;
		m_ResultToInventory[index] = result.ToInventory;
		m_ResultReplacesIngredient[index] = result.ReplacesIngredient;
		m_ResultUseSoftSkills[index] = false;
	}
	
	void InitTerjeCustomRecipeData(TerjeCustomRecipeData data)
	{
		if (data != null)
		{
			m_Name = data.Name;
			m_IsInstaRecipe = data.IsInstaRecipe;
			m_AnimationLength = data.AnimationLength;
			m_Specialty = 0;
			
			if (data.FirstIngredient != null)
			{
				InitTerjeIngredient(0, data.FirstIngredient);
			}
			
			if (data.SecondIngredient != null)
			{
				InitTerjeIngredient(1, data.SecondIngredient);
			}
			
			if (data.CraftingResults != null)
			{
				foreach (ref TerjeCustomRecipeResult result : data.CraftingResults)
				{
					if (result != null)
					{
						InitTerjeResult(result);
					}
				}
			}
		}
	}
	
	override void Init()
	{
	
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return true;
	}
}

class TerjeCustomRecipeData
{
	string Name = "";
	bool Enabled = false;
	bool IsInstaRecipe = false;
	float AnimationLength = 1.0;

	ref TerjeCustomRecipeIngredient FirstIngredient = new TerjeCustomRecipeIngredient;
	ref TerjeCustomRecipeIngredient SecondIngredient = new TerjeCustomRecipeIngredient;
	ref array<ref TerjeCustomRecipeResult> CraftingResults = new array<ref TerjeCustomRecipeResult>;
}

class TerjeCustomRecipeIngredient
{
	ref array<string> Items = new array<string>;
	bool DeleteRequired = true;
	float MinQuantity = -1;
	float MaxQuantity = -1;
	float MinDamage = -1;
	float MaxDamage = 3;
	float AddHealth = 0;
	float SetHealth = -1;
	float AddQuantity = 0;
}

class TerjeCustomRecipeResult
{
	string Item = string.Empty;
	bool SetFullQuantity = true;
	float SetQuantity = -1;
	float SetHealth = -1;
	int InheritsHealth = -1;
	int InheritsColor = -1;
	int ToInventory = -2;
	int ReplacesIngredient = -1;
}