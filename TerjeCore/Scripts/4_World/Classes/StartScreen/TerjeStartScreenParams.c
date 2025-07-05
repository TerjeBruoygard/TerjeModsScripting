// <copyright file="TerjeStartScreenParams.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenParams
{
	protected ref array<typename> m_contextTypes = new array<typename>;
	protected ref TerjeStartScreenContextBase m_actualContext = null;
	protected int m_actualServerContextId = -1;
	
	protected void RegisterContextType(typename type)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			m_contextTypes.Insert(type);
		}
	}
	
	bool Serialize(Serializer ctx)
	{
		if (m_actualContext != null)
		{
			if (!ctx.Write(true))
				return false;
			
			if (!ctx.Write(m_actualContext.Type().ToString()))
				return false;
			
			if (!m_actualContext.Serialize(ctx))
				return false;
		}
		else
		{
			if (!ctx.Write(false))
				return false;
		}
		
		return true;
	}
		
	bool Deserialize(Serializer ctx)
	{
		bool state;
		if (!ctx.Read(state))
			return false;
		
		if (state)
		{
			string type;
			if (!ctx.Read(type))
				return false;
			
			typename typeName = type.ToType();
			if (!typeName)
				return false;
			
			if (!typeName.IsInherited(TerjeStartScreenContextBase))
				return false;
			
			m_actualContext = TerjeStartScreenContextBase.Cast(typeName.Spawn());
			if (m_actualContext == null)
				return false;
			
			if (!m_actualContext.Deserialize(ctx))
				return false;
		}
		
		return true;
	}
	
	void Build(PlayerBase player)
	{
	
	}
	
	void OnServerTick(PlayerBase player, float deltaTime)
	{
	
	}
	
	void OnServerDone(PlayerBase player)
	{
	
	}
	
	void ApplyServerContext(PlayerBase player)
	{
		if (m_actualContext != null)
		{
			m_actualContext.Apply(player);
			m_actualContext = null;
		}
	}
	
	void NextServerContext(PlayerBase player)
	{
		m_actualServerContextId = m_actualServerContextId + 1;
		if ((m_actualServerContextId >= 0) && (m_actualServerContextId < m_contextTypes.Count()))
		{
			typename spawnType = m_contextTypes.Get(m_actualServerContextId);
			m_actualContext = TerjeStartScreenContextBase.Cast(spawnType.Spawn());
			if (m_actualContext != null)
			{
				m_actualContext.Build(player);
			}
		}
	}
	
	void SetPlayerStats(TerjeXmlObject xmlNode)
	{
	
	}
	
	TerjeStartScreenContextBase GetActualContext()
	{
		return m_actualContext;
	}
}