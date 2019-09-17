---
pagetitle: DAAP
lang: fr-FR
compile: pandoc -t revealjs -V theme=white -s Lightning.md -o lightning.html --css=devfest.css 
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


<!-- Extrait BD de Calvin & Hobbs-->
# 
![](assets/img/calvin.png)

::: notes
Passer rapidement.

==> littérature sur le sujet
:::

<!-- Courte introduction à l'argent de poche et genèse du projet -->
# 

:::notes
- règles de l'argent de poche :
  - quantité libre,
  - distribution 1x/sem,
  - Pas de privation,
  - not(rémunération),
  - l'enfant dépense librement.

==> quitte à faire comme les grands, est-ce qu'on peu aller plus loin ?
:::

# 
![](assets/img/mouvement.gif){ height=600px }

:::notes
Passez rapidement pour ne pas perdre l'attention de l'auditoire.

- joli ;
- hypnotique ;
- facile à concevoir.

==> il est constitué de != éléments
:::

# 
![](assets/img/poussoir.png){ height=600px }

::: notes
**Le poussoir**

- mouvement bielle-manivelle ;
- rotation -> translation.

==> parce que j'aime bien le mouvement
:::


# 
![](assets/img/Impression clip.png){ width=1000px }

:::notes
  - Toujours penser le design 3D en fonction de la technique de production
  - paramètres d'impression dans Cura (Simplify3D) ;
  - Pros'n Cons des 3 impressions ;
  - insertion manivelle/poussoir ;
  - mouvement rectiligne, support servo, réservoir pièce.

  ==> Je vous présente le support.
:::

# 
![](assets/img/support.png){ height=600px }

::: notes

:::


# SLE 4442
![](assets/img/carte+connecteur.png){height="400px"}

:::notes
  - carte sécurisée ;
  - connecteur ;
==> on y stocke
:::

# 
![](assets/img/LCD.png){height="250px"}
![](assets/img/clavier.png){height="250px"}

# 
![](assets/img/arduino_nano.png){ height=600px }

:::notes
:::

# 
![](assets/img/breadboard.jpg){ width=500px }



# 
![](assets/img/circuit.png){ height=600px }

# 
![](assets/img/PCB2.png){ height=600px }

# 
![](assets/img/PCB étamé.jpg){ width=400px }

# 
![](assets/img/Circuit imprimé.jpg){ width=500px }

# 
![](assets/img/boitier.png){ width=500px }

# 
Sans cahnger les branchements mais uniquement le programme on peut se servir du DAAP comme programmateur de càp, d'éditer l'heure et de daap

# Démonstration