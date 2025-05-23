# Terje Start Screen

## ОПИСАНИЕ

Этот FAQ предназначен для администраторов серверов DayZ, которые настраивают мод **Terje Start Screen**. Все настройки мода находятся в папке `TerjeSettings`.

## СТРУКТУРА ФАЙЛОВ НАСТРОЕК

```
TerjeSettings/
├── StartScreen.cfg         // Основные настройки мода
├── Core.cfg               // Настройки TerjeCore
└── StartScreen/
    ├── General.xml        // Общие параметры интерфейса
    ├── Faces.xml          // Доступные лица персонажей
    ├── Loadouts.xml       // Наборы стартового снаряжения
    └── Respawns.xml       // Точки возрождения
```

## Основной файл конфигурации - StartScreen.cfg

### 🛡️ Настройки безопасности игрока во время создания персонажа

```cfg
StartScreen.OnActiveGodMode = false;                    // Режим бога (ОТКЛЮЧЕН для совместимости с админ-инструментами)
StartScreen.OnActiveIgnoreDamage = true;               // Игнорировать урон
StartScreen.OnActiveInvisible = true;                  // Сделать игрока невидимым
StartScreen.OnActiveNoClip = true;                     // Отключить коллизии
StartScreen.OnActiveNoTargeting = true;                // ИИ не может нацеливаться на игрока
StartScreen.OnActiveFreezePos = true;                  // Заморозить движение игрока
StartScreen.OnActiveDisableSimulation = true;          // Отключить симуляцию игрока
StartScreen.OnActiveDisableTemperature = true;         // Отключить температуру
StartScreen.OnActiveSafePos = true;                    // Телепортировать в безопасное место
StartScreen.TeleportSafePos = "0 1000 0";             // Координаты безопасного места
```

**⚠️ ВАЖНО:** `OnActiveGodMode` отключен по умолчанию из-за конфликтов с админ-инструментами типа COT.

### 👤 Настройки страницы выбора имени

```cfg
StartScreen.NamePageEnabled = true;                     // Включить страницу ввода имени
StartScreen.DisplayPlayerNamesMode = 0;                 // Режим отображения имен игроков
StartScreen.NamePageLengthMin = 3;                      // Минимальная длина имени
StartScreen.NamePageLengthMax = 16;                     // Максимальная длина имени
```

**Режимы отображения имен:**
- `-1` - отключено
- `0` - всегда
- `1` - только мертвые игроки
- `2` - когда лицо видно
- `3` - мертвые игроки когда лицо видно

### 🗺️ Остальные настройки

```cfg
StartScreen.FacePageEnabled = true;                     // Включить выбор внешности
StartScreen.SkillsPageEnabled = true;                   // Включить выбор навыков (требует TerjeSkills)
StartScreen.SkillsPagePoints = 10;                      // Количество очков для распределения
StartScreen.LoadoutPageEnabled = true;                  // Включить выбор снаряжения
StartScreen.MapPageEnabled = true;                      // Включить выбор точки возрождения
StartScreen.MapPageAttempts = 8;                        // Количество попыток найти безопасное место
StartScreen.OverviewPageEnabled = true;                 // Включить страницу управления персонажем
StartScreen.OverviewPageAllowDeletion = true;           // Разрешить удаление персонажа
StartScreen.AllowProfileDeletion = true;                // Разрешить удаление профиля
```

### 💀 Система душ (Souls System)

```cfg
StartScreen.SoulsEnabled = true;                        // Включить систему душ
StartScreen.SoulsMaxCount = 7;                          // Максимальное количество душ
StartScreen.SoulsAutoDelete = true;                     // Автоудаление при 0 душ
StartScreen.SoulsNotifications = true;                  // Уведомления об изменении душ
StartScreen.SoulsDisplayBadge = false;                  // Показать значок на HUD
StartScreen.SoulsInitCount = 3;                         // Начальное количество душ

// Получение душ за убийства
StartScreen.SoulsOnKillPlayerCount = 1;                 // Души за убийство игрока
StartScreen.SoulsOnKillPlayerChance = 1;                // Шанс получения (0-1)
StartScreen.SoulsOnKillAiCount = 1;                     // Души за убийство ИИ
StartScreen.SoulsOnKillAiChance = 0.25;                 // Шанс получения
StartScreen.SoulsOnKillZombieCount = 1;                 // Души за убийство зомби
StartScreen.SoulsOnKillZombieChance = 0.01;             // Шанс получения
StartScreen.SoulsOnKillAnimalCount = 1;                 // Души за убийство животного
StartScreen.SoulsOnKillAnimalChance = 0.05;             // Шанс получения

// Души за выживание
StartScreen.SoulsLongSurviveTime = 14400;               // Время выживания в секундах (4 часа)
StartScreen.SoulsLongSurviveCount = 1;                  // Количество душ за выживание
StartScreen.SoulsLongSurviveChance = 1;                 // Шанс получения
StartScreen.SoulsGainTimeout = -1;                      // Таймаут получения душ (-1 = отключено)
```

