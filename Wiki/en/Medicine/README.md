# TerjeMedicine

Medicine mod for DayZ

![image](/Wiki/logos/TerjeMedicine.jpg)


## DESCRIPTION

This mod adds a deeper and more realistic health system to the game, allowing you to immerse yourself in the dangers of survival across the vast landscapes of DayZ.
Now, every illness and injury has its own stages, symptoms, and treatment methods. Explore and utilize new mechanics to maintain your health and avoid the dangers lurking at every step.
Each symptom and disease requires a unique approach to treatment.
The mod includes a wide range of medications, tools, and methods for diagnosis and treatment, from simple bandaging to complex surgery.
**Test your survival skills on a new level. Monitor your character's condition to prevent diseases and infections from breaking you!**

## COMPONENTS

Mechanics included in the mod:

1. **PROPHYLAXIS AND TREATMENT**
   + Medicines
   + Vaccines **NEW!!!**
   + Disinfection of hands and tools
     
2. **PHYSICAL CONDITION**
   + Hematomas
   + Bullet wounds
   + Piercing wounds
   + Internal organ damage
   + Surgical sutures
   + Concussion

3. **INFECTIONS AND DISEASES**
   + Cold
   + Food poisoning
   + Chemical poisoning
   + Radiation poisoning
   + Zombie virus
   + Sepsis
   + Rabies **NEW!!!**

4. **SYMPTOMS**
   + Pain
   + Overdose

5. **EMOTIONAL STATE**
   + Sleep
   + Mental state

6. **ZONES**
   + Radioactive zones
   + Psychic zones

# PROPHYLAXIS AND TREATMENT

## ![image](/Wiki/images/tablets.png) MEDICINES

> Medicines are divided into three categories: tablets, ampoules, and injectors.
Tablets are usually used in the early stages of illness and for prevention.
A package contains ten tablets.
Packages with identical tablets can be combined.
Ampoules contain strong-acting medications for treating complex illnesses or diseases in the medium and severe stages.
Players must use a syringe to administer the substance.
After each injection, the syringe becomes contaminated and must be disinfected with alcohol or boiled in a pot of water over fire.
Injectors are similar to ampoules but do not require syringes.
All injectors are disposable.

## ![image](/Wiki/images/vaccine.png) VACCINES

> Vaccines allow you to protect yourself from dangerous diseases, significantly reducing the likelihood of infection. When used, a vaccine creates immunity against certain infections, helping the character avoid diseases they may encounter in a contaminated environment. Use the vaccine in advance to strengthen the character's immunity and always monitor the need for revaccination to maintain protection.

| Name       | Item                      | Stage   | Form and Packaging | Duration (s) | Overdose |
|:----------:|:-------------------------:|:-------:|:-------------------:|:------------:|:--------:|
| Vaxikam    | TerjeAmpouleVaxicam       | Vaccine | Ampoule             | 14400        | 0.8      |
| Zerivax    | TerjeAmpouleZerivax       | Vaccine | Ampoule             | 7200         | 1.5      |
| Rabivax    | TerjeAmpouleRabivax       | Vaccine | Ampoule             | 14400        | 1.3      |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medInfluenzaVacineTime  = 14400; // Vaccine against Cold
    medZVirusVacineTime     = 7200;  // Vaccine against Z Virus
    medRabiesVacineTime     = 14400; // Vaccine against Rabies
```

## ![image](/Wiki/images/desinfection.png) DISINFECTION

> A mandatory procedure to maintain sterility and prevent wound infections.
Dirty medical items must be thoroughly disinfected before use to eliminate the risk of infection.
Before any manipulations or operations, hands should also be disinfected, especially in field conditions where the risk of infections increases.
Disinfection is the key to successful treatment and health safety in extreme conditions.

| Name                      | Item                 | Stage        |
|:-------------------------:|:--------------------:|:------------:|
| Alcoholic Tincture        | DisinfectantAlcohol  | Disinfection |
| Disinfectant Spray        | DisinfectantSpray    | Disinfection |

# PHYSICAL CONDITION

## ![image](/Wiki/images/hematoma.png) HEMATOMAS

> Hematomas can be caused if you are hit by a zombie or struck with blunt weapons.
If you have many hematomas, your health will start to decrease.
Hematomas heal on their own over time.
Use ointments to accelerate their healing.

| Name        | Item                  | Form and Packaging | Duration (s) | Overdose |
|:-----------:|:---------------------:|:-------------------:|:------------:|:--------:|
| Capsikam    | TerjeSalveViprosal    | Tube of ointment    | 300          | 0.0      |
| Viprosal    | TerjeSalveCapsicum    | Tube of ointment    | 400          | 0.0      |
| Finalgon    | TerjeSalveFinalgon    | Tube of ointment    | 600          | 0.0      |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medHematomaHeal=1; // Strength
    medHematomaHealTimeSec=400; // Duration (s)
```


