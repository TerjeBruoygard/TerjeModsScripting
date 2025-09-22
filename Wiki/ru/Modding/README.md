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

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода
###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих предметов.
```xml
<CfgVehicles>
	<Apple> <!-- Класс съедобного предмета -->
		<medAntibioticLevel>1</medAntibioticLevel> <!-- Сила -->
		<medAntibioticsTimeSec>0</medAntibioticsTimeSec> <!-- Время действия (с) -->
		<medAntibioticsMaxTimeSec>10</medAntibioticsMaxTimeSec> <!-- Максимальное время действия (с), после употребления всего объема -->
		<terjeAddBlood>25</terjeAddBlood> <!-- Добавить 50 Крови (Отрицательные значения - уменьшить) -->
		<terjeAddHealth>-15</terjeAddHealth> <!-- Убавить 15 здоровья (Положительные значения - увеличить) -->
		<terjeAddShock>50</terjeAddShock> <!-- Добавить 50 Шока (Отрицательные значения - уменьшить) -->
		<overdosedIncrement>0.0</overdosedIncrement> <!-- Передозировка -->
	</Apple>
</CfgVehicles>
```
###### СОЗДАНИЕ Config.cpp
Если вы хотите создать свои предметы, которые будут иметь определенные функции лечения, нужно будет создать свой мод в котором у вас будет находиться переопределяющие файлы основного мода. 
Далее по руководству мы попробуем дать **Apple** (у вас может быть любой другой предмет) свойства лечения от простуды.
1. Создаем config.cpp в корне своего мода. 
2. Так как мы собираемся переопределить ванильный предмет, то нам нужно найти название мода (класса CfgPatches) в котором он находится, чтобы прописать его в **requiredAddons** (так же нужно сделать и с любым другим предметом из стороннего мода).
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
		medAntibioticsMaxTimeSec=1800; // Максимальное время действия (с), после употребления всего объема
		terjeAddBlood = 25; //Добавить 50 Крови (Отрицательные значения - уменьшить)
		terjeAddHealth = 15; //Добавить 15 Здоровья (Отрицательные значения - уменьшить)
		terjeAddShock = 50; //Добавить 50 Шока (Отрицательные значения - уменьшить)
		overdosedIncrement = 0.00; // Передозировка
	};
};
```

Как вычисляется общее время действия препарата, начисялемое при употреблении предмета. Возьмем за пример такие данные:
```cs
	medAntidepresantLevel=1;
	medAntidepresantTimer=120;
	medAntidepresantMaxTimer=1800;
```
Допустим, у вас есть предмет объемом 1000 г/мл. Начисление таймера происходит за каждую единицу(quantity) предмета. Когда вы употребляете 100 г/мл (100 * medAntidepresantTimer), вы получаете таймер на 1200 секунд. Когда вы выпьете 500 мл, вы получите таймер (100 * medAntidepresantTimer) = 5000 секунд. Но если у вас указан параметр medAntidepresantMaxTimer, то время будет равно 1800 секундам (medAntidepresantMaxTimer).

##### 2. НА ОСНОВЕ ЖИДКОСТИ

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода
###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих жидкостей.
```xml
<cfgLiquidDefinitions>
	<Vodka> <!-- Класс съедобного предмета -->
		<medAntibioticLevel>1</medAntibioticLevel> <!-- Сила -->
		<medAntibioticsTimeSec>0</medAntibioticsTimeSec> <!-- Время действия (с) -->
		<medAntibioticsMaxTimeSec>10</medAntibioticsMaxTimeSec> <!-- Максимальное время действия (с), после употребления всего объема -->
		<terjeAddBlood>25</terjeAddBlood> <!-- Добавить 50 Крови (Отрицательные значения - уменьшить) -->
		<terjeAddHealth>-15</terjeAddHealth> <!-- Убавить 15 здоровья (Положительные значения - увеличить) -->
		<terjeAddShock>50</terjeAddShock> <!-- Добавить 50 Шока (Отрицательные значения - уменьшить) -->
		<overdosedIncrement>0.0</overdosedIncrement> <!-- Передозировка -->
	</Vodka>
</cfgLiquidDefinitions>
```
###### СОЗДАНИЕ Config.cpp
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
		medAntiradMaxTimeSec=1800; // Максимальное время действия (с), после употребления всего объема
		terjeAddBlood = 1; //Добавить 1 Крови за 1 мл (Отрицательные значения - уменьшить)
		terjeAddHealth = 2; //Добавить 2 Здоровья за 1 мл (Отрицательные значения - уменьшить)
		terjeAddShock = 3; //Добавить 3 Шока за 1 мл (Отрицательные значения - уменьшить)
		overdosedIncrement = 0.15; // Передозировка
	};
};
```

###### СОЗДАНИЕ Config.cpp

Если мы используем свою новую жидкость, сделанную на основе мода TerjeCore файл **config.cpp** будет выглядеть вот так:

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
			"TerjeCore"
		};
	};
};

class CfgTerjeCustomLiquids
{
	class MyTestLiquid
	{
		displayName="MY LIQUID";
		flammability=-10;
		liquidFreezeThreshold=0;
		liquidThawThreshold=0;
		liquidBoilingThreshold=150;
		terjeRadiationCleanupForce=1;
		medAntiradLevel = 1; //Сила
		medAntiradTimer = 10; // Время действия (с)
		medAntiradMaxTimeSec=1800; // Максимальное время действия (с), после употребления всего объема
		terjeAddBlood = 1; //Добавить 1 Крови за 1 мл (Отрицательные значения - уменьшить)
		terjeAddHealth = 2; //Добавить 2 Здоровья за 1 мл (Отрицательные значения - уменьшить)
		terjeAddShock = 3; //Добавить 3 Шока за 1 мл (Отрицательные значения - уменьшить)
		class Nutrition
		{
			fullnessIndex=1;
			energy=-5;
			water=5;
			nutritionalIndex=75;
			toxicity=1;
			digestibility=2;
			agents=16;
		};
	};
};
```
###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих жидкостей сделанных на основе мода TerjeCore.
```xml
<CfgTerjeCustomLiquids>
	<MyTestLiquid> <!-- Класс съедобного предмета -->
		<medAntibioticLevel>1</medAntibioticLevel> <!-- Сила -->
		<medAntibioticsTimeSec>0</medAntibioticsTimeSec> <!-- Время действия (с) -->
		<medAntibioticsMaxTimeSec>10</medAntibioticsMaxTimeSec> <!-- Максимальное время действия (с), после употребления всего объема -->
		<terjeAddBlood>25</terjeAddBlood> <!-- Добавить 50 Крови (Отрицательные значения - уменьшить) -->
		<terjeAddHealth>-15</terjeAddHealth> <!-- Убавить 15 здоровья (Положительные значения - увеличить) -->
		<terjeAddShock>50</terjeAddShock> <!-- Добавить 50 Шока (Отрицательные значения - уменьшить) -->
		<overdosedIncrement>0.0</overdosedIncrement> <!-- Передозировка -->
	</MyTestLiquid>