## XML файлы конфигурации

### 📋 General.xml

```xml
<General>
    <!-- Путь к фоновому изображению -->
    <BackgroundImage value="Gui/textures/loading_screens/loading_screen_3_co.edds"/>
    
    <!-- Разрешенные символы для имен (только латиница по умолчанию) -->
    <NamePageFilter value="ABCDEFGHIJKLMNOPQRSTUVWXYZ"/>
</General>
```

### 👥 Faces.xml

```xml
<Faces>
    <!-- Вы можете поставить свои иконки персонажей -->
    <Face classname="SurvivorM_Mirek" icon="TerjeStartScreen/Faces/SurvivorM_Mirek.paa" />
    <Face classname="SurvivorF_Eva" icon="TerjeStartScreen/Faces/SurvivorF_Eva.paa" />
    <!-- ... остальные лица -->
</Faces>
```

### 🎒 НАСТРОЙКА LOADOUTS.XML - НАБОРЫ СТАРТОВОГО СНАРЯЖЕНИЯ

Файл `Loadouts.xml` содержит списки наборов стартового снаряжения, которые игроки смогут выбирать при возрождении, когда параметр `StartScreen.LoadoutPageEnabled` включен в `StartScreen.cfg`.

#### Основная структура Loadout

```xml
<Loadout id="уникальный_идентификатор" displayName="Название для игрока">
    <Items>
        <!-- Список предметов для этого набора -->
    </Items>
    <Conditions>
        <!-- Условия доступа к набору (опционально) -->
    </Conditions>
</Loadout>
```

**Обязательные параметры:**
- `id` - уникальный идентификатор набора, должен быть коротким и уникальным
- `displayName` - название набора, которое увидит игрок в интерфейсе. Можно использовать ключ из `stringtable.csv` для локализации

#### 📦 ПРЕДМЕТЫ (Items)

##### Базовый предмет (Item)

Каждый отдельный предмет может содержать другие предметы рекурсивно.

```xml
<Item classname="TShirt_Red" 
      displayName="Красная футболка"           <!-- (опционально) переопределяет название предмета в меню выбора -->
      quantity="0.8"                           <!-- (опционально) количество предмета от 0 до 1 (1=100%, 0.5=50%) -->
      count="5"                                <!-- (опционально) количество предметов в стаке -->
      health="0.75"                            <!-- (опционально) здоровье предмета от 0 до 1 -->
      position="@InHands"                      <!-- (опционально) позиция появления -->
      liquid="Water"                           <!-- (опционально) тип жидкости из cfgLiquidDefinitions -->
      temperature="36.6"                       <!-- (опционально) температура предмета в градусах Цельсия -->
      foodStage="BOILED"                       <!-- (опционально) стадия еды: RAW, BAKED, BOILED, DRIED, BURNED, ROTTEN -->
      disinfected="1"                          <!-- (опционально) стерильность: 0 - нет, 1 - да -->
      agents="CHOLERA,INFLUENZA"               <!-- (опционально) список агентов через запятую -->
      quickbar="1"                             <!-- (опционально) слот быстрого доступа (0-9) -->
      ammoType="Ammo_762x39"                   <!-- (опционально) тип патронов для спавна в магазине или оружии -->
      ammoCount="30"                           <!-- (опционально) количество патронов в магазине или оружии -->
      cost="10"                                <!-- (опционально) стоимость в очках для селектора с очками -->
/>
```

**Диапазоны значений:**
Можно использовать диапазоны для случайных значений:
```xml
<Item classname="Canteen" 
      quantity="0.0:1.0"                      <!-- случайное заполнение от 0% до 100% -->
      health="0.3:0.8"                        <!-- случайное здоровье от 30% до 80% -->
      temperature="36.6:41.0"                 <!-- случайная температура -->
      count="10:20"                           <!-- случайное количество от 10 до 20 -->
      ammoCount="10:20"                       <!-- случайное количество патронов -->
/>
```

