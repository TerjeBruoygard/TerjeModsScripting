// <copyright file="TerjeXmlBase.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeXmlBase
{
	protected ref array<ref TerjeXmlObject> m_Children = null;
	
	void DeleteComments(bool recursive = true)
	{
		int i = 0;
		while (i < GetChildrenCount())
		{
			TerjeXmlObject child = GetChild(i);
			if (child != null)
			{
				if (child.IsCommentNode())
				{
					RemoveChild(i);
					continue;
				}
				else if (recursive)
				{
					child.DeleteComments(recursive);
				}
			}
			
			i = i + 1;
		}
	}
	
	void ClearChildren()
	{
		m_Children = null;
	}
	
	TerjeXmlObject CreateChild(string name)
	{
		if (m_Children == null)
		{
			m_Children = new array<ref TerjeXmlObject>;
		}
		
		ref TerjeXmlObject child = new TerjeXmlObject;
		child.SetName(name);
		m_Children.Insert(child);
		return child;
	}
	
	TerjeXmlObject CreateChildAt(string name, int index)
	{
		if (m_Children == null)
		{
			m_Children = new array<ref TerjeXmlObject>;
		}
		
		ref TerjeXmlObject child = new TerjeXmlObject;
		child.SetName(name);
		m_Children.InsertAt(child, index);
		return child;
	}
	
	void RemoveChild(int index)
	{
		if (m_Children != null)
		{
			m_Children.RemoveOrdered(index);
		}
	}
	
	void RemoveAllChildrenWithName(string name)
	{
		if (m_Children != null)
		{
			int index = 0;
			while (index < m_Children.Count())
			{
				TerjeXmlObject child = m_Children.Get(index);
				if ((child != null) && (child.IsObjectNode()) && (child.GetName() == name))
				{
					m_Children.RemoveOrdered(index);
				}
				else
				{
					index++;
				}
			}
		}
	}
	
	int GetChildrenCount()
	{
		if (m_Children != null)
		{
			return m_Children.Count();
		}
		
		return 0;
	}
	
	TerjeXmlObject GetChild(int index)
	{
		if (m_Children != null)
		{
			return m_Children.Get(index);
		}
		
		return null;
	}
	
	TerjeXmlObject GetChildByNodeName(string nodeName)
	{
		int index = FindChildIndexByNodeName(nodeName);
		if (index != -1)
		{
			return GetChild(index);
		}
		
		return null;
	}
	
	int FindChildIndexByNodeName(string nodeName, int startIndex = 0)
	{
		if (m_Children != null)
		{
			for (int i = startIndex; i < m_Children.Count(); i++)
			{
				TerjeXmlObject node = m_Children.Get(i);
				if ((node.IsObjectNode()) && (node.GetName() == nodeName))
				{
					return i;
				}
			}
		}
		
		return -1;
	}
	
	TerjeXmlObject GetChildByAttrName(string nodeName, string attrName)
	{
		int index = FindChildIndexByAttrName(nodeName, attrName);
		if (index != -1)
		{
			return GetChild(index);
		}
		
		return null;
	}
	
	int FindChildIndexByAttrName(string nodeName, string attrName, int startIndex = 0)
	{
		if (m_Children != null)
		{
			for (int i = startIndex; i < m_Children.Count(); i++)
			{
				TerjeXmlObject node = m_Children.Get(i);
				if ((node.IsObjectNode()) && (node.GetName() == nodeName) && (node.HasAttribute(attrName)))
				{
					return i;
				}
			}
		}
		
		return -1;
	}
	
	TerjeXmlObject GetChildByAttrPair(string nodeName, string attrName, string attrValue)
	{
		int index = FindChildIndexByAttrPair(nodeName, attrName, attrValue);
		if (index != -1)
		{
			return GetChild(index);
		}
		
		return null;
	}
	
	int FindChildIndexByAttrPair(string nodeName, string attrName, string attrValue, int startIndex = 0)
	{
		if (m_Children != null)
		{
			for (int i = startIndex; i < m_Children.Count(); i++)
			{
				string value;
				TerjeXmlObject node = m_Children.Get(i);
				if ((node.IsObjectNode()) && (node.GetName() == nodeName) && (node.FindAttribute(attrName, value)) && (value == attrValue))
				{
					return i;
				}
			}
		}
		
		return -1;
	}
	
	bool FindValueByNodeName(string nodeName, out string value)
	{
		TerjeXmlObject node = GetChildByNodeName(nodeName);
		if ((node != null) && (node.IsObjectNode()) && (node.HasValue()))
		{
			value = node.GetValue();
			return true;
		}
		
		return false;
	}
	
	bool HasChildren()
	{
		return m_Children != null && m_Children.Count() > 0;
	}
	
	array<ref TerjeXmlObject> GetChildren()
	{
		return m_Children;
	}
}