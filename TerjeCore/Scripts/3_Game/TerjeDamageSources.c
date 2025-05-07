// <copyright file="TerjeDamageSources.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeDamageSource
{
	protected string m_id;
	
	void TerjeDamageSource(string id)
	{
		m_id = id;
	}
	
	string GetId()
	{
		return m_id;
	}
	
	static ref TerjeDamageSource CreateDamageSource(string id)
	{
		return new TerjeDamageSource(id);
	}
	
	static ref TerjeDamageSource CONSUMABLE_EFFECT = CreateDamageSource("CONSUMABLE_EFFECT");
	static ref TerjeDamageSource HUNGER = CreateDamageSource("HUNGER");
	static ref TerjeDamageSource THIRST = CreateDamageSource("THIRST");
	static ref TerjeDamageSource BLEEDING = CreateDamageSource("BLEEDING");
}