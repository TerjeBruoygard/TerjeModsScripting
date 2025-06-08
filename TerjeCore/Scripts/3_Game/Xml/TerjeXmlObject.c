// <copyright file="TerjeXmlObject.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeXmlObject : TerjeXmlBase
{
	protected string m_Name = string.Empty;
	protected string m_Value = string.Empty;
	protected string m_Extra = string.Empty;
	protected ref map<string, string> m_Attributes = null;
	protected ref array<string> m_AttributesOrder = null;
	
	void Clear()
	{
		m_Name = string.Empty;
		m_Value = string.Empty;
		m_Extra = string.Empty;
		m_Attributes = null;
		m_AttributesOrder = null;
		ClearChildren();
	}
	
	void SetName(string name)
	{
		m_Name = name;
	}
	
	string GetName()
	{
		return m_Name;
	}
	
	void SetValue(string value)
	{
		m_Value = value;
	}
	
	string GetValue()
	{
		return m_Value;
	}
	
	bool HasValue()
	{
		return m_Value.Length() > 0;
	}
	
	void SetExtra(string extra)
	{
		m_Extra = extra;
	}
	
	string GetExtra()
	{
		return m_Extra;
	}
	
	bool IsObjectNode()
	{
		return GetExtra().Length() == 0;
	}
	
	bool IsManifestNode()
	{
		return GetExtra() == "manifest";
	}
	
	bool IsCommentNode()
	{
		return GetExtra() == "comment";
	}
	
	void ClearAttributes()
	{
		m_Attributes = null;
		m_AttributesOrder = null;
	}
	
	void SetAttribute(string name, string value)
	{
		if (m_Attributes == null)
		{
			m_Attributes = new map<string, string>;
			m_AttributesOrder = new array<string>;
		}
		
		if (!m_Attributes.Contains(name))
		{
			m_AttributesOrder.Insert(name);
		}
		
		m_Attributes.Set(name, value);
	}
	
	void RemoveAttribute(string name)
	{
		if (m_Attributes != null)
		{
			m_Attributes.Remove(name);
			m_AttributesOrder.RemoveItem(name);
		}
	}
	
	void GetAttribute(int index, out string attrName, out string attrValue)
	{
		attrName = m_AttributesOrder.Get(index);
		attrValue = m_Attributes.Get(attrName);
	}
	
	string GetAttribute(string name)
	{
		string result;
		FindAttribute(name, result);
		return result;
	}
	
	bool FindAttribute(string name, out string value)
	{
		if (m_Attributes != null)
		{
			return m_Attributes.Find(name, value);
		}
		
		value = string.Empty;
		return false;
	}
	
	bool HasAttribute(string name)
	{		
		return m_Attributes != null && m_Attributes.Contains(name);
	}
	
	bool EqualAttribute(string name, string expectedValue)
	{
		string actualValue;
		return FindAttribute(name, actualValue) && (actualValue == expectedValue);
	}
	
	bool HasAttributes()
	{
		return m_Attributes != null && m_Attributes.Count() > 0;
	}
	
	int GetAttributesCount()
	{
		if (m_Attributes != null)
		{
			return m_Attributes.Count();
		}
		
		return 0;
	}
	
	map<string, string> GetAttributes()
	{
		return m_Attributes;
	}
	
	array<string> GetAttributeNames()
	{
		return m_AttributesOrder;
	}
	
	void DeepCopy(TerjeXmlObject dst, bool copyChildren, bool copyComments)
	{
		dst.Clear();
		dst.SetName(this.GetName());
		dst.SetValue(this.GetValue());
		dst.SetExtra(this.GetExtra());
		
		if (this.HasAttributes())
		{
			string attrName;
			string attrValue;
			for (int attrId = 0; attrId < this.GetAttributesCount(); attrId++)
			{
				this.GetAttribute(attrId, attrName, attrValue);
				dst.SetAttribute(attrName, attrValue);
			}
		}
		
		if (copyChildren && this.HasChildren())
		{
			for (int childId = 0; childId < this.GetChildrenCount(); childId++)
			{
				TerjeXmlObject srcChild = this.GetChild(childId);
				if (copyComments || !srcChild.IsCommentNode())
				{
					srcChild.DeepCopy(dst.CreateChild(""), copyChildren, copyComments);
				}
			}
		}
	}
	
	bool Binarize(Serializer ctx)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
		
		return true;
	}
	
	bool Unbinarize(Serializer ctx)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
		
		return true;
	}
	
	void Serialize(TerjeTextStreamWriter stream, bool useIntents = true)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
	bool Deserialize(TerjeTextStreamReader stream)
	{
		/*
		 This code block is private and was hidden before publishing on github.
		 
		 This repository does not provide full code of our mods need to be fully functional.
		 That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
		 Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
		 Copyright (c) TerjeMods. All rights reserved.
		*/
	}
	
}