// <copyright file="IngameHud.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class IngameHud
{
	private ref map<int,TerjeBadgeType> m_BadgesWidgetTerjeType;
	
	override void Init( Widget hud_panel_widget )
	{
		m_BadgesWidgetTerjeType = new map<int,TerjeBadgeType>;
		super.Init(hud_panel_widget);
	}
	
	void InitConditionalTerjeBadgesAndNotifiers()
	{
	
	}
	
	protected int RegisterTerjeNotifierWidget(string iconPath, string name)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	protected int RegisterTerjeBadgetWidget(string iconPath, string name, TerjeBadgeType type)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	override void DisplayBadge( int key, int value )
	{
		super.DisplayBadge(key, value);
		
		string name;
		TerjeBadgeType terjeType;
		if (m_BadgesWidgetTerjeType.Find(key, terjeType) && m_BadgesWidgetNames.Find(key, name))
		{
			ref TextWidget badgeText = TextWidget.Cast( m_Badges.FindAnyWidget( name + "_TerjeCounter" ) );
			if (badgeText)
			{
				if (terjeType == TerjeBadgeType.DEFAULT)
				{
					badgeText.SetText("");
				}
				else if (terjeType == TerjeBadgeType.COUNTER)
				{
					badgeText.SetText(Math.Clamp(value, 0, 99).ToString());
				}
				else if (terjeType == TerjeBadgeType.LEVELED)
				{
					if (value == 1) { badgeText.SetText("I "); }
					else if (value == 2) { badgeText.SetText("II"); }
					else if (value == 3) { badgeText.SetText("III"); }
					else if (value == 4) { badgeText.SetText("IV"); }
					else if (value == 5) { badgeText.SetText("V "); }
					else if (value == 6) { badgeText.SetText("VI "); }
					else if (value == 7) { badgeText.SetText("VII"); }
					else if (value == 8) { badgeText.SetText("VIII"); }
					else if (value == 9) { badgeText.SetText("IX "); }
					else if (value == 10) { badgeText.SetText("X "); }
					else { badgeText.SetText(""); }
				}
			}
		}
		
		bool colorizedHudBadges;
		int overridedBadgeColor;
		if (GetTerjeSettingBool(TerjeSettingsCollection.CORE_COLORIZED_HUD_BADGES, colorizedHudBadges) && colorizedHudBadges && m_BadgesWidgetNames.Find(key, name) && GetTerjeBadgeColor(key, value, overridedBadgeColor))
		{
			ref ImageWidget badgeImageCol = ImageWidget.Cast( m_Badges.FindAnyWidget( name ) );
			if (badgeImageCol)
			{
				badgeImageCol.SetColor(overridedBadgeColor);
			}
			
			ref TextWidget badgeTextCol = TextWidget.Cast( m_Badges.FindAnyWidget( name + "_TerjeCounter" ) );
			if (badgeTextCol)
			{
				badgeTextCol.SetColor(overridedBadgeColor);
			}
		}
	}
	
	bool GetTerjeBadgeColor( int key, int value, out int outputColor )
	{
		if (key == NTFKEY_FRACTURE || key == NTFKEY_BLEEDISH)
		{
			outputColor = GetTerjeBadgeColorCritical();
			return true;
		}
		else if (key == NTFKEY_SICK || key == NTFKEY_POISONED || key == NTFKEY_LEGS)
		{
			outputColor = GetTerjeBadgeColorWarning();
			return true;
		}
		
		outputColor = GetTerjeBadgeColorDefault();
		return false;
	}
	
	int GetTerjeBadgeColorDefault()
	{
		return ARGB( 255, 220, 220, 220 );
	}
	
	int GetTerjeBadgeColorWarning()
	{
		return ARGB( 255, 220, 220, 0 );
	}
	
	int GetTerjeBadgeColorCritical()
	{
		return ARGB( 255, 220, 0, 0 );
	}
}