---
pagetitle: DAAP
lang: fr-FR
---


# Distributeur Automatique d'Argent de Poche

Richard Fagot

:::notes
1. Tiens-toi bien ;
1. Pense à ta première phrase ;
1. Prend une inspiration ;
1. Embrasse la salle d'un regard et lance-toi.
:::

Il y a quelques mois, avec mon épouse, nous avons décidé de donner de l'argent de poche à nos enfants et, ce, malgré les terribles risques encourus.
 

# 
![](assets/img/calvin.png)

::: notes
Passer rapidement.
:::




#
::: notes
Histoire du projet

- Décision de donner des sous aux enfants ;
- Règles de l'argent de poche ;
- Quitte à faire comme les grands autant aller jusqu'au bout ;

==> C'est comme ça qu'est née l'idée du DAAP : les enfants insèrent leur CB, tapent leur code en suivant les instructions à l'écran et la machine distribue l'argent de poche, la pièce étant éjectée par un petit mécanisme.
    
:::

Nous avons fait ce choix pour qu'elles puissent commencer à apprendre à gérer leur argent, à découvrir la valeur de l'argent.
Avant de se lancer j'ai quand même regardé dans la littérature ce qu'il s'en disait et j'ai découvert un certains concensus en 5 "règles" :
1. 1 fois par semaine car une fois par mois c'est trop long pour eux, 1 fois par semaine est plus en accord avec leur échelle de temps et encore, au début elles oubliaient assez vite ;
2. Toutes les semaines, même si elles ont fait un bêtise, une grosse bêtise voire même une trés trés grosse bêtise ;
3. Ce n'est pas une rémunération, en échange de tâches ménagères par exemple, elles touchent leur argent de poche de manière inconditionnelle (cela vient plus tard la notion de rémunération) ;
4. Elles dépensent leur argent comme elles l'entendent, exception faite de la drogue, des armes et autres produit récréatifs du même acabit. Personnellement, vu qu'elles ont des chambres déjà bien saturée, lorsqu'on fait un cide-grenier par exemple, je les invite à en faire le tour et à s'acheter 1 ou 2 objets maximum.

L'idée générale étant de pouvoir faire "comme les grands". Mais quite à faire comme les grands, est-ce qu'on ne pourrait pas aller un peu plus loin avec un projet qui serait fun pour elles et fun pour leur papounet ?

C'est comme ça qu'est née l'idée d'un distributeur automatique d'argent de poche : fabriquer une machine dans laquelle elle inséreraient leur "carte bleue", saisiraient leur code secret en suivant les instructions à l'écran et regarderaient la machine se mettre en action pour distribuer l'argent de poche en poussant les pièces une à une.

Ce mécanisme du poussoir est la première chose à laquelle je me suis intéressé parce que c'est la partie la plus concrête, on peut la voir, la toucher, la regarder bouger toute seule.

Au début, je m'étais inspiré d'une trieuse à pièce sur laquelle il y avait une sorte de corbeille remplie de pièces en vrac et une roue dans laquelle étaient aménagés des espaces pour accueillir une pièce à la fois. La roue, en tournant, capture une pièce et la dépose dans la trieuse. Je la voyait bien à l'horizontale sous une colonne de pièce. En tournant elle prendrait une pièce et la déposerait à l'endroit de la distribution. Mais ça manquait un peut de vie et la conception mécanique m'embetait un peu : soit il fallait utiliser une vis sans fin avec une mauvaise maîtrise des mouvements à cause des jeux entre les différents éléments, ou alors en prise directe sur un moteur pas à pas mais je craignais de ne pas avoir suffisamment de puissance ou que cela consomme trop.

Et puis j'ai pensé au mouvement bielle-manivelle qu'on retrouve dans les moteurs à explosion et qui permet de transformer un mouvement de rotation en mouvement de translation (le piston dans le moteur). Le mouvement est sympas, presque hypnotique, les pièces sont faciles à concevoir et fabriquer et on peut connecter le tout à un servo moteur, de ceux qu'on utilise dans le modélisme, et qui sont commandable par un signal PWM facilement générable par l'arduino.

Mon premier essai était de réaliser une impression en une seule "pièce" inspirée de ces impressions de dragons, serpents et autres robots articulés qu'on imprime en un seul bloc sans assemblage. Après quelques tatonnements (et il y en a beaucoup en impression 3D, il ne faut pas hésiter à concevoir puis imprimer pour voir ce que cela donne) j'ai obtenu ce magnifique spécimen de bielle-manivelle en une seule impression.

