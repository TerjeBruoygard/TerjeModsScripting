# TerjeMedicine

DayZ 的醫療模組

![image](/Wiki/logos/TerjeMedicine.jpg)


## 描述

這個模組為遊戲增加了一個更深入且更真實的健康系統，讓你能夠更深入地體驗在 DayZ 廣大景觀中生存的危險。 現在，每種疾病和傷害都有各自的階段、症狀和治療方法。探索並利用新的機制來維持你的健康，避免每一步都潛伏的危險。 每種症狀和疾病都需要獨特的治療方法。 這個模組包括了各種藥物、工具和診斷與治療方法，從簡單的包紮到複雜的手術。
**在全新的層次上測試你的生存技巧。監控你的角色狀況，避免疾病和感染摧毀你！**

## COMPONENTS

模組中包含的機制：

1. **預防與治療**
   + 藥物
   + 疫苗 **新推出!!!**
   + 手部與工具的消毒
     
2. **身體狀況**
   + 瘀傷
   + 子彈傷
   + 穿刺傷
   + 內部器官損傷
   + 手術縫合
   + 腦震盪

3. **感染與疾病**
   + 感冒
   + 食物中毒
   + 化學中毒
   + 輻射中毒
   + 喪屍病毒
   + 脓毒症
   + 狂犬病 **新推出!!!**

4. **症狀**
   + 疼痛
   + 藥物過量

5. **情緒狀態**
   + 睡眠
   + 心理狀態

6. **區域**
   + 輻射區
   + 精神區域

# 預防與治療

## ![image](/Wiki/images/tablets.png) 藥物

> 藥物分為三種類別：藥片、安瓿瓶和注射器。  
藥片通常用於疾病的早期階段和預防。  
每包藥片包含十顆。  
相同種類的藥片包裝可以合併使用。  
安瓿瓶包含強效藥物，用於治療中重度階段的複雜疾病或病症。  
玩家必須使用針筒來注射藥物。  
每次注射後，針筒會被污染，必須用酒精消毒或在火爐上用水煮沸來清潔。  
注射器與安瓿瓶類似，但不需要針筒。  
所有注射器都是一次性的。

## ![image](/Wiki/images/vaccine.png) 疫苗

> 疫苗可以讓你保護自己免受危險疾病的侵害，顯著降低感染的可能性。使用疫苗後，會對特定感染產生免疫力，幫助角色避免在污染環境中遭遇的疾病。提前使用疫苗來增強角色的免疫力，並始終監控是否需要重新接種以維持保護。

| 名稱       | 物品                      | Stage   | Form and Packaging | 持續時間（秒） | Overdose |
|:----------:|:-------------------------:|:-------:|:-------------------:|:------------:|:--------:|
| Vaxicam    | TerjeAmpouleVaxicam       | Vaccine | Ampoule             | 14400        | 0.8      |
| Zerivax    | TerjeAmpouleZerivax       | Vaccine | Ampoule             | 7200         | 1.5      |
| Rabivax    | TerjeAmpouleRabivax       | Vaccine | Ampoule             | 14400        | 1.3      |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medInfluenzaVacineTime  = 14400; // Vaccine against Cold
    medZVirusVacineTime     = 7200;  // Vaccine against Z Virus
    medRabiesVacineTime     = 14400; // Vaccine against Rabies
```

## ![image](/Wiki/images/desinfection.png) 消毒

> 保持無菌狀態並防止傷口感染的必要程序。
髒汙的醫療用品在使用前必須徹底消毒，以消除感染風險。
在進行任何操作或手術之前，手部也應進行消毒，尤其是在野外環境中，感染風險會增加。
消毒是極端條件下成功治療和健康安全的關鍵。

| 名稱                      | 物品                 | Stage        |
|:-------------------------:|:--------------------:|:------------:|
| Alcoholic Tincture        | 消毒酒精              | 消毒         |
| Disinfectant Spray        | 消毒噴霧              | 消毒         |

# 身體狀況

## ![image](/Wiki/images/hematoma.png) 血腫(瘀傷)

> 瘀傷可能是由於被喪屍擊中或受到鈍器攻擊所引起的。  
如果有很多瘀傷，健康狀況會開始下降。  
瘀傷會隨著時間自動癒合。  
使用藥膏可以加速其癒合過程。

| Name        | Item                  | Form and Packaging | Duration (s) | Overdose |
|:-----------:|:---------------------:|:-------------------:|:------------:|:--------:|
| Viprosal    | TerjeSalveViprosal    | Tube of ointment    | 300          | 0.0      |
| Capsicum    | TerjeSalveCapsicum    | Tube of ointment    | 400          | 0.0      |
| Finalgon    | TerjeSalveFinalgon    | Tube of ointment    | 600          | 0.0      |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medHematomaHeal=1; // Strength
    medHematomaHealTimeSec=400; // Duration (s)
```


