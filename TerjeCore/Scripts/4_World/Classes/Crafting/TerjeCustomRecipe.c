// <copyright file="TerjeCustomRecipe.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeCustomRecipe : RecipeBase
{	
	const string TERJE_RECIPE_BLOCKED_TITLE = "#STR_TERJECORE_CRAFT_BLOCK";
	const string TERJE_RECIPE_BLOCKED_ICON = "set:dayz_gui image:icon_lock";
	protected ref TerjeXmlObject m_terjeRecipeData = null;
	protected bool m_terjeCheckServerConditions = false;
	
	void InitTerjeIngredient(int index, TerjeXmlObject xmlIngredient)
	{
		string xmlValue;
		if (xmlIngredient.FindAttribute("singleUse", xmlValue))
		{
			m_IngredientDestroy[index] = (xmlValue == "1");
		}
		else
		{
			m_IngredientDestroy[index] = false;
		}
		
		if (xmlIngredient.FindAttribute("minQuantity", xmlValue))
		{
			m_MinQuantityIngredient[index] = xmlValue.ToFloat();
		}
		else
		{
			m_MinQuantityIngredient[index] = -1;
		}
		
		if (xmlIngredient.FindAttribute("maxQuantity", xmlValue))
		{
			m_MaxQuantityIngredient[index] = xmlValue.ToFloat();
		}
		else
		{
			m_MaxQuantityIngredient[index] = -1;
		}
		
		if (xmlIngredient.FindAttribute("minDamage", xmlValue))
		{
			m_MinDamageIngredient[index] = xmlValue.ToFloat();
		}
		else
		{
			m_MinDamageIngredient[index] = -1;
		}
		
		if (xmlIngredient.FindAttribute("maxDamage", xmlValue))
		{
			m_MaxDamageIngredient[index] = xmlValue.ToFloat();
		}
		else
		{
			m_MaxDamageIngredient[index] = -1;
		}
		
		if (xmlIngredient.FindAttribute("addHealth", xmlValue))
		{
			m_IngredientAddHealth[index] = xmlValue.ToFloat();
		}
		else
		{
			m_IngredientAddHealth[index] = 0;
		}
		
		if (xmlIngredient.FindAttribute("setHealth", xmlValue))
		{
			m_IngredientSetHealth[index] = xmlValue.ToFloat();
		}
		else
		{
			m_IngredientSetHealth[index] = -1;
		}
		
		if (xmlIngredient.FindAttribute("addQuantity", xmlValue))
		{
			m_IngredientAddQuantity[index] = xmlValue.ToFloat();
		}
		else
		{
			m_IngredientAddQuantity[index] = 0;
		}
		
		for (int i = 0; i < xmlIngredient.GetChildrenCount(); i++)
		{
			TerjeXmlObject xmlItem = xmlIngredient.GetChild(i);
			if ((xmlItem != null) && (xmlItem.GetName() == "Item") && (xmlItem.HasValue()))
			{
				InsertIngredient(index, xmlItem.GetValue());
			}
		}
	}
	
	void InitTerjeResult(TerjeXmlObject xmlResult)
	{
		if (!xmlResult.HasValue())
		{
			return;
		}
		
		string xmlValue;
		int index = m_NumberOfResults;
		AddResult(xmlResult.GetValue());
		
		if (xmlResult.FindAttribute("setFullQuantity", xmlValue))
		{
			m_ResultSetFullQuantity[index] = (xmlValue == "1");
		}
		else
		{
			m_ResultSetFullQuantity[index] = false;
		}
		
		if (xmlResult.FindAttribute("setQuantity", xmlValue))
		{
			m_ResultSetQuantity[index] = xmlValue.ToFloat();
		}
		else
		{
			m_ResultSetQuantity[index] = -1;
		}
		
		if (xmlResult.FindAttribute("setHealth", xmlValue))
		{
			m_ResultSetHealth[index] = xmlValue.ToFloat();
		}
		else
		{
			m_ResultSetHealth[index] = -1;
		}
		
		if (xmlResult.FindAttribute("inheritsHealth", xmlValue))
		{
			m_ResultInheritsHealth[index] = xmlValue.ToInt();
		}
		else
		{
			m_ResultInheritsHealth[index] = -1;
		}
		
		if (xmlResult.FindAttribute("inheritsColor", xmlValue))
		{
			m_ResultInheritsColor[index] = xmlValue.ToInt();
		}
		else
		{
			m_ResultInheritsColor[index] = -1;
		}
		
		if (xmlResult.FindAttribute("spawnMode", xmlValue))
		{
			m_ResultToInventory[index] = xmlValue.ToInt();
		}
		else
		{
			m_ResultToInventory[index] = -2;
		}
		
		m_ResultReplacesIngredient[index] = -1;
	}
	
	void InitTerjeCustomRecipeData(TerjeXmlObject xmlRecipe)
	{
		m_terjeRecipeData = xmlRecipe;
		
		string xmlValue;
		if (xmlRecipe.FindAttribute("displayName", xmlValue))
		{
			m_Name = xmlValue;
		}
		else
		{
			m_Name = "UNKNOWN RECIPE";
		}
		
		if (xmlRecipe.FindAttribute("time", xmlValue))
		{
			m_AnimationLength = xmlValue.ToFloat();
			if (m_AnimationLength < 0)
			{
				m_AnimationLength = 0;
				m_IsInstaRecipe = true;
			}
			else
			{
				m_IsInstaRecipe = false;
			}
		}
		else
		{
			m_AnimationLength = 0;
			m_IsInstaRecipe = true;
		}
		
		TerjeXmlObject xmlFirstIngredient = xmlRecipe.GetChildByNodeName("FirstIngredient");
		if (xmlFirstIngredient != null)
		{
			InitTerjeIngredient(0, xmlFirstIngredient);
		}
		
		TerjeXmlObject xmlSecondIngredient = xmlRecipe.GetChildByNodeName("SecondIngredient");
		if (xmlSecondIngredient != null)
		{
			InitTerjeIngredient(1, xmlSecondIngredient);
		}
		
		TerjeXmlObject xmlResults = xmlRecipe.GetChildByNodeName("CraftingResults");
		if (xmlResults != null)
		{
			for (int i = 0; i < xmlResults.GetChildrenCount(); i++)
			{
				TerjeXmlObject xmlResult = xmlResults.GetChild(i);
				if ((xmlResult != null) && (xmlResult.IsObjectNode()) && (xmlResult.GetName() == "Result"))
				{
					InitTerjeResult(xmlResult);
				}
			}
		}
	}
	
	bool CheckTerjeServerConditions(ItemBase item1, ItemBase item2, PlayerBase player, out string errorMessage)
	{
		bool result = true;
		errorMessage = string.Empty;
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			TerjeXmlObject conditions = m_terjeRecipeData.GetChildByNodeName("Conditions");
			if (conditions != null)
			{
				TerjePlayerConditions filter = TerjePlayerConditions.GetInstance();
				for (int i = 0; i < conditions.GetChildrenCount(); i++)
				{
					TerjeXmlObject condition = conditions.GetChild(i);
					if ((condition != null) && (condition.IsObjectNode()))
					{
						string resultMessage = string.Empty;
						if (!filter.ProcessCondition(player, condition, resultMessage))
						{
							result = false;
							if (resultMessage != string.Empty)
							{
								if (errorMessage != string.Empty)
								{
									errorMessage = errorMessage + "<br/>";
								}
								
								errorMessage = errorMessage + resultMessage;
							}
						}
					}
				}
			}
		}
		
		return result;
	}
	
	override void Init()
	{
	
	}
	
	override void PerformRecipe(ItemBase item1, ItemBase item2, PlayerBase player)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			m_terjeCheckServerConditions = true;
		}
		
		super.PerformRecipe(item1, item2, player);
	}
	
	override bool CheckRecipe(ItemBase item1, ItemBase item2, PlayerBase player)
	{
		bool requestCheck = m_terjeCheckServerConditions;
		m_terjeCheckServerConditions = false;
		
		if (super.CheckRecipe(item1, item2, player))
		{
			string errorMessage;
			if (requestCheck && !CheckTerjeServerConditions(item1, item2, player, errorMessage))
			{
				NotificationSystem.SendNotificationToPlayerExtended(player, 5, TERJE_RECIPE_BLOCKED_TITLE, errorMessage, TERJE_RECIPE_BLOCKED_ICON);
				return false;
			}
			
			return true;
		}
		
		return false;
	}
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return (m_terjeRecipeData != null) && (m_terjeRecipeData.EqualAttribute("enabled", "1"));
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			TerjeXmlObject conditions = m_terjeRecipeData.GetChildByNodeName("Conditions");
			if (conditions != null)
			{
				TerjePlayerConditions filter = TerjePlayerConditions.GetInstance();
				for (int i = 0; i < conditions.GetChildrenCount(); i++)
				{
					TerjeXmlObject condition = conditions.GetChild(i);
					if ((condition != null) && (condition.IsObjectNode()))
					{
						filter.ApplyCondition(player, condition);
					}
				}
			}
		}
	}
}