## ![image](/Wiki/images/organs.png)  ![image](/Wiki/images/bullet.png)  ![image](/Wiki/images/cut3.png) INTERNAL ORGAN DAMAGE, BULLET AND PIERCING WOUNDS

> A player can sustain a bullet wound from firearms.
It is characterized by severe bleeding and requires immediate bandaging.
Bandaging with a hemostatic bandage will be more effective than a regular bandage or cloth.
After bandaging, the wound will continue to bleed slightly until the bullet is removed with a surgical kit.
A well-maintained bulletproof vest can protect you from bullet wounds. However, the probability of the armor being penetrated is calculated using a ballistic calculator.
Thus, a light bulletproof vest will protect you from small calibers but not from medium and large calibers. If the vest blocks the bullet, you will receive an unarmored wound in the form of a hematoma.

| Name                        | Item                             | Form and Packaging | Volume | Internal Organs (strength/time) | Bullet (strength/time) | StubEffectivity (strength/time) | 
|:---------------------------:|:--------------------------------:|:-------------------:|:------:|:-------------------------------:|:---------------------:|:--------------------------------:|
| Surgical Tool Bowl (Ceramic)| TerjeSurgicalTool_Ceramic        | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Surgical Tool Bowl (White)  | TerjeSurgicalTool_White          | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Field Kit                   | TerjeSurgicalKit                 | Surgical kit       | 5      | 0.2/40                          | 0.5/25                | 0.7/20                           |
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

## ![image](/Wiki/images/cut2.png) SURGICAL SUTURES

| Name                      | Item                             | Form and Packaging | Volume | Internal Organs (strength/time) | Bullet (strength/time) | StubEffectivity (strength/time) | 
|:-------------------------:|:--------------------------------:|:-------------------:|:------:|:-------------------------------:|:---------------------:|:--------------------------------:|
| Surgical Tool Bowl (Ceramic) | TerjeSurgicalTool_Ceramic      | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Surgical Tool Bowl (White) | TerjeSurgicalTool_White        | Surgical tools     | 1      | 0.05/90                         | 0.2/40                | 0.4/30                           |
| Field Kit                  | TerjeSurgicalKit               | Surgical kit       | 5      | 0.2/40                          | 0.5/25                | 0.7/20                           |
| IFAK                       | TerjeFirstAidKitIndividual_Black | Universal kit      | 10     | 0.3/40                          | 0.6/30                | 0.8/20                           |
| AFAK                       | TerjeFirstAidKitAdvance_Black  | Universal kit      | 20     | 0.3/40                          | 0.6/30                | 0.8/20                           |

## ![image](/Wiki/images/brain.png) CONCUSSION

>A concussion occurs from a strong blow to the head with a blunt object, an explosion near the character, or from being hit by a low-caliber bullet while using a ballistic helmet. The first symptoms of a concussion include headache, dizziness, unstable coordination, and blurred vision, which make movement and combat difficult. Over time, the concussion subsides on its own, but to accelerate recovery, you can use special medications that reduce the intensity of symptoms.

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

# INFECTIONS AND DISEASES

## ![image](/Wiki/images/influenza.png) COLD / PNEUMONIA

