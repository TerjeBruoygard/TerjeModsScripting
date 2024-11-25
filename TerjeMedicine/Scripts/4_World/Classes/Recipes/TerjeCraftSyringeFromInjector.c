// <copyright file="TerjeCraftSyringeFromInjector.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeCraftSyringeFromInjector extends RecipeBase
{	
	override void Init()
	{
		m_Name = "#STR_TERJEMED_CRAFTSYRINGE0";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 1;//animation length in relative time units
		m_Specialty = -0.02;// value > 0 for roughness, value < 0 for precision
		
		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[0] = -1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check
		
		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[1] = -1;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------
		
		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0,"Sickle");
		InsertIngredient(0,"Hacksaw");
		InsertIngredient(0,"HandSaw");
		InsertIngredient(0,"KitchenKnife");
		InsertIngredient(0,"SteakKnife");
		InsertIngredient(0,"HayHook");
		InsertIngredient(0,"StoneKnife");
		InsertIngredient(0,"Cleaver");
		InsertIngredient(0,"CombatKnife");
		InsertIngredient(0,"HuntingKnife");
		InsertIngredient(0,"KukriKnife");
		InsertIngredient(0,"FangeKnife");
		InsertIngredient(0,"Machete");
		InsertIngredient(0,"CrudeMachete");
		InsertIngredient(0,"OrientalMachete");
		InsertIngredient(0,"Screwdriver");
		InsertIngredient(0,"Crowbar");
		InsertIngredient(0,"Pickaxe");
		InsertIngredient(0,"WoodAxe");
		InsertIngredient(0,"Hatchet");
		InsertIngredient(0,"FirefighterAxe");
		InsertIngredient(0,"Sword");
		InsertIngredient(0,"AK_Bayonet");
		InsertIngredient(0,"M9A1_Bayonet");
		InsertIngredient(0,"Mosin_Bayonet");
		InsertIngredient(0,"SKS_Bayonet");	
		InsertIngredient(0,"FarmingHoe");
		InsertIngredient(0,"Shovel");
		InsertIngredient(0,"FieldShovel");
		InsertIngredient(0,"BoneKnife");
		InsertIngredient(0,"Iceaxe");	
	
		m_IngredientAddHealth[0]			= -2;				// 0 = do nothing
		m_IngredientSetHealth[0]			= -1;				// -1 = do nothing
		m_IngredientAddQuantity[0]			= 0;				// 0 = do nothing
		m_IngredientDestroy[0]				= false;			// true = destroy, false = do nothing

		//ingredient 2
		InsertIngredient(1,"Inventory_Base");
		
		m_IngredientAddHealth[1] = 0;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0;// 0 = do nothing
		m_IngredientDestroy[1] = true;// false = do nothing
		//----------------------------------------------------------------------------------------------------------------------
		
		//result1
		AddResult("TerjeImprovisedSyringeEmpty");
		m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
		m_ResultSetQuantity[0] = -1;//-1 = do nothing
		m_ResultSetHealth[0] = -1;//-1 = do nothing
		m_ResultInheritsHealth[0] = 1;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
		m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		if (ingredients[1] && ingredients[1].ConfigGetBool("medicalInjectorsCategory"))
		{
			return true;
		}
		
		return false;
	}
}
