// <copyright file="Cooking.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class Cooking
{
	override void ProcessItemToCook(notnull ItemBase pItem, ItemBase cookingEquip, Param2<CookingMethodType, float> pCookingMethod, out Param2<bool, bool> pStateFlags)
	{
		super.ProcessItemToCook(pItem, cookingEquip, pCookingMethod, pStateFlags);
		
		if (GetGame().IsDedicatedServer() && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_MEDICAL_BOILING))
		{
			Bottle_Base bottleBase = Bottle_Base.Cast(cookingEquip);
			if (bottleBase && pItem && pItem.CanBeDisinfected())
			{
				float cookingEquipmentTemp = bottleBase.GetTemperature();
				int liquidType = bottleBase.GetLiquidType();
				if (liquidType != LIQUID_NONE && cookingEquipmentTemp >= Liquid.GetBoilThreshold(liquidType))
				{
					pItem.SetCleanness(1);
				}
			}
		}
	}
}