// <copyright file="TerjeSyringeFill.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSyringeFill extends RecipeBase
{
	override void Init()
	{
		m_Name = "#fill";
		m_IsInstaRecipe = true;//should this recipe be performed instantly without animation
		m_Specialty = -0.02;// value > 0 for roughness, value < 0 for precision
		
		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[0] = -1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check
		
		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[1] = 1;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------
		
		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0,"TerjeSyringeEmpty");//you can insert multiple ingredients this way

		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = 0;// 0 = do nothing
		m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		
		//ingredient 2
		InsertIngredient(1,"TerjeAmpouleBase");//you can insert multiple ingredients this way
		
		m_IngredientAddHealth[1] = 0;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0;// 0 = do nothing
		m_IngredientDestroy[1] = false;// false = do nothing
		m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		//----------------------------------------------------------------------------------------------------------------------
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player) //final check for recipe's validity
	{
		return true;
	}

	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		TerjeSyringeEmpty syringeItem = TerjeSyringeEmpty.Cast(ingredients[0]);
		ItemBase ampouleItem = ingredients[1];
		
		if (syringeItem && ampouleItem)
		{
			TerjeSyringeFillLambda lambda = new TerjeSyringeFillLambda(syringeItem, syringeItem.GetTerjeSyringeClassnameFull(), player);
			lambda.InitValues(ampouleItem);
			MiscGameplayFunctions.TurnItemIntoItemEx(player, lambda);
		}
	}
}

class TerjeSyringeFillLambda : TurnItemIntoItemLambda
{
	ItemBase m_medSolutionItem;
	
	void InitValues(ItemBase medSolutionItem)
	{
		m_medSolutionItem = medSolutionItem;
	}
	
	override void CopyOldPropertiesToNew (notnull EntityAI old_item, EntityAI new_item)
	{
		super.CopyOldPropertiesToNew(old_item, new_item);
		new_item.SetHealth01("", "", old_item.GetHealth01());
		new_item.SetCleanness(old_item.GetCleanness());
	}
	
	override void OnSuccess (EntityAI new_item)
	{
		super.OnSuccess(new_item);
		
		TerjeSyringeFull syringeFull = TerjeSyringeFull.Cast(new_item);
		if (syringeFull)
		{
			syringeFull.UpdateSyringeData(m_medSolutionItem.GetType());
			
			if (m_medSolutionItem.HasQuantity())
			{
				m_medSolutionItem.AddQuantity(-1,true);
			}
			else
			{
				m_medSolutionItem.Delete();
			}
		}
	} 
}