## ![image](/Wiki/images/organs.png)  ![image](/Wiki/images/bullet.png)  ![image](/Wiki/images/cut3.png) 內臟器官損傷、槍傷和刺傷

> 玩家可能會因為槍械而受子彈傷。  
這種傷口特徵為劇烈出血，需立即包紮。  
使用止血繃帶進行包紮會比普通繃帶或布料更有效。  
包紮後，傷口會繼續輕微出血，直到使用手術包移除子彈。  
維護良好的防彈背心可以保護你免受子彈傷害。然而，防彈背心被穿透的機率是通過彈道計算器計算的。  
因此，輕型防彈背心可以保護你免受小口徑子彈的傷害，但無法防止中等和大口徑子彈。如果背心擋住了子彈，你會受到一個未裝甲的傷口，通常表現為瘀傷。

| Name                        | Item                             | Form and Packaging | Volume | Internal Organs (strength/time) | Bullet (strength/time) | StubEffectivity (strength/time) | 
|:---------------------------:|:--------------------------------:|:-------------------:|:------:|:-------------------------------:|:---------------------:|:--------------------------------:|
| Medical Bowl with Instrument (Ceramic)| TerjeSurgicalTool_Ceramic        | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Medical Bowl with Instrument (White)  | TerjeSurgicalTool_White          | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Field Surgical Kit                   | TerjeSurgicalKit                 | Surgical kit       | 5      | 0.2/40                          | 0.5/25                | 0.7/20                           |
| IFAK                        | TerjeFirstAidKitIndividual_Black | Universal kit      | 10     | 0.3/40                          | 0.6/30                | 0.8/20                           |
| AFAK                        | TerjeFirstAidKitAdvance_Black    | Universal kit      | 20     | 0.3/40                          | 0.6/30                | 0.8/20                           |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medBloodStop=3;
	medBloodHemostaticValue=3;
	medBloodHemostaticTimeSec=60; // Duration (s)
	terjeSurgeryKitRefill=1;
	terjeSurgeryVisceraEffectivity=0.3; // Chance to heal
	terjeSurgeryVisceraTime=40; // Duration (s)
	terjeSurgeryBulletEffectivity=0.6; // Chance to heal
	terjeSurgeryBulletTime=30; // Duration (s)
	terjeSurgeryStubEffectivity=0.8; // Chance to heal
	terjeSurgeryStubTime=20; // Duration (s)
