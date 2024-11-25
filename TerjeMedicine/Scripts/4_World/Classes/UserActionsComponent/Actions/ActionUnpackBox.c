// <copyright file="ActionUnpackBox.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class UnboxLambda
{
	override void CopyOldPropertiesToNew (notnull EntityAI old_item, EntityAI new_item)
	{
		super.CopyOldPropertiesToNew(old_item, new_item);
		
		ItemBase oldItemBase;
		ItemBase newItemBase;
		if (ItemBase.CastTo(oldItemBase, old_item) && ItemBase.CastTo(newItemBase, new_item) && oldItemBase.IsDisinfected())
		{
			newItemBase.SetCleanness(1);
		}
	}
}