**Позиции размещения (position):**
- `@Attachment` или название слота крепления, в котором будет заспавнен предмет
- `@Magazine` - заспавнить как магазин оружия
- `@InHands` - заспавнить в руках игрока
- `@Cargo` - заспавнить в первом свободном месте в инвентаре
- `@Cargo:0:3:h` - заспавнить в конкретном месте инвентаря (колонка:ряд:ориентация v/h)

**Агенты (agents):**
`CHOLERA, INFLUENZA, SALMONELLA, BRAIN, FOOD_POISON, CHEMICAL_POISON, WOUND_AGENT, NERVE_AGENT, HEAVYMETAL`

##### Примеры предметов с вложенностью:

```xml
<!-- Рюкзак с содержимым -->
<Item classname="FieldBackpack">
    <Item classname="BandageDressing" count="3" disinfected="1" />
    <Item classname="Morphine" />
    <Item classname="TacticalBaconCan" count="2" />
    <Item classname="WaterBottle" liquid="Water" quantity="1.0" />
</Item>

<!-- Оружие с модификациями и магазином -->
<Item classname="M4A1" ammoType="Ammo_556x45Tracer" position="@InHands">
    <Item classname="M4_CQBBttstck" />                      <!-- Приклад -->
    <Item classname="M4_RISHndgrd" />                       <!-- Цевье -->
    <Item classname="M4_Suppressor" />                      <!-- Глушитель -->
    <Item classname="M4_T3NRDSOptic" />                     <!-- Прицел -->
    <Item classname="Mag_STANAG_60Rnd" ammoType="Ammo_556x45Tracer" ammoCount="60" />
</Item>

<!-- Ботинки с ножом внутри -->
<Item classname="MilitaryBoots_Black">
    <Item classname="HuntingKnife" health="0.25" />
</Item>

<!-- Куртка с GPS и батарейкой (многоуровневая вложенность) -->
<Item classname="HuntingJacket_Brown">
    <Item classname="GPSReceiver">
        <Item classname="Battery9V" />
    </Item>
</Item>
```

#### 🎯 СЕЛЕКТОРЫ (Selector)

Селекторы объединяют несколько предметов в группу, позволяя выбрать только один предмет по выбору игрока или случайно.

```xml
<Selector type="ТИП_СЕЛЕКТОРА" 
          displayName="Название для игрока"          <!-- (опционально) название селектора в интерфейсе -->
          pointsCount="25"                           <!-- (только для MULTIPLE) количество очков -->
          pointsHandler="MyPointsHandler"            <!-- (только для MULTIPLE) класс обработчика очков -->
          pointsIcon="path/to/icon.paa"              <!-- (только для MULTIPLE) иконка очков -->
>
    <!-- Предметы для выбора -->
</Selector>
```

**Типы селекторов:**

##### 1. RANDOM - Случайный выбор сервером
```xml
<Selector type="RANDOM">
    <Item classname="Chemlight_Red" />
    <Item classname="Chemlight_Green" />
    <Item classname="Chemlight_Yellow" />
    <Item classname="Chemlight_White" />
</Selector>
```

##### 2. SINGLE - Игрок выбирает один предмет
```xml
<Selector type="SINGLE" displayName="ВЫБЕРИТЕ ОРУЖИЕ">
    <Item classname="TShirt_Beige" health="0.6:0.8" />
    <Item classname="TShirt_Black" health="0.6:0.8" />
    <Item classname="TShirt_Blue" health="0.6:0.8" />
</Selector>
```

##### 3. MULTIPLE - Игрок выбирает несколько предметов за очки
```xml
<Selector type="MULTIPLE" displayName="ОБОРУДОВАНИЕ" pointsCount="20">
    <Item classname="WaterBottle" liquid="Gasoline" quantity="0.1:0.5" cost="5" displayName="Топливо для мозга" />
    <Item classname="HumanSteakMeat" foodStage="BOILED" agents="BRAIN" cost="5" displayName="Завтрак" />
    <Item classname="MimeMask_Male" cost="5" />
    <Item classname="SteakKnife" cost="10" />
    <Item classname="Machete" cost="15" />
</Selector>
```

**Обработчик очков (pointsHandler):**
Для продвинутых пользователей - класс, который будет использоваться для получения количества очков для конкретного набора и игрока:

```cpp
// В файле init.c миссии
class MyPointsHandler : TerjeCustomPointsHandler
{
    override int GetPoints(PlayerBase player, string loadoutId, int selectionId)
    {
        return 25; // Вернуть количество очков
    }
}
```

#### 🔗 ГРУППЫ (Group)

Группы объединяют несколько предметов вместе. Можно использовать в селекторе для выбора нескольких предметов одновременно.

