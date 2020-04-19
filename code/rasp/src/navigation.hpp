#ifndef __NAVIGATION_H_
#define __NAVIGATION_H_

#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <array>
#include <cfloat>
#include <stack>

#include "world.hpp"
#include "asserv.hpp"
#include "affichage.hpp"

/**
 * @file navigation.hpp
 * @brief Ce fichier contient toutes les méthodes permettant de réaliser une recherche de chemin sur la table de jeu
 * @author SD*/

/**
 * @class Navigation
 * @brief Contient les méthodes permettant de faire fonctionner correctement l'astar*/
class Navigation
{
//Méthode
        public:
                Navigation();
                /**
                 * @brief Permet d'initialiser la classe Navigation à un point x y
                 * @param node: Le node où la classe Navigation doit s'initialiser*/
                Navigation(Node node);
                /**
                 * @brief Fonction principale de la classe, permet d'effecteur une recherche de chemin entre deux points
                 * @param src: le point de départ
                 * @param dest: le point d'arrivée
                 * @param list_obstacle: la liste des obstacles actuellement présent sur la table
                 * @return Un vecteur de Node constituant le chemin entre les deux points en évitant les obstacles*/
                static std::vector<Node> Astar(Navigation src, Navigation dest, std::vector<obstacle> list_obstacles); //Coeur de l'algorithme A*
                /**
                 * @brief Permet de transformer une grille représentant la table
                 * en un chemin Cette fonction est utilisée dans l'Astar,
                 * l'Astar commence par remplir une grille représentant la table
                 * pour déterminer le trajet le plus court reliant les deux
                 * points évitant les obstacles, une fois cela fait cette
                 * fonction est appelée pour transformer cette grille en un chemin
                 * @param[in] map: la grille
                 * représentant la table complété par la première partie de
                 * l'Astar
                 * @param dest: Le point à atteindre
                 * @return Une suite de points constituant un chemin*/
                static std::vector<Node> MakePath(std::array<std::array<Node,Y_MAX>,X_MAX> map, Navigation dest); //Permet de recréer le chemin
                /**
                 * @brief Permet d'afficher un chemin calculé par l'Astar
                 * @param usablePath: un chemin calculé par exemple par MakePath
                 * @bug Affiche beaucoup beaucoup de lignes*/
                static void Print_path(std::vector<Node> usablePath); //Juste du débeugage permet d'afficher coordonnées par coordonnées un chemin
                /**
                 * @brief Permet de convertir un chemin en informations
                 * transmettables à l'asservissement. L'idée générale est de
                 * récupérer le chemin crée par MakePath chemin qui est précis
                 * case par case c'est à dire centimètre par centimètre. Pour ne
                 * pas transformer le robot en papybot on ne peut pas envoyer
                 * tous les points à l'asservissement, ainsi ne transmet à
                 * l'asservissement que les points de changement de direction.
                 * @param usablePath: un chemin utilisable crée par MakePath par
                 * exemple
                 * @param dest: le point à atteindre @param
                 * list_obstacles: la liste des obstacles sur la table
                 * @return un entier correspondant au code d'erreur du protocole*/
                static int Navigate_to_asserv(std::vector<Node>usablePath, Navigation dest, std::vector<obstacle> list_obstacles); //Permet de convertir un chemin en instruction asserv
                /**
                 * @brief Permet de prendre un branchement dans la stratégie en
                 * fonction du retour du protocole, si le protocole nous indique
                 * une détection ou un timeout cette fonction permet de refaire
                 * les actions qui n'ont pas été transmises ou d'éviter l'obstacle.
                 * @param back: entier représentant le retour du protocole
                 * @param dest: le point à atteindre
                 * @param list_obstacles: la liste des obstacles sur la table*/
                static void back_effect(int back, Navigation dest, std::vector<obstacle> list_obstacles); //Permet de faire un branchement de stratégie pour renvoyer un effet
                /**
                 * @brief Cette fonction permet de gérer un cas particulier où
                 * l'on détecte un robot et que l'Astar n'arrive plus à trouver
                 * un chemin pour sortir car il est bloqué par d'autres
                 * obstacles. Dans ce cas là, on supprime de la liste des
                 * obstacles les éco cups et on se permet de rouler dessus pour
                 * éviter le robot adverse en rappelant l'Astar
                 * @param list_obstacles: la liste des obstacles de la table
                 * @return la liste des obstacles sans les écos cups*/
                static std::vector<obstacle> stun(std::vector<obstacle> list_obstacles); //Permet de réagir si on est totalement bloqué
                ~Navigation();
                Node node;

//Attributs
        private:
                /**
                 * @brief Simple fonction pour savoir si une position x y est
                 * la destination demandée
                 * @param x : la coordonnée x de la position à tester
                 * @param y : la coordonnée y de la position à tester
                 * @param dest : le point de comparaison */
                static bool isDestination(int x, int y, Navigation dest); //Permet de savoir si le noeud est la destination ou non
                /**
                 * @brief Permet de calculer l'heuristique selon Euclide entre
                 * deux points
                 * @param x: coordonnée x du point actuel
                 * @param y: coordonnée y du point actuel
                 * @param dest: deuxième point de comparaison
                 * @param[out] E: conteneur de l'heuristique
                 * @return La valeur de racine((x-dest.x)^2 + (y-dest.y)^2)*/
                static double calculateE(int x, int y, Navigation dest,double E);//Permet de calculer la distance euclidienne entre deux noeuds
                /**
                 * @brief Permet de savoir si un point est sur la table
                 * @param pos: le point à tester
                 * @return True ou False*/
                static bool onTable(Navigation pos); //Permet de savoir si on est sur la table
};

#endif
