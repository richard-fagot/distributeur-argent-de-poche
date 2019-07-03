# Distributeur Automatique d'Argent de Poche

## Phrase d'introduction

Il y a quelques mois, avec mon épouse, nous avons décidé de donner de l'argent de poche à nos enfants et, ce, malgré les terribles risques encourus...
 

# Pause blagounette
![](assets/img/calvin.png)


## Courte introduction à l'argent de poche et genèse du projet

Nous avons fait ce choix pour qu'elles puissent commencer à apprendre à gérer leur argent, à découvrir la valeur de l'argent.
Avant de se lancer j'ai quand même regardé dans la littérature ce qu'il s'en disait et j'ai découvert un certains concensus autour 5 "règles" :
1. 1 fois par semaine car une fois par mois c'est trop long pour eux, 1 fois par semaine est plus en accord avec leur échelle de temps et encore, au début elles oubliaient assez vite ;
2. On le donne tout le temps, même si elles ont fait un bêtise, une grosse bêtise voire même une trés trés grosse bêtise ;
3. Ce n'est pas une rémunération, en échange de tâches ménagères par exemple, elles touchent leur argent de poche de manière inconditionnelle (cela vient plus tard la notion de rémunération) ;
4. Elles dépensent leur argent comme elles l'entendent, exception faite de la drogue, des armes et autres produit récréatifs du même acabit. Personnellement, vu qu'elles ont des chambres déjà bien saturée, lorsqu'on fait un cide-grenier par exemple, je les invite à en faire le tour et à s'acheter 1 ou 2 objets maximum.

L'idée générale étant de pouvoir faire "comme les grands". Mais quitte à faire comme les grands, est-ce qu'on ne pourrait pas aller un peu plus loin avec un projet qui serait fun pour elles et fun pour leur papounet ?

C'est comme ça qu'est née l'idée d'un distributeur automatique d'argent de poche : fabriquer une machine dans laquelle elle inséreraient leur "carte bleue", saisiraient leur code secret en suivant les instructions à l'écran et regarderaient la machine se mettre en action pour distribuer les pièces une à une à l'aide d'un petit mécanisme...

## Le poussoir
...que je me suis empressé de concevoir. C'est la première chose à laquelle je me suis intéressé parce que c'est la partie la plus concrète, on peut la voir, la toucher, la regarder bouger toute seule.

Au début, je m'étais inspiré d'une trieuse à pièce sur laquelle il y avait une sorte de corbeille remplie de pièces en vrac et une roue dans laquelle étaient aménagés des espaces pour accueillir une pièce à la fois. La roue, en tournant, capture une pièce et la dépose dans la trieuse. Je la voyait bien à l'horizontale sous une colonne de pièce. En tournant elle prendrait une pièce et la déposerait à l'endroit de la distribution. Mais ça manquait un peut de vie et la conception mécanique m'embêtait un peu : soit il fallait utiliser une vis sans fin avec une mauvaise maîtrise des mouvements à cause des jeux entre les différents éléments, ou alors en prise directe sur un moteur pas à pas mais je craignais de ne pas avoir suffisamment de puissance ou que cela consomme trop.

Et puis j'ai pensé au mouvement bielle-manivelle qu'on retrouve dans les moteurs à explosion et qui permet de transformer un mouvement de rotation en mouvement de translation (le piston dans le moteur). Le mouvement est sympas, presque hypnotique, les pièces sont faciles à concevoir et fabriquer et on peut connecter le tout à un servo moteur, de ceux qu'on utilise dans le modélisme, et qui sont commandables par un signal PWM facilement générale par l'*arduino*.

Mon premier essai a été de réaliser une impression en une seule "pièce" inspirée de ces impressions de dragons, serpents et autres robots articulés qu'on imprime en un seul bloc sans assemblage. Après quelques tatonnements (et il y en a beaucoup en impression 3D, il ne faut pas hésiter à concevoir puis imprimer pour voir ce que cela donne) j'ai obtenu ce magnifique spécimen de bielle-manivelle en une seule impression.

Donc, j'ai réussi à imprimer le poussoir en une seule pièce et en plus, sans résistance au niveau des axes ce qui m'a permis de valider la puissance des servos de 9g et dun peu plus d'un kg de couple. J'ai assemblé un système rudimentaire et tenté de pousser une pièce de 2€ en bas d'une colonne de 25 pièces et ça a marché du premier coup.

