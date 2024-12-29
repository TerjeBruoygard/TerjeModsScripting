// <copyright file="ZombieBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ZombieBase
{
	bool AddTerjeRadiation(float rAmount)
	{
		// Universal interface to insert radiation agents into the entity.
		// Implemented in TerjeRadiation mod.
		return false;
	}
	
	float GetTerjeRadiation()
	{
		// Universal interface to get radiation agents from the entity.
		// Implemented in TerjeRadiation mod.
		return 0;
	}
	
	bool IsTerjeRadiationAccumulated()
	{
		// Can entity accumulate radiation inside
		return false;
	}
	
	void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		// A safe context for writing to the server database without the risk of corruption when changing the order of mods.
	}
	
	void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		// A safe context for reading from the server database without the risk of corruption when changing the order of mods.
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		TerjeStorageHelpers.SetActualTerjeStorageVersion();
		if (TerjeStorageHelpers.GetTerjeStorageVersion() == 1)
		{
			TerjeStorageWritingContext terjeStorageCtx();
			OnTerjeStoreSave(terjeStorageCtx);
			terjeStorageCtx.OnStoreSave(ctx);
		}
		
		super.OnStoreSave(ctx);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		int terjeStorageVersion = TerjeStorageHelpers.GetTerjeStorageVersion();
		if (terjeStorageVersion == 1)
		{
			TerjeStorageReadingContext terjeStorageCtx();
			if (!terjeStorageCtx.OnStoreLoad(ctx))
			{
				return false;
			}
			
			OnTerjeStoreLoad(terjeStorageCtx);
		}
		
		return super.OnStoreLoad(ctx, version);
	}
}