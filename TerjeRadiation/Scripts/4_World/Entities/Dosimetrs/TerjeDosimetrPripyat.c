// <copyright file="TerjeDosimetrPripyat.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeDosimetrPripyat : TerjeDosimetrBase
{
	override void TerjeEnableDisplayClient()
	{
		TerjeUpdateDisplaySelectionsClient(0, 0, 0, 0);
	}
	
	override void TerjeDisableDisplayClient()
	{
		TerjeUpdateDisplaySelectionsClient(-1, -1, -1, -1);
	}
	
	override void TerjeUpdateDisplayValueClient(int value)
	{
		string strValue = TerjeMathHelper.ClampInt(value, 0, TerjeGeigerMaxLimit()).ToString();
		while (strValue.Length() < 4)
		{
			strValue = "0" + strValue;
		}
		
		TerjeUpdateDisplaySelectionsClient(strValue.Get(0).ToInt(), strValue.Get(1).ToInt(), strValue.Get(2).ToInt(), strValue.Get(3).ToInt());
	}
	
	override int TerjeGeigerSoundsCount()
	{
		return 4;
	}
	
	override int TerjeGeigerMaxLimit()
	{
		return 9999;
	}
	
	override float TerjeGeigerRadiationModifier()
	{
		return 10000;
	}
	
	override float GetTerjeSensitivityRadius()
	{
		return 3;
	}
	
	override string TerjeGeigerGetSoundSet(int index)
	{
		return "TerjeGeigerElectro" + index + "_SoundSet";
	}
	
	protected void TerjeUpdateDisplaySelectionsClient(int num1, int num2, int num3, int num4)
	{
		SetObjectTexture(GetTerjeHiddenSelection("pos_4"), TerjeConvertNumberToTexture(num1));
		SetObjectTexture(GetTerjeHiddenSelection("pos_3"), TerjeConvertNumberToTexture(num2));
		SetObjectTexture(GetTerjeHiddenSelection("pos_2"), TerjeConvertNumberToTexture(num3));
		SetObjectTexture(GetTerjeHiddenSelection("pos_1"), TerjeConvertNumberToTexture(num4));
	}
}