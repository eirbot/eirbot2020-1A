# EIRBOT 2020-1A : Equipe EIRBOAT
![alt text](https://raw.githubusercontent.com/eirbot/eirbot2020-1A/master/eirbot_logo.png)
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

## Mécanique
Dans un premier temps nous avons la mécanique, le [schéma](https://github.com/eirbot/eirbot2020-1A/blob/master/meca/maquette_robot/AssemblageV2.stl) général se base sur une architecture octogonale, structuré par des profilées et via la notion d'étage . La conception de ce dernier à été mené par **Erwann** aidé par **Julien**.

## Alimentation 
Un autre étape cruciale de notre robot est la distribution de l'énergie dans ce dernier. Pour ce faire nous passons via une carte d'alimentation, so rôle est de distribuer aux différentes instances l'énergie nécessaire pour fonctionner. Cette partie à été réalisé par **Lucas** et **Yohann** 
### Schéma de principe
![alt text](https://raw.githubusercontent.com/eirbot/eirbot2020-1A/master/schema_bloc_connexions.png)
### Résultat
![alt text](https://github.com/eirbot/eirbot2020-1A/blob/master/reunion/alimentation.jpg)

## Actionneur
Nous allons avoir besoin d'un actionneur principal pour réaliser nos principales actions. Cet actionneur possèdera un mouvement vertical par rapport à la table. Il permettra d'une part d'actionner les manches à air et d'autre part d'actionner le phare (i.e. de réaliser toutes nos actions) cette partie est gérée par **Filipe**

## Puissance 
Une fois que nous pouvons alimenter tous les composants de notre robot nous devons encore permettre un contrôle de la puissance fournie au moteur, pour cela nous créons deux cartes possédant un pont en H, cela nous permet de délivrer la puissance nécessaire à nos moteurs pour nos robots. Cette partie comprend la conception de deux cartes et a été réalisé par **Martin**.
### Schéma de conception

### Résultat

## Asservissement
L'idée maintenant que nous avons une mécanique propre, nos différents modules aliméntés et que nous pouvons contrôler précsiement nos moteurs est de créer un asservissement. Le but de l'[asservissement](https://github.com/eirbot/eirbot2020-1A/tree/master/code/nucleo) est de récupérer les informations des encodeurs et de permettre au robot d'atteindre une certainne position tout en gérant l'angle, la puissance des moteurs etc. Cette partie est réalisé par **Liam**, **Clément** et **Emile** sur nucléo.

## Stratégie
Maintenant que nous avons un asservissement nous devons réaliser les choix de stratégie. L'algorithme principal de la stratégie est un algorithme de pathfinding appelé A*. Autour de cela nous avons construit la trajectoire entre les différents objectifs, les différents choix de stragéies mais aussi les procédures d'évitements. Les codes sont disponibles [ici](https://github.com/eirbot/eirbot2020-1A/tree/master/code/rasp/src), la commande permettant de visualiser au mieux l'avancement actuel est `make test` puis `./test base debug`. La plupart de ces algorithmes est réalisé par **Sébastien** sur raspberry.

## Protocole de communication
Nous pouvons observer que l'asservissement est proposé pour nucléo alors que la stratégie est proposée pour raspberry. Dans cette optique nous nécessitons un protocole de communication entre la raspberry et la nucléo. Ce projet a été mené par **Lucas**, l'idée est de mettre en place un système "master<->slave" où la rasp envoie des requêtes à la nucléo et où cette dernière répond à ces requêtes. 

## Phare
En marge du robot nous devons réaliser l'expérience. Cette partie est réalisée par **Marius**. L'objectif du phare est de se déployer pendant le match pour permettre d'atteindre une certainne hauteur. Cela est réalisé par un bras robotique imprimé en PLA. Ce dernier possède un design comme suit.
![alt text](https://raw.githubusercontent.com/eirbot/eirbot2020-1A/master/reunion/phare.jpg)



