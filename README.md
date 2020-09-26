# EIRBOT 2020-1A : Equipe EIRBOAT ![Code check](https://github.com/eirbot/eirbot2020-1A/workflows/Code%20check/badge.svg) ![Documentation](https://github.com/eirbot/eirbot2020-1A/workflows/Documentation/badge.svg) ![Valgrind](https://github.com/eirbot/eirbot2020-1A/workflows/Valgrind/badge.svg)

![alt text](https://raw.githubusercontent.com/eirbot/eirbot2020-1A/loutreB&W.png)


Ceci est le dépôt de l'équipe de 1A de l'association de robotique Eirbot. La
description de l'avancement des différents projets est disponible via la 
[descrition](https://github.com/eirbot/eirbot2020-1A/blob/master/description/descrption.pdf) de nos projets. Le projet se divise en plusieures catégories allant du plus bas au plus au niveau (en terme de raprochement avec le côté physique). 

## Membres
Ce projet est réalisé par les différents membres de Eirbot en première année : 
- Alberty Maxime (SEE)
- Barrais Marius
- Camberlin Erwann (Matmeca)
- Delpeuch Sébastien (Informatique)
- Mangin Lucas
- Moroy Liam
- Neveu Emile
- Pouget Filipe
- Poupon Julien
- Savary Clément (SEE)
- Vaquori Yohann
- Vidal Martin

## Installation 
Le projet est construit avec Cmake, il suffit donc de cloner le projet puis 

```
cd eirbot2020-1A/code/
cd build/
cmake .. 
```

## Éxecution 

Depuis le dossier `build/`

Pour compiler le projet il suffit de faire `make project` en ayant un compilateur
de C++.

Plusieurs méthodes permettent d'exécuter le projet. 

En local un `./project` suffit, si la nucléo est branchée via le port USB une
simulation de communication est enclenchée (la nucléo renvoie toujours vrai à
chaque demande). Cela peut demander de faire la commande en super utilisateur ou
changer le chemin d'accès au port USB (ligne 110 de ce
[code](https://github.com/eirbot2020-1A/tree/master/code/rasp/src/main.cc)). 

Pour mettre le projet sur la rasp et donc le robot il faut être connecté au même
wifi que la raspeberry puis faire un `make final`.

En plus de l'exécution des tests sont effectués sur les codes, ils peuvent être
compilés en faisant `make test` puis `./test`. A partir de ce moment des tests
sur tous les modules implémentés sont exécutés, le coverage actuel est de 87%

Finalement un `make doc` permet d'afficher la documentation de nos codes.
Elle est de plus disponible sur notre [page web](https://eirbot.github.io/eirbot2020-1A/md__r_e_a_d_m_e.html)


## Description du projet 
### Mécanique
Dans un premier temps nous avons la mécanique, le
[schéma](https://github.com/eirbot/eirbot2020-1A/blob/master/meca/maquette_robot/AssemblageV2.stl)
général se base sur une architecture octogonale, structuré par des profilés et
via la notion d'étage.

Un porte batterie a été fait pour éviter que la batterie bouge pendant le
déplacement 

Le design des étages est en cours. 

Le design des portes GP2 est en cours.

### Alimentation 
Un autre étape cruciale de notre robot est la distribution de l'énergie dans ce dernier. Pour ce faire nous passons via une carte d'alimentation, so rôle est de distribuer aux différentes instances l'énergie nécessaire pour fonctionner. 
#### Schéma de principe
![principe alimentation](https://raw.githubusercontent.com/eirbot/eirbot2020-1A/master/schema_bloc_connexions.png)
#### Résultat
![résultat alimentation](https://github.com/eirbot/eirbot2020-1A/blob/master/reunion/alimentation.jpg)

### Actionneur
Pour réaliser les différentes actions nous avons besoins de différents
actionneurs. 

Tout d'abord des actionneurs simples utiles pour activer le phare et les manches
à air, ils sont au nombre de deux pour gérer facilement chaque côté de la table.

Ensuite un actionneur représentant le pavillon et permettant de lever le
drapeau.

Finalement un pince est en cours de réflexion pour ramasser les ecocups

### Puissance 
Une fois que nous pouvons alimenter tous les composants de notre robot nous devons encore permettre un contrôle de la puissance fournie au moteur, pour cela nous créons deux cartes possédant un pont en H, cela nous permet de délivrer la puissance nécessaire à nos moteurs pour nos robots.
#### Schéma de conception

#### Résultat

### Asservissement
L'idée maintenant que nous avons une mécanique propre, nos différents modules aliméntés et que nous pouvons contrôler précsiement nos moteurs est de créer un asservissement. Le but de l'[asservissement](https://github.com/eirbot/eirbot2020-1A/tree/master/code/nucleo) est de récupérer les informations des encodeurs et de permettre au robot d'atteindre une certainne position tout en gérant l'angle, la puissance des moteurs etc.

### Stratégie
Maintenant que nous avons un asservissement nous devons réaliser les choix pour
notre stratégie. 

La stratégie se décompose en deux parties. Une partie sur la nucléo contenant
les actions "matérielles" à faire (par exemple tourner le servomoteur de
l'actionneur pour la phare). Et une partie de stratégie plus abstraite sur
raspeberry. 

La partie abstraite a plusieurs rôles 
+ Elle contrôle le déroulement de la partie (initialisation, ordre des actions,
  demandes de déplacements ...)
+ Elle gère la communication avec la balise lisant la boussole et le phare 
+ Elle est la seule à connaître la disposition de la table (disposition des
  obstacles, place des ecocups initialement)
+ Elle est capable de calculer une trajectoire entre les obstacles (via un
  algorithme de pathfinding l'A*)
+ Elle est capable de définir dans quel sens il faut ramasser les ecocups
  (probleme du voyageur de commerce, algorithme des colonies de fourmis)
  
Les codes sont disponibles
[ici](https://github.com/eirbot/eirbot2020-1A/tree/master/code/rasp/src). 


### Protocole de communication

Comme dit précédemment nous avons séparé la partie d'implémentation du contrôle
physique (sur la nucléo) et la partie d'implémentation de la stratégie (sur la
rasp). Cela implique donc une communication entre les deux cartes. L'idée est
d'utiliser un protocole de communication du type maitre esclave. Par exemple
lorsque la rasp a trouvé la trajectoire demandé, elle fournit au fur et à mesure
les coordonnées qu'elle souhaite atteindre à la nucléo. Cette dernière via
l'asservissement déplace le robot à la position souhaitée, elle a un certains
temps pour le faire. Si elle arrive à la position demandée elle renvoie "OK", si
elle n'y arrive pas automatiquement le protocole renvoie "TIMEOUT". Si les GP2,
reliés à la nucléo détectent un robot ennemi pendant le déplacement, la nucléo
stoppe le robot et renvoie "DETECTION" à la rasp. Cette dernière prendra alors
les mesures nécessaires pour éviter le robot. C'est ainsi que se déroule la
communication entre la rasp et la nucleo. 

## Phare
En marge du robot nous devons réaliser l'expérience. L'objectif du phare est de se déployer pendant le match pour permettre d'atteindre une certainne hauteur. Cela est réalisé par un bras robotique imprimé en PLA. Ce dernier possède un design comme suit.
![phare](https://eirbot.github.io/assets/images/phare_d.png)