Ça marche très bien, c'est cool mais ça manque de couleurs et mes filles sont très exigeantes en matière de couleurs flashy qui font saigner des yeux et en plus, une seule couleur ne permet pas de bien visualiser le mouvement des différentes pièces. Alors j'ai repris ma conception pour avoir des pièces indépendantes et pouvoir les imprimer chacune dans une couleur différente (je n'ai qu'une seule tête d'impression sur mon imprimante 3D). L'exercice est assez facile avec un outil comme fusion 360 mais la question la plus délicate était de savoir comment assembler ces éléments. 

La première idée est d'utiliser des écrous et des boulons pour maintenir les pièces entre elles et jouer le rôle des axes de rotations. Mais, d'abord, je trouve ça assez moche et je voulais au maximum utiliser du PLA en quantité la plus petite possible (le plastique c'est fantastique mais ça fait pas du bien à la planète bien que celui-ci soit biodégradable assez rapidement). Alors je me suis inspiré des légos techniques : ils des petites pièces qui permettent d'assembles les élements entre eux et même servir d'axe de rotation. Elles ont la particularité d'être fendues sur un diamètre ce qui leur donne de la flexibilité pour les enfoncer dans les trous et à leur extrémité un bourelet permer de s'accrocher à la pièce lorsque cette attache se détend en sortant du trou.

**Et ça donne ça (image du poussoir en éclaté)**

À l'impression on prend garde à imprimer la pièce de telle sorte que les efforts de flexion soient perpendiculaire aux couches d'impression pour plus de solidité.

**Montrer la pièce physique, en l'assemblant devant l'assistance**

Pour que le poussoir ait un mouvement rectiligne il faut le contraindre dans cette direction. Et puis, il faut aussi lui ajouter le servo qui va engager le mouvement de rotation de la manivelle et puisqu'on y est, il faut aussi ajouter la réserve de pièces à distribuer grâce au poussoir. Alors je vous présente le support sur lequel le servo vient se fixer, qui présente un guide rectiligne pour le poussoir au bout duquel on retrouve la colonne de pièces.

Dans cette colonne j'ai pratiqué une ouverture pour pouvoir récupérer facilement les pièces (notamment quand on par en vacance, quand le distributeur est plein il y a plus de **XX€**). L'ouverture par laquelle les pièces vont s'échapper est large d'un diamètre de  la plus grande pièce (2€) sinon elle serait piégée un peu comme dans une pince. En hauteur, on est à un petit peu plus d'une hauteur de pièce, ça permet de prendre en compte les imprecisions d'impression et des jeux dans les mouvement tout en bloquant la pièce en contact direct avec celle qu'on pousse et qui pourrait être entraînée par frottement.

**Montrer le mécanisme complet**
On a donc un mécanisme complet qui permet de distribuer des pièces de monnaies : un distributeur par valeur faciale.

Il ne reste plus qu'à le commander grâce à un arduino.

J'ai choisi d'utilise un arduino nano parce que d'une part parce qu'il est vraiment compact, ce qui permet de l'intégrer facilement sur un PCB proprement et d'autre part, par un coup de bol incroyable, car il contient tout juste suffisament d'entrées/sorties pour tout le projet.





# Distribuer les pièces
1. Historique du poussoir (roue) ;
1. Le poussoir en une impression ;
1. Le poussoir en plusieurs impressions pour avoir plusieurs couleurs ;
1. Evolution pour prendre en compte les différents types de visserie ;
1. Choix du servo (couple, taille) ;
1. Controle du servo (lib par défaut, disconnect pour le bruit, prise en compte du temps d'éxécution du mouvement).
1. Le design dans fusion 360 (+mouvements) ;
1. Le support (pièce, guide poussoir, support servo) ;

==> le servo permet d'actionner le mouvement du poussoir qui lui-même distribue une pièce. Dans ce DAAP il y a 3 valeurs faciales différentes et en fonction de l'enfant, la quantité d'argent à distribuer varie. Il faut trouver un moyen pour identifier l'enfant et trouver la somme d'argent qui lui est associée.

# Combien, pour qui ?
==> Il y a plusieurs possibilités pour faire ça
- Stockage en dur dans le programme : le code secret devient l'id de l'enfant (mais somme change dans le temps, ajout d'un enfant) ;
- pour être plus fun on utilise la mémoire d'une carte à puce :
    - Pour l'ajout ou la modif d'une carte on peut passer par un menu du DAAP ;
    - Carte personnalisable
    - fun
- Ici, j'utilise une CAP SL4442 est est une carte sécurisée.
- Difficile de trouver un lib arduino, presque abandon, implémenter moi-même le protocole ?
- Stockage du nom, montant et code. 
=> mais aussi le nombre de lettres du prénom (20 car max) à cause écran.

## Ecran


# Quand ?
Les enfants peuvent retirer leur argent de poche une fois par semaine dans le créneau des deux jours du WE.

Et on imagine vite ces petits chenapans tenter de hacker le système en venant plusieurs fois dans le WE venir retirer leur argent de poche.

# My little Hackers

# Interactions


# Le séquenceur