```

## ![image](/Wiki/images/cut2.png) 手術縫合線

| Name                      | Item                             | Form and Packaging | Volume | Internal Organs (strength/time) | Bullet (strength/time) | StubEffectivity (strength/time) | 
|:-------------------------:|:--------------------------------:|:-------------------:|:------:|:-------------------------------:|:---------------------:|:--------------------------------:|
| Medical Bowl with Instrument (Ceramic) | TerjeSurgicalTool_Ceramic      | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Medical Bowl with Instrument (White) | TerjeSurgicalTool_White        | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Field Surgical Kit                  | TerjeSurgicalKit               | Surgical kit       | 5      | 0.2/40                          | 0.5/25                | 0.7/20                           |
| IFAK                       | TerjeFirstAidKitIndividual_Black | Universal kit      | 10     | 0.3/40                          | 0.6/30                | 0.8/20                           |
| AFAK                       | TerjeFirstAidKitAdvance_Black  | Universal kit      | 20     | 0.3/40                          | 0.6/30                | 0.8/20                           |

## ![image](/Wiki/images/brain.png) 腦震盪

>頭部受到鈍器的強力打擊、角色附近的爆炸或使用防彈頭盔時被小口徑子彈擊中都會發生腦震盪。腦震蕩的最初症狀包括頭痛、頭暈、協調性不穩定和視力模糊，這使得行動和戰鬥變得困難。隨著時間的推移，腦震盪會自行消退，但為了加速康復，您可以使用特殊藥物來減輕症狀的強度。

Name  | Item | Stage | Level | Form and Packaging | Duration (sec) | Overdose |
|:-----------:|:-----------:|:-----------:|:-----:|:---------:|:-------------:|:------------------:|
|  Noopept  | TerjePillsNoopept | Treatment | -   |   Tablets  |      380      |         0.35        |
|   Neirox  | TerjeAmpouleNeirox | Treatment | -   |   Ampoule  |      600      |        0.6        |
|   Neirox  | TerjeInjectorNeirox | Treatment | -  |   Injector  |      500      |        0.3        |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medConcussionHealTimeSec = 300; // Duration (sec)
    overdosedIncrement = 0.3; // Overdose
```

# 感染和疾病

## ![image](/Wiki/images/influenza.png) COLD / 肺炎

> 暴露在低溫下可能會感冒或感染流感。
隨著時間的推移，感冒可能會發展為輕度，並最終發展為肺炎。
當患有肺炎時，你的角色會開始慢慢失去健康。
使用同級別或更高級別的抗生素進行治療。
可能需要多次服用藥物才能完全康復。
輕微的感冒可以透過在溫暖的地方睡覺來治癒。

| Name          | Item                     | Stage    | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------:|:------------------------:|:--------:|:-----:|:-------------------:|:------------:|:--------:|
| Tetracycline  | TetracyclineAntibiotics  | Treatment| 1     | Tablets             | 300          | 0.45     |
| Paracetamol   | TerjePillsParacetamol    | Treatment| 1     | Tablets             | 200          | 0.45     |
| Ibuprofen     | TerjePillsIbuprofen      | Treatment| 2     | Tablets             | 300          | 0.35     |
| Nurofen       | TerjePillsNurofen        | Treatment| 2     | Tablets             | 300          | 0.52     |
| Amoxiclav     | TerjePillsAmoxiclav      | Treatment| 2     | Tablets             | 1200         | 0.75     |
| Piperacillin  | TerjePillsPiperacylin    | Treatment| 2     | Tablets             | 1100         | 0.45     |
| Ketarol       | TerjeAmpouleKetarol      | Treatment| 2     | Ampoule             | 1200         | 0.5      |
| Amoxivan      | TerjeAmpouleAmoxivan     | Treatment| 2     | Ampoule             | 900          | 0.3      |
| Topoisomerase | TerjeInjectorTopoizomeraza| Treatment| 3     | Injector            | 900          | 0.65     |
| Imipenem      | TerjeAmpouleImipenem     | Treatment| 3     | Ampoule             | 900          | 0.7      |
| Flemoclave     | TerjeAmpouleFlemoclav    | Treatment| 3     | Ampoule             | 1200         | 0.8      |
| Amoxiclav     | TerjeInjectorAmoxiclav   | Treatment| 3     | Injector            | 1800         | 0.6      |
| Vaxicam       | TerjeAmpouleVaxicam      | Vaccine  | -     | Ampoule             | 14400        | 0.8      |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medAntibioticLevel = 1; // Strength
    medAntibioticsTimeSec = 300; // Duration (s)
    overdosedIncrement = 0.45; // Overdose
