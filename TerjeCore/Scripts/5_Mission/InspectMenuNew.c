// <copyright file="InspectMenuNew.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

modded class InspectMenuNew
{
	override Widget Init()
	{
		Widget rootWidget = super.Init();
		Widget textDescWidget = rootWidget.FindAnyWidget("ItemDescWidget");
		if (textDescWidget && !textDescWidget.IsInherited(RichTextWidget) && textDescWidget.IsInherited(TextWidget))
		{
			// Replace TextWidget to RichTextWidget
			float left;
			float top;
			textDescWidget.GetScreenPos(left, top);
			
			float width;
			float height;
			textDescWidget.GetScreenSize(width, height);

			Widget parent = textDescWidget.GetParent();
			if (parent)
			{
				RichTextWidget newTextWidget = RichTextWidget.Cast(GetGame().GetWorkspace().CreateWidgets("TerjeCore/Layouts/RichTextInspectWidget.layout", parent));
				if (newTextWidget)
				{
					parent.RemoveChild(textDescWidget);
					newTextWidget.SetName("ItemDescWidget");
					newTextWidget.SetScreenPos(left, top);
					newTextWidget.SetScreenSize(width, height);
					newTextWidget.SetTextExactSize(24);
					newTextWidget.Update();
				}
			}
		}
		
		return rootWidget;
	}
}