</CfgTerjeCustomLiquids>
```

#### ЗАЩИТА ОТ РАНЕНИЙ

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода
###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих предметов.
```xml
<CfgVehicles>
	<ParamedicPants> <!-- Класс предмета одежды-->
		<Protection>
			<melee>0.3</melee> <!-- Защищает от колотых ран (примерно 3 класс брони) -->
			<firearm>0.4</firearm> <!-- Защищает от огнестрельных ранений (примерно 4 класс брони) -->
		</Protection>
	</ParamedicPants>
</CfgVehicles>
```
###### СОЗДАНИЕ Config.cpp
Создание вещей, у которых будет защита колотых ран и огнестрелов. 
За пример возьмем любую ванильную одежду, допустим базовый класс - **ParamedicPants_ColorBase**.

1. Создаем config.cpp в корне своего мода **TerjeModding**. 
2. Так как мы собираемся переопределить ванильный предмет, то нам нужно найти название мода (класса CfgPatches) в котором он находится, чтобы прописать его в **requiredAddons** (так же нужно сделать и с любой другой одеждой из стороннего мода).
3. Находим файл config.cpp по данному пути - **P:/DZ/characters/pants/config.cpp**. (если он у вас в формате .bin, то используем DayZ Tools и конвертируем его в .cpp).
4. Проверяем поиском что одежда **ParamedicPants_ColorBase** присутствует в данном config.cpp, копируем его название с его наследованием - **class ParamedicPants_ColorBase: Clothing**.
5. Переходим в самый верх и копируем название класса, находящегося в **CfgPatches**. В нашем случае это будет - **DZ_Characters_Pants**.
6. Переходим в наш config.cpp и данное название - **DZ_Characters_Pants**  мы прописываем в **class TerjeModding** в **requiredAddons** после **TerjeMedicine** через запятую.
7. Далее переходим ниже в **CfgVehicles** и прописываем наш предмет - **ParamedicPants_ColorBase**, вызвав перед этим **Clothing** который наследует данный предмет.
8. Прописываем защиту требуемой нам одежде. Образец по [ссылке](../../../TerjeMedicine/FixVanilla/config.cpp#L28)


Значение защиты мода относительно реальной бронезащиты.

- Level 2 (Kevlar) = 0.2
- Level 2+ (Kevlar) = 0.25
- Level 3 (SAPI III) = 0.3
- Level 3+ (SAPI III+) = 0.35
- Level 4 (SAPI IV) = 0.4
- Level 4+ (SAPI IV+) = 0.45
- Level 5 (SAPI V) = 0.5
- Level 6 (SAPI VI) = 0.6

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
			melee = 0.3; //Защищает от колотых ран (примерно 3 класс брони)
			firearm = 0.4; //Защищает от огнестрельных ранений (примерно 4 класс брони)
		};
	};
};
```

#### НАСТРОЙКА МОДИФИЦИРОВАННОГО УРОНА ОТ ЖИВОТНЫХ, ЗОМБЕЙ, МУТАНТОВ

Вы можете добавить(настроить) любому животному, зомби, мутанту дополнительный модифицированный урон по игроку. 

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода
###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих животных, зомбей.
```xml
<CfgVehicles>
	<Animal_UrsusArctos> <!-- Класс существующего животного/зомби-->
        <TerjeCustomInjuries>
			<!-- Игнорировать блок и броню игрока при расчете попадания. -->
			<ignorePlayerBlock>0</ignorePlayerBlock> <!-- 0 = false, 1 = true -->
			<!-- 
			Перезаписывать раны по умолчанию ранами из конфигурации или дополнять их.
				Если 1 - то ранения идут только из этого конифга. 
				Если 0 - то к ранениям по дефолту (прописаные тому или иному типу животных и зомби
				- колотые раны, ушибы и т.д.) будут дополнительно добавляться ранения из этого конфига.
			-->
			<overrideDefaultInjueries>0</overrideDefaultInjueries> <!-- 0 = false, 1 = true -->
			<!-- Вероятность кровотечения при попадании -->
			<lightBleedingChance>0.1</lightBleedingChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<heavyBleedingChance>0.0</heavyBleedingChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<internalBleedingChance>0.2</internalBleedingChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<!-- Вероятность образования гематомы (ушиба) -->
			<hematomaChance>0.1</hematomaChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<!-- Вероятность сотрясения головы (ушиб головного мозга) -->
			<lightContussionChance>0.1</lightContussionChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<heavyContussionChance>0.1</heavyContussionChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<!-- Химическое отравление -->
			<chemicalPoisonChance>0.1</chemicalPoisonChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<chemicalPoisonValue>1.0</chemicalPoisonValue> <!-- Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д... -->
			<!-- Простуда -->
			<infuenzaInfectionChance>0.1</infuenzaInfectionChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<infuenzaInfectionValue>1.0</infuenzaInfectionValue> <!-- Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д... -->
			<!-- Радиация (если установлен мод TerjeRadiation) -->
			<radiationChance>0.1</radiationChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<radiationValue>1.0</radiationValue> <!-- Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д... -->
			<!-- Зомби вирус -->
			<zombieVirusChance>0.1</zombieVirusChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<zombieVirusValue>1.0</zombieVirusValue> <!-- Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д... -->
			<!-- Сепсис (заражение крови) -->
			<sepsisInfectionChance>0.1</sepsisInfectionChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<sepsisInfectionValue>1.0</sepsisInfectionValue> <!-- Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д... -->
			<!-- Бешенство -->
			<rabiesVirusChance>0.1</rabiesVirusChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<rabiesVirusValue>1.0</rabiesVirusValue> <!-- Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д... -->
			<!-- Психическое состояние. -->
			<psiDamageChance>0.1</psiDamageChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<psiDamageValue>0.1</psiDamageValue> <!-- Урон по разуму в секунду (например, 10) -->
			<psiDamageTime>1.0</psiDamageTime> <!-- Время действия в секундах (например, 5) -->
			<!-- Сон -->
			<sleepDamageChance>0.1</sleepDamageChance> <!-- Шанс 0.0 = 0%, 1.0 = 100% -->
			<sleepDamageValue>0.1</sleepDamageValue> <!-- Урон по разуму в секунду (например, 10) -->
			<sleepDamageTime>1.0</sleepDamageTime> <!-- Время действия в секундах (например, 5) -->
        </TerjeCustomInjuries>
	</Animal_UrsusArctos>
</CfgVehicles>
```
###### СОЗДАНИЕ Config.cpp
За пример возмем медведя - **Animal_UrsusArctos**:
1. Создаем config.cpp в корне своего мода **TerjeModding** на диске P. 
2. Так как мы собираемся переопределить существующее животное, то нам нужно найти название мода (класса CfgPatches) в котором он находится, чтобы прописать его в **requiredAddons** (так же нужно сделать и с любым другим животным, зомби, мутантом из стороннего мода).
3. Находим файл config.cpp по данному пути - **P:\DZ\animals_bliss\ursus_arctos\config.cpp**. (если он у вас в формате .bin, то используем DayZ Tools и конвертируем его в .cpp).
4. Проверяем поиском что животное **Animal_UrsusArctos** присутствует в данном config.cpp, копируем его название с его наследованием - **class Animal_UrsusArctos: AnimalBase**.
5. Переходим в самый верх и копируем название класса, находящегося в **CfgPatches**. В нашем случае это будет - **DZ_Animals_ursus_arctos**.
6. Переходим в наш config.cpp и данное название - **DZ_Animals_ursus_arctos**  мы прописываем в **class TerjeModding** в **requiredAddons** после **TerjeMedicine** через запятую.
7. Далее переходим ниже в **CfgVehicles** и прописываем наше животное - **DZ_Animals_ursus_arctos**, вызвав перед этим **AnimalBase** который наследует данное животное.
8. Прописываем в классе **TerjeCustomInjuries** требуемые нам дополнительные модификаторы.

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
			"DZ_Data",
			"TerjeMedicine",
			"DZ_Animals_ursus_arctos"
		};
	};
};

