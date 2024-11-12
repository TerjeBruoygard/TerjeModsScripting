// <copyright file="CAContinuousQuantityLiquidTransfer.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class CAContinuousQuantityLiquidTransfer
{
	override void CalcAndSetQuantity(ActionData action_data)
	{
		int quantity = m_SpentQuantity;
		super.CalcAndSetQuantity(action_data);
		
		ItemBase target_item = ItemBase.Cast(action_data.m_Target.GetObject());
		if (GetGame().IsDedicatedServer())
		{
			if (m_TendencyDrain)
			{
				TerjeCustomLiquids.GetInstance().FixVanillaTransfer(target_item, action_data.m_MainItem, quantity);
			}
			else
			{
				TerjeCustomLiquids.GetInstance().FixVanillaTransfer(action_data.m_MainItem, target_item, quantity);
			}
		}
	}
};