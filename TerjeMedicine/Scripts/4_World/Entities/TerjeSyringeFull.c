// <copyright file="TerjeSyringeFull.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeSyringeFull extends Inventory_Base
{
	private string m_medSolution;
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		m_medSolution = "";
	}
	
	override void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		super.OnTerjeStoreSave(ctx);
		ctx.WriteString("medSolution", m_medSolution);
	}
	
	override void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		super.OnTerjeStoreLoad(ctx);
		ctx.ReadString("medSolution", m_medSolution);
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionEmptySyringe);
		AddAction(ActionInjectSyringeSelf);
		AddAction(ActionInjectSyringeTarget);
	}
	
	override bool CanBeDisinfected()
	{
		return false;
	}
	
	string GetMedSolutionClassname()
	{
		return m_medSolution;
	}
	
	void UpdateSyringeData(string solutionClassname)
	{
		m_medSolution = solutionClassname;
	}
	
	string GetTerjeSyringeClassnameEmpty()
	{
		return "TerjeSyringeEmpty";
	}
	
	float GetTerjeDamageOnUse()
	{
		return 5;
	}
	
	override void OnApply(PlayerBase player)
	{
		if (GetGame().IsDedicatedServer())
		{
			float perkValue;
			float operatorPerkSterilityMod = 1.0;
			PlayerBase operator = PlayerBase.Cast( this.GetHierarchyRootPlayer() ); 
			if (operator && operator.GetTerjeSkills() && operator.GetTerjeSkills().GetPerkValue("med", "cleanstr", perkValue))
			{
				operatorPerkSterilityMod = Math.Clamp(1.0 + perkValue, 0, 1);
			}
			
			float dirtySyringeSepsisChance = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SYRINGE_SEPSIS_CHANCE, dirtySyringeSepsisChance);	
			if (!IsDisinfected() && Math.RandomFloat01() < dirtySyringeSepsisChance * operatorPerkSterilityMod)
			{
				player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.1);
			}
			
			TerjeConsumableEffects medEffects = new TerjeConsumableEffects();
			if (medEffects && GetMedSolutionClassname() != "")
			{
				medEffects.Apply(this, "CfgVehicles " + GetMedSolutionClassname(), player, 1.0);
			}
			
			MiscGameplayFunctions.DealAbsoluteDmg(this, GetTerjeDamageOnUse());
		}
	}
}

class TerjeImprovisedSyringeFull : TerjeSyringeFull
{
	override string GetTerjeSyringeClassnameEmpty()
	{
		return "TerjeImprovisedSyringeEmpty";
	}
}