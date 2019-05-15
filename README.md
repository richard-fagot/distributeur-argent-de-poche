# Distributeur automatique d'argent de poche pour les enfants.

Pour qu'ils puissent faire "comme les grands", avoir une carte bleue personnalisée et saisir un code pour pouvoir retirer leur argent de poche au distributeur, mais uniquement le samedi.

Le projet fait intervenir plusieurs disciplines :

- **La programmation Arduino**, pour coder la logique du distributeur ;
- **L'électronique**, pour l'alimentation, les différents composants autour de l'arduino, la fabrication du PCB, la lecture de carte à puce... ;
- **La conception 3D**, pour dessiner les pièces mécaniques, supports et boitier du distributeur ;
- **L'impression 3D**, pour fabriquer les pièces conçues sur mesure ;

L'objectif est de faire un truc fun pour les enfants (et pour moi aussi du coup :D). Et comme tout ne va pas se dérouler sans accros, j'en profite pour tenir un journal de bord des problèmes rencontrés et des solutions trouvées pour les résoudre.

Tant qu'à y être, ça me semble intéressant de partager tout ça, alors ce journal de bord sert de base à une présentation sous forme de quickie plein de trucs et astuces dans chacun des domaines du projet.

# Matériel
- Arduino Uno R3 ? ;
- Pavé numérique à matrice ;
- Ecran LCD 2004 (4 lignes de 20 caractères) avec module I2C ;
- Module RTC DS3231 (ne pas prendre le DS1307 car il a une large dérive (il peut perdre plus d'une minute par jour)) en I2C ;
- 2 micro servos type HXT900 ;
- Connecteur carte à puce ;
- Lot de carte à puce vierge SLE4442.

# Logiciel
- **Arduino IDE** ou VSCode avec l'extension Arduino ;
- **Fusion 360** pour modéliser les pièces mécaniques ;
- **Cura** pour préparer les pièces destinées à l'impression 3D ;
- **Tinkercad** pour la simulation d'un environnement Arduino ;
- **EasyEDA** pour la conception de la partie électronique et du PCB.