```xml
<Group cost="20">                                    <!-- стоимость группы в очках -->
    <Item classname="Izh43Shotgun" position="@InHands" ammoType="Ammo_12gaPellets" health="0.25" />
    <Item classname="Ammo_12gaPellets" ammoCount="4:8" />
</Group>
```

#### 🔒 УСЛОВИЯ ДОСТУПА (Conditions)

##### 1. Таймаут (Timeout)
Этот набор нельзя выбрать снова в течение указанного времени.

```xml
<Timeout id="строковый_идентификатор"               <!-- идентификатор таймаута -->
         hours="6"                                   <!-- часы (опционально) -->
         minutes="30"                                <!-- минуты (опционально) -->
         seconds="15"                                <!-- секунды (опционально) -->
         hideOwnerWhenFalse="0"                      <!-- скрывать набор если условие не выполнено -->
/>
```

##### 2. Уровень навыка (SkillLevel) - требует мод TerjeSkills
```xml
<SkillLevel skillId="hunt"                          <!-- идентификатор навыка -->
            requiredLevel="25"                      <!-- требуемый уровень -->
            hideOwnerWhenFalse="0"                  <!-- скрывать если не выполнено -->
/>
```

##### 3. Уровень перка (SkillPerk) - требует мод TerjeSkills
```xml
<SkillPerk skillId="hunt"                           <!-- идентификатор навыка -->
           perkId="exphunter"                       <!-- идентификатор перка -->
           requiredLevel="1"                        <!-- требуемый уровень перка -->
           hideOwnerWhenFalse="0"                   <!-- скрывать если не выполнено -->
/>
```

##### 4. Конкретные игроки (SpecificPlayers)
```xml
<SpecificPlayers hideOwnerWhenFalse="1">
    <SpecificPlayer steamGUID="76561198..." />
    <SpecificPlayer steamGUID="76561198..." />
</SpecificPlayers>
```

##### 5. Кастомное условие (CustomCondition)
Для продвинутых пользователей - специальное кастомное условие:

```xml
<CustomCondition classname="MyCustomConditionHandler" hideOwnerWhenFalse="0" />
```

```cpp
// В файле init.c
class MyCustomConditionHandler : TerjeCustomConditionHandler
{
    override bool ProcessCondition(PlayerBase player, TerjeXmlObject condition)
    {
        return player.GetMoney() >= 100; // Пример условия
    }
    
    void ApplyCondition(PlayerBase player, TerjeXmlObject condition)
    {
        player.AddMoney(-100); // Применить эффект условия
    }
    
    override string GetConditionText(PlayerBase player, TerjeXmlObject condition)
    {
        return "Цена: 100 монет"; // Текст условия
    }
}
```

#### 📋 ПОЛНЫЕ ПРИМЕРЫ LOADOUTS

##### Пример 1: Базовый выживший
```xml
<Loadout id="survivor" displayName="Обычный выживший">
    <Items>
        <Selector type="SINGLE" displayName="ВЕРХ">
            <Item classname="TShirt_Beige" health="0.6:0.8" />
            <Item classname="TShirt_Black" health="0.6:0.8" />
            <Item classname="TShirt_Blue" health="0.6:0.8" />
        </Selector>
        <Selector type="SINGLE" displayName="НИЗ">
            <Item classname="CanvasPantsMidi_Beige" health="0.6:0.8" />
            <Item classname="CanvasPantsMidi_Blue" health="0.6:0.8" />
            <Item classname="CanvasPantsMidi_Grey" health="0.6:0.8" />
        </Selector>
        <Selector type="RANDOM">
            <Item classname="Apple" />
            <Item classname="Pear" />
            <Item classname="Plum" />
            <Item classname="Tomato" />
        </Selector>
        <Item classname="BandageDressing" disinfected="1" />
    </Items>
</Loadout>
```