J'ain un système qui marche très bien, c'est cool mais ça manque de couleurs et mes filles sont très exigeantes en matière de couleurs flashy qui font saigner des yeux et en plus, une seule couleur ne permet pas de bien visualiser le mouvement des différentes pièces. Alors j'ai repris ma conception pour avoir des pièces indépendantes et pouvoir les imprimer chacune dans une couleur différente (je n'ai qu'une seule tête d'impression sur mon imprimante 3D). L'exercice est assez facile avec un outil comme fusion 360 mais la question la plus délicate était de savoir comment assembler ces éléments. 

La première idée est d'utiliser des écrous et des boulons pour maintenir les pièces entre elles et jouer le rôle des axes de rotations. Mais, d'abord, je trouve ça assez moche et je voulais au maximum utiliser du PLA en quantité la plus petite possible (le plastique c'est fantastique mais ça fait pas du bien à la planète bien que celui-ci soit biodégradable assez rapidement). Alors je me suis inspiré des légos techniques : ils des petites pièces qui permettent d'assembles les élements entre eux et même servir d'axe de rotation. Elles ont la particularité d'être fendues sur un diamètre ce qui leur donne de la flexibilité pour les enfoncer dans les trous et à leur extrémité un bourelet permer de s'accrocher à la pièce lorsque cette attache se détend en sortant du trou.

**Et ça donne ça (image du poussoir en éclaté)**

Là aussi on travaille par tatonnement. Par exemple, sur cet ensemble le mouvement est dur. D'une par parce que la pièce est voilée : il faut attendre que la température du plateau soit redescendu sinon, la pièce encore chaude de déforme et garde le pli. D'autre part parce que les jeux que j'avais mis étaient trop serrés.


À l'impression on prend garde à imprimer la pièce de telle sorte que les efforts de flexion soient perpendiculaire aux couches d'impression pour plus de solidité.

C'est important de garder à l'esprit la méthode que l'on va employer pour imprimer en 3D au moment où on fait la conception dans le logiciel 3D ET au moment du slicing. Par exemple, si on observe le premier poussoir en une seule fois on remarquera que l'extrémité inférieur du poussoir arrive au ras du disque de maintient, qui est lui-même d'un diamètre égal à la largeur de la bielle : parce qu'en fait, **cette pièce s'imprime comme ça**.

**Montrer la pièce physique, en l'assemblant devant l'assistance**

Pour que le poussoir ait un mouvement rectiligne il faut le contraindre dans cette direction. Et puis, il faut aussi lui ajouter le servo qui va engager le mouvement de rotation de la manivelle et puisqu'on y est, il faut aussi ajouter la réserve de pièces à distribuer grâce au poussoir. Alors je vous présente le support sur lequel le servo vient se fixer, qui présente un guide rectiligne pour le poussoir au bout duquel on retrouve la colonne de pièces.

L'ouverture pratiquée à la sortie vaut environ 1.5 la hauteur d'une pièce de 2€ pour être sûr, à caus des imprecision d'impression que la pièce va pouvoir sortir sans contrainte tout en assurant que la pièce du dessus ne soit pas emportée à cause des frottement ni au moment de l'extraction de la pièce inférieur ni au moment du retour du poussoir à sa position initiale.

- diamètre plus grand que diagonale 2€ qui marche pour toutes les autres pièces

Dans cette colonne j'ai pratiqué une rainure pour pouvoir récupérer facilement les pièces (notamment quand on par en vacance, quand le distributeur est plein il y a plus de **XX€** en plus de pouvoir visualiser la quantité de pièces restantes). L'ouverture par laquelle les pièces vont s'échapper est large d'un diamètre de  la plus grande pièce (2€) sinon elle serait piégée un peu comme dans une pince. En hauteur, on est à un petit peu plus d'une hauteur de pièce, ça permet de prendre en compte les imprecisions d'impression et des jeux dans les mouvement tout en bloquant la pièce en contact direct avec celle qu'on pousse et qui pourrait être entraînée par frottement.

**Montrer le mécanisme complet**
On a donc un mécanisme complet qui permet de distribuer des pièces de monnaies : un distributeur par valeur faciale.

Il ne reste plus qu'à le commander.

Et on va faire ça grâce à un arduino.

J'ai choisi d'utiliser un arduino nano parce que d'une part parce qu'il est vraiment compact, ce qui permet de l'intégrer facilement sur un PCB proprement et d'autre part, par un coup de bol incroyable, car il contient tout juste suffisament d'entrées/sorties pour le projet dans son ensemble.

Pour commander un servo avec un arduino c'est simple si on a un servo qui se contrôle avec une commande PWM.
Le PWM sert à générer une tension continue à partir d'un signal carré. La valeur de la tension varie en fonction du rapport entre la durée d'une impulsion et la période du signal.

**/!\ alimentation**

Pour un servo commandable en PWM, un niveau de signal correspond soit à une position soit à une vitesse de rotation. Moi j'ai un contrôle de position et en fonction du signal PWM le servo va à la position demandée et essaie d'y rester.
Si on lui envoi 0 il va à la position 0 et essai d'y rester (ce sont des servos de modélisme qui sont asservi en position). Si on lui envoi du 180 il fait une demi-rotation et cherche à y rester (attention, j'ai des servo qui ont une amplitude de 180°, d'autres sont plus large et d'autre plus ressérés. Dans ce cas, il faut bien connaître les propriétés de son servo car si on lui envoi une commande qui va au-delà de ses capacités il risque de forcé, le courant va augmenter fortement et l'arduino et le servo risque de mourir).

Il existe une librairie de base Servo.h qui permet de manipuler des servo. 

**présentation du code**

__**description code broche pwm**__

Au départ, j'ai utilisé ce code comme ça. Mais j'ai eu un problème d'ordre sonnore : tant qu'on écrit un signal sur le servo, lui, il essai de maintenir sa position. Et comme ce sont des servo à pas cher ils ont tendance à osciller autour de leur position de référence et ça fait du bruit. Vu que le DAAP va se trouver dans le salon, c'est pas top. Au début je me suis dit que j'allais commander l'alimentation des servos via l'arduino mais dans mon cas ça fait prendre 3 pattes supplémentaires et trois transistors supplémentaires. Et puis j'ai fait un truc incroyable : j'ai lu la doc !

Et on découvre qu'il y a une méthode qui s'appelle `Servo::detach()` et qui permet de "déconnecter" le servo de la patte à laquelle il est attaché. Et c'est magique, plus de bruit.


On a donc trois petits distributeurs qui attendent qu'on leur disent combien de pièces chacun doit distribuer.  La somme d'argent est libre du moment que c'est une combinaison des pièces disponibles. Mais on ne va pas stocker la combinaison des pièce mais la somme d'argent à distribuer. C'est à partir de ce nombre qu'il faut reconstituer la séquence de distribution.

Dans mon code, j'ai une liste de pousseur de monnaie, chacun associé à une valeur faciale. Pour reconstituer la séquence de distribution je compte combien de fois on peut trouver la valeur faciale du distributeur courant dans le montant qu'il reste à distribuer et je place dans la séquence ce pousseur autant de fois. Ensuite je le montant restant et je recommence avec la valeur faciale du pousseur suivant jusqu'à ce que je ne puisse plus.

La distribution consiste à parcourir la liste sequence en appelant à chaque fois la méthode `CoinPusher::pushCoin()`. Ça permet de reconstituer le montant à distribuer.

Ce montant doit être stocké quelque part soit dans le code soit dans une mémoire extérieure.
Le problème qu'on rencontre en stockant ce montant dans le code c'est de réussir à retrouver à quel enfant il appartient. On peut se dire que le code secret est en fait l'identifiant unique de l'enfant mais c'est moche et ce n'est pas hyper fun. L'autre solution c'est de le stocker dans une mémoire extérieure que l'enfant pourrait conserver avec lui et  qui pourrait contenir toutes les informations liées à la distribution : le nom de l'enfant, le montant de l'argent de poche pour cet enfant et le code secret de l'enfant. Ça évite de devoir flasher l'arduino chaque fois que l'argent de poche change ou que l'enfant à oublié son code ou que le petit dernier a enfin le droit, lui aussi, de pouvoir acheter ses amis. 

Et pour ça il y a une super mémoire : la carte à puce.

<!-- SLE 4442 -->
Ce modèle est une SLE4442, une carte à puce sécurisée, c'est-à-dire que pour pouvoir écrire dedans où accéder à certaines zones mémoire il faut disposer du bon code pin, qui par défaut est FFFF, c'est pratique de le savoir quand on commence à expérimenter avec ce type de carte, surtout quand on sait qu'après trois mauvaises saisies la carte devient inutilisable. Pour la relier à l'arduino on utilise un connecteur de ce type qui est un simple boitier avec des broches souples qui viennent en contact des contacts dorés de la carte à puce. On y trouve également un petit intérupteur qui permet de détecter la présence de la carte.
<!-- ---FIN--- SLE 4442 -->

<!-- Structure carte -->
Ce code pin n'est pas le code de l'enfant, il pourrait, mais j'ai choisit de ne pas le faire par soucis de simplicité. Pour écrire les infos à l'intérieur de la carte j'ai créé un petit programme indépendant du projet, avec une petite interface avec le Serial de l'arduino qui permet de consulter le contenu de la carte et aussi d'y inscrire les données qu'on a besoin : le code secret, le montant de l'argent de poche, le nom de l'enfant mais aussi le nombre de caractères du prénom de l'enfant.

Même si en C/C++ il existe des méthodes de manipulation de chaines de caractères, ici je ne peux pas les utilser car c'est moi qui doit écrire dans la carte octet par octet et, pour une raison que j'ignore encore, j'ai eu un soucis en tentant d'écrire la valeur 0 dans la carte. Je pense que c'est un fausse manip mais pour avancer j'ai retenu cette solution-là.
<!-- ---FIN--- Structure carte -->


<!-- Discours trouver la librairie SClib-->
Ça peut paraître facile comme ça, et ça l'est dès qu'on a trouvé la bonne librairie. Et ça a été compliqué de trouver la bonne librairie. J'ai même faillit abandonné alors que je n'en trouvais pas et que l'implémentation du protocole dans un librairie maison constitue un projet en soi. Il faut manipuler des timers, il faut manipuler l'AVR en programmation bas niveau, c'est une tâche assez complexe. Mais à force de persévérence, je suis tombé sur une librairie, **sclib** qui n'a plus été touchée depuis 2015 mais ce n'est pas grave elle marche du feu de dieu. Elle permet normalement de travailler avec toutes les cartes de type SLE44X2 (carte sécurisé, synchrone ou pas). Elle est plutôt bien fichu, notamment parce qu'on peut, à l'aide d'un `#define` supprimer du code généré toute la partie concernant les cartes asynchrone ce qui allège fortement la taille du programme à téléverser dans l'arduino. Cette librairie implémente le protocole pour la SLE 4442 et...
<!-- FIN -- Discours trouver la librairie SClib-->


<!-- Protocole SLE4442 -->
... pour illustrer rapidement comment ça marche voici ce qu'il se passe lorsqu'on insère la carte dans le connecteur de carte à puce.

Donc ça c'est une partie de ce qu'il se passe lorsque l'enfant insère la carte dans l'appareil qui, par ailleur,  l'y invitait poliment par l'intermédiaire de l'écran LCD.
<!-- FIN -- Protocole SLE4442 -->


<!-- Présentation de L'écran LCD -->
C'est un écran à fond bleu conçu pour bousiller la rétine des enfants, il faut les habituer tôt. Mais surtout il permet d'afficher 4 lignes de 20 caractères (les fameux 20 caractères max du prénom que l'on stocke dans la carte à puce, si vous vous souvenez bien), je voulais un gros écran parce qu'en général les écrans LCD sont assez petits surtout si on se laisse tenter par les magniques écrans OLED polychromes, qui eux, sont franchement rikikis.

À la base, pour commander cet écran, il faut prévoir 6 broches sur l'arduino avec les librairies à disposition. Ça fait beaucoup, chaque broche de l'arduino est précieuse et donc il faut toujours passer un peu de temps à chercher si il y a un moyen de diminuer ce nombre de broches. Il se trouve que pour ce type d'écran il existe un petit modeil qui permet de communiquer avec lui en utilisant le protocole I2C qui, lui, n'utilise que deuxx broches de l'arduino. Et non seulement, l'implémentation de ce protocole est fournie par défaut avec l'arduino (c'est la librairie Wire) mais en plus, l'arduino possède (pour le nano) deux broches dédiées à cette fonction. Ce sont les broches SDA et SCL qu'on retrouve sur les diagrammes de *pinout*.
<!-- FIN -- Présentation de L'écran LCD -->

<!-- Introduction au protocole I2C -->
La norme I2C c'est un protocole de communication série, un peu comme l'USB. C'est un gros gros gros standard industriel implémenté par une grosse grosse grosse quantité d'équipements. On le retrouve partout. C'est basé sur une communication maître-esclave exclusive. Le ou les maîtres sont connectés via les ligne SCL/SDA aux différents esclaves. Le principe consiste à ce qu'un maître emette une condition START, tous les esclaves écoutent, le maître transmet alors l'adresse de l'esclave auquel il souhaite s'adresser (chaque composant dispose de sa propre adresse codée sur 7 bit) le 8ème bit permet de préciser s'il veut envoyer des données ou en recevoir. 


Autant dire que je suis bien content de ne pas avoir à l'implémenter. Maiiiiis ce serait intéressant !
<!-- FIN -- Introduction au protocole I2C -->

<!-- Librairie LCD -->
On a trouvé un composant qui réduit le nombre de broches, mais ça ne ne signifie pas pour autant qu'il existe une librairie qui va bien. On a de la chance, la communauté arduino est plutôt riche, et il se trouve qu'il en existe plusieurs. Par contre, il faut tester parce que toutes ne se valent pas. J'ai dû en essayer plusieurs, entre celles qui vendent du rêve, celles qui sont obsolettes et celles qui ne remplissent pas toutes les fonctions j'ai quand même fini par trouver la perle rare faite par un certain **Mathias Hertel**. 

Elle marche et en plus elle est simple d'utilisation : après avoir déclarer l'include qui va bien (pensez à donner des indices sur comment retrouver la livrairies, l'auteur, le nom dans la bibliothèque ou encore la version) il suffit de créer une instance de l'écran en précisant l'adresse I2C où le trouver puis d'écrire le texte qu'on veut là où on lui indique. Il y a également des fonctions utilisaires pour effacer l'écran par exemple. 
C'est le genre de fonction qu'on va utiliser pour changer le message à l'écran, pour, par exemple, inviter l'enfant à saisir son code une fois qu'il a inséré sa carte...
<!-- FIN -- Librairie LCD -->

<!-- Clavier matriciel -->
...La saisie du code se fait grace à un petit clavier matriciel de ce type, à 16 touche, 4x4. Là, niveau broche c'est du lourd parce qu'il en faut 8 : 1 pour chacune des 4 lignes et 1 pour chacune des 4 colonnes.
Ce genre de clavier fonctionne ainsi :
<!-- FIN -- Clavier matriciel -->

<!-- Clavier matriciel fonctionnement-->
C'est un ensemble d'interrupteurs. L'arduino va allumer tour à tour chaque colonne par exemple. Et dans le même il va scanner chaque ligne. Lorsqu'il allume la colonne 2 et que il détecte un signal sur la ligne 3 c'est que la touche 8 a été préssée. Il peut même détecter plusieurs touche en même temps.
Et il répète cette opération trés rapidement tout en prenant en compte le rebond des touches. 
<!-- FIN -- Clavier matriciel fonctionnement-->

<!-- Le rebond -->
Le rebond, c'est un phénomène qui se produit sur les composants mécaniques généralement, et souvant sur les interupteurs/bouton poussoir. Le contact n'est jamais franc, les pièces ont tendances à rebondir les unes sur les autres provoquant une signal aléatoir interprété comme une série de 0 et de 1 consécutifs (dont d'appui et de relachement du bouton) pendant un temps très court. Mais à 16 MHz, ce qui est court pour un humain est long pour un arduino qui les détecte tous. On peut implémenter un antirebond de manière électronique en insérant des filtres de type RC ou en l'implémentant de manière logicielle comme dans la librairie keypad.
<!-- FIN - Le rebond -->