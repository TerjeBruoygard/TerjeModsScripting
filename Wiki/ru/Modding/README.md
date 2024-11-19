# TerjeModding

![image](../../logos/General.png)

Руководство для разработчиков модов.  
Создавайте собственные модифицированные предметы, моды и многое другое с помощью расширенного API, которое включает мощные инструменты для настройки и интеграции.

## ОПИСАНИЕ
1. Эта инструкция подразумевает что вы уже понимаете, что такое моддинг в игре DayZ. 
2. У вас уже настроен и установлен DayZ Tools, создан диск P, распакована в него игра и вы умеете создавать свой мод. 
3. Далее по тексту мы будем рассматривать папку, а также и название самого мода - **TerjeModding**, созданную на диске Р.
4. Если вы моддите скрипты соответственно создаем следующие папки:
```cs
TerjeModding/scripts/3_Game
TerjeModding/scripts/4_World
TerjeModding/scripts/5_Mission
```
5. Либо скачиваем готовый шаблон по [ссылке](/Wiki/examples/TerjeModding) - и размещаем его на диск Р.

6. После внесения требуемых изменений пакуем получившийся мод в pbo. И размещаем его в своем клиентском моде (не серверном).
7. Учтите, что в данной инструкции предполагается что вы каждый раз создаете новый мод **TerjeModding** с новым config.cpp. Вы можете объединить несколько настроек в одном config.cpp. Не обязательно создавать каждый раз новый.

## TerjeMedicine

Моддинг мода на медицину для DayZ

### МЕДИЦИНА

#### ЛЕЧЕБНЫЕ СВОЙСТВА

##### 1. НА ОСНОВЕ ПРЕДМЕТА

Если вы хотите создать свои предметы, которые будут иметь определенные функции лечения, нужно будет создать свой мод в котором у вас будет находиться переопределяющие файлы основного мода. 
Далее по руководству мы попробуем дать **Apple** (у вас может быть любой другой предмет) свойства лечения от простуды.
1. Создаем config.cpp в корне своего мода. 
2. Так как мы собираемся переопределить ванильный предмет, то нам нужно найти название мода в котором он находится, чтобы прописать его в **requiredAddons** (так же нужно сделать и с любым другим предметом из стороннего мода).
3. Находим файл config.cpp по данному пути - **P:/DZ/gear/food/config.cpp**. (если он у вас в формате .bin, то используем DayZ Tools и конвертируем его в .cpp).
4. Проверяем поиском что предмет **Apple** присутствует в данном config.cpp, копируем его название с его наследованием - **class Apple: Edible_Base**.
5. Переходим в самый верх и копируем название класса, находящегося в **CfgPatches**. В нашем случае это будет - **DZ_Gear_Food**.
6. Переходим в наш config.cpp и данное название - **DZ_Gear_Food** мы прописываем в **class TerjeModding** в **requiredAddons** после **TerjeMedicine** через запятую.
7. Далее переходим ниже в **CfgVehicles** и прописываем наш предмет - **Apple**, вызвав перед этим **Edible_Base** который наследует данный предмет.
8. Переходим в Wiki [TerjeMedicine](../Medicine/README.md), копируем требуемые нам данные для лечения от простуды и вставляем в класс нашего предмета **Apple**.

По итогу у нас должен получиться такой **config.cpp**:
```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "DZ_Gear_Food"
        };
    };
};

class CfgVehicles
{
    class Edible_Base;
    class Apple: Edible_Base
    {
        medAntibioticLevel = 1; //Сила
        medAntibioticsTimeSec = 10; // Время действия (с)
        overdosedIncrement = 0.00; // Передозировка
    }
};
```
##### 2. НА ОСНОВЕ ЖИДКОСТИ

