// <copyright file="TerjeStringHelper.c" author="Terje Bruoygard">
//     This repository does not provide full code of our mods need to be fully functional.
//     That's just interfaces and simple logic that may be helpful to other developers while using our mods as dependencies.
//     Modification, repackaging, distribution or any other use of the code from this file except as specified in the LICENSE.md is strictly prohibited.
//     Copyright (c) TerjeMods. All rights reserved.
// </copyright>

class TerjeStringHelper
{
	private static const string HEX_ENCODER = "0123456789ABCDEF";
	private static const int HEX_DECODER[] = { 
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 
		0x06, 0x07, 0x08, 0x09, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x0A,
		0x0B, 0x0C, 0x0D, 0x0E, 0x0F
	};
	
	static string EncodeToHex(string input)
	{
		string result = string.Empty;
		for (int i = 0; i < input.Length(); i++)
		{
			int byte = (input.Substring(i, 1).ToAscii()) & 255;
			result += HEX_ENCODER.Get((int)Math.Floor(byte / 16));
			result += HEX_ENCODER.Get((int)(byte % 16));
		}
		
		return result;
	}
	
	static string DecodeFromHex(string input)
	{
		int zeroCode = "0".ToAscii();
		string result = string.Empty;
		for (int i = 0; i < input.Length(); i+=2)
		{
			int n0 = input.Get(i).ToAscii() - zeroCode;
			int n1 = input.Get(i+1).ToAscii() - zeroCode;
			int byte = (int)((HEX_DECODER[n0] << 4) | (HEX_DECODER[n1]));
			result += byte.AsciiToString();
		}
		
		return result;
	}
	
	static float ParseFloatRangeIdentifier(string value)
	{
		int rangeDelimIndex = value.IndexOf(":");
		if (rangeDelimIndex != -1)
		{
			float min = value.Substring(0, rangeDelimIndex).ToFloat();
			float max = value.Substring(rangeDelimIndex + 1, value.Length() - (rangeDelimIndex + 1)).ToFloat();
			if (min == max)
			{
				return min;
			}
			
			if (min > max)
			{
				return min;
			}
			
			return Math.RandomFloatInclusive(min, max);
		}
		
		return value.ToFloat();
	}
	
	static int ParseIntRangeIdentifier(string value)
	{
		int rangeDelimIndex = value.IndexOf(":");
		if (rangeDelimIndex != -1)
		{
			int min = value.Substring(0, rangeDelimIndex).ToInt();
			int max = value.Substring(rangeDelimIndex + 1, value.Length() - (rangeDelimIndex + 1)).ToInt();
			if (min == max)
			{
				return min;
			}
			
			if (min > max)
			{
				return min;
			}
			
			return Math.RandomIntInclusive(min, max);
		}
		
		return value.ToInt();
	}
	
	static string SecondsToHMS(int seconds)
	{
		string result = string.Empty;	
		if (seconds >= 3600)
		{
			int hours = seconds / 3600;
			result = result + hours + " #STR_TERJECORE_HOURS ";
			seconds = seconds - (hours * 3600);
		}
		
		if (seconds >= 60)
		{
			int minutes = seconds / 60;
			result = result + minutes + " #STR_TERJECORE_MINUTES ";
			seconds = seconds - (minutes * 60);
		}
		
		if (seconds >= 0)
		{
			result = result + seconds + " #STR_TERJECORE_SECOND";
		}
		
		return result;
	}
	
	static string SecondsToHM(int seconds)
	{
		if ((seconds >= 0) && (seconds < 60))
		{
			return seconds.ToString() + " #STR_TERJECORE_SECOND";
		}
		
		string result = string.Empty;	
		if (seconds >= 3600)
		{
			int hours = seconds / 3600;
			result = result + hours + " #STR_TERJECORE_HOURS ";
			seconds = seconds - (hours * 3600);
		}
		
		if (seconds >= 60)
		{
			int minutes = seconds / 60;
			result = result + minutes + " #STR_TERJECORE_MINUTES ";
			seconds = seconds - (minutes * 60);
		}
		
		return result;
	}
	
	static string SecondsToDHM(int seconds)
	{
		if ((seconds >= 0) && (seconds < 60))
		{
			return seconds.ToString() + " #STR_TERJECORE_SECOND";
		}
		
		string result = string.Empty;
		if (seconds >= 86400)
		{
			int days = seconds / 86400;
			result = result + days + " #STR_TERJECORE_DAYS ";
			seconds = seconds - (days * 86400);
		}
		
		if (seconds >= 3600)
		{
			int hours = seconds / 3600;
			result = result + hours + " #STR_TERJECORE_HOURS ";
			seconds = seconds - (hours * 3600);
		}
		
		if (seconds >= 60)
		{
			int minutes = seconds / 60;
			result = result + minutes + " #STR_TERJECORE_MINUTES ";
			seconds = seconds - (minutes * 60);
		}
		
		return result;
	}
	
	static string MetersToKMm(int meters)
	{
		string result = string.Empty;	
		if (meters >= 1000)
		{
			int kms = meters / 1000;
			result = result + kms + " #STR_TERJECORE_KILOMETERS ";
			meters = meters - (kms * 1000);
		}
		
		if (meters >= 0)
		{
			result = result + meters + " #STR_TERJECORE_METERS";
		}
		
		return result;
	}
	
	static string FloatToStr(float value, int prec = 2)
	{
		string result = value.ToString();
		int dotIdx = result.IndexOf(".");
		if ((dotIdx != -1) && (result.Length() > (dotIdx + prec + 1)))
		{
			result = result.Substring(0, dotIdx + prec + 1);
		}
		
		return result;
	}
	
	static string FixTexturePath(string value)
	{
		value.Replace("/", "\\");
		value.Replace("\\" + "\\", "\\");
		if (value.IndexOf("\\") == 0)
		{
			value = value.Substring(1, value.Length() - 1);
		}
		
		return value;
	}
	
	static bool StartsWith(string data, string value)
	{
		if (value.Length() > data.Length())
		{
			return false;
		}
		
		for (int i = 0; i < value.Length(); i++)
		{
			if (data.Get(i) != value.Get(i))
			{
				return false;
			}
		}
		
		return true;
	}
}