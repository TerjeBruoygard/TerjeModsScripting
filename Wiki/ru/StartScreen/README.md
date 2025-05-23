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

### 🎒 Loadouts.xml

Содержит сложную структуру наборов снаряжения с поддержкой:
- Условий доступа (навыки, перки, таймауты)
- Селекторов (одиночный выбор, случайный, множественный)
- Системы очков для покупки предметов
- Кастомных обработчиков

### 🗺️ Respawns.xml

Содержит настройки точек возрождения:
- Фиксированные координаты
- Привязка к объектам
- Безопасные радиусы
- Превью карты
- Условия доступа

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

## Рекомендации по настройке

### 🏷️ Для PvE серверов
- Увеличьте `SoulsOnKillZombieChance` и `SoulsOnKillAnimalChance`
- Уменьшите `SoulsLongSurviveTime`
- Включите `SoulsDisplayBadge` для лучшего UX

### ⚔️ Для PvP серверов
- Уменьшите `SoulsMaxCount` и `SoulsInitCount`
- Добавьте `SoulsGainTimeout` чтобы предотвратить фарм
- Настройте жесткие условия для элитного снаряжения

### 🎭 Для RP серверов
- Включите все страницы создания персонажа
- Добавьте поддержку кириллицы в фильтр имен
- Создайте тематические наборы снаряжения
- Настройте точки возрождения по ролевым локациям
