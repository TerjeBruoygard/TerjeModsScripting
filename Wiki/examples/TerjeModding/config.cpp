class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeCore",
            "DZ_Data",
            "DZ_Gear_Food"
        };
    };
};

class CfgMods
{
    class TerjeModding
    {
        dir = "TerjeModding";
        action = "https://steamcommunity.com/id/terjebruoygard/myworkshopfiles/";
        hideName = 0;
        hidePicture = 0;
        name = "Terje Medicine";
        credits = "Terje Bruoygard";
        version = "1.0.0";
        author = "TerjeBruoygard";
        dependencies[] = {"Core","Game","World","Mission"};
        extra = 0;
        type = "mod"; 
        
        class defs
        {
            class gameScriptModule {
                value = "";
                files[] = {"TerjeModding/Scripts/3_Game"};
            };
            
            class worldScriptModule {
                value = "";
                files[] = {"TerjeModding/Scripts/4_World"};
            };

            class missionScriptModule {
                value = "";
                files[] = {"TerjeModding/Scripts/5_Mission"};
            };
        };
    };
};
class CfgVehicles
{
    class Edible_Base;
    class Apple: Edible_Base //Предмет которому вы хотите прописать лечение
    {
        medAntibioticLevel = 1; //Сила
        medAntibioticsTimeSec = 10; // Время действия (с)
        overdosedIncrement = 0.00; // Передозировка
    }
};
class cfgLiquidDefinitions
{
    class Vodka //Ванильная жидкость
    {
        medAntiradLevel = 1; //Сила
        medAntiradTimer = 10; // Время действия (с)
        overdosedIncrement = 0.15; // Передозировка
    };
};
class CfgTerjeCustomLiquids
{
    class CustomLiquids //Ваша кастомная жидкость
    {
        medAntiradLevel = 1; //Сила
        medAntiradTimer = 10; // Время действия (с)
        overdosedIncrement = 0.15; // Передозировка
    };
};