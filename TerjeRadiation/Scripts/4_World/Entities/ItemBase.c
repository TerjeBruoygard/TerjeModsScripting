// <copyright file="ItemBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class ItemBase
{
	private float m_terjeRadiationServer = 0;
	private int m_terjeRadiationSynch = 0;
	
	void ItemBase()
	{
		RegisterNetSyncVariableInt("m_terjeRadiationSynch", 0, TerjeRadiationConstants.RADIATION_ITEMS_ACCUMULATOR_SYNCH_MAX);
	}
	
	override bool AddTerjeRadiation(float rAmount)
	{
		if (GetGame().IsDedicatedServer() && IsTerjeRadiationAccumulated())
		{
			if (rAmount > 0)
			{
				rAmount *= Math.Clamp(1.0 - GetTerjeProtectionLevel("radiation"), 0, 1);
			}
			
			m_terjeRadiationServer = Math.Clamp(m_terjeRadiationServer + rAmount, 0, TerjeRadiationConstants.RADIATION_ITEMS_ACCUMULATOR_SERVER_MAX);
			
			int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_ITEMS_ACCUMULATOR_SYNCH_DIVIDER);
			if (newRadiationSynchValue != m_terjeRadiationSynch)
			{
				m_terjeRadiationSynch = newRadiationSynchValue;
				SetSynchDirty();
			}
			
			return true;
		}

		return false;
	};
	
	override float GetTerjeRadiation()
	{
		if (GetGame().IsDedicatedServer())
		{
			return m_terjeRadiationServer;
		}
		else
		{
			return m_terjeRadiationSynch * TerjeRadiationConstants.RADIATION_ITEMS_ACCUMULATOR_SYNCH_DIVIDER;
		}
	};
	
	override bool IsTerjeRadiationAccumulated()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_DO_ITEMS_ACCUMULATE);
	};
	
	override void ProcessVariables()
	{
		super.ProcessVariables();
		
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_terjeRadiationServer);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
		{
			return false;
		}
		
		if (!ctx.Read(m_terjeRadiationServer))
		{
			m_terjeRadiationServer = 0;
			return false;
		}
		
		return true;
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_ITEMS_ACCUMULATOR_SYNCH_DIVIDER);
		if (newRadiationSynchValue != m_terjeRadiationSynch)
		{
			m_terjeRadiationSynch = newRadiationSynchValue;
			SetSynchDirty();
		}
	}

	override void AddAction(typename actionName)
	{
		// Bind radiation cleaning action
		if (actionName == ActionDrainLiquid)
		{
			super.AddAction(ActionWashRadioactiveItems);
		}
		
		// Default
		super.AddAction(actionName);
	};
};