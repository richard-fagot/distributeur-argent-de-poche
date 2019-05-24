# Distributeur automatique d'argent de poche pour les enfants.

Pour qu'ils puissent faire "comme les grands", avoir une carte bleue personnalisée et saisir un code pour pouvoir retirer leur argent de poche au distributeur, mais uniquement le samedi.

L'objectif est de faire un truc fun pour les enfants (et pour moi aussi du coup :D). Et comme tout ne va pas se dérouler sans accros, j'en profite pour tenir un journal de bord des problèmes rencontrés et des solutions trouvées pour les résoudre.

Tant qu'à y être, ça me semble intéressant de partager tout ça, alors ce journal de bord sert de base à une présentation sous forme de quickie plein de trucs et astuces dans chacun des domaines du projet.

# Disciplines associées

- **La programmation Arduino**, pour coder la logique du distributeur :
    - C++,
    - Optimisation de la taille du code généré,
    - Minimisation de la fragmentation du tas,
    - Gestion du temps ;

- **L'électronique**, pour l'alimentation, les différents composants autour de l'arduino, la fabrication du PCB, la lecture de carte à puce... :
  - Design du schéma életronique,
  - Routing,
  - Gravure du PCB,
  - Soudage ;

- **La conception 3D** pour dessiner les pièces mécaniques, supports et boitier du distributeur :
    - Conception des pièces,
    - Définition des liaisons mécaniques,
    - Assemblage des différents éléments entre eux ;

- **L'impression 3D**, pour fabriquer les pièces conçues sur mesure :
    - Slicing,
    - Prise en compte des contraintes liées au FDM ;


# Matériel
- Arduino Nano ;
- Pavé numérique à matrice (keypad) ;
- Écran LCD 2004 (4 lignes de 20 caractères) avec module I2C ;
- Module RTC DS3231 (ne pas prendre le DS1307 car il dérive beaucoup (il peut perdre plus d'une minute par jour)) en I2C ;
- 2 micro servos type HXT900 ;
- Connecteur carte à puce ;
- Lot de carte à puce vierge SLE4442.


# Logiciel
- [**Arduino IDE**](https://www.arduino.cc/en/Main/Software) ou VSCode avec l'extension Arduino ;
- [**Fusion 360**](https://www.autodesk.com/products/fusion-360) pour modéliser les pièces mécaniques ;
- [**Cura**](https://ultimaker.com/en/products/ultimaker-cura-software) pour préparer les pièces destinées à l'impression 3D ;
- [**Tinkercad**](https://www.tinkercad.com) pour la simulation d'un environnement Arduino ;
- [**EasyEDA**](https://easyeda.com) pour la conception de la partie électronique et du routage du PCB.

# Références
- Éviter la fragmentation de la pile : https://cpp4arduino.com/2018/11/06/what-is-heap-fragmentation.html 