// <copyright file="TerjeWidgetPlayerPreview.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeWidgetPlayerPreview : TerjeWidgetBase
{
	protected bool m_initialized;
	protected bool m_isHolding;
	protected vector m_characterOrientation;
	protected int m_characterRotationX;
	protected int m_characterRotationY;
	protected PlayerPreviewWidget m_playerWidget;
	
	override string GetNativeLayout()
	{
		return "TerjeCore/Layouts/TerjeWidgetPlayerPreview.layout";
	}
	
	override void OnInit()
	{
		super.OnInit();
		m_playerWidget = PlayerPreviewWidget.Cast(GetNativeWidget().FindAnyWidget("PlayerPreview"));
		m_initialized = false;
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		if (m_playerWidget && GetGame().GetPlayer())
		{
			if (!m_initialized)
			{
				m_initialized = true;
				m_playerWidget.SetPlayer(GetGame().GetPlayer());
			}
			
			m_playerWidget.UpdateItemInHands(GetGame().GetPlayer().GetHumanInventory().GetEntityInHands());
			m_playerWidget.Refresh();
			
			if ( m_isHolding )
			{
				int mouseX;
				int mouseY;	
				GetMousePos(mouseX, mouseY);
				if ( GetMouseState(MouseState.LEFT) & 0x80000000 )
				{
					UpdateCharacterRotation( mouseX, mouseY, true );
				}
				else
				{
					UpdateCharacterRotation( mouseX, mouseY, false );
					m_isHolding = false;
				}
			}
		}
	}
	
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		if (w == m_playerWidget)
		{
			GetMousePos( m_characterRotationX, m_characterRotationY );
			m_isHolding = true;
		}
		
		return true;
	}
	
	protected void UpdateCharacterRotation( int mouseX, int mouseY, bool dragging )
	{
		if (m_playerWidget)
		{
			vector orientation = m_characterOrientation;
			orientation[1] = orientation[1] - ((m_characterRotationX - mouseX) * 0.5);
			
			m_playerWidget.SetModelOrientation( orientation );
	
			if ( !dragging )
			{	
				m_characterOrientation = orientation;
			}
		}
	}
}