class CfgVehicles
{
	class AnimalBase; //Базовый класс Животных или Зомби: class ZombieBase;

	class YourCustomAnimal: AnimalBase ///Ваш класс Животного или Зомби:  class YourCustomZmb: ZombieBase 
	{
		class TerjeCustomInjuries
		{
			// Игнорировать блок и броню игрока при расчете попадания. 
			ignorePlayerBlock=0; // 0 = false, 1 = true
			
			// Перезаписывать раны по умолчанию ранами из конфигурации или дополнять их.
					// Если 1 - то ранения идут только из этого конифга. 
					// Если 0 - то к ранениям по дефолту (прописаные тому или иному типу животных и зомби
			// - колотые раны, ушибы и т.д.) будут дополнительно добавляться ранения из этого конфига. 
			overrideDefaultInjueries=1; // 0 = false, 1 = true
			
			// Вероятность кровотечения при попадании
			lightBleedingChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			heavyBleedingChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			internalBleedingChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			
			// Вероятность образования гематомы (ушиба)
			hematomaChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			
			// Вероятность сотрясения головы (ушиб головного мозга)
			lightContussionChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			heavyContussionChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			
			// Химическое отравление
			chemicalPoisonChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			chemicalPoisonValue=0.0; // Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д...
			
			// Простуда
			infuenzaInfectionChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			infuenzaInfectionValue=0.0; // Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д...
			
			// Радиация (если установлен мод TerjeRadiation)
			radiationChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			radiationValue=0.0; // Значение, добавляемое к радиационному буферу игрока
			
			// Зомби вирус
			zombieVirusChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			zombieVirusValue=0.0; // Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д...
			
			// Сепсис (заражение крови)
			sepsisInfectionChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			sepsisInfectionValue=0.0; // Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д...
			
			// Бешенство
			rabiesVirusChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			rabiesVirusValue=0.0; // Значение 1.0 для уровня 1, 2.0 для уровня 2 и т.д...
			
			// Психическое состояние.
			psiDamageChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			psiDamageValue=0.0; // Урон по разуму в секунду (например, 10)
			psiDamageTime=0.0; // Время действия в секундах (например, 5)
			
			// Сон
			sleepDamageChance=0.0; // Шанс 0.0 = 0%, 1.0 = 100%
			sleepDamageValue=0.0; // Урон по сну в секунду (например, 10)
			sleepDamageTime=0.0; // Время действия в секундах (например, 5)
		};
	};
};
```

### ЗОНЫ

#### НАСТРОЙКА ЗОН
Настройка Пси-зон и Радиационных зон производится в конфигурационном файле по пути **profiles/TerjeSettings/ScriptableAreas/ScriptableAreasSpawner.xml**

Пример настройки 3 зон:
Радиационной - **TerjeRadioactiveScriptableArea**,
Пси-зоны - **TerjePsionicScriptableArea**,
Зоны отключения начисления опыта для скилов - **TerjeExperienceModScriptableArea**:
```xml
<Areas>
	<Area>
		<Active>1</Active>
		<Classname>TerjeRadioactiveScriptableArea</Classname>
		<Position>341.0 0.0 9401.0</Position>
		<SpawnChance>1</SpawnChance>
		<Data>
			<OuterRadius>150</OuterRadius>
			<InnerRadius>50</InnerRadius>
			<HeightMin>-100</HeightMin>
			<HeightMax>100</HeightMax>
			<Power>2.5</Power>
		</Data>
	</Area>
	<Area>
		<Active>1</Active>
		<Classname>TerjePsionicScriptableArea</Classname>
		<Position>1254.0 0.0 4401.0</Position>
		<SpawnChance>1</SpawnChance>
		<Data>
			<OuterRadius>150</OuterRadius>
			<InnerRadius>50</InnerRadius>
			<HeightMin>-100</HeightMin>
			<HeightMax>100</HeightMax>
			<Power>2.5</Power>
		</Data>
	</Area>