##### Пример 2: Набор с множественным выбором и таймаутом
```xml
<Loadout id="multiselect" displayName="Набор с выбором за очки">
    <Items>
        <Item classname="PrisonerCap" health="0.5" />
        <Item classname="WorkingBoots_Grey" health="0.5" />
        <Item classname="PrisonUniformJacket" health="0.5" />
        <Item classname="PrisonUniformPants" health="0.5" />
        <Item classname="Slingbag_Gray" health="0.5" />
        
        <Selector type="MULTIPLE" displayName="ОБОРУДОВАНИЕ" pointsCount="20">
            <Item classname="WaterBottle" liquid="Gasoline" quantity="0.1:0.5" cost="5" displayName="Топливо для мозга" />
            <Item classname="HumanSteakMeat" foodStage="BOILED" agents="BRAIN" cost="5" displayName="Завтрак" />
            <Item classname="MimeMask_Male" cost="5" />
            <Item classname="MimeMask_Female" cost="5" />
            <Item classname="SteakKnife" cost="10" />
            <Item classname="Machete" cost="15" />
            <Group cost="20">
                <Item classname="Izh43Shotgun" position="@InHands" ammoType="Ammo_12gaPellets" health="0.25" />
                <Item classname="Ammo_12gaPellets" ammoCount="4:8" />
            </Group>
        </Selector>
    </Items>
    <Conditions>
        <Timeout id="test" minutes="15" />
    </Conditions>
</Loadout>
```

##### Пример 3: Охотник с требованиями к навыкам
```xml
<Loadout id="hunter" displayName="Охотник (требуется навык)">
    <Items>
        <Item classname="CowboyHat_Brown" />
        <Item classname="MilitaryBoots_Black">
            <Item classname="HuntingKnife" health="0.25" />
        </Item>
        <Item classname="MilitaryBelt">
            <Item classname="Canteen" liquid="Vodka" quantity="0.5" />
        </Item>
        <Item classname="HuntingJacket_Brown">
            <Item classname="GPSReceiver">
                <Item classname="Battery9V" />
            </Item>
        </Item>
        <Item classname="HunterPants_Brown">
            <Item classname="TacticalBaconCan" />
        </Item>
        
        <Selector type="SINGLE" displayName="ОРУЖИЕ">
            <Group>
                <Item classname="Izh18" position="@InHands" ammoType="Ammo_762x39" health="0.25" />
                <Item classname="Ammo_762x39" ammoCount="5:10" />
            </Group>
            <Group>
                <Item classname="Izh18Shotgun" position="@InHands" ammoType="Ammo_12gaPellets" health="0.25" />
                <Item classname="Ammo_12gaPellets" ammoCount="4:8" />
            </Group>
        </Selector>
    </Items>
    <Conditions>
        <SkillLevel skillId="hunt" requiredLevel="25" />
        <SkillPerk skillId="hunt" perkId="exphunter" requiredLevel="1" />
    </Conditions>
</Loadout>
```

##### Пример 4: Админский набор
```xml
<Loadout id="admin" displayName="Админское снаряжение">
    <Items>
        <Item classname="BaseballCap_Red" />
        <Item classname="ChildBag_Red" />
        <Item classname="Hoodie_Red" />
        <Item classname="ParamedicPants_Crimson" />
        <Item classname="MilitaryBoots_Redpunk" />
        <Item classname="M4A1" ammoType="Ammo_556x45Tracer" position="@InHands">
            <Item classname="M4_CQBBttstck" />
            <Item classname="M4_RISHndgrd" />
            <Item classname="M4_Suppressor" />
            <Item classname="M4_T3NRDSOptic" />
            <Item classname="Mag_STANAG_60Rnd" ammoType="Ammo_556x45Tracer" ammoCount="60" />
        </Item>
    </Items>
    <Conditions>
        <SpecificPlayers hideOwnerWhenFalse="1">
            <!-- УКАЖИТЕ STEAM GUID ВАШИХ АДМИНОВ -->
            <SpecificPlayer steamGUID="dzWbglNhfeOd..." />
            <SpecificPlayer steamGUID="nvv238NwFBBr..." />
        </SpecificPlayers>
    </Conditions>
</Loadout>
```

### 🗺️ НАСТРОЙКА RESPAWNS.XML - ТОЧКИ ВОЗРОЖДЕНИЯ

Файл `Respawns.xml` содержит список точек возрождения, которые игроки смогут выбирать при создании персонажа, когда параметр `StartScreen.MapPageEnabled` включен в `StartScreen.cfg`.

#### Основная структура Respawn

```xml
<Respawn id="уникальный_идентификатор" displayName="Название для игрока">
    <Options>
        <!-- Дополнительные настройки возрождения -->
    </Options>
    <Points>
        <!-- Список фиксированных точек для возрождения -->
    </Points>
    <!-- ИЛИ -->
    <Objects>
        <!-- Список объектов для использования в качестве точек возрождения -->
    </Objects>
    <Conditions>
        <!-- Условия доступа к точке возрождения -->
    </Conditions>
</Respawn>
```

**Обязательные параметры:**
- `id` - уникальный идентификатор точки возрождения
- `displayName` - название, которое увидит игрок в интерфейсе

