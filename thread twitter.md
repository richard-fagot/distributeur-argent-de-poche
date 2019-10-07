#

Un petit #THREAD pour détailler un peu plus mon talk au #DevfestToulouse
⬇️⬇️⬇️


#

Ce projet fait intervenir plein de domaines différents : conception 3D, impression 3D, électronique, arduino, C++, fabrication de PCB, un peu de mécanique, etc.

#

La conception 3D a été faite avec #Fusion360 (mais on peut utiliser #sketchup #Blender3d et plein d'autres) parce que c'était nouveau pour moi, il est super intuitif et qu'il y a une grosse communauté autour de ce logiciel pour apprendre facilement à s'en servir.

==> photo du projet fini dans Fusion360

#

Le design a été pensé pour tenir compte des contraintes de l'#impression3D :
- limiter les porte-à-faux ;
- tenir compte du sens d'impression des pièces subissant des contraintes mécaniques ;
- limiter la quantité de matière ;
- Faire des pièces qui s'impriment en 2h à 3h max.

#

J'ai voulu des temps d'impression courts d'une part parce que j'ai régulièrement des coupures de courant chez moi et que mon imprimante n'a pas de fonction "resume" et, d'autre part, parce que ça facilite le prototypage en pouvant plus facilement refaire une pièce défectueuse.

#

Pour la partie électronique j'ai utilisé ces composants :
- écran LCD2004 (20 cols, 4l) ;
- module I2C pour le LCD ;
- module RTC (horloge temps réel) ;
- Arduino nano ;
- Clavier matriciel 4x4 ;
- Servo HXT900 de modélisme ;
- Connecteur de carte à puce ;
- Carte à puce SLE4442.

#

Tous ces composants ont une librairie qu'on trouve facilement dans le gestionnaire de bibliothèque sauf pour la carte à puce. Il faut aller la trouver sur le net : https://sourceforge.net/p/arduinosclib/wiki/Home/
Et se la garder quelque part au cas où le lien disparaisse.

#

D'ailleurs, je vous recommande d'annoter vos imports de librairie dans le code avec suffisamment de détails pour la retrouver. Les librairies pour clavier matriciel ont la fâcheuse tendance à s'appeler "keypad.h".


#

Pour programmer la carte à puce et y mettre le code secret, la somme d'argent à distribuer et le prénom de l'enfant c'est par là : https://github.com/richard-fagot/DAAP-Smartcard

#

Sans rien changer aux branchements du distributeur on peut l'utiliser tel quel pour programmer une carte à puce, le mettre à l'heure et faire la distribution d'argent de poche uniquement en téléversant le programme qui va bien.

#

Pour la carte à puce : https://github.com/richard-fagot/DAAP-Smartcard

Pour l'heure il suffit de prendre les programmes d'exemple du DS3231.

#

L'horloge me permet de contrôler que les enfants ne font pas plus d'un retrait par semaine (samedi ou dimanche) en gérant les changements de mois et les années bissextiles.

#

Je n'en ai pas parlé pendant le talk mais il y a du code #cpp, beaucoup de code, que vous pouvez retrouver là : https://github.com/richard-fagot/distributeur-argent-de-poche/tree/master/sketch

Le point d'entrée c'est Sketch.ino à ouvrir dans l'IDE arduino : https://www.arduino.cc/en/Main/Software

#

Dans ce sketch il y a une première fonction 𝘀𝗲𝘁𝘂𝗽() d'initialisation des paramètres du programme et des périphériques. Le fonction 𝗹𝗼𝗼𝗽() contient la logique du programme. Une bonne pratique consiste à faire en sorte qu'elle s'exécute très rapidement.

#

C'est surtout pour dire qu'il faut remplacer les 𝗱𝗲𝗹𝗮𝘆() qui bloquent l'arduino par :

	𝗶𝗳(𝗺𝗶𝗹𝗹𝗶𝘀() - 𝗽𝗿𝗲𝘃𝗶𝗼𝘂𝘀𝗠𝗶𝗹𝗹𝗶𝘀 > 𝗺𝗼𝗻𝗗𝗲𝗹𝗮𝘆) {...}

ça permet de faire d'autres tâches en attendant qu'un servomoteur ait fini de tourner par exemple.

#

La gestion du temps c'est compliqué ! Sur ce projet j'ai mis en place une machine à état parce que c'est ce qui me semblait le plus naturel pour gérer les différents états du distributeur mais aussi les délais et notamment ceux qui concernent les mouvements des servos.


#

Mais attention aux noeuds au cerveau :D

#

Pour coder on peut utiliser l'IDE Arduino mais on peut aussi utiliser VS Code avec l'extension #Arduino (il sert à tout ce VS Code) et ça marche plutôt bien même si il y a des écarts sur la taille des programmes. Il faudrait regarder du côté des options de compilation du #cpp.

#

À un moment j'ai grillé un servo en faisant une fausse manipulation. J'ai cherché un logiciel qui permettrait de simuler un environnement #arduino et des périphériques autours, comme des servos.


#

Hé bien ça existe ! c'est @tinkercad. J'ai fait une grosse partie de la conception grâce à ça, sans rien casser ! On peut s'en servir comme dans @scratch ou en code pur. Et utiliser des servos, des LCD, la mémoire EEPROM...

#

Quand la phase de prototypage est terminée on va créer le PCB. J'ai utilisé @EasyEDA mais on peut utiliser aussi @kicad_pcb qui est open source.

==> image du pcb


#

Après il suffit de suivre cet excellent tuto de @Heliox_Lab en prenant un papier glacé le plus fin possible pour éviter le gondolage : https://youtu.be/UTe3eYCj6vU


#

Et quand tout est enfin terminé, on profite du résultat final :

(Qu'est-ce que t'en dit @Heliox_Lab ? :D)

Si vous avez des questions, mes DM sont ouverts.
