// <copyright file="TerjeStartScreenContextMap.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenContextMap : TerjeStartScreenContextBase
{
	ref TerjeXmlObject m_inputRespawns = new TerjeXmlObject;
	string m_outputSelectedRespawnId;
	
	override string GetPageName()
	{
		return "map";
	}
	
	override bool Serialize(Serializer ctx)
	{
		if (!super.Serialize(ctx))
			return false;
		
		if (!m_inputRespawns.Binarize(ctx))
			return false;
		
		if (!ctx.Write(m_outputSelectedRespawnId))
			return false;
		
		return true;
	}
	
	override bool Deserialize(Serializer ctx)
	{
		if (!super.Deserialize(ctx))
			return false;
		
		if (!m_inputRespawns.Unbinarize(ctx))
			return false;
		
		if (!ctx.Read(m_outputSelectedRespawnId))
			return false;
		
		return true;
	}
	
	override void Build(PlayerBase player)
	{
		super.Build(player);
		GetPluginTerjeStartScreen().BuildRespawnsForPlayer(player, m_inputRespawns);
	}
	
	override void Apply(PlayerBase player)
	{
		super.Apply(player);
		
		if (!player)
			return;
		
		TerjeXmlObject respawnXml = GetPluginTerjeStartScreen().GetRespawnById(m_outputSelectedRespawnId);
		if (!respawnXml)
			return;
		
		TerjeXmlObject points = respawnXml.GetChildByNodeName("Points");
		if (points == null)
		{
			vector objectToPlayerPos;
			vector objectToPlayerRot;
			if ((respawnXml.FindChildIndexByNodeName("Objects") != -1) && (GetPluginTerjeRespawnObjects().FindAndValidateRespawnObject(player, m_outputSelectedRespawnId, objectToPlayerPos, objectToPlayerRot)))
			{
				points = new TerjeXmlObject();
				points.SetName("Points");
				TerjeXmlObject respawnObjPoint = points.CreateChild("Point");
				respawnObjPoint.SetAttribute("pos", objectToPlayerPos.ToString(false));
				respawnObjPoint.SetAttribute("angle", (objectToPlayerRot[0]).ToString());
			}
			else
			{
				return;
			}
		}
		
		vector pos;
		float angle;
		TerjeXmlObject options = respawnXml.GetChildByNodeName("Options");
		if (SelectRespawnPoint(player, points, options, pos, angle) && (player.m_terjeStartScreenParams != null))
		{
			vector ori = player.GetOrientation();
			ori[0] = angle;
			player.m_terjeStartScreenParams.m_position = pos;
			player.m_terjeStartScreenParams.m_orientation = ori;
			
			TerjeXmlObject playerStatsXml = options.GetChildByNodeName("PlayerStats");
			if (playerStatsXml != null)
			{
				player.m_terjeStartScreenParams.SetPlayerStats(playerStatsXml);
			}
		}
		else
		{
			TerjeLog_Warning("TerjeStartScreenContextMap::SelectRespawnPoint failed to select respawn point for '" + m_outputSelectedRespawnId + "'.");
		}
		
		TerjeXmlObject conditions = respawnXml.GetChildByNodeName("Conditions");
		if (conditions != null)
		{
			TerjePlayerConditions playerConds();
			for (int condId = 0; condId < conditions.GetChildrenCount(); condId++)
			{
				TerjeXmlObject condXml = conditions.GetChild(condId);
				if (condXml != null && condXml.IsObjectNode())
				{
					playerConds.ApplyCondition(player, condXml);
				}
			}
		}
	}
	
	protected bool SelectRespawnPoint(PlayerBase player, TerjeXmlObject points, TerjeXmlObject options, out vector pos, out float angle)
	{
		int count = points.GetChildrenCount();
		if (count == 0)
			return false;
		
		string attrValue;
		int attempts = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_MAP_PAGE_ATTEMPTS);
		for (int i = 1; i <= attempts; i++)
		{
			int index = Math.RandomInt(0, count);
			TerjeXmlObject point = points.GetChild(index);
			if ((point != null) && point.IsObjectNode() && (point.GetName() == "Point"))
			{
				if (ValidateRespawnPoint(player, point, options) || (i == attempts))
				{
					pos = TerjeVectorHelper.XmlToVector(point);
					
					if (point.FindAttribute("angle", attrValue))
					{
						angle = Math.Clamp(attrValue.ToFloat(), 0, 360);
					}
					else
					{
						angle = Math.RandomFloat(0, 360);
					}
					
					if (i == attempts)
					{
						TerjeLog_Warning("The maximum number of attempts reached when searching for a safe respawn point for respawn '" + m_outputSelectedRespawnId + "'.");
					}
					
					return true;
				}
			}
		}
		
		return false;
	}
	
	protected bool ValidateRespawnPoint(PlayerBase player, TerjeXmlObject point, TerjeXmlObject options)
	{
		string attrValue;
		vector pos = TerjeVectorHelper.XmlToVector(point);
		TerjeXmlObject safeRadius = options.GetChildByNodeName("SafeRadius");
		if (safeRadius != null)
		{
			float maxRadius = 0;
			float zombieRadius = 0;
			if (safeRadius.FindAttribute("zombie", attrValue))
			{
				zombieRadius = attrValue.ToFloat();
				if (zombieRadius > maxRadius)
				{
					maxRadius = zombieRadius;
				}
			}
			
			float animalRadius = 0;
			if (safeRadius.FindAttribute("animal", attrValue))
			{
				animalRadius = attrValue.ToFloat();
				if (animalRadius > maxRadius)
				{
					maxRadius = animalRadius;
				}
			}
			
			float playerRadius = 0;
			if (safeRadius.FindAttribute("player", attrValue))
			{
				playerRadius = attrValue.ToFloat();
				if (playerRadius > maxRadius)
				{
					maxRadius = playerRadius;
				}
			}
			
			float otherRadius = 0;
			if (safeRadius.FindAttribute("other", attrValue))
			{
				otherRadius = attrValue.ToFloat();
				if (otherRadius > maxRadius)
				{
					maxRadius = otherRadius;
				}
			}
			
			array<Object> safeRadObjects();
			maxRadius = Math.Clamp(maxRadius, 0, 500);
			if (maxRadius > 0)
			{
				GetGame().GetObjectsAtPosition3D(pos, maxRadius, safeRadObjects, null);
				foreach (Object obj : safeRadObjects)
				{
					EntityAI objEntity = EntityAI.Cast(obj);
					if (objEntity && objEntity.IsAlive())
					{
						float objDist = vector.Distance(objEntity.GetWorldPosition(), pos);
						if (objEntity.IsZombie() || objEntity.IsZombieMilitary() || objEntity.IsInherited(ZombieBase))
						{
							if (objDist < zombieRadius)
							{
								return false;
							}
						}
						else if (objEntity.IsAnimal() || objEntity.IsInherited(AnimalBase))
						{
							if (objDist < animalRadius)
							{
								return false;
							}
						}
						else if (objEntity.IsPlayer() || objEntity.IsInherited(PlayerBase))
						{
							if (objDist < playerRadius)
							{
								return false;
							}
						}
						else
						{
							if (objDist < otherRadius)
							{
								return false;
							}
						}
					}
				}
			}
		}
		
		return true;
	}
}