Теперь используя мод **TerjeMedicine** вы можете добавлять неограниченное количество жидкостей. [Подробнее](../Core/README.md#создание-новой-жидкости). Разберем способ лечения определенной жидкостью. Допустим мы хотим, чтобы водка выводила радиацию в небольших количествах:
1. Выполняем пункты 1 и 2 из раздела 1.
2. Находим файл config.cpp в котором прописаны все ванильные жидкости по пути **P:/DZ/data/config.cpp**
3. Находим поиском **class cfgLiquidDefinitions** и в нем ищем название требуемой нам жидкости. В нашем случаем **class Vodka**. Копируем оба класса.
4. Переходим в самый верх файла config.cpp и копируем название класса, находящегося в **CfgPatches**. В нашем случае это будет - **DZ_Data**.
5. Переходим в наш config.cpp и данное название мы прописываем в **class TerjeModding** в **requiredAddons** после **TerjeMedicine** через запятую.
6. Далее переходим ниже и добавляем **class cfgLiquidDefinitions** и прописываем требуемую жидкость - **Vodka**.
7. Переходим в Wiki [TerjeMedicine](..\Medicine\README.md), копируем требуемые нам данные для лечения от радиации и вставляем в класс нашей жидкости **Vodka**.

По итогу у нас должен получиться такой **config.cpp**:
```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "DZ_Data"
        };
    };
};

class cfgLiquidDefinitions
{
    class Vodka
    {
        medAntiradLevel = 1; //Сила
        medAntiradTimer = 10; // Время действия (с)
        overdosedIncrement = 0.15; // Передозировка
    };
};
```

Если мы используем свою новую жидкость, сделанную на основе мода TerjeMedicine файл **config.cpp** будет выглядеть вот так:

```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "TerjeMedicine_Liquids"
        };
    };
};

class CfgTerjeCustomLiquids
{
    class CustomLiquids
    {
        medAntiradLevel = 1; //Сила
        medAntiradTimer = 10; // Время действия (с)
        overdosedIncrement = 0.15; // Передозировка
    };
};
```

#### ЗАЩИТА ОТ РАНЕНИЙ

Создание вещей, у которых будет защита колотых ран и огнестрелов. 
За пример возьмем любую ванильную одежду, допустим базовый класс - **ParamedicPants_ColorBase**.

1. Создаем config.cpp в корне своего мода **TerjeModding**. 
2. Так как мы собираемся переопределить ванильный предмет, то нам нужно найти название мода в котором он находится, чтобы прописать его в **requiredAddons** (так же нужно сделать и с любой другой одеждой из стороннего мода).
3. Находим файл config.cpp по данному пути - **P:/DZ/characters/pants/config.cpp**. (если он у вас в формате .bin, то используем DayZ Tools и конвертируем его в .cpp).
4. Проверяем поиском что одежда **ParamedicPants_ColorBase** присутствует в данном config.cpp, копируем его название с его наследованием - **class ParamedicPants_ColorBase: Clothing**.
5. Переходим в самый верх и копируем название класса, находящегося в **CfgPatches**. В нашем случае это будет - **DZ_Characters_Pants**.
6. Переходим в наш config.cpp и данное название - **DZ_Characters_Pants**  мы прописываем в **class TerjeModding** в **requiredAddons** после **TerjeMedicine** через запятую.
7. Далее переходим ниже в **CfgVehicles** и прописываем наш предмет - **ParamedicPants_ColorBase**, вызвав перед этим **Clothing** который наследует данный предмет.
8. Прописываем защиту требуемой нам одежде. Образец по [ссылке](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/TerjeMedicine/FixVanilla/config.cpp#L28)

```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "DZ_Characters_Pants"
        };
    };
};

class CfgVehicles
{
    class Clothing;
    class ParamedicPants_ColorBase: Clothing
    {
        class Protection
        {
            meleeProtection = 0.3; //Защищает от колотых ран (примерно 3 класс брони)
            firearmProtection = 0.4; //Защищает от огнестрельных ранений (примерно 4 класс брони)
        };
    };
};
```

### ЗОНЫ

#### НАСТРОЙКА ЗОН
Настройка Пси-зон и Радиационных зон производится в конфигурационном файле по пути **DayZServer/mpmissions/ваша_карта/terje_config/spawn_scriptable_areas.json**

Пример настройки 2 зон, Радиационной - **TerjeRadioactiveScriptableArea** и Пси-зоны - **TerjePsionicScriptableArea**:
```javascript
{
    "Areas": [
        {
            "Active": 1,
            "Classname": "TerjeRadioactiveScriptableArea",
            "Position": [
                341.0,
                0.0,
                9401.0
            ],
            "SpawnChance": 1.0,
            "Data": {
                "HeightMin": -100.0,
                "HeightMax": 100.0,
                "OuterRadius": 150.0,
                "InnerRadius": 50.0,
                "Power": 2.5
            }
        },
        {
            "Active": 1,
            "Classname": "TerjePsionicScriptableArea",
            "Position": [
                1254.0,
                0.0,
                4401.0
            ],
            "SpawnChance": 1.0,
            "Data": {
                "HeightMin": -100.0,
                "HeightMax": 100.0,
                "OuterRadius": 150.0,
                "InnerRadius": 50.0,
                "Power": 2.5
            }
        }
    ]
}
```
Параметры:
* Active - 1/0 - Включен/Выключен
* Classname - Название зоны (прописывается в кавычка)
* Position - Координаты расположения зоны. Высоту берем нулевую.
* SpawnChance - Шанс спавна зоны, где 1.0 - 100%
* Data - Настраиваемые значения зон
* HeightMin - Минимальная высота зоны. Нижний диапазон площади цилиндра.
* HeightMax - Максимальная высота зоны. Верхний диапазон площади цилиндра.
* OuterRadius - Внешний радиус зоны. Игроки внутри этого радиуса получат пропорциональный урон в зависимости от расстояния между двумя радиусами.
* InnerRadius - Внутренний радиус зоны. Игроки внутри этого радиуса получат полный урон.
* Power - Модификатор мощности зоны.

Вы можете создать так же зоны, которые можно спавнить через админку как предмет.
Создаем файл config.cpp в корне своего мода **TerjeModding** и прописываем в него следующе:
```cs
class CfgPatches
{
    class TerjeModdingAreas
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine", 
            "TerjeCore",
            "TerjeMedicine_Areas"
        };
    };
};

class CfgVehicles
{
    class TerjePsionicScriptableArea;
    class TerjeRadioactiveScriptableArea;
    class TerjePsiCustomArea: TerjePsionicScriptableArea //Ваша кастомная пси зона.
    {
        scope=2;
        terjeInnerRadius = 50.0; // Внутренний радиус зоны. Игроки внутри этого радиуса получат полный урон.
        terjeOuterRadius = 150.0; // Внешний радиус зоны. Игроки внутри этого радиуса получат пропорциональный урон в зависимости от расстояния между двумя радиусами.
        terjeHeightMin = -100.0; // Минимальная высота зоны. Нижний диапазон площади цилиндра.
        terjeHeightMax = 100.0; // Максимальная высота зоны. Верхний диапазон площади цилиндра.
        terjePower = 2.0; // Модификатор мощности зоны.
    };
    class TerjeRadCustomArea: TerjeRadioactiveScriptableArea //Ваша кастомная радиационная зона.
    {
        scope=2;
        terjeInnerRadius = 50.0; // Внутренний радиус зоны. Игроки внутри этого радиуса получат полный урон.
        terjeOuterRadius = 150.0; // Внешний радиус зоны. Игроки внутри этого радиуса получат пропорциональный урон в зависимости от расстояния между двумя радиусами.
        terjeHeightMin = -100.0; // Минимальная высота зоны. Нижний диапазон площади цилиндра.
        terjeHeightMax = 100.0; // Максимальная высота зоны. Верхний диапазон площади цилиндра.
        terjePower = 2.0; // Модификатор мощности зоны.
    };
};
```

#### ЗАЩИТА ОТ ЗОН

Создание вещей, у которых будет защита от Пси и Радиационных зон. 
За пример возьмем любую ванильную одежду, допустим - **BomberJacket_ColorBase**.

1. Создаем config.cpp в корне своего мода **TerjeModding**. 
2. Так как мы собираемся переопределить ванильный предмет, то нам нужно найти название мода в котором он находится, чтобы прописать его в **requiredAddons** (так же нужно сделать и с любой другой одеждой из стороннего мода).
3. Находим файл config.cpp по данному пути - **P:/DZ/characters/tops/config.cpp**. (если он у вас в формате .bin, то используем DayZ Tools и конвертируем его в .cpp).
4. Проверяем поиском что одежда **BomberJacket_ColorBase** присутствует в данном config.cpp, копируем его название с его наследованием - **class BomberJacket_ColorBase: Clothing**.
5. Переходим в самый верх и копируем название класса, находящегося в **CfgPatches**. В нашем случае это будет - **DZ_Characters_Vests**.
6. Переходим в наш config.cpp и данное название - **DZ_Characters_Vests**  мы прописываем в **class TerjeModding** в **requiredAddons** после **TerjeMedicine** через запятую.
7. Далее переходим ниже в **CfgVehicles** и прописываем наш предмет - **BomberJacket_ColorBase**, вызвав перед этим **Clothing** который наследует данный предмет.
8. Прописываем защиту требуемой нам одежде. Образец по [ссылке](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/TerjeMedicine/Protection/config.cpp#L50)

Учтите, что общая защищённость игрока от воздействия зоны складывается из 6 предметов одежды. Противогаз, Штаны, Куртка, Перчатки, Капюшон, Ботинки.

```cs
class CfgPatches
{
    class TerjeModding
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
            "TerjeMedicine",
            "DZ_Characters_Vests"
        };
    };
};

class CfgVehicles
{
    class Clothing;
    class BomberJacket_ColorBase: Clothing
    {
        class Protection
        {
            radiation=0.95; //Защищает от радиационной зоны на 95%
            psionic=1.0; //Защищает от пси-зоны на 100%
        };
    };
};
```
## TerjeSkills
**Config.cpp** с полным списком перков и их настройками - [ссылка](https://github.com/TerjeBruoygard/TerjeModsScripting/blob/master/TerjeSkills/config.cpp#L68).

Для настройки перков вам потребуется создать свой мод с файлом config.cpp.
Разберем пример настроек скила **Атлетика** и перка **Быстрые ноги**.
```cs
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
            "TerjeSkills"
        };
    };
};
class CfgTerjeSkills
{
    class Athletic
    {
        enabled=1; //Включить, выключить перк
        perkPointsPerLevel=1; //Сколько начисляется поинтов за каждый прокаченный уровень
        expLoseOnDeath=-100; //Сколько вычитается очков уровня при смерти
        levels[]= //Колличество уровней и требуемое кол-во очков для получения следующего уровня
        {
            100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // 1-10 - каждое значение череззапятую равно уровню в данной строке 10 уровней
            1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // 11-20 - тут тоже 10уровней
            6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // 20-30 - тут тоже10 уровней
            16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // 31-40 - туттоже 10 уровней
            37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // 41-50 - туттоже 10 уровней
        };
        class Modifiers
        {
            class MaxStaminaModifier //Модификатор который автоматически прокачивается при каждом прокаченном уровне.
            {
                enabled=1; //Включить, выключить модификатор
                value=0.02; //Кол-во начисляемое при каждом уровне
            }
        }
        class Perks
        {
            class QuickFeet
            {
                enabled=1; //Включить, выключить перк
                stagesCount=6; //Количество стадий у перка
                requiredSkillLevels[]={1,10,20,30,40,50}; //Уровни скила для получения следующей стадии перка
                requiredPerkPoints[]={1,2,3,4,5,10}; //Кол-во очков для прокачки соответсвующей стадии
                values[]={-0.05,-0.1,-0.2,-0.3,-0.4,-0.8}; //Процентое соотношения прокачки навыка за каждую стадию
            };
        };
    };
};
```
Основные ответы по параметрам:
- вы можете настраивать любое колличество уровней скила при помощи массива **levels[]**
- названия классов строго запрещено изменять, поломаете мод
- параметр **values[]** это процентное соотношение (т.е 0,05 - 5%)
- при изменении параметра **values[]** в перках обращайте внимание на их значение. Если оно изначально стоит отрицательное, значит и последующие настройки производите с отрицательным значением.
- для изменения количества стадий прокачки вы можете изменить параметр **stagesCount** на требуемое количество, но при этом вы так же должны изменить количество стадий в полях **requiredSkillLevels**, **requiredPerkPoints**, **values[]**.
- максимальное количество стадий перков равно - 10




