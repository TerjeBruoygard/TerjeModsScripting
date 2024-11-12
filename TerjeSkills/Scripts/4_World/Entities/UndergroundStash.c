// <copyright file="UndergroundStash.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class UndergroundStash
{
	private bool m_terjeStashInvisible = false;
	
	void UndergroundStash()
	{
		RegisterNetSyncVariableBool("m_terjeStashInvisible");
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		ctx.Write(m_terjeStashInvisible);		
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{   
		if (!super.OnStoreLoad(ctx, version))
			return false;
		
		if (!ctx.Read(m_terjeStashInvisible))
			m_terjeStashInvisible = false;
		
		return true;
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		SetInvisible(m_terjeStashInvisible);
	}
	
	void SetTerjeStashInvisible(bool state)
	{
		if (GetGame().IsDedicatedServer())
		{
			m_terjeStashInvisible = state;
			SetSynchDirty();
		}
	}
	
	bool GetTerjeStashInvisible()
	{
		return m_terjeStashInvisible;
	}
};