</Areas>
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
Создаем файл config.cpp в корне своего мода **TerjeModding** и прописываем в него следующее:
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
			"TerjeCore",
			"TerjeRadiation"
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

#### ЗАЩИТА НА ВЕЩИ
Создание(Редактирование) вещей, у которых будет защита от Пси и Радиационных зон. 
За пример возьмем любую ванильную одежду, допустим - **ParamedicPants** или **BomberJacket_ColorBase**.

**Учтите, что общая защищённость игрока от воздействия зоны складывается из 8 предметов одежды. Противогаз, Штаны, Куртка, Перчатки, Капюшон, Ботинки, Рюкзак, Нарукавная повязка**
Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода
###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих вещей.
```xml
<CfgVehicles>
	<ParamedicPants> <!-- Класс предмета одежды-->
		<Protection>
			<radiation>0.3</radiation> <!-- Защищает от радиационной зоны на 30% -->
			<psionic>0.4</psionic> <!-- Защищает от пси-зоны на 40% -->
		<Protection>
	</ParamedicPants>
</CfgVehicles>
```
###### СОЗДАНИЕ Config.cpp


1. Создаем config.cpp в корне своего мода **TerjeModding**. 
2. Так как мы собираемся переопределить ванильный предмет, то нам нужно найти название мода в котором он находится, чтобы прописать его в **requiredAddons** (так же нужно сделать и с любой другой одеждой из стороннего мода).
3. Находим файл config.cpp по данному пути - **P:/DZ/characters/tops/config.cpp**. (если он у вас в формате .bin, то используем DayZ Tools и конвертируем его в .cpp).
4. Проверяем поиском что одежда **BomberJacket_ColorBase** присутствует в данном config.cpp, копируем его название с его наследованием - **class BomberJacket_ColorBase: Clothing**.
5. Переходим в самый верх и копируем название класса, находящегося в **CfgPatches**. В нашем случае это будет - **DZ_Characters_Vests**.
6. Переходим в наш config.cpp и данное название - **DZ_Characters_Vests**  мы прописываем в **class TerjeModding** в **requiredAddons** после **TerjeMedicine** через запятую.
7. Далее переходим ниже в **CfgVehicles** и прописываем наш предмет - **BomberJacket_ColorBase**, вызвав перед этим **Clothing** который наследует данный предмет.
8. Прописываем защиту требуемой нам одежде. Образец по [ссылке](../../../TerjeRadiation/Protection/config.cpp#L50)


##### Способ №1 (Стандартный)
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
			"DZ_Characters_Tops"
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
##### Способ №2 (Опциональный, только для мода TerjeRadiation)
Данный способ позволяет вещам прописывать разные уровни защиты в зависимости от силы радиации.

Этот способ расчитывается также вместе с влиянием (весом) у частей тела, но не учитывает защиту прописанную в параметре radiation.

###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих вещей.
```xml
<CfgVehicles>
	<ParamedicPants> <!-- Класс предмета одежды-->
		<Protection>
			<!-- Данный параметр мы оставляем в стандартном значении 1.0 для накопления одеждой радиации -->
			<radiation>1.0</radiation> 
			<!-- Защита одежды при разных уровнях силы радиоактивной зоны (где 1.0 - 100%)-->
			<radiationValues type="[]"> 
				<i>1.0</i><i>0.75</i><i>0.5</i><i>0.25</i><i>0.0</i>
			</radiationValues>
			<!-- Разные уровни силы радиоактивной зоны-->
			<radiationThresholds type="[]"> 
				<i>0.6</i><i>0.7</i><i>0.8</i><i>0.9</i><i>1.0</i>
			</radiationThresholds>
		<Protection>
	</ParamedicPants>
</CfgVehicles>
```
###### СОЗДАНИЕ Config.cpp
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
			"DZ_Characters_Tops"
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
			radiation=1.0; //Данный параметр мы оставляем в стандартном значении 1.0 для накопления одеждой радиации.
			radiationValues[]={1.0,0.75,0.5,0.25,0.0}; //Защита одежды при разных уровнях силы радиоактивной зоны (где 1.0 - 100%)
			radiationThresholds[]={0.6,0.7,0.8,0.9,1.0}; //Разные уровни силы радиоактивной зоны
		};
	};
};
```
## TerjeRadiation

Параметры защиты для предметов описаны выше в [ЗАЩИТА ОТ ЗОН](#защита-на-вещи).

Параметры настройки радиоактивных зон описаны выше в [НАСТРОЙКА ЗОН](#настройка-зон).

Ознакомьтесь со стандартными настройками защиты в  **Config.cpp** - [ссылка](../../../TerjeRadiation/Protection/config.cpp).

### РАСШИРЕННАЯ НАСТРОЙКА ЗАЩИТЫ 

Рассмотрим параметры настройки слотов игрока, а так же индивидуальное влияние защиты каждой части защитного костюма.

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода
##### РЕДАКТИРОВАНИЕ GameOverrides.xml
```xml
<CfgTerjeScriptableProtection>
	<Radiation>
		<Gloves> <!-- Слот на персонаже -->
			<weight>0.5</weight> <!-- вес каждого из элементов защитного костюма -->
			<protectionBodyValues type="[]">
				<i>1.0</i><i>0.75</i><i>0.5</i><i>0.25</i><i>0.0</i>
			</protectionBodyValues> <!-- защита слота при разных уровнях силы радиоактивной зоны (где 1.0 - 100%) -->
			<protectionBodyThresholds type="[]">
				<i>0.6</i><i>0.7</i><i>0.8</i><i>0.9</i><i>1.0</i>
			</protectionBodyThresholds> <!-- разные уровни силы радиоактивной зоны -->
		</Gloves>
		<Mask>
			<weight>2.5</weight>  <!-- вес каждого из элементов защитного костюма -->
			<protectionBodyValues type="[]"></protectionBodyValues> <!-- защита слота при разных уровнях силы радиоактивной зоны (где 1.0 - 100%) -->
			<protectionBodyThresholds type="[]"></protectionBodyThresholds> <!-- разные уровни силы радиоактивной зоны -->
		</Mask>
	</Radiation>
