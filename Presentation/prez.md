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




# L'argent de poche

![Calvin et l'argent de poche](assets/img/calvin.jpg)


::: notes
- Décision de donner des sous aux enfants ;
- Règles de l'argent de poche ;
- Quitte à faire comme les grands autant aller jusqu'au bout ;
- Projet fun pour les enfants ;
- (et fun pour le papa).
:::




# Le Distributeur

![](assets/img/eclaté.png){ height=400px }


::: notes

- Utiliser la photo du distributeur pour expliquer le workflow :
    - Insertion d'une carte à puce,
    - Saisie du code secret,
    - Distribution de l'argent,
    - Uniquement le week-end ;

- Présenter chaque partie par un éclaté progressif :
    - le poussoir,
    - la carte à puce,
    - le clavier,
    - l'écran,
    - le module RTC,
    - le boitier,
    - l'arduino pour les contrôler tous.

:::


# Le mécanisme de distribution
 - Le poids des pièces ;
 - Le système bielle-manivelle.

::: note
- Recherche d'une solution (la roue en premier)
:::

# 
![](assets/img/poussoir.png){ height=600px }

::: note
- Impression en une fois ;
- Puis en plusieurs pièces pour pouvoir avoir plusieurs couleurs ;
- Clipper les pièces ensembles ;
- Raffinement à cause de la nouvelle visserie des servos
:::

#
![](assets/img/porte-pieces.png){ height=600px }

#
![](assets/img/face-pieces.png){ height=600px }

# 
![](assets/img/distributeur.png){ height=600px }


# Recherche d'une solution

Image du trieur avec la roue qui tourne + image de ce que le système aurait pu être.

::: note
Pas assez ludique et visuel
:::

# Le système bielle-manivelle
Image dans le moteur + capture fusion
http://subaru.univ-lemans.fr/AccesLibre/UM/Pedago/physique/02/meca/bielle.html

::: note
- comment relier les pièces entre elles ?
:::

# Avec le porte-pièces
Image dans fusion + Photo réélle

# Fusion 360
Demo !

::: note
- Extrusion et opérations booléénes
- liaisons
- les contraintes de l'impression 3D (porte à faux, résistance)
:::

# Le système de saisie
- écran / clavier

# Gestion de l'heure
-RTC

# L'impression 3D

# L'Arduino
Le C++ c'est l'enfer : déclaration d'un int et d'un char [20] mais lecture de 21 caractère écrase une partie du int.
```cpp
void setup() {

}

void loop() {

}

```


# My Little Hackers
Empêcher les enfants de hacker le système


# Évolution

- Transformer les distributeurs en petits robots autonomes.
- Rust

::: notes

Transformer les distributeurs en petits robots automnomes (par exemple avec une tête de chat) placés dans une petite niche.
Quand l'enfant insère sa carte ils se mettent à trépigner d'impatience.
Une fois la carte retirée ils foncent vers un bol pour cracher par leur petite bouche les pièces qu'il faut.

:::