```

## ![image](/Wiki/images/poisoning.png) 食物中毒

> 食用變質或未煮熟的食物、腐爛的水果、有毒的蘑菇、髒水或意外攝入汽油都可能導致食物中毒。
食用此類食物後立即出現噁心和嘔吐等症狀。
如果不及時治療，你的角色的病情可能會惡化，導致脫水和隨後的健康損失。
要治療它，請多喝水並使用特殊藥物來緩解症狀。

| Name                | Item                       | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------------:|:-------------------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| Charcoal  | CharcoalTablets           | Treatment |   1   | Tablets           |      300     |   0.01   |
| Polysorb            | TerjePillsPolisorb        | Treatment |   1   | Tablets           |      300     |   0.05   |
| Phthalazole          | TerjePillsFtalazol        | Treatment |   1   | Tablets           |     1200     |   0.25   |
| Mesalazine          | TerjePillsMesalazin       | Treatment |   2   | Tablets           |      600     |   0.35   |
| Chelating Tablets   | ChelatingTablets          | Treatment |   2   | Tablets           |      600     |   0.6    |
| Metoclopramid      | TerjeAmpouleMetoclopramid | Treatment |   2   | Ampoule           |     1200     |   0.4    |
| Heptral             | TerjeAmpouleHeptral       | Treatment |   3   | Ampoule           |      600     |   0.6    |
| Stomaproxidal       | TerjeInjectorStomaproxidal| Treatment |   3   | Injector          |      900     |   0.68   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medAntipoisonLevel = 1; // Strength
    medAntipoisonTimeSec = 300; // Duration (s)
    overdosedIncrement = 0.45; // Overdose
```

## ![image](/Wiki/images/biohazard.png) 化學中毒

>化學中毒是由於吸入有毒氣體而發生的。早期症狀包括咳嗽。隨著中毒的進展，會出現嘔吐、噁心等症狀。在後期階段，化學中毒會導致嚴重的健康損失，如果不及時治療可能會致命。
要治療中毒，請服用解毒劑或減少毒性作用的特殊藥物。

| Name             | Item                      | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:----------------:|:------------------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| Rombiopental     | TerjePillsRombiopental   | Treatment |   1   | Tablets           |       30     |   0.15   |
| Neuroсetal       | TerjeAmpouleNeirocetal   | Treatment |   2   | Ampoule           |      500     |   1.25   |
| AntiChem Injector | AntiChemInjector         | Treatment |   3   | Injector          |      180     |   1.1    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medAntibiohazardLevel = 1; // Strength
	medAntibiohazardTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/Wiki/images/radiation.png) 輻射中毒

>處於高輻射水平的區域或接觸受污染的物品會導致輻射中毒。早期症狀包括虛弱、噁心和頭暈。隨著時間的推移，角色可能會出現流血和免疫系統減弱的情況。在後期，輻射中毒會導致嚴重的健康損失和身體疲憊，威脅角色的生命。
要治療輻射中毒，請服用消除體內輻射的藥物，例如碘片或抗輻射藥物。避開輻射區域或使用防護裝備以盡量減少暴露。

| Name                        | Item                          | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:---------------------------:|:----------------------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| B190                       | TerjePillsB190               | Treatment |   1   | Tablets           |      140     |   0.3    |
| Potassium Iodide           | TerjePillsPotassiumIodide    | Treatment |   1   | Tablets           |       60     |   0.2    |
| Hexacyanoferrate           | TerjePillsHexacyanoferrate   | Treatment |   1   | Tablets           |      120     |   0.3    |
| Mexamine                   | TerjePillsMexamine           | Treatment |   2   | Tablets           |       25     |   0.75   |
| Pentacin                   | TerjeAmpoulePentacin         | Treatment |   2   | Ampoule           |      400     |   0.5    |
| Carboxyme     | TerjeAmpouleCarboxyme        | Treatment |   2   | Ampoule           |      600     |   0.6    |
| Radioprotector             | TerjeInjectorRadioprotector  | Treatment |   3   | Injector          |      600     |   0.75   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medAntiradLevel = 1; // Strength
	medAntiradTimer = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/Wiki/images/virusz.png) 殭屍病毒

>殭屍病毒透過空氣中的飛沫和體液傳播。在與殭屍的近距離戰鬥中，有很小的幾率被感染。如果殭屍對你造成傷害，幾率就會增加。使用面罩和防彈衣以減少感染的可能性。該病毒有很長的潛伏期。玩家有一個多小時的即時時間來尋找解藥。在感染的末期，您的健康狀況開始迅速惡化。