</CfgTerjeScriptableProtection>
```
##### СОЗДАНИЕ Config.cpp
```cs
class CfgTerjeScriptableProtection
{
	class radiation
	{
		class Gloves // Слот на персонаже
		{
			weight=0.5; //вес каждого из элементов защитного костюма
			protectionBodyValues[]={1.0,0.75,0.5,0.25,0.0}; //защита слота при разных уровнях силы радиоактивной зоны (где 1.0 - 100%)
			protectionBodyThresholds[]={0.6,0.7,0.8,0.9,1.0}; //разные уровни силы радиоактивной зоны
		};
		class Mask //Слот на персонаже
		{
			weight=2.5; //вес каждого из элементов защитного костюма
			protectionBodyValues[]={}; //защита слота при разных уровнях силы радиоактивной зоны (где 1.0 - 100%)
			protectionBodyThresholds[]={}; //разные уровни силы радиоактивной зоны
		};
	};
};
```
#### ПАРАМЕТР **weight**

Рассмотрим влияние (вес) на защиту у всех частей тела:
```cs
Feet - weight=0.5;
Legs - weight=1.0;
Body - weight=1.0;
Gloves - weight=0.5;
Headgear - weight=0.5;
Mask - weight=2.5;
Back - weight=0.0;
Armband - weight=0.0;
```

При любых числах указанных в весе - это всегда будет равно 100 процентам общей защиты.

Исходя из этого мы получаем следующие процентные соотношения.

Получаем общую сумму веса - (0,5 + 1,0 + 1,0 + 0,5 + 0,5 +2,5) = 6,0
Получаем процентное соотношение:
```cs
Feet - 0.5/6.0*100 = 8.33%;
Legs - 1.0/6.0*100 = 16.67%;
Body - 1.0/6.0*100 = 16.67%;
Gloves - 0.5/6.0*100 = 8.33%;
Headgear - 0.5/6.0*100 = 8.33%;
Mask - 2.5/6.0*100 = 41.67%;
Back - 0.0/6.0*100 = 0.0%;
Armband - 0.0/6.0*100 = 0.0%;
```
Исходя из этих процентов, мы понимаем что отсутствие противогаза, который имеет наибольшее влияние (вес) (41.67%), значительно снижает общий уровень защиты. Например, если противогаз отсутствует, суммарное влияние (вес) остальных частей костюма составит всего **58.33%** от общей защиты. Таким образом мы можем настраивать в какой части тела у нас будет находится часть костюма с наибольшим или наименьшим влиянием на расчет общей защиты костюма.

#### ПАРАМЕТРЫ **protectionBodyValues** и **protectionBodyThresholds**.

Значения protectionBodyValues зависимы от значений protectionBodyThresholds. Где protectionBodyValues  является процентным соотношением защиты у части тела, а protectionBodyThresholds является силой зоны.
Рассмотрим часть тела `Gloves`
##### РЕДАКТИРОВАНИЕ GameOverrides.xml
```xml
<CfgTerjeScriptableProtection>
	<Radiation>
		<Gloves>
			<weight>0.5</weight>
			<protectionBodyValues type="[]">
				<i>1.0</i><i>0.75</i><i>0.5</i><i>0.25</i><i>0.0</i>
			</protectionBodyValues>
			<protectionBodyThresholds type="[]">
				<i>0.6</i><i>0.7</i><i>0.8</i><i>0.9</i><i>1.0</i>
			</protectionBodyThresholds>
		</Gloves>
	</Radiation>
</CfgTerjeScriptableProtection>
```
##### СОЗДАНИЕ Config.cpp
```cs
class Gloves
{
	weight=0.5;
	protectionBodyValues[]={1.0,0.75,0.5,0.25,0.0};
	protectionBodyThresholds[]={0.6,0.7,0.8,0.9,1.0};
};
```
>При силе зоны  которая меньше либо равна 0,6 (protectionBodyThresholds) - будет 100 процентная защита рук (значение 1,0 в protectionBodyValues) от радиоактивной зоны.

>При силе зоны  от 0,6 до 0,7 (protectionBodyThresholds) - будет 75 процентная защита рук (значение 0,75 в protectionBodyValues) от радиоактивной зоны.

Рассмотрим часть тела `Mask`
##### РЕДАКТИРОВАНИЕ GameOverrides.xml
```xml
<CfgTerjeScriptableProtection>
	<Radiation>
		<Mask>
			<weight>0.5</weight>
			<protectionBodyValues type="[]"></protectionBodyValues>
			<protectionBodyThresholds type="[]"></protectionBodyThresholds>
		</Mask>
	</Radiation>
</CfgTerjeScriptableProtection>
```
##### СОЗДАНИЕ Config.cpp
```cs
class Mask
{
	weight=2.5;
	protectionBodyValues[]={};
	protectionBodyThresholds[]={};
};
```
>При пустых параметрах `protectionBodyValues` и `protectionBodyThresholds`, защита на данную часть тела не распространяется.

Итог:

Допустим радиационная зона имеет общую силу 2.5. По краям этой зоны, радиация слабее и начинается от 0,01 на увеличение ближе к центру зоны. При параметрах которые мы рассмотретли выше, на краю зоны по слоту рук не будет проходить заражение, а по слоту маски будет. При этом если в слоте маски будет находиться противогаз мы добиваемся того что для нахождения в слабозараженной части зоны нам достаточно только противогаза (при условии что остальным частям тела тоже прописаны параметры protectionBodyValues и protectionBodyThresholds). Но при продвижении ближе к центру зоны потребуется уже полный комплект защитного костюма.

### ДОБАВЛЕНИЕ ПРЕДМЕТА С ЗАРАЖЕНИЕМ/ЛЕЧЕНИЕМ РАДИАЦИИ

Вы можете любому предмету основанному на **Inventory_Base** добавить возможность заражения радиацией или лечения от нее, при нахождении данного предмета в инветаре игрока.

Для создания такого предмета вам понадобится взять какой либо свой предмет и добавить этому предмету следующий параметр - **terjeStaticRadiationValue**.
Возьмем за пример камень - **Stone** с возможностью добавления/удаления радиации

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода

##### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих предметов.
```xml
<CfgVehicles>
	<Stone>
		<terjeStaticRadiationValue>500</terjeStaticRadiationValue> <!-- Добавляет радиацию игроку при нахождении предмета в инвентаре -->
		<!-- <terjeStaticRadiationValue>-10</terjeStaticRadiationValue>  Удаляет радиацию у игрока при нахождении предмета в инвентаре -->
	</Stone>
