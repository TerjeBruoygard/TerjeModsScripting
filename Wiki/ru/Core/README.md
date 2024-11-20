# TerjeCore

Это основной мод, который используется в качестве базовой зависимости для всех остальных модов

![image](/Wiki/logos/TerjeCore.jpg)

## ОПИСАНИЕ
* Эта инструкция подразумевает что вы уже понимаете, что такое моддинг в игре DayZ. 
* У вас уже настроен и установлен DayZ Tools, создан диск P, распакована в него игра и вы умеете создавать свой мод. 
* Далее по тексту мы будем рассматривать папку, а также и название самого мода - **TerjeModding**, созданную на диске Р.
* Если вы моддите скрипты соответственно создаем папки:
```cs
TerjeModding/scripts/3_Game
TerjeModding/scripts/4_World
TerjeModding/scripts/5_Mission
```
* Либо скачиваем готовый шаблон по [ссылке](/Wiki/examples/TerjeModding) - и размещаем его на диск Р.

* После внесения требуемых изменений пакуем получившийся мод в pbo.

## МОДДИНГ

### ФУНКЦИОНАЛЬНЫЕ ВОЗМОЖНОСТИ

#### [TerjeSettings](/TerjeCore/Scripts/4_World/Plugins/PluginTerjeSettings.c) - Интерфейс для работы с настройками мода в удобном виде и с минимальным количеством кода.
```cs
// Регистрация настроек
modded class TerjeSettingsCollection
{
    override void OnInit()
    {
        super.OnInit();
        RegisterSettingFloat("MyCategory.MySettingName", "MyCategory", "Description for the user", 0.5 /*ЗНАЧЕНИЕ ПО УМОЛЧАНИЮ*/, true /*ТОЛЬКО НА СТОРОНЕ СЕРВЕРА (НЕ СИНХРОНИЗИРУЮТСЯ С КЛИЕНТОМ).*/);
    }
}

...

// Чтение настроек из скрипта
float mySettingValue;
if (GetTerjeSettingFloat("MyCategory.MySettingName", mySettingValue))
{
    Print("My setting value is: " + mySettingValue);
}
```

#### [TerjeRpc](/TerjeCore/Scripts/4_World/Plugins/PluginTerjeRpc.c) - Интерфейс для удобной работы с Remote Procedure Calls (RPC).
```cs
// Отправка RPC
GetTerjeRPC().SendToServer("MyModName.MyRpcName"/*ID*/, new Param1<string>("Hello")/*Аргумент*/);
GetTerjeRPC().SendToClient("MyModName.MyRpcName"/*ID*/, identity/*Получатель*/, new Param1<string>("Hello")/*Аргумент*/);

// Обработка RPC
GetTerjeRPC().RegisterHandler("MyModName.MyRpcName"/*ID*/, this /*Экземпляр обработчика*/, "OnReceiveRPC"/*Имя функции обработчика*/);

private void OnReceiveRPC(ParamsReadContext ctx, PlayerIdentity sender)
{
    Param1<string> clientData;
    if (ctx.Read(clientData))
    {
        Print("RPC RECEIVED: " + clientData.param1);
    }
}
```

#### [TerjePlayerProfile](/TerjeCore/Scripts/4_World/Types/TerjePlayerProfile.c) - Предоставляет интерфейс для записи и чтения данных в профиле игрока (которые НЕ сбрасываются после смерти или возрождения).
```cs
// Регистрация данных профиля
modded class TerjePlayerProfile
{
    override void OnInit()
    {
        RegisterRecord("UNIQ_RECORD_NAME", new TerjeRecordInt(0 /*INIT VALUE*/, false/*ТОЛЬКО НА СЕРВЕРЕ (НЕ СИНХРОНИЗИРУЮТСЯ С КЛИЕНТОМ).*/));
    }
}

// Чтение и запись данных профиля
int recordValue;
if (player.GetTerjeProfile() && player.GetTerjeProfile().GetIntValue("UNIQ_RECORD_NAME", recordValue))
{
    recordValue = recordValue + 10;
    player.GetTerjeProfile().SetIntValue("UNIQ_RECORD_NAME", recordValue);
}
```