| Name      | Item                      | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:---------:|:-------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Zivirol   | TerjeAmpouleZivirol       | Treatment |   -   | Ampoule           |     1000     |   2.35   |
| Zivirol   | TerjeInjectorZivirol      | Treatment |   -   | Injector          |     1200     |   2.5    |
| Zerivax   | TerjeAmpouleZerivax       | Vaccine   |   -   | Ampoule           |     7200     |   1.5    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medZAntidotTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
	terjeAddHealth = -20; // Health reduction upon medicine injection
	terjeAddBlood = -10; // Blood reduction upon medicine injection
	terjeAddShock = -100; // Shock reduction upon medicine injection
```

## ![image](/Wiki/images/blood2.png) 敗血症

>當感染進入開放性傷口時就會發生敗血症。
殭屍抓傷、刀傷或槍傷都有可能發生這種情況，機率很小。
如果您用髒手處理開放性傷口，也很有可能發生這種情況。
如果不及時治療，敗血症會隨著時間的推移逐漸導致您的健康狀況惡化。

| Name          | Item                        | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------:|:---------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Flemoclav     | TerjeAmpouleFlemoclav       | Treatment |   3   | Ampoule           |     1200     |   0.8    |
| Imipenem      | TerjeAmpouleImipenem        | Treatment |   3   | Ampoule           |      900     |   0.7    |
| Amoxiclav     | TerjeInjectorAmoxiclav      | Treatment |   3   | Injector          |      300     |   0.6    |
| Topoisomerase | TerjeInjectorTopoizomeraza  | Treatment |   3   | Injector          |      600     |   0.65   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medAntibioticLevel = 1; // Strength
	medAntisepsisTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/Wiki/images/virus.png) 狂犬病

>狂犬病透過受感染動物（例如狼）的叮咬傳播。感染後，病情逐漸進展，不會立即出現症狀。
在早期階段，溫度波動和弱點開始出現，這可能會被忽略。
在第二階段，病情惡化－角色出現嚴重的噁心和嘔吐，無法進食或飲水。
在第三個關鍵階段，氣溫飆升，導致健康迅速喪失、精疲力盡和無法有效生存。
如果不及時治療，這種疾病將不可避免地導致死亡。在感染前使用特殊藥物進行早期治療或接種疫苗可以防止疾病惡化。

| Name            | Item                      | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:---------------:|:-------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Rifampicin     | TerjeAmpouleRifampicyne  | Treatment |   3   | Ampoule           |      300     |   1.35   |
| Rabinoline      | TerjeAmpouleRabinoline   | Treatment |   2   | Ampoule           |      600     |   0.8    |
| Rabinucoline    | TerjeInjectorRabinucoline| Treatment |   3   | Injector          |      900     |   1.46   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medRabiesAntibioticLevel = 1; // Strength
	medRabiesAntibioticTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

# 症狀

## ![image](/Wiki/images/pain.png) 疼痛

>疼痛是由各種傷害引起的。
疼痛的強度取決於創傷的嚴重程度。
一段時間後疼痛會自行消退。
為了緩解疼痛，請使用相應等級或更高等級的止痛藥。

| Name             | Item                      | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:----------------:|:-------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Painkiller       | PainkillerTablets         | Treatment |   1   | Tablets           |      300     |   0.2    |
| Analgin          | TerjePillsAnalgin         | Treatment |   1   | Tablets           |      500     |   0.15   |
| Nimesulide        | TerjePillsNimesulid       | Treatment |   1   | Tablets           |      600     |   0.25   |
| Paracetamol      | TerjePillsParacetamol     | Treatment |   1   | Tablets           |      200     |   0.45   |
| Ibuprofen        | TerjePillsIbuprofen       | Treatment |   1   | Tablets           |      600     |   0.35   |
| Nurofen          | TerjePillsNurofen         | Treatment |   1   | Tablets           |      350     |   0.52   |
| Noopept          | TerjePillsNoopept         | Treatment |   1   | Tablets           |      380     |   0.35   |
| Ketarol          | TerjeAmpouleKetarol       | Treatment |   1   | Ampoule           |     1200     |   0.5    |
| Novacaine        | TerjeAmpouleNovacaine     | Treatment |   2   | Ampoule           |     1200     |   0.4    |
| Morphinocin         | TerjeAmpouleMorphine      | Treatment |   3   | Ampoule           |      850     |   0.52   |
| Hexobarbital     | TerjeAmpouleGexobarbital  | Treatment |   3   | Ampoule           |      900     |   0.65   |
| Reanimatal       | TerjeInjectorReanimatal   | Treatment |   1   | Injector          |      240     |   1.85   |
| Morphine         | Morphine                  | Treatment |   3   | Injector          |      300     |   0.75   |
| Promidol         | TerjeInjectorPromidol     | Treatment |   3   | Injector          |      600     |   0.45   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medPainkillerLevel = 1; // Strength
	medPainkillerTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/Wiki/images/overdose.png) 藥物過量

>當過量的藥物或有毒物質進入體內時，就會發生藥物過量。
隨著毒素從系統中排出，過量的藥物逐漸減弱。它經歷三個階段：

>**第一階段:** 角色會感到噁心和幻覺，失去清晰的知覺。

>**第二階段:** 病情惡化，角色可能會失去意識，變得容易受到環境的影響。

>**第三階段:** 健康狀況嚴重惡化，威脅角色的生命。

| Name          | Item          | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------:|:-------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| Water         | WaterBottle   | Treatment |   1   | Bottle            |      300     |   0.0    |

# 情緒狀態

## ![image](/Wiki/images/dream.png) 睡覺

>你的角色現在需要睡眠，就像食物和水一樣。定期休息對於保持健康和體力是必要的。
如果睡眠指示燈變黃，角色就會開始打哈欠，視力也會逐漸惡化。
當指示器達到紅色水平時，角色可能會因精疲力竭而失去知覺。
溫暖的地方是睡覺的理想場所——壁爐附近、帳篷裡、房子或睡袋裡。
如果角色處於寒冷、飢餓或有嚴重的健康問題（第二階段及以上疾病），則無法入睡。
在睡眠期間，角色會迅速恢復健康，並可能以很小的機率從輕微疾病（例如第一階段流感）中康復。
睡袋提供額外的溫暖和舒適，使睡眠在惡劣條件下更安全、更有效。

| Name               | Item                | Stage          | Level | Form and Packaging | Duration (s) | Overdose |
|:------------------:|:------------------:|:--------------:|:-----:|:------------------:|:------------:|:--------:|
| MadBull® Energy Drink     | TerjeDrinkMadBull  | Recovery       |   8   | Bottle            |      1.0     |   0.0    |
| Gang® Energy Drink        | TerjeDrinkGang     | Recovery       |   6   | Bottle            |      1.0     |   0.0    |
| Yaguar® Energy Drink      | TerjeDrinkYaguar   | Recovery       |  10   | Bottle            |      1.0     |   0.0    |
| PrayBoy® Energy Drink     | TerjeDrinkPrayboy  | Recovery       |   4   | Bottle            |      1.0     |   0.0    |
| 6Energy® Energy Drink      | TerjeDrink6Energy  | Recovery       |   8   | Bottle            |      0.8     |   0.0    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medSleepingIncrementValue = 8; // Strength
	medSleepingIncrementTimeSec = 0.8; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/Wiki/images/mental.png) 精神狀態

>角色的精神狀態在極度壓力下會惡化：殭屍攻擊、長時間暴露在危險的靈能區以及食用人肉都會導致神經衰弱和幻覺。
在這種情況下，角色可能會感到恐慌和迷失方向，使生存和與環境的互動變得複雜。
為了緩解症狀，可以使用抗憂鬱藥物來穩定心理並減輕壓力因素的負面影響。

| Name              | Item                         | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:-----------------:|:----------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Adepress          | TerjePillsAdepress          | Treatment |   1   | Tablets           |      150     |   0.2    |
| Agteminol         | TerjePillsAgteminol         | Treatment |   1   | Tablets           |      120     |   0.2    |
| Venlafaxine       | TerjePillsVenlafaxine       | Treatment |   1   | Tablets           |      250     |   0.3    |
| Actaparoxetine    | TerjeAmpouleActaparoxetine  | Treatment |   2   | Ampoule           |      400     |   0.4    |
| Amitriptyline     | TerjeAmpouleAmitriptyline   | Treatment |   3   | Ampoule           |      600     |   0.4    |
| Metralindole      | TerjeAmpouleMetralindole    | Treatment |   2   | Ampoule           |      300     |   0.1    |
| Amfitalicyne      | TerjeInjectorAmfitalicyne   | Treatment |   3   | Injector          |      520     |   0.6    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medAntidepresantLevel = 1; // Strength
	medAntidepresantTimer = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

# 區域

# ☢️ 輻射區

輻射區是**輻射水平較高的危險區域**，對倖存者的生命構成嚴重威脅。
拜訪他們需要充分的準備並使用防護裝備。

## ⚠️ 污染如何運作：
1. **輻射透過以下方式積聚在體內**作為「輻射緩衝器」：
   - 處於輻射區。
   - 接觸受污染的物品。
2. The **radiation buffer** gradually causes [Radiation Poisoning](#image-radiation-poisoning), which develops as radiation accumulates.  
3. **Objects and clothing also become contaminated**:
   - All items in the radiation zone, including vehicles, accumulate radiation.
   - Items worn by the character also become radioactive.

## 🩸 Effects of Irradiation:
- A person **does not die directly from radiation**, but:
  - Severe irradiation causes [Radiation Poisoning](#image-radiation-poisoning).
  - Mild irradiation weakens the body, provoking other ailments.

## 🧽 How to Decontaminate Items:
After leaving the radiation zone, contaminated items and objects can be decontaminated using:
- **A large amount of clean water**.
- **Soap solution**.
- **Special chemical agents**.

To prevent contamination, **use protective containers** that keep items inside clean.

## 📟 Detection of Zones

- **Radiation Detectors**:  
  Use radiation dosimeters to measure the radiation level in the surrounding area, on contaminated items, and on the character.  
  Detectors have **different levels of sensitivity** and range, which helps to more accurately determine the level of danger.

### Types of Dosimeters:

1. **"Pripyat" Dosimeter**  
   - Measures radiation in microsieverts per hour (equivalent to 0.1 mR/h).  
   - Provides the most accurate readings but is limited to a maximum detectable radiation level of **9,999 µSv/h**.  
   - Range: **3 m**.  
   - Note: Maximum value in millirads is **999 mR/h**.

2. **"MKS-01A" Dosimeter**  
   - Measures radiation in millirads per hour.  
   - Less accurate but with an increased range.  
   - Limited to a maximum radiation level of **9,999 mR/h**.  
   - Range: **5 m**.

3. **"CDV 700" Dosimeter**  
   - Measures radiation in millirads per hour.  
   - Maximum radiation level: **5,000 mR/h**.
   - Provides a wide range: **10 m**.  
   - Suitable for detecting zones at a large distance.

4. **Household Dosimeter "DPG-05"**  
   - Measures radiation in millirads per hour.  
   - Limited to a maximum radiation level of **999 mR/h**.  
   - Compact, but with a small range: **1.5 m**.  
   - Ideal for use in local points with low radiation levels.

Each dosimeter is designed for different tasks: from precise measurements in small ranges to detecting zones at a large distance. Choose a device depending on the situation and level of threat.

## 🛡️ Radiation Protection:
For safe visits to radiation zones, a **complete set of protective suits** is necessary:
- 🥽 **Gas Mask**  
- 🧥 **Jacket**  
- 👖 **Pants**  
- 👟 **Shoes**  
- 🧤 **Gloves**  
- 🧢 **Hood**

## ⚙️ Settings:
- **Intensity and size of zones** can be configured in the [configuration](../Modding/README.md#zones) to regulate the level of danger. 
- To create a **set of protective suits**, follow the [instructions](../Modding/README.md#zone-protection).

Without proper protection and preparation, radiation zones become **deadly dangerous** for the lives of survivors.
