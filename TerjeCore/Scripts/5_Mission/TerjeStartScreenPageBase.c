// <copyright file="TerjeStartScreenPageBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStartScreenPageBase : TerjeWidgetBase
{
	ref ScriptCaller m_NextPageCallback = null;
	
	void InitInputContext(TerjeStartScreenContextBase context)
	{
		
	}
	
	void InitOutputContext(TerjeStartScreenContextBase context)
	{
	
	}
	
	void ExecuteNextPage()
	{
		if (m_NextPageCallback != null && m_NextPageCallback.IsValid())
		{
			m_NextPageCallback.Invoke();
			m_NextPageCallback = null;
		}
	}
}