// <copyright file="TerjeVectorHelper.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeVectorHelper
{
	static vector XmlToVector(TerjeXmlObject node)
	{
		bool ySet = false;
		vector result = vector.Zero;
		string attrValue;
		
		if (node.FindAttribute("pos", attrValue))
		{
			if (attrValue.Contains(","))
			{
				array<string> parts();
				attrValue.Split(",", parts);
				
				if (parts.Count() == 2)
				{
					result[0] = parts.Get(0).Trim().ToFloat();
					result[2] = parts.Get(1).Trim().ToFloat();
				}
				else if (parts.Count() == 3)
				{
					result[0] = parts.Get(0).Trim().ToFloat();
					result[1] = parts.Get(1).Trim().ToFloat();
					result[2] = parts.Get(2).Trim().ToFloat();
					ySet = true;
				}
			}
			else
			{
				result = attrValue.ToVector();
				ySet = true;
			}
		}
		else
		{
			if (node.FindAttribute("x", attrValue))
			{
				result[0] = attrValue.ToFloat();
			}
			
			if (node.FindAttribute("y", attrValue))
			{
				result[1] = attrValue.ToFloat();
				ySet = true;
			}
			
			if (node.FindAttribute("z", attrValue))
			{
				result[2] = attrValue.ToFloat();
			}
		}
		
		if (!ySet)
		{
			result[1] = GetGame().SurfaceRoadY( result[0], result[2] );
		}
		
		return result;
	}
	
	static vector StrToVector(string value)
	{
		bool ySet = false;
		vector result = vector.Zero;
		
		if (value.Contains(","))
		{
			array<string> parts();
			value.Split(",", parts);
			
			if (parts.Count() == 2)
			{
				result[0] = parts.Get(0).Trim().ToFloat();
				result[2] = parts.Get(1).Trim().ToFloat();
			}
			else if (parts.Count() == 3)
			{
				result[0] = parts.Get(0).Trim().ToFloat();
				result[1] = parts.Get(1).Trim().ToFloat();
				result[2] = parts.Get(2).Trim().ToFloat();
				ySet = true;
			}
		}
		else
		{
			result = value.ToVector();
			ySet = true;
		}
		
		if (!ySet)
		{
			result[1] = GetGame().SurfaceRoadY( result[0], result[2] );
		}
		
		return result;
	}
}