> You can catch a cold or get the flu from exposure to cold temperatures.
Over time, a cold can progress to a mild form and eventually develop into pneumonia.
When suffering from pneumonia, your character will begin to lose health slowly.
Use antibiotics of the same level or higher for treatment.
Multiple doses of the medication may be required for full recovery.
A mild cold can be cured by sleeping in a warm place.

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
| Topoizomerase | TerjeInjectorTopoizomeraza| Treatment| 3     | Injector            | 900          | 0.65     |
| Imipenem      | TerjeAmpouleImipenem     | Treatment| 3     | Ampoule             | 900          | 0.7      |
| Flemoclav     | TerjeAmpouleFlemoclav    | Treatment| 3     | Ampoule             | 1200         | 0.8      |
| Amoxiclav     | TerjeInjectorAmoxiclav   | Treatment| 3     | Injector            | 1800         | 0.6      |
| Vaxicam       | TerjeAmpouleVaxicam      | Vaccine  | -     | Ampoule             | 14400        | 0.8      |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medAntibioticLevel = 1; // Strength
    medAntibioticsTimeSec = 300; // Duration (s)
    overdosedIncrement = 0.45; // Overdose
```

## ![image](/Wiki/images/poisoning.png) FOOD POISONING

> Food poisoning can occur from consuming spoiled or improperly cooked food, rotten fruits, poisonous mushrooms, dirty water, or accidentally ingesting gasoline.  
Symptoms like nausea and vomiting appear immediately after consuming such food.  
If left untreated, your character's condition may worsen, leading to dehydration and subsequent health loss.  
To treat it, drink plenty of water and use special medications to alleviate the symptoms.

| Name                | Item                       | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------------:|:-------------------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| Activated Charcoal  | CharcoalTablets           | Treatment |   1   | Tablets           |      300     |   0.01   |
| Polysorb            | TerjePillsPolisorb        | Treatment |   1   | Tablets           |      300     |   0.05   |
| Phthalazol          | TerjePillsFtalazol        | Treatment |   1   | Tablets           |     1200     |   0.25   |
| Mesalazine          | TerjePillsMesalazin       | Treatment |   2   | Tablets           |      600     |   0.35   |
| Chelating Tablets   | ChelatingTablets          | Treatment |   2   | Tablets           |      600     |   0.6    |
| Metoclopramide      | TerjeAmpouleMetoclopramid | Treatment |   2   | Ampoule           |     1200     |   0.4    |
| Heptral             | TerjeAmpouleHeptral       | Treatment |   3   | Ampoule           |      600     |   0.6    |
| Stomaproxidal       | TerjeInjectorStomaproxidal| Treatment |   3   | Injector          |      900     |   0.68   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
    medAntipoisonLevel = 1; // Strength
    medAntipoisonTimeSec = 300; // Duration (s)
    overdosedIncrement = 0.45; // Overdose
```

## ![image](/Wiki/images/biohazard.png) ХИМИЧЕСКОЕ ОТРАВЛЕНИЕ

## ![image](/Wiki/images/biohazard.png) CHEMICAL POISONING

>Chemical poisoning occurs from inhaling toxic gases. Early symptoms include the character coughing. As the poisoning progresses, symptoms such as vomiting and nausea appear. In the later stages, chemical poisoning causes critical health loss and can be fatal without timely treatment.  
To treat poisoning, take an antidote or special medication that reduces toxic effects.

| Name             | Item                      | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:----------------:|:------------------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| Rombiopental     | TerjePillsRombiopental   | Treatment |   1   | Tablets           |       30     |   0.15   |
| Neirocetal       | TerjeAmpouleNeirocetal   | Treatment |   2   | Ampoule           |      500     |   1.25   |
| AntiChemInjector | AntiChemInjector         | Treatment |   3   | Injector          |      180     |   1.1    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medAntibiohazardLevel = 1; // Strength
	medAntibiohazardTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/Wiki/images/radiation.png) RADIATION POISONING

>Radiation poisoning develops from being in areas with high radiation levels or contact with contaminated items. Early symptoms include weakness, nausea, and dizziness. Over time, the character may experience bleeding and a weakened immune system. In the later stages, radiation poisoning leads to significant health loss and body exhaustion, threatening the character's life.  
To treat radiation poisoning, take medications that remove radiation from the body, such as iodine tablets or anti-radiation drugs. Avoid radiation zones or use protective gear to minimize exposure.