</CfgVehicles>
```
##### СОЗДАНИЕ Config.cpp
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
			"TerjeRadiation"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class Stone: Inventory_Base
	{
	terjeStaticRadiationValue=10; // Добавляет радиацию игроку при нахождении предмета в инвентаре
	//terjeStaticRadiationValue=-10; //Удаляет радиацию у игрока при нахождении предмета в инвентаре
	};
};
```

## TerjeSkills
### НАСТРОЙКИ СКИЛОВ И ПЕРКОВ
**Config.cpp** с полным списком перков и их настройками - [ссылка](../../../TerjeSkills/config.cpp#L68).

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода

##### РЕДАКТИРОВАНИЕ GameOverrides.xml
```xml
<CfgTerjeSkills>
	<Athletic>
		<!-- Включить, выключить навык -->
		<enabled>1</enabled> 
		<!-- Сколько начисляется очков перков за каждый прокаченный уровень -->
		<perkPointsPerLevel>1</perkPointsPerLevel>
		<!-- Сколько вычитается опыта из навыка при смерти -->
		<expLoseOnDeath>-500</expLoseOnDeath>
		<!-- Колличество уровней и требуемое кол-во очков для получения следующего уровня -->
		<levels type="[]">
			<!-- 1-10 - каждое значение через запятую равно уровню, в данной строке 10 уровней -->
			<i>100</i><i>200</i><i>300</i><i>400</i><i>500</i><i>700</i><i>900</i><i>1100</i><i>1300</i><i>1500</i>
			<!-- c 11 по 20 уровень -->
			<i>1750</i><i>2000</i><i>2250</i><i>2500</i><i>2750</i><i>3000</i><i>3500</i><i>4000</i><i>4500</i><i>5000</i>
			<!-- c 21 по 30 уровень -->
			<i>6000</i><i>6750</i><i>7500</i><i>8250</i><i>9000</i><i>10000</i><i>11000</i><i>12000</i><i>13000</i><i>14000</i>
			<!-- c 31 по 40 уровень -->
			<i>16000</i><i>18000</i><i>20000</i><i>22000</i><i>24000</i><i>26000</i><i>28000</i><i>30000</i><i>32000</i><i>34000</i>
			<!-- c 41 по 50 уровень -->
			<i>37000</i><i>40000</i><i>43000</i><i>46000</i><i>50000</i><i>55000</i><i>60000</i><i>70000</i><i>80000</i><i>100000</i> 
		</levels>
		<Modifiers>
			<!-- Модификатор навыка который сумируется за все уровни.-->
			<MaxStaminaModifier>
				<!-- Включить, выключить модификатор -->
				<enabled>1</enabled>
				<!-- Значение за 1 уровень -->
				<value>0.02</value> 
			</MaxStaminaModifier>
		</Modifiers>
		<Perks>
			<!-- Название перка -->
			<QuickFeet>
				<!-- Включить, выключить перк -->
				<enabled>1</enabled>
				<!-- Количество стадий у перка -->
				<stagesCount>6</stagesCount>
				<!-- Уровни скила необходимые для получения следующей стадии перка -->
				<requiredSkillLevels type="[]"> 
					<i>1</i><i>10</i><i>20</i><i>30</i><i>40</i><i>45</i>
				</requiredSkillLevels>
				<!-- Кол-во очков перков необходимое для активации соответсвующей стадии перка -->
				<requiredPerkPoints type="[]"> 
					<i>1</i><i>2</i><i>3</i><i>4</i><i>5</i><i>10</i>
				</requiredPerkPoints>
				<!-- Значение используемое в скриптах для каждой стадии навыка. Меняйте только если понимаете как оно работает. -->
				<values type="[]"> 
					<i>-0.05</i><i>-0.1</i><i>-0.2</i><i>-0.3</i><i>-0.4</i><i>-0.8</i>
				</values>
			</QuickFeet>
		</Perks>
	</Athletic>
</CfgTerjeSkills>
```

##### СОЗДАНИЕ Config.cpp
Для настройки перков вам потребуется создать свой мод с файлом config.cpp в корне своего мода **TerjeModding**.

Разберем пример **config.cpp** для настроек скила **Атлетика** и перка **Быстрые ноги**.
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
		enabled=1; // Включить, выключить навык
		perkPointsPerLevel=1; // Сколько начисляется очков перков за каждый прокаченный уровень
		expLoseOnDeath=-100; // Сколько вычитается опыта из навыка при смерти
		levels[]= // Колличество уровней и требуемое кол-во очков для получения следующего уровня
		{
			100, 200, 300, 400, 500, 700, 900, 1100, 1300, 1500, // 1-10 - каждое значение через запятую равно уровню, в данной строке 10 уровней
			1750, 2000, 2250, 2500, 2750, 3000, 3500, 4000, 4500, 5000, // c 11 по 20 уровень
			6000, 6750, 7500, 8250, 9000, 10000, 11000, 12000, 13000, 14000, // с 20 по 30 уровень
			16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // с 31 по 40 уровень
			37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // с 41 по 50 уровень
		};
		class Modifiers
		{
			class MaxStaminaModifier // Модификатор навыка который сумируется за все уровни.
			{
				enabled=1; // Включить, выключить модификатор
				value=0.02; // Значение за 1 уровень
			};
		};
		class Perks
		{
			class QuickFeet
			{
				enabled=1; // Включить, выключить перк
				stagesCount=6; // Количество стадий у перка
				requiredSkillLevels[]={1,10,20,30,40,50}; // Уровни скила необходимые для получения следующей стадии перка
				requiredPerkPoints[]={1,2,3,4,5,10}; // Кол-во очков перков необходимое для активации соответсвующей стадии перка
				values[]={-0.05,-0.1,-0.2,-0.3,-0.4,-0.8}; // Значение используемое в скриптах для каждой стадии навыка. Меняйте только если понимаете как оно работает.
			};
		};
	};
};
```

Основные ответы по параметрам:
- вы можете настраивать любое количество уровней скила при помощи массива **levels[]**
- названия классов строго запрещено изменять, поломаете мод
- параметр **values[]** это процентное соотношение влияния перка (т.е 0,05 - 5%)
- при изменении параметра **values[]** в перках обращайте внимание на их значение. Если оно изначально стоит отрицательное, значит и последующие настройки производите с отрицательным значением.
- для изменения количества стадий прокачки вы можете изменить параметр **stagesCount** на требуемое количество, но при этом вы так же должны изменить количество стадий в полях **requiredSkillLevels**, **requiredPerkPoints**, **values[]**.
- максимальное количество стадий перков равно - 10
#### НАСТРОЙКИ ПОЛУЧАЕМОГО ОПЫТА 
##### МОДОВЫЕ ЖИВОТНЫЕ, ЗОМБИ, РЫБА

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода
###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих животных, зомбей.
```xml
<CfgVehicles>
	<Zmb_mutant> <!-- Зомби мутант -->
		<!-- Количество очков охоты начисляемое за убийство. -->
		<terjeOnKillHuntingExp>500</terjeOnKillHuntingExp>
		<!-- Количество очков охоты начисляемое при поподании в голову. -->
		<terjeOnHeadshotHuntingExp>250</terjeOnHeadshotHuntingExp>
		<!-- Количество очков охоты начисляемое при разделывании. -->
		<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
	</Zmb_mutant>
	<BlackWolf> <!-- Зомби мутант -->
		<!-- Количество очков охоты начисляемое за убийство. -->
		<terjeOnKillHuntingExp>500</terjeOnKillHuntingExp>
		<!-- Количество очков охоты начисляемое при поподании в голову. -->
		<terjeOnHeadshotHuntingExp>250</terjeOnHeadshotHuntingExp>
		<!-- Количество очков охоты начисляемое при разделывании. -->
		<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
		<!-- Вкл/Откл партиклов, отображаемых при прокаченном перке "Следопыт". -->
		<terjeHighlightWithPathfinder>0</terjeHighlightWithPathfinder> 
	</BlackWolf>
	<Squirrel> <!-- Белка -->
		<!-- Количество очков охоты начисляемое за убийство. -->
		<terjeOnKillHuntingExp>400</terjeOnKillHuntingExp>
		<!-- Количество очков охоты начисляемое при поподании в голову. -->
		<terjeOnHeadshotHuntingExp>100</terjeOnHeadshotHuntingExp>
		<!-- Количество очков охоты начисляемое при разделывании. -->
		<terjeOnButchHuntingExp>100</terjeOnButchHuntingExp>
		<!-- Вкл/Откл партиклов, отображаемых при прокаченном перке "Следопыт". -->
		<terjeHighlightWithPathfinder>1</terjeHighlightWithPathfinder> 
	</Squirrel>
	<DeadSquirrel> <!-- Мертвая белка (Так как небольшие животные после убийства изменяют свой класс -->
		<!-- Количество очков охоты начисляемое при разделывании. -->
		<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
	</DeadSquirrel>
	<Pike> <!-- Щука -->
		<!-- Количество очков охоты начисляемое при разделывании. -->
		<terjeOnButchHuntingExp>250</terjeOnButchHuntingExp>
	</Pike>
</CfgVehicles>
```
###### СОЗДАНИЕ Config.cpp
**Config.cpp** с образцом настройки ванильных животных - [ссылка](../../../TerjeSkills/Animals/config.cpp#L47).

Для настройки получения опыта при убийстве модовых животных и зомби вам потребуется создать файл config.cpp в корне своего мода **TerjeModding**.

Разберем пример **config.cpp** на добавление модовых животных - **BlackWolf**, **Squirrel**, зомби - **Zmb_mutant** и модовой рыбы - **Pike**

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
			"TerjeSkills",
			"Mod_BlackWolf", //Не забудьте прописать class CfgPatches редактируемого животного
			"Mod_Squirrel", //Не забудьте прописать class CfgPatches редактируемого животного
			"Mod_Zmb_mutant", //Не забудьте прописать class CfgPatches редактируемого зомби
			"Mod_Pike" //Не забудьте прописать class CfgPatches редактируемого животного
		};
	};
};
class CfgVehicles
{
	class AnimalBase;
	class ZombieBase;
	class Edible_Base;

	class Zmb_mutant: ZombieBase //Зомби мутант
	{
		terjeOnKillHuntingExp = 500; //Количество очков охоты начисляемое за убийство.
		terjeOnHeadshotHuntingExp = 250; //Количество очков охоты начисляемое при поподании в голову.
		terjeOnButchHuntingExp = 250; //Количество очков охоты начисляемое при разделывании.
	};
	class BlackWolf: AnimalBase //Черный Волк
	{
		terjeOnKillHuntingExp = 500; //Количество очков охоты начисляемое за убийство.
		terjeOnHeadshotHuntingExp = 250; //Количество очков охоты начисляемое при поподании в голову. (при смерти учитывается был ли последний зарегистрированный урон в голову)
		terjeOnButchHuntingExp = 250; //Количество очков охоты начисляемое при разделывании.
		terjeHighlightWithPathfinder = 0; //Вкл/Откл партиклов, отображаемых при прокаченном перке "Следопыт".
	};
	class Squirrel: AnimalBase //Белка
	{
		terjeOnKillHuntingExp = 500; //Количество очков охоты начисляемое за убийство.
		terjeOnHeadshotHuntingExp = 250; //Количество очков охоты начисляемое при поподании в голову. (при смерти учитывается был ли последний зарегистрированный урон в голову)
		terjeHighlightWithPathfinder = 0; //Вкл/Откл партиклов, отображаемых при прокаченном перке "Следопыт".
	};
	class DeadSquirrel: Edible_Base //Мертвая белка (Так как небольшие животные после убийства изменяют свой класс в игре, то для добавления очков за разделку нужно использовать класс Dead..... )
	{
		terjeOnButchHuntingExp = 250; //Количество очков охоты начисляемое при разделывании.
	};
	class Pike: Edible_Base //Щука
	{
		terjeOnButchFishingExp = 250; //Количество очков охоты начисляемое при разделывании.
	};
};
```

#### НАСТРОЙКИ СКОРОСТИ РАЗДЕЛКИ
Вы можете настроить скорость разделки животных для любого типа ножа.

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода
###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих предметов.
```xml
<CfgVehicles>
	<HuntingKnife> <!--  Ванильный нож 5 секунд -->
		<!--  модификатор резки ножа с учетом навыков. -->
		<terjeSkinningTimeModifier>0.5</terjeSkinningTimeModifier> 
		<!--
		 Т.е. например стандартное время резки 10 секунд. 
		Четвертый уровень навыка "Быстрой резки" дает модификатор 0.6, нож дает еще модификатор 0.5. 
		В итоге получаем 10 * 0.6 * 0.5 = 3 сек при 4 уровне перка. (5 секунд без навыка)
		-->
	</HuntingKnife>
	<CustomKnifeFast> <!-- Модовый нож с быстрой резкой игнорирующий прокачку навыка -->
		<!--  модификатор резки ножа игнорирующий прокачку навыка. -->
		<terjeSkinningModifierOverride>0.1</terjeSkinningModifierOverride> 
		<!--
		 Т.е. например стандартное время резки 10 секунд. 
		Модификатор перка не учитывается. 
		В итоге получаем 10 * 0.1 = 1 сек.
		-->
	</CustomKnifeFast>
</CfgVehicles>
```
###### СОЗДАНИЕ Config.cpp
**Config.cpp** с образцом настройки ванильных ножей - [ссылка](../../../TerjeSkills/Knifes/config.cpp#L19).

Для настройки скорости разделки вам потребуется создать файл config.cpp в корне своего мода **TerjeModding**.

Разберем пример **config.cpp** на модифицирование модового ножа - **YourCustomKnife_1**, **YourCustomKnife_2**, ванильного - **HuntingKnife**.
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
			"TerjeSkills", 
			"DZ_Gear_Tools", 
			"DZ_Weapons_Melee_Blade", //Класс CfgPatches ванильных ножей
			"КЛАСС CfgPatches ВАШЕГО МОДОВОГО НОЖА"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	
	class HuntingKnife: Inventory_Base // Ванильный нож
	{
		terjeSkinningTimeModifier = 0.75; //модификатор резки ножа с учетом навыков.
			// Т.е. например стандартное время резки 10 секунд. 
			// Четвертый уровень навыка "Быстрой резки" дает модификатор 0.6, нож дает еще модификатор 0.75. 
			// В итоге получаем 10 * 0.6 * 0.75 = 4,5 сек при 4 уровне перка. (7,5 секунд без навыка)
	};
	class CustomKnife5seconds: Inventory_Base // Модовый нож 5 секунд
	{
		terjeSkinningTimeModifier = 0.5; //модификатор резки ножа с учетом навыков.
			// Т.е. например стандартное время резки 10 секунд. 
			// Четвертый уровень навыка "Быстрой резки" дает модификатор 0.6, нож дает еще модификатор 0.5. 
			// В итоге получаем 10 * 0.6 * 0.5 = 3 сек при 4 уровне перка. (5 секунд без навыка)
	};
	class CustomKnifeFast: Inventory_Base // Модовый нож с быстрой резкой
	{
		terjeSkinningTimeModifierOverride = 0.1; //модификатор резки ножа игнорирующий прокачку навыка.
			// Т.е. например стандартное время резки 10 секунд. 
			// Модификатор перка не учитывается.
			// В итоге получаем 10 * 0.1 = 1 сек.
	};
};
```

#### НАСТРОЙКИ КНИГ ОПЫТА
Вы можете настроить начисляемый опыт для любого перка при прочтении определенной книги.

Есть два варианта настройки:
- через редактирование файла **GameOverrides.xml** в папке **profiles\TerjeSettings\Core**
- через создание config.cpp и создание своего мода
###### РЕДАКТИРОВАНИЕ GameOverrides.xml
При это способе возможно редактирование только существующих книг.
```xml
<CfgVehicles>
	<TerjeBookAthletic1> <!--  Класс книги -->
		<terjeSkillId>athlc</terjeSkillId> <!--  ИД скилла который качает книга -->
		<terjeSkillMinLevel>0</terjeSkillMinLevel> <!--  Минимальный необходимый уровень -->
		<terjeSkillMaxLevel>10</terjeSkillMaxLevel> <!--  Максимальный допустимый уровень -->
		<terjeSkillExpGain>300</terjeSkillExpGain> <!--  Кол-во опыта после прочтения -->
	</TerjeBookAthletic1>
</CfgVehicles>
```
###### СОЗДАНИЕ Config.cpp

**Config.cpp** с образцом настройки ванильных ножей - [ссылка](../../../TerjeSkills/Books/config.cpp#L22).

Для настройки начисляемого опыта вам потребуется создать файл config.cpp в корне своего мода **TerjeModding**.

Разберем пример **config.cpp** на изменение опыта у книг - **TerjeBookAthletic1**, **TerjeBookAthletic5**.
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
			"TerjeSkills"
		};
	};
};

class CfgVehicles
{
	class TerjeBookBase;
	
	class TerjeBookAthletic1: TerjeBookBase //Класс книги наследуемый от TerjeBookBase
	{
		terjeSkillId="athlc"; // ИД скилла который качает книга
		terjeSkillMinLevel=0; // Минимальный необходимый уровень
		terjeSkillMaxLevel=10; // Максимальный допустимый уровень
		terjeSkillExpGain=300; // Кол-во опыта после прочтения
	};
	class YourCustomBookAthletic10: TerjeBookBase //Ваша кастомная книга наследуемая от TerjeBookBase
	{
		rotationFlags=1;
		displayName="#STR_TERJEMODDING_BOOK_ATHLETIC1"; //Название книги
		//descriptionShort= не добавляйте, вместо описания автоматически подтягиваются данные по кол-ву опыта и перка
		hiddenSelectionsTextures[]={ "TerjeModding\Books\data\book_athletic10_co.paa" }; //Путь до текстуры вашей книги
		terjeSkillId="athlc"; // ID скилла который качает книга
		terjeSkillMinLevel=30; // Минимальный необходимый уровень
		terjeSkillMaxLevel=50; // Максимальный допустимый уровень
		terjeSkillExpGain=10000; // Кол-во опыта после прочтения
	};
};
```

Для создания новой книги вам понадобятся ID скила.

ID скилов вы можете найти в config.cpp [ссылка](../../../TerjeSkills/Books/config.cpp#L22) с книгами.

##### Общий список ID

Название скила | ID |
|:-----------:|:-----------:|
| ИММУНИТЕТ  |   immunity|   
|  МЕДИЦИНА |   med|   
|  АТЛЕТИКА |   athlc|   
|  РЫБАЛКА |   fish|   
|  ОХОТА |   hunt|   
|  МЕТАБОЛИЗМ |   mtblsm|   
|  СКРЫТНОСТЬ |   stlth|   
|  СИЛА |   strng|   
|  ВЫЖИВАНИЕ |   surv|   