#### 📍 ТОЧКИ ВОЗРОЖДЕНИЯ (Points vs Objects)

##### Фиксированные точки (Points)
Каждая отдельная точка для возрождения:

```xml
<Point pos="14162.81, 12405.00" />                    <!-- позиция в формате с сайта https://dayz.xam.nu/ -->
<Point pos="14162.81, 12405.00" angle="180" />        <!-- с углом поворота (0-360) -->

<!-- Альтернативный формат координат -->
<Point x="14162.81" y="0" z="12405.00" angle="90" />
```

##### Объекты для возрождения (Objects)
Объекты, которые игрок может использовать как кастомную точку возрождения (спальные мешки, флаги):

```xml
<Object classname="TerjeSleepingBag_Blue" />
<Object classname="TerritoryFlag" handler="MyRespawnObjectHandler" />
```

**Обработчик объектов (handler):**
Для продвинутых пользователей - можно определить дополнительную логику и условия для объекта:

```cpp
// Пример для флага территории Expansion
class MyRespawnObjectHandler : TerjeRespawnObjectHandler
{
    override bool SetAsRespawnObject(PlayerBase player, Object object, string respawnId)
    {
        TerritoryFlag territoryFlag = TerritoryFlag.Cast(object);
        if (territoryFlag && territoryFlag.GetTerritory() && player.GetIdentity())
        {
            return territoryFlag.GetTerritory().IsMember(player.GetIdentity().GetId());
        }
        return false;
    }
    
    override bool RespawnOnObject(PlayerBase player, Object object, string respawnId)
    {
        TerritoryFlag territoryFlag = TerritoryFlag.Cast(object);
        if (territoryFlag && territoryFlag.GetTerritory() && player.GetIdentity())
        {
            return territoryFlag.GetTerritory().IsMember(player.GetIdentity().GetId());
        }
        return false;
    }
}
```

#### ⚙️ ДОПОЛНИТЕЛЬНЫЕ НАСТРОЙКИ (Options)

##### Безопасные радиусы (SafeRadius)
Устанавливает безопасные радиусы при выборе точки для возрождения игрока:

```xml
<SafeRadius zombie="15"                               <!-- минимальное расстояние до зараженных -->
            animal="25"                               <!-- минимальное расстояние до животных -->
            player="50"                               <!-- минимальное расстояние до других игроков -->
            other="5"                                 <!-- минимальное расстояние до статичных объектов -->
/>
```

##### Превью изображения (MapImage)
Использует изображение по указанному пути как превью:

```xml
<MapImage path="TerjeStartScreen\Textures\chernarusplus.paa" />
```

##### Рендеринг карты (MapRender)
Использует виджет рендеринга карты для отображения целевой позиции как превью:

```xml
<MapRender pos="10363.13, 2182.50"                   <!-- позиция центра карты -->
           x="10363.13" y="0" z="2182.50"            <!-- альтернативный формат координат -->
           zoom="0.25"                                <!-- масштаб карты (рекомендуется 0.1-1.0) -->
           showPoints="always"                        <!-- отображение точек возрождения -->
           showMarker="always"                        <!-- отображение маркера -->
           showMarkerName="1"                         <!-- показать название рядом с маркером -->
           allowInteraction="1"                       <!-- разрешить интерактивность карты -->
           markerPath="path/to/marker.paa"            <!-- путь к иконке маркера -->
           pointsPath="path/to/dot.paa"               <!-- путь к иконке точек -->
           activePointsColor="0xFFB40000"             <!-- цвет активных точек (ARGB) -->
           inactivePointsColor="0xFF191919"           <!-- цвет неактивных точек (ARGB) -->
           activeMarkerColor="0xFFB40000"             <!-- цвет активного маркера (ARGB) -->
           inactiveMarkerColor="0xFF191919"           <!-- цвет неактивного маркера (ARGB) -->
/>
```

**Параметры отображения:**
- `showPoints` / `showMarker`:
  - `"never"` - никогда не показывать
  - `"active"` - показывать только когда этот набор точек активен
  - `"always"` - всегда показывать

##### Статистики игрока (PlayerStats)
Игрок будет возрожден со следующими конкретными характеристиками:

