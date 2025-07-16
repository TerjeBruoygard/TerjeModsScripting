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
		ref Widget defaultNotifiersPanel = m_HudPanelWidget.FindAnyWidget("NotifiersPanel");
		ref Widget oldNotifierWidget = defaultNotifiersPanel.FindAnyWidget(name);
		if (oldNotifierWidget != null)
		{
			m_StatesWidgets.Set(oldNotifierWidget.GetUserID(), ImageWidget.Cast( oldNotifierWidget.FindAnyWidget("Icon" + name) ));
			m_StatesWidgetNames.Set( oldNotifierWidget.GetUserID(), name );
			return oldNotifierWidget.GetUserID();
		}
		
		ref Widget tendencyRoot = GetGame().GetWorkspace().CreateWidgets("TerjeCore/Layouts/TendencyTemplate.layout");
		ref Widget notifierWidget = tendencyRoot.FindAnyWidget("TendencyTemplate");
		
		notifierWidget.SetName(name);
		notifierWidget.FindAnyWidget("IconTendencyTemplate").SetName("Icon" + name);
		notifierWidget.FindAnyWidget("TendencyTemplateArrowUp1").SetName(name + "ArrowUp1");
		notifierWidget.FindAnyWidget("TendencyTemplateArrowUp2").SetName(name + "ArrowUp2");
		notifierWidget.FindAnyWidget("TendencyTemplateArrowUp3").SetName(name + "ArrowUp3");
		notifierWidget.FindAnyWidget("TendencyTemplateArrowDown1").SetName(name + "ArrowDown1");
		notifierWidget.FindAnyWidget("TendencyTemplateArrowDown2").SetName(name + "ArrowDown2");
		notifierWidget.FindAnyWidget("TendencyTemplateArrowDown3").SetName(name + "ArrowDown3");
		tendencyRoot.RemoveChild(notifierWidget);
		
		int id = 0;
		foreach (int xid, string xname : m_StatesWidgetNames)
		{
			if (id <= xid)
			{
				id = xid + 1;
			}
		}
		
		m_StatesWidgetNames.Set( id, name );
		
		ref Widget defaultBadgesSpacer = m_HudPanelWidget.FindAnyWidget("BadgesSpacer");
		ref Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
		
		float widgetWidth;
		float x;
		float y;
		float x2;
		float offsetX = 0;
		float offsetY = 0;
		Widget childNotifierIter = defaultNotifiersPanel.GetChildren();
		while (childNotifierIter)
		{
			if (childNotifierIter != null && childNotifierIter.IsVisible())
			{
				childNotifierIter.GetPos(x, y);
				if (offsetX < x)
				{
					offsetX = x;
				}
			}
			
			childNotifierIter = childNotifierIter.GetSibling();
		}
		
		defaultNotifiersPanel.FindAnyWidget("Thirsty").GetPos(x, offsetY);
		defaultNotifiersPanel.FindAnyWidget("Hungry").GetPos(x2, offsetY);
		widgetWidth = x - x2;
		
		defaultNotifiersPanel.GetSize(x, y);
		defaultNotifiersPanel.SetSize(x + widgetWidth, y);
		
		defaultNotifiersPanel.AddChild(notifierWidget);
		notifierWidget.SetPos(offsetX + widgetWidth, offsetY);
		notifierWidget.SetUserID(id);
		notifierWidget.Show(true);
		
		defaultBadgesSpacer.GetPos(x, y);
		defaultBadgesSpacer.SetPos(x + widgetWidth, y);
		
		defaultBadgesPanel.GetPos(x, y);
		defaultBadgesPanel.SetPos(x + widgetWidth, y);
		
		ref ImageWidget imagew = ImageWidget.Cast( notifierWidget.FindAnyWidget("Icon" + name) ); 
		m_StatesWidgets.Set(id, imagew);
		for ( int i = 0; i < 5; i++ )
		{
			string iconPathFixed = "";
			iconPathFixed = iconPathFixed + iconPath;
			iconPathFixed.Replace("{ID}", i.ToString());
			imagew.LoadImageFile( i, iconPathFixed);
		}	
		
		return id;
	}
	
	protected int RegisterTerjeBadgetWidget(string iconPath, string name, TerjeBadgeType type)
	{
		ref Widget oldBadgeWidget = m_Badges.FindAnyWidget(name);
		if (oldBadgeWidget != null)
		{
			oldBadgeWidget.Unlink();
		}
		
		ref Widget badgeRoot = GetGame().GetWorkspace().CreateWidgets("TerjeCore/Layouts/BadgeTemplate.layout");	
		ref ImageWidget badgeWidget = ImageWidget.Cast( badgeRoot.FindAnyWidget("BadgeTemplate") );
		ref TextWidget badgeText = TextWidget.Cast( badgeRoot.FindAnyWidget("BadgeTemplateText") );
		
		badgeWidget.SetName(name);
		badgeText.SetName(name + "_TerjeCounter");
		badgeText.SetText("");
		badgeWidget.LoadImageFile(0, iconPath);
		badgeRoot.RemoveChild(badgeWidget);
		m_Badges.AddChild(badgeWidget);
		
		int id = 0;
		foreach (int xid, string xname : m_BadgesWidgetNames)
		{
			if (id <= xid)
			{
				id = xid + 1;
			}
		}

		m_BadgesWidgetNames.Set( id, name );
		m_BadgesWidgets.Set( id, badgeWidget );
		m_BadgesWidgetDisplay.Set( id, false );
		m_BadgesWidgetTerjeType.Set( id, type );
		badgeWidget.Show( false );
		return id;
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
					badgeText.SetText(Math.Clamp(value, 0, 999).ToString());
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