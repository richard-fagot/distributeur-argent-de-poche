---
pagetitle: DAAP Conf
lang: fr-FR
---

<!-- Phrase d'introduction -->
# Distributeur Automatique d'Argent de Poche

Richard Fagot

:::notes
1. Tiens-toi bien ;
1. Pense à ta première phrase ;
1. Prend une inspiration ;
1. Embrasse la salle d'un regard et lance-toi.
:::


<!-- Pause blagounette -->
# 
![](assets/img/calvin.png)

::: notes
Passer rapidement.
:::

<!-- Courte introduction à l'argent de poche et genèse du projet -->
#

:::notes
Intro + genèse du projet :

- règles de l'argent de poche ;
- quitte à faire comme les grands, est-ce qu'on peu aller plus loin ?
:::


<!-- Le poussoir -->
# 
![](assets/img/poussoir.png){ height=600px }

::: notes
**Le poussoir **

- http://subaru.univ-lemans.fr/AccesLibre/UM/Pedago/physique/02/meca/bielle.html
- conception 3D fusion 360 ;
- Impression en une fois ;
- Puis en plusieurs pièces pour pouvoir avoir plusieurs couleurs ;
- Raffinement à cause de la nouvelle visserie des servos
- Clipper les pièces ensembles ;
- ==> mécanisme retenu.
:::

# PWM
![](assets/img/PWM.png)


<!-- Contrôler le servo -->
#
```c++
#include <Servo.h>

Servo myServo;
byte position;
byte servoPin;

void setup() {
    myServo.attach(servoPin);
    myServo.write(position);
}

void loop() {...}
```

::: notes

:::

# <!-- Detach -->
```c++
#include <Servo.h>

Servo myServo;
byte position;
byte servoPin;

void setup() {
    myServo.attach(servoPin);
    myServo.write(position);
    myServo.detach();
}

void loop() {...}
```

# <!-- Séquenceur -->
```cpp
CoinPusher *coinPushers[MAX_PUSHER_COUNT];
CoinPusher *sequence[MAX_SEQUENCE_COUNT];

while(remaining != 0) {
  int actualCoinValue = 
     coinPushers[pusherIndex]->getFacialValue();
  byte pushCount = remaining / actualFacialValue;
  for(int i = 0 ; i < pushCount ; i++) {
      sequence[sequenceIndex] = coinPushers[pusherIndex];
      sequenceIndex++;
  }
  remaining -= actualFacialValue * pushCount;
}

```

<!-- Discours -->
#

<!-- SLE 4442 -->
# SLE 4442
![](assets/img/carte+connecteur.png){height="400px"}


<!-- Structure carte -->
# 
```cpp
struct {
  char name[20+1];
  int pocketMoney;
  int secret;

  byte nameLength;
};
```

<!-- Discours trouver la librairie SClib-->
# 

<!-- Protocole SLE4442 -->
#
![](assets/img/protocole2.png){height="400px"}

<!-- Présentation de L'écran LCD -->
#
![](assets/img/LCD.png){height="400px"}

<!-- Introduction au protocole I2C -->
#
![](assets/img/I2C.png){height="600px"}


<!-- Librairie LCD -->
#
```cpp
#include <LiquidCrystal_PCF8574.h> // by Mathias Hertel

LiquidCrystal_PCF8574 lcd = LiquidCrystal_PCF8574(0x27);

lcd.setCursor(col, row);
lcd.print(message);
```

<!-- Clavier matriciel -->
#
![](assets/img/keypad.png){height="600px"}


<!-- Clavier matriciel fonctionnement-->
#
![](assets/img/clavier_4x4_schema_interne.gif){height="600px"}


<!-- anti-rebond -->
#
![](assets/img/rebond.png){height="400px"}

#
![](assets/img/anti-rebond.png){height="400px"}