#### [TerjeAdmintoolSupport](/TerjeCore/Scripts/4_World/Compatibility/TerjeAdmintoolSupport.c) - Интерфейс для поддержки совместимости статистики игроков с популярными инструментами администрирования.
```cs
modded class TerjeAdmintoolSupport
{
    override void OnInit()
    {
        super.OnInit();
        RegisterPlayerStat(new TerjeAdmintoolSupport_MyCustomStat("MyStatID", "Display Name", "PATH TO ICON", 0/*МИН ЗНАЧЕНИЕ*/, 100/*МАКС ЗНАЧЕНИЕ*/));
    }
}

class TerjeAdmintoolSupport_MyCustomStat : TerjeAdmintoolSupport_PlayerStat
{
    override float GetValue(PlayerBase player)
    {
        return player.GetMyCustomParameter();
    }
    
    override void SetValue(PlayerBase player, float value)
    {
        player.SetMyCustomParameter(value);
    }
};
```

#### [TerjePlayerSkillsAccessor](/TerjeCore/Scripts/4_World/Classes/TerjePlayerSkillsAccessor.c) - Интерфейс для доступа к системе навыков и перков.
```cs
float perkValue;
if (player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("skill_name", "perk_name", perkValue))
{
    Print("PERK IS ACTIVE. VALUE IS: " + perkValue);
}
else
{
    // Перк не активен.
    // Или мод TerjeSkills отсутствует на сервере.
    Print("PERK IS NOT ACTIVE.");
}
```

### СОЗДАНИЕ НОВОЙ ЖИДКОСТИ

Благодаря данному моду снимается ванильное ограничение на создание жидкостей в количестве 32 шт. (поскольку ванильная система жидкостей жестко закодирована в битовой маске). Теперь вы можете создавать новые типы жидкостей, не опасаясь конфликтов с другими модами

#### Создаем жидкость с названием - **MeatSoup**.

Создаем файл config.cpp
```cs
class CfgPatches
{
    class TerjeModding_Liquids
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeCore"
        };
    };
};

class CfgTerjeCustomLiquids
{
    class MeatSoup
    {
        displayName="#STR_TERJEMED_MEATSOUP_WATER"; //Название жидкости
        flammability=-10; //Горючесть
        liquidFreezeThreshold=0; //Порог замерзания жидкости
        liquidThawThreshold=0; //Порог оттаивания жидкости
        liquidBoilingThreshold=150; //Порог кипения жидкости
        terjeOverrideLiquidColor=-10267848; // Используйте https://argb-int-calculator.netlify.app/ для получения значения цвета.
        class Nutrition
        {
            fullnessIndex=1; //Индекс полноты
            energy=-5; //Кол-во добавляемой еды на каждые 100 мл жидкости.
            water=5; //Кол-во добавляемой воды на каждые 100 мл жидкости.
            nutritionalIndex=75; //Индекс пищевой ценности
            toxicity=0; //Токсичность
            digestibility=2; //Усвояемость
            agents=0; //Агенты
        };
    };
};

class CfgVehicles
{
    class CanisterGasoline;

    class CanisterWithMeatSoup : CanisterGasoline
    {
        varTerjeCustomLiquidTypeInit="MeatSoup"; // Установка пользовательской жидкости в качестве начальной жидкости для вашего предмета.
    };
};
```

#### Функции для работы с жидкостями:
Получаем название жидкости (string) - **GetTerjeLiquidClassname();**
```cs
    //Пример использования:
    void MyTestFunction(ItemBase item)
    {
        string liquidClass = item.GetTerjeLiquidClassname();
        Print("My liquid is " + liquidClass);
    }
```
Устанавливаем тип жидкости - **SetTerjeLiquidClassname();**
```cs
    //Пример использования:
    void FillMyTestContainer(ItemBase item, float amount)
    {
        item.SetTerjeLiquidClassname("MeatSoup"); //Устанавливаем тип жидкости
        item.SetQuantity(amount); //Задаем ее объем
    }
```
