// <copyright file="TerjeStartScreenParams.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class TerjeStartScreenParams
{
	// Synch
	string m_background = "";
	
	// Server only
	vector m_position = vector.Zero;
	vector m_orientation = vector.Zero;
	vector m_safepos = vector.Zero;
	float m_health = -1;
	float m_blood = -1;
	float m_shock = -1;
	float m_energy = -1;
	float m_water = -1;
	float m_heatComfort = 0;
	float m_heatBuffer = 0;

	override bool Serialize(Serializer ctx)
	{
		if (!super.Serialize(ctx))
			return false;
		
		if (!ctx.Write(m_background))
			return false;

		return true;
	}
	
	override bool Deserialize(Serializer ctx)
	{
		if (!super.Deserialize(ctx))
			return false;
		
		if (!ctx.Read(m_background))
			return false;
		
		return true;
	}
	
	override void Build(PlayerBase player)
	{
		super.Build(player);
		
		m_background = GetPluginTerjeStartScreen().GetGeneralXmlValue("BackgroundImage", "Gui/textures/loading_screens/loading_screen_3_co.edds");
		m_safepos = TerjeVectorHelper.StrToVector(GetTerjeSettingString(TerjeSettingsCollection.STARTSCREEN_TELEPORT_SAFEPOS));
		m_position = player.GetWorldPosition();
		m_orientation = player.GetOrientation();
		m_health = player.GetTerjeHealth().GetHealth();
		m_blood = player.GetTerjeHealth().GetBlood();
		m_shock = player.GetTerjeHealth().GetShock();
		m_energy = player.GetStatEnergy().Get();
		m_water = player.GetStatWater().Get();
		m_heatComfort = player.GetStatHeatComfort().Get();
		m_heatBuffer = player.GetStatHeatBuffer().Get();
		
		TerjePlayerProfile profile = player.GetTerjeProfile();
		if (profile != null)
		{
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_RULES_PAGE_ENABLED))
			{
				if ((!profile.GetServerRulesAccepted()) || (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_RULES_SHOW_ALWAYS)))
				{
					RegisterContextType(TerjeStartScreenContextRules);
				}
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_NAME_PAGE_ENABLED))
			{
				if ((profile.GetFirstName() == string.Empty) && (profile.GetLastName() == string.Empty))
				{
					RegisterContextType(TerjeStartScreenContextName);
				}
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_FACE_PAGE_ENABLED))
			{
				if (profile.GetCharacterClassname() == string.Empty)
				{
					RegisterContextType(TerjeStartScreenContextFace);
				}
			}
			
			if (GetTerjeSkillsRegistry().HasSkillsMod() && GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_SKILLS_PAGE_ENABLED))
			{
				if (profile.GetSkillsSelectedFlag() == 1)
				{
					RegisterContextType(TerjeStartScreenContextSkills);
				}
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_OVERVIEW_PAGE_ENABLED))
			{
				RegisterContextType(TerjeStartScreenContextOverview);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_LOADOUT_PAGE_ENABLED))
			{
				RegisterContextType(TerjeStartScreenContextLoadout);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_MAP_PAGE_ENABLED))
			{
				RegisterContextType(TerjeStartScreenContextMap);
			}
		}
	}
	
	override void OnServerTick(PlayerBase player, float deltaTime)
	{
		super.OnServerTick(player, deltaTime);
		
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_ONACTIVE_SAFEPOS))
			{
				player.SetPosition(m_safepos);
			}
			
			player.SetHealth01("GlobalHealth", "Health", 1.0);
			player.SetHealth01("GlobalHealth", "Blood", 1.0);
			player.SetHealth01("", "Shock", 1.0);
			player.GetStatEnergy().Set(player.GetStatEnergy().GetMax());
			player.GetStatWater().Set(player.GetStatWater().GetMax());
			player.GetStatHeatComfort().Set(0);
			player.GetStatHeatBuffer().Set(0);
		}
	}
	
	override void SetPlayerStats(TerjeXmlObject xmlNode)
	{
		super.SetPlayerStats(xmlNode);
		
		string attrValue;
		if (xmlNode.FindAttribute("health", attrValue))
		{
			m_health = attrValue.ToFloat();
		}
		
		if (xmlNode.FindAttribute("blood", attrValue))
		{
			m_blood = attrValue.ToFloat();
		}
		
		if (xmlNode.FindAttribute("shock", attrValue))
		{
			m_shock = attrValue.ToFloat();
		}
		
		if (xmlNode.FindAttribute("energy", attrValue))
		{
			m_energy = attrValue.ToFloat();
		}
		
		if (xmlNode.FindAttribute("water", attrValue))
		{
			m_water = attrValue.ToFloat();
		}
		
		if (xmlNode.FindAttribute("heatComfort", attrValue))
		{
			m_heatComfort = attrValue.ToFloat();
		}
		
		if (xmlNode.FindAttribute("heatBuffer", attrValue))
		{
			m_heatBuffer = attrValue.ToFloat();
		}
	}
	
	override void OnServerDone(PlayerBase player)
	{
		super.OnServerDone(player);
		
		if (player && player.IsAlive())
		{
			player.SetPosition(m_position);
			player.SetOrientation(m_orientation);
			
			if (m_health > 0)
			{
				player.GetTerjeHealth().SetHealth(m_health, null);
			}
			
			if (m_blood > 0)
			{
				player.GetTerjeHealth().SetBlood(m_blood, null);
			}
			
			if (m_shock > 0)
			{
				player.GetTerjeHealth().SetShock(m_shock, null);
			}
			
			if (m_energy > 0)
			{
				player.GetStatEnergy().Set(m_energy);
			}
			
			if (m_water > 0)
			{
				player.GetStatWater().Set(m_water);
			}
			
			player.GetStatHeatComfort().Set(m_heatComfort);
			player.GetStatHeatBuffer().Set(m_heatBuffer);
			player.GetTerjeCharacterName();
			GetTerjeDatabase().SaveProfileByPlayer(player);
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_PASSPORT_SPAWN))
			{
				player.CreateInInventory("TerjePassport");
			}
		}
	}
}