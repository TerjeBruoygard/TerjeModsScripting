// <copyright file="TerjeStartScreenParams.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenParams
{
	ref array<ref TerjeStartScreenContextBase> m_contexts = new array<ref TerjeStartScreenContextBase>;
	
	bool Serialize(Serializer ctx)
	{
		if (!ctx.Write(m_contexts.Count()))
			return false;
		
		foreach (ref TerjeStartScreenContextBase context : m_contexts)
		{
			if (!ctx.Write(context.Type().ToString()))
				return false;
			
			if (!context.Serialize(ctx))
				return false;
		}
		
		return true;
	}
		
	bool Deserialize(Serializer ctx)
	{
		int count;
		if (!ctx.Read(count))
			return false;
		
		for (int i = 0; i < count; i++)
		{
			string type;
			if (!ctx.Read(type))
				return false;
			
			typename typeName = type.ToType();
			if (!typeName)
				return false;
			
			if (!typeName.IsInherited(TerjeStartScreenContextBase))
				return false;
			
			ref TerjeStartScreenContextBase context = TerjeStartScreenContextBase.Cast(typeName.Spawn());
			if (context == null)
				return false;
			
			if (!context.Deserialize(ctx))
				return false;
			
			m_contexts.Insert(context);
		}
		
		return true;
	}
	
	void Build(PlayerBase player)
	{
	
	}
	
	void Apply(PlayerBase player)
	{
		foreach (ref TerjeStartScreenContextBase context : m_contexts)
		{
			context.Apply(player);
		}
	}
	
	TerjeStartScreenContextBase GetContext(typename name)
	{
		if (m_contexts != null)
		{
			foreach (ref TerjeStartScreenContextBase context : m_contexts)
			{
				if (context != null && context.Type() == name)
				{
					return context;
				}
			}
		}
		
		return null;
	}
}