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


# Le séquenceur

# Quand ?

# My little Hackers

# Interactions

