# Distributeur automatique d'argent de poche - Retour d'expérience

## Description du projet

## Domaines qu'il a fait intervenir
- **Design 3D** pour la conception des éléments mécaniques et boîtes ;
- **Impression 3D** pour la fabrication des éléments mécaniques et boîtes ;
- **Programmation Arduino** pour le développement de la logique du système ;
- **Electronique** pour les éléments autour de l'arduino.

## Design 3D
Pour le design 3D j'utilise Fusion 360. ça marche bien et on peut même simuler les mouvements mécaniques.

C'est probablement la partie la plus longue car il faut beaucoup expérimenter, imprimer un draft pour voir ce que cela donne, adapter le design, etc.

Il faut toujours garder à l'esprit le mode de production des pièces, ici par FDM (Fused Deposition Modeling). Les pièces produites par cette méthode sont fragiles dans le sens de la hauteur. Des porte-à-faux peuvent apparaître, certains nécessitant des supports pour le pas voir ces parties s'affaisser à l'impression.

### Comment visser le système bielle-manivelle
Au repos et à l'initialisation du distributeur, toutes les bielles-manivelles sont en retrait. Dans cette position la manivelle est totalement cachée sous la bielle et la vis de fixation sur le servo n'est pas accessible. Au début je fixais la manivelle sans insérer le système dans le rail et je jouais sur la flexibilité du plastique pour la rentrer de force.

Et puis j'ai pratiquer une ouverture de 5mm dans la bielle, là où se trouve la vis dans la position de repos.

## Impression 3D
### Laisser les pièces refroidir
A la fin d'une impression les pièces sont encore chaudes. Si on tente de les décoller à ce moment là elles risque de se déformer irrémédiablement.

Il faut être patient en impression 3D, patienter pendant le looooooonnnnnng temps d'impression et patienter pendant le refroidissement des pièces.

## Programmation Arduino
Après avoir malencontreusement grillé une carte, j'ai cherché une solution qui permette de tester son code dans un environnement virtuel, et donc sans risques pour la carte le temps de la première mise au point.

Pour cela j'ai utilisé *Tinkercad* qui offre, entre autre, un environnement de simulation Arduino.

### Tinkercad
#### Avantages
- offre un environnement virtuel sans risque pour les cartes physiques ;
- permet de commencer à travailler sur du matériel qu'on n'a pas encore reçu (écran LCD, calvier...) ;
- exécute le code arduino (simulation, on peut voir les LED s'allumer, les servos tourner....) ;
- certaines librairies sont disponibles (Servo, Keypad...) ;
- simulation du serial ;
- possibilité de coder en *Scratch* ;
- En ligne, on peut reprendre son travail depuis n'importe quel ordinateur connecté à internet ;
- On peut copier-coller le code dans l'Aduino IDE et le téleverser, ça marche (modulo quelques ajustements de type délai d'attente pour que les servos aient fini leur action, debounce (pas de rebond des interrupteurs en virtuel...) ;
- Il y a des circuits tout fait, ce qui fait gagner du temps (design, code...), par exemple pour controler un LCD.

#### Inconvénient
- Seulement Arduino UNO R3 ;
- Bibliothèque composants limitée (pas d'I2C par exemple : obligé d'utiliser un autre arduino virtuel  pour simuler l'I2C) ;
- Bibliothèque de librairies limitée ;
- Impossible de faire appel à des librairies externes (choix interne limité) ;
- 3 arduinos, un lcd et clavier : tinkercad n'en demandait pas tant...

## Electronique
### Les servomoteurs
Les servos que j'ai choisi sont commandés en PWM qui traduit l'angle auquel on veut que le servo aille.
Une fois arrivé à l'angle indiqué le servo fait tout ce qu'il peut pour s'y maintenir. Il fait des gros efforts pour ça et ça s'entend...
Le distributeur ayant vocation à se trouver dans le salon, c'était inenvisageable d'avoir ce bruit en permanence.
Comme je n'ai pas besoin que le servo maintienne sa position (par de contraintes extérieures pour modifier sa position), la première solution à laquelle j'ai pensé est de commander l'alimentation via l'arduino (alimenté pendant les mouvements, coupé le reste du temps). ça prend deux broches supplémentaires plus un peu d'électronique pour implémenter tout ça. Rien de méchant mais les broches sont précieuses, on en a peu.

En regardant plus attentivement la documentation j'ai découvert le ``Servo::detach()`` qui permet de "déconnecter" le servo de sa broche. 
> En plus, si on a utilisé les broches 9 et/ou 10 on peut les utiliser à nouveau pour faire du PWM ?????

### Alimentation de l'ensemble
Ce qui consomme le plus ici ce sont les servomoteurs.

| Composant      | Consommation (mA) |
|----------------|:-----------------:|
| Arduino Uno R3 | x                 |
| Servox2        | x                 |
| LCD            | x                 |
| Clavier        | x                 |
| RTC            | x                 |

## Arduino
### La broche 13
La broche 13 est souvent reliée à une led soudée sur l'arduino. La LED est reliée à la masse et pour l'allumer il suffit de configurer la broche 13 en sortie et d'y envoyer un niveau HAUT.
Mais on peut se servir de cette broche pour autre chose, par exemple, pour y brancher un interrupteur. C'est ce que j'ai fait. J'ai configurer la broche en INPUT_PULLUP et je détecte les états HAUT et BAS de la broche en fonction de la position de l’interrupteur. Sauf que j'avais un niveau BAS quelque soit la position de l'interrupteur.

En fait, c'est à cause de la LED. La résistance qui y est associée est trop faible et relie la broche 13 en permanence à l'état BAS. Pour corriger cela, il faut ajouter une résistance de PULLUP externe d'au moins 1kOhms.