| Name                        | Item                          | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:---------------------------:|:----------------------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| B190                       | TerjePillsB190               | Treatment |   1   | Tablets           |      140     |   0.3    |
| Potassium Iodide           | TerjePillsPotassiumIodide    | Treatment |   1   | Tablets           |       60     |   0.2    |
| Hexacyanoferrate           | TerjePillsHexacyanoferrate   | Treatment |   1   | Tablets           |      120     |   0.3    |
| Mexamine                   | TerjePillsMexamine           | Treatment |   2   | Tablets           |       25     |   0.75   |
| Pentacin                   | TerjeAmpoulePentacin         | Treatment |   2   | Ampoule           |      400     |   0.5    |
| Carboxymethylcellulose     | TerjeAmpouleCarboxyme        | Treatment |   2   | Ampoule           |      600     |   0.6    |
| Radioprotector             | TerjeInjectorRadioprotector  | Treatment |   3   | Injector          |      600     |   0.75   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item)
```cs
	medAntiradLevel = 1; // Strength
	medAntiradTimer = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/Wiki/images/virusz.png) ZOMBIE VIRUS

>The zombie virus is transmitted through airborne droplets and bodily fluids. There is a small chance of getting infected during close combat with zombies. The chance increases if a zombie inflicts wounds on you. Use a face mask and ballistic armor to reduce the likelihood of infection. The virus has a very long incubation period. Players have more than an hour of real time to find an antidote. In the terminal stage of the infection, your health begins to rapidly deteriorate.

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

## ![image](/Wiki/images/blood2.png) SEPSIS

>Sepsis occurs when an infection enters an open wound.  
This can happen with a zombie scratch, a knife wound, or a gunshot wound with a small probability.  
It is also highly likely if you handle an open wound with dirty hands.  
If untreated, sepsis will gradually cause your health to deteriorate over time.

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

## ![image](/Wiki/images/virus.png) RABIES

>Rabies is transmitted through bites from infected animals, such as wolves. After infection, the disease progresses gradually and does not show symptoms immediately.  
In the early stage, temperature fluctuations and weakness begin, which may go unnoticed.  
In the second stage, the condition worsens — the character suffers from severe nausea and vomiting, making it impossible to eat or drink.  
In the third, critical stage, the temperature spikes, leading to rapid health loss, exhaustion, and the inability to survive effectively.  
Without timely treatment, the disease inevitably results in death. Early-stage treatment with special medications or vaccination before infection can prevent the disease from progressing.

| Name            | Item                      | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:---------------:|:-------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Rifampicine     | TerjeAmpouleRifampicyne  | Treatment |   3   | Ampoule           |      300     |   1.35   |
| Rabinoline      | TerjeAmpouleRabinoline   | Treatment |   2   | Ampoule           |      600     |   0.8    |
| Rabinucoline    | TerjeInjectorRabinucoline| Treatment |   3   | Injector          |      900     |   1.46   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medRabiesAntibioticLevel = 1; // Strength
	medRabiesAntibioticTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

# SYMPTOMS

## ![image](/Wiki/images/pain.png) PAIN

>Pain occurs as a result of various injuries.  
The intensity of the pain depends on the severity of the trauma.  
Pain subsides on its own after some time.  
To relieve pain, use painkillers of the corresponding level or higher.

| Name             | Item                      | Stage     | Level | Form and Packaging | Duration (s) | Overdose |
|:----------------:|:-------------------------:|:---------:|:-----:|:------------------:|:------------:|:--------:|
| Painkiller       | PainkillerTablets         | Treatment |   1   | Tablets           |      300     |   0.2    |
| Analgin          | TerjePillsAnalgin         | Treatment |   1   | Tablets           |      500     |   0.15   |
| Nimesulid        | TerjePillsNimesulid       | Treatment |   1   | Tablets           |      600     |   0.25   |
| Paracetamol      | TerjePillsParacetamol     | Treatment |   1   | Tablets           |      200     |   0.45   |
| Ibuprofen        | TerjePillsIbuprofen       | Treatment |   1   | Tablets           |      600     |   0.35   |
| Nurofen          | TerjePillsNurofen         | Treatment |   1   | Tablets           |      350     |   0.52   |
| Noopept          | TerjePillsNoopept         | Treatment |   1   | Tablets           |      380     |   0.35   |
| Ketarol          | TerjeAmpouleKetarol       | Treatment |   1   | Ampoule           |     1200     |   0.5    |
| Novacaine        | TerjeAmpouleNovacaine     | Treatment |   2   | Ampoule           |     1200     |   0.4    |
| Morphine         | TerjeAmpouleMorphine      | Treatment |   3   | Ampoule           |      850     |   0.52   |
| Gexobarbital     | TerjeAmpouleGexobarbital  | Treatment |   3   | Ampoule           |      900     |   0.65   |
| Reanimatal       | TerjeInjectorReanimatal   | Treatment |   1   | Injector          |      240     |   1.85   |
| Morphine         | Morphine                  | Treatment |   3   | Injector          |      300     |   0.75   |
| Promidol         | TerjeInjectorPromidol     | Treatment |   3   | Injector          |      600     |   0.45   |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medPainkillerLevel = 1; // Strength
	medPainkillerTimeSec = 300; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/Wiki/images/overdose.png) OVERDOSE

>Overdose occurs when excessive amounts of medication or toxic substances are introduced into the body.  
The overdose gradually weakens as toxins are eliminated from the system. It progresses through three stages:

>**First stage:** The character experiences nausea and hallucinations, losing clarity of perception.

>**Second stage:** The condition worsens, and the character may lose consciousness, becoming vulnerable to the environment.

>**Third stage:** Critical health deterioration occurs, threatening the character's life.

| Name          | Item          | Stage   | Level | Form and Packaging | Duration (s) | Overdose |
|:-------------:|:-------------:|:-------:|:-----:|:------------------:|:------------:|:--------:|
| Water         | WaterBottle   | Treatment |   1   | Bottle            |      300     |   0.0    |

# EMOTIONAL STATE

## ![image](/Wiki/images/dream.png) SLEEP

>Your character now needs sleep just like food and water. Regular rest is necessary to maintain health and stamina.  
If the sleep indicator turns yellow, the character will start yawning, and their vision will gradually worsen.  
When the indicator reaches the red level, the character may lose consciousness from exhaustion.  
Warm places are ideal for sleeping — near a fireplace, in a tent, inside a house, or in a sleeping bag.  
Sleep is impossible if the character is freezing, starving, or has serious health problems (stage two illnesses and above).  
During sleep, the character rapidly restores health and may recover from mild illnesses, such as stage one flu, with a small probability.  
Sleeping bags provide extra warmth and comfort, making sleep safer and more effective in harsh conditions.

| Name               | Item                | Stage          | Level | Form and Packaging | Duration (s) | Overdose |
|:------------------:|:------------------:|:--------------:|:-----:|:------------------:|:------------:|:--------:|
| MadBull Energy     | TerjeDrinkMadBull  | Recovery       |   8   | Bottle            |      1.0     |   0.0    |
| Gang Energy        | TerjeDrinkGang     | Recovery       |   6   | Bottle            |      1.0     |   0.0    |
| Yaguar Energy      | TerjeDrinkYaguar   | Recovery       |  10   | Bottle            |      1.0     |   0.0    |
| Prayboy Energy     | TerjeDrinkPrayboy  | Recovery       |   4   | Bottle            |      1.0     |   0.0    |
| 6Energy Drink      | TerjeDrink6Energy  | Recovery       |   8   | Bottle            |      0.8     |   0.0    |

Parameters for [creating your own items](../Modding/README.md#1-based-on-item):
```cs
	medSleepingIncrementValue = 8; // Strength
	medSleepingIncrementTimeSec = 0.8; // Duration (s)
	overdosedIncrement = 0.45; // Overdose increment
```

## ![image](/Wiki/images/mental.png) MENTAL STATE

>The character's mental state deteriorates under extreme stress: zombie attacks, prolonged exposure to dangerous Psi-zones, and consuming human meat can lead to nervous breakdowns and hallucinations.  
In such conditions, the character may experience panic and disorientation, complicating survival and interaction with the environment.  
To alleviate symptoms, use antidepressants to stabilize the psyche and mitigate the negative effects of stress factors.

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

# ZONES

# ☢️ Radiation Zone

Radiation zones are **dangerous areas with elevated radiation levels**, posing a serious threat to the lives of survivors.  
Visiting them requires thorough preparation and the use of protective equipment.

## ⚠️ How Contamination Works:
1. **Radiation accumulates in the body** as a "radiation buffer" through:
   - Being in a radiation zone.
   - Contact with contaminated items.  
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
- To create a **set of protective suits**, follow the [instructions](../Modding/README.md#защита-от-зон).

Without proper protection and preparation, radiation zones become **deadly dangerous** for the lives of survivors.