```xml
<PlayerStats health="100"                             <!-- здоровье игрока (1-100) -->
             blood="5000"                             <!-- кровь игрока (2500-5000) -->
             shock="0"                                <!-- шок игрока (0-100) -->
             energy="5000"                            <!-- энергия/еда игрока (0-5000) -->
             water="5000"                             <!-- вода игрока (0-5000) -->
             sleep="14000"                            <!-- сон игрока (0-14000, требует TerjeMedicine) -->
             mind="100"                               <!-- психика игрока (0-100, требует TerjeMedicine) -->
             heatComfort="0"                          <!-- температурный комфорт (-1 до 1) -->
             heatBuffer="30"                          <!-- температурный буфер (-30 до 30) -->
/>
```

#### 🔒 УСЛОВИЯ ДОСТУПА (Conditions)

##### 1. Таймаут (Timeout)
Эту точку возрождения нельзя выбрать снова в течение указанного времени:

```xml
<Timeout id="строковый_идентификатор"               <!-- идентификатор таймаута -->
         hours="2"                                   <!-- часы (опционально) -->
         minutes="30"                                <!-- минуты (опционально) -->
         seconds="45"                                <!-- секунды (опционально) -->
         hideOwnerWhenFalse="0"                      <!-- скрывать точку если условие не выполнено -->
/>
```

##### 2. Уровень навыка (SkillLevel) - требует мод TerjeSkills
```xml
<SkillLevel skillId="hunt"                          <!-- идентификатор навыка -->
            requiredLevel="25"                      <!-- требуемый уровень -->
            hideOwnerWhenFalse="0"                  <!-- скрывать если не выполнено -->
/>
```

##### 3. Уровень перка (SkillPerk) - требует мод TerjeSkills
```xml
<SkillPerk skillId="hunt"                           <!-- идентификатор навыка -->
           perkId="exphunter"                       <!-- идентификатор перка -->
           requiredLevel="1"                        <!-- требуемый уровень перка -->
           hideOwnerWhenFalse="0"                   <!-- скрывать если не выполнено -->
/>
```

##### 4. Конкретные игроки (SpecificPlayers)
```xml
<SpecificPlayers hideOwnerWhenFalse="1">
    <SpecificPlayer steamGUID="76561198..." />
    <SpecificPlayer steamGUID="76561198..." />
</SpecificPlayers>
```

##### 5. Кастомное условие (CustomCondition)
Специальное кастомное условие для продвинутых пользователей:

```xml
<CustomCondition classname="MyCustomConditionHandler" hideOwnerWhenFalse="0" />
```

```cpp
// В файле init.c
class MyCustomConditionHandler : TerjeCustomConditionHandler
{
    override bool ProcessCondition(PlayerBase player, TerjeXmlObject condition)
    {
        return player.GetMoney() >= 100; // Пример условия
    }
    
    void ApplyCondition(PlayerBase player, TerjeXmlObject condition)
    {
        player.AddMoney(-100); // Применить эффект
    }
    
    override string GetConditionText(PlayerBase player, TerjeXmlObject condition)
    {
        return "Цена: 100 монет"; // Текст условия
    }
}
```

#### 📋 ПОЛНЫЕ ПРИМЕРЫ RESPAWNS

##### Пример 1: Случайное возрождение по всей карте
```xml
<Respawn id="chernarus" displayName="Чернарусь (случайно)">
    <Options>
        <MapImage path="TerjeStartScreen\Textures\chernarusplus.paa" />
        <SafeRadius zombie="15" animal="0" player="50" other="0" />
    </Options>
    <Points>
        <Point pos="14162.81, 12405.00" />
        <Point pos="14163.75, 12210.94" />
        <Point pos="14074.69, 12028.13" />
        <Point pos="13910.63, 11782.50" />
        <Point pos="13347.19, 10829.06" />
        <!-- ... больше точек по всей карте -->
    </Points>
</Respawn>
```

##### Пример 2: Городское возрождение с интерактивной картой
```xml
<Respawn id="electro" displayName="Электрозаводск">
    <Options>
        <MapRender pos="10363.13, 2182.50" 
                   zoom="0.25" 
                   showPoints="always" 
                   showMarker="always" 
                   allowInteraction="1" />
        <SafeRadius zombie="15" animal="0" player="50" other="0" />
    </Options>
    <Points>
        <Point pos="11094.84, 2876.25" />
        <Point pos="10910.16, 2602.97" />
        <Point pos="10864.69, 2443.13" />
        <Point pos="10435.78, 1908.75" />
        <Point pos="9985.31, 1630.78" />
    </Points>
    <Conditions>
        <Timeout id="city_spawn" minutes="15" />
    </Conditions>
</Respawn>
```

