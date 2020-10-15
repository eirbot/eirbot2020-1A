#ifndef __WORLD_H_
#define __WORLD_H_

#include <vector>
using namespace std;

/**
 * @brief La largeur du robot*/
#define ROBOT_WIDTH 32
/**
 * @brief La longueur du robot*/
#define ROBOT_LENGTH 32
/**
 * @brief La longueur de la table*/
#define X_MAX 300
/**
 * @brief La largeur de la table*/
#define Y_MAX 200

/**
 * @file world.hpp
 * @brief Permet definir la table de jeu et les différentes structures nécessaires au fonctionnement de la navigation
 * @author SD*/

/**
 * @brief Structure permettant de définir un Node, essentiel pour réaliser l'Astar
 * @param x: coordonnée x
 * @param y: coordonnée y
 * @param parentX: coordonnée x du parent du point, rempli uniquement pendant l'exécution de l'Astar
 * @param parentY: coordonnée y du parent du point, rempli uniquement pendant l'exécution de l'Astar
 * @param gcost: cout entre le noeud de départ et le noeud actuel, non vide seulement si l'Astar est executé
 * @param hcost: cout estimé entre le noeud actuel et le noeud d'arrivée, non vide seulement si l'Astar est executé
 * @param fcost: plus petit cout parmis les voisins du noeud actuel, non vide seulement si l'Astar est executé*/
struct Node{
        short x;
        short y;
        short parentX;
        short parentY;
        float gcost;
        float hcost;
        float fcost;

};


/**
 * @brief Permet de définir une forme pour ensuite être utilisé dans un obstacle
 * @param width: la largeur de l'obstacle en centimètre
 * @param length: la longeur de l'obstacle en centimètre*/
struct shape{
    short width;
    short length;
};

/**
 * @brief Permet de définir un obstacle sur la table
 * @param center_x: la coordonnée x du centre de l'obstacle
 * @param center_y: la coordonnée y du centre de l'obstacle
 * @param shape: la forme de l'objet*/
struct obstacle{
    short center_x;
    short center_y;
    struct shape *shape;
};

/**
 * @brief Permet de remplir un vecteur avec la liste des obstacles, c'est ici que l'on ajoute ou enlève des obstacles
 * @return un vecteur avec la liste des obstacles*/
std::vector<obstacle> fillVector(); //Permet de remplir un vecteur avec la liste des obstacles
/**
 * @brief Permet de savoir, si le robot est dans une position si il entre en collision avec un obstacle
 * @param x: coordonnée x du point à tester
 * @param y: coordonnée y du point à tester
 * @param list_obstacles: listes des obstacles sur la table*/
bool isValid(short x, short y,std::vector<obstacle> list_obstacles); //Renvoie faux si la case n'est pas valide
bool who_here(short x, short y, struct shape shape,std::vector<obstacle> list_obstacles);

/**
 * @brief Cette fonction permet de gérer un cas particulier où
 * l'on détecte un robot et que l'Astar n'arrive plus à trouver
 * un chemin pour sortir car il est bloqué par d'autres
 * obstacles. Dans ce cas là, on supprime de la liste des
 * obstacles les éco cups et on se permet de rouler dessus pour
 * éviter le robot adverse en rappelant l'Astar
 * @param list_obstacles: la liste des obstacles de la table
 * @return la liste des obstacles sans les écos cups*/
std::vector<obstacle> fillVector_no_ecocup(); //Permet de remplir un vecteur avec la liste des obstacles sans les eco cups



#endif
