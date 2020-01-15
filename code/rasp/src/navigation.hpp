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

class Navigation
{
//Méthode
        public:
                Navigation();
                Navigation(Node node);
                static std::vector<Node> Astar(Navigation src, Navigation dest, std::vector<obstacle> list_obstacles); //Coeur de l'algorithme A*
                static std::vector<Node> MakePath(std::array<std::array<Node,Y_MAX>,X_MAX> map, Navigation dest); //Permet de recréer le chemin
                static void Print_path(std::vector<Node> usablePath); //Juste du débeugage permet d'afficher coordonnées par coordonnées un chemin
                static void Navigate_to_asserv(std::vector<Node>usablePath, Navigation dest); //Permet de convertir un chemin en instruction asserv
                ~Navigation();
                Node node;

//Attributs
        private:
                static bool isDestination(int x, int y, Navigation dest); //Permet de savoir si le noeud est la destination ou non
                static double calculateE(int x, int y, Navigation dest,double E);//Permet de calculer la distance euclidienne entre deux noeuds
                static bool onTable(Navigation pos); //Permet de savoir si on est sur la table
};

#endif