##### Пример 3: Охотничья зона с требованиями к навыкам
```xml
<Respawn id="hunting" displayName="Охотничья зона (требуется навык)">
    <Options>
        <SafeRadius zombie="15" animal="25" player="50" other="0" />
    </Options>
    <Points>
        <Point pos="10108.13, 11988.75" />
        <Point pos="9078.75, 11985.00" />
        <Point pos="7327.50, 11587.50" />
        <Point pos="6678.75, 11403.75" />
        <Point pos="5910.00, 11047.50" />
    </Points>
    <Conditions>
        <Timeout id="hunting" minutes="30" />
        <SkillLevel skillId="hunt" requiredLevel="25" />
        <SkillPerk skillId="hunt" perkId="exphunter" requiredLevel="1" />
    </Conditions>
</Respawn>
```

##### Пример 4: Админская база
```xml
<Respawn id="admin" displayName="База администрации">
    <Options>
        <PlayerStats health="100" 
                     blood="5000" 
                     shock="0" 
                     energy="5000" 
                     water="5000" 
                     sleep="14000" 
                     mind="100" 
                     heatComfort="0" 
                     heatBuffer="30" />
    </Options>
    <Points>
        <Point pos="2606.37, 14830.66" angle="180" />
    </Points>
    <Conditions>
        <SpecificPlayers hideOwnerWhenFalse="1">
            <!-- УКАЖИТЕ STEAM GUID ВАШИХ АДМИНОВ -->
            <SpecificPlayer steamGUID="dzWbglNhfeOd..." />
            <SpecificPlayer steamGUID="nvv238NwFBBr..." />
        </SpecificPlayers>
    </Conditions>
</Respawn>
```

##### Пример 5: Возрождение на спальных мешках
```xml
<Respawn id="sleepingbag" displayName="Возрождение на спальном мешке">
    <Options>
        <MapRender zoom="0.25" showMarker="always" allowInteraction="1" />
    </Options>
    <Objects>
        <!-- Можно указать любой класс объекта для возможности установки как точки возрождения -->
        <Object classname="TerjeSleepingBag_Blue" />
        <Object classname="TerjeSleepingBag_Woodland" />
    </Objects>
    <Conditions>
        <Timeout id="sleepingbag" minutes="60" />
    </Conditions>
</Respawn>
```

## Часто задаваемые вопросы

### ❓ Как отключить определенные страницы при входе игрока?

Установите соответствующий параметр в `false`:
```cfg
StartScreen.NamePageEnabled = false;        // Отключить выбор имени
StartScreen.FacePageEnabled = false;        // Отключить выбор лица
StartScreen.SkillsPageEnabled = false;      // Отключить выбор навыков
StartScreen.LoadoutPageEnabled = false;     // Отключить выбор снаряжения
StartScreen.MapPageEnabled = false;         // Отключить выбор точки возрождения
```

### ❓ Как изменить фоновое изображение?

В файле `TerjeSettings/StartScreen/General.xml`:
```xml
<BackgroundImage value="путь/к/вашему/изображению.edds"/>
```

Поддерживаются форматы: `.paa`, `.edds`, или imageset.

### ❓ Как добавить поддержку кириллицы в именах?

В файле `TerjeSettings/StartScreen/General.xml`:
```xml
<NamePageFilter value="ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"/>
```

### ❓ Как настроить систему душ для хардкорного сервера?

```cfg
StartScreen.SoulsMaxCount = 3;              // Меньше максимальных душ
StartScreen.SoulsInitCount = 1;             // Меньше стартовых душ
StartScreen.SoulsOnKillZombieChance = 0.005; // Снизить шанс получения
StartScreen.SoulsLongSurviveTime = 28800;   // Увеличить время выживания (8 часов)
StartScreen.SoulsGainTimeout = 3600;        // Добавить таймаут (1 час)
```

### ❓ Как изменить безопасное место телепортации?

```cfg
StartScreen.TeleportSafePos = "X Y Z";      // Замените на нужные координаты
```

Например: `"7500 0 7500"`

### ❓ Как получить координаты для точек возрождения?

1. Используйте сайт https://dayz.xam.nu/
2. Найдите нужное место на карте
3. Нажмите Ctrl+C для копирования координат
4. Вставьте в формате `pos="X, Z"`

### ❓ Как создать кастомный обработчик очков для loadouts?

В файле `init.c` миссии:
```cpp
class MyPointsHandler : TerjeCustomPointsHandler
{
    override int GetPoints(PlayerBase player, string loadoutId, int selectionId)
    {
        // Вернуть количество очков в зависимости от условий
        if (loadoutId == "military")
            return player.GetLevel() * 5; // Пример
        return 25; // По умолчанию
    }
}
```
