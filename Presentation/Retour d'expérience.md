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

Et puis une petite ouverture de 5mm pratiquée dans la bielle, là où se trouve la vis dans la position de repos, c'est bien plus pratique.

## Impression 3D
### Laisser les pièces refroidir
A la fin d'une impression les pièces sont encore chaudes. Si on tente de les décoller à ce moment là elles risque de se déformer irrémédiablement.

Il faut être patient en impression 3D, patienter pendant le looooooonnnnnng temps d'impression et patienter pendant le refroidissement des pièces.

## Programmation Arduino

### La gestion du temps sans Delay
Diantre que c'est compliqué.


### Tinkercad
    Après avoir malencontreusement grillé une carte, j'ai cherché une solution qui permette de tester son code dans un environnement virtuel, et donc sans risques pour la carte le temps de la première mise au point.

    Pour cela j'ai utilisé *Tinkercad* qui offre, entre autre, un environnement de simulation Arduino.
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

### Optimisation du code

#### Fragmentation du tas
Le diable s'habille en string :
https://hackingmajenkoblog.wordpress.com/2016/02/04/the-evils-of-arduino-strings/

https://cpp4arduino.com/2018/11/06/what-is-heap-fragmentation.html

Le fait de remplacer des `string` par des `char*` permet de gagner pas mal de place en mémoire (taille du programme après compilation)

| Taille | Action |
|-------|-------|
|8466| avec `display(String)` et `log(string)`|
|8068| avec des `char*`|

### Tenir compte des spécificités de chaque arduino
Tous les arduinos n'ont pas forcément le même comportement avec le même code :
 - les broches ne sont pas forcéments les mêmes ;
 - les fonctions associées au différentes broches peuvent être différentes (par exemple le timer1 qu'on trouve sur un uno se retrouve sur la broche 11 d'un mega) ;
 - la fonction Serial nécessite un `while(!Serial) {}` sur un leonardo. C'est spécifique aux cartes basées sur un AVR de type 32u4 dont la Leonardo fait partie (mail la yùn également).

## Électronique
### Le bruit des servomoteurs
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

### Les parasites
Lorsqu'on fait les montages sur les breadboards on relie les différents éléments entre eux avec des fils. Et ces fils font de magnifiques antennes sensibles au 50Hz du courant domestique, aus lampes à décharge, aux moteurs qui tournent ou tout simplement quand on les touche (c'est même une propriété utilisée dans les capteurs capacitifs).

Et il arrive que le montage ait des comportements étranges : des actions lancées par un bouton sur lequel on n'a pas appuyé, un écran LCD qui se met à verser dans la magie noire en inscrivant des signes cabalistiques mystérieux...

Pour éviter cela, il faut ([ref](https://forum.arduino.cc/index.php?topic=78406.0)) :
 - charger les lignes, en mettant une résistance de pullup par exemple ;
 - ajouter un condensateur de filtrage entre la ligne et la masse pour bloquer les signaux basse fréquence.



## Arduino
### La broche 13
La broche 13 est souvent reliée à une led soudée sur l'arduino. La LED est reliée à la masse et pour l'allumer il suffit de configurer la broche 13 en sortie et d'y envoyer un niveau HAUT.
Mais on peut se servir de cette broche pour autre chose, par exemple, pour y brancher un interrupteur. C'est ce que j'ai fait. J'ai configurer la broche en INPUT_PULLUP et je détecte les états HAUT et BAS de la broche en fonction de la position de l’interrupteur. Sauf que j'avais un niveau BAS quelque soit la position de l'interrupteur.

En fait, c'est à cause de la LED. La résistance qui y est associée est trop faible et relie la broche 13 en permanence à l'état BAS. Pour corriger cela, il faut ajouter une résistance de PULLUP externe d'au moins 1kOhms.

### Machine à état
J'ai commencé à coder de façon simple, assez linéaire. Mais assez rapidemment, je me suis retrouvé avec plein de booléens un peu partout pour contrôler le nombre de passages dans certains bouts de code et plus particulièrement pour savoir où j'en étais dans les étapes, dans quel état j'erre. 

Ce qui m'a conduit à coder mon programme grâce à une machine à état (simplifiée de chez simplifiée, un bon gros switch quoi). Pour une meilleur lisibilité, j'ai essayé autant que possible de faire les changements d'état dans le switch principal (parce que sinon c'est vite difficile de repérer le fil conducteur (cas nominal) du programme).


Cela m'a permis de résoudre des problèmes de répétitions non nécessaires d'exécution de code, comme par exemple afficher un message sur le LCD. Dans ce dernier cas, une seule exécution suffit à afficher et maintenir un texte, mais comme l'arduino passe dans sa boucle des millions de fois par seconde (ou pas loin), avec la machine à état j'ai un état qui affiche le message une fois et passe à un état suivant.

### Les pièces de monnaie pour tester
Ne les laissez pas trop près de l'arduino. Les pièces sont en métal, le métal est conducteur et les arduino n'aiment pas les courts-circuits.