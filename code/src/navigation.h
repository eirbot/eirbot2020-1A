#ifndef __NAVIGATION_H_
#define __NAVIGATION_H_

#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <array>
#include <cfloat>
#include <stack>

#include "asserv.hpp"

#define X_MAX 300 //Longueur de la table
#define Y_MAX 200 //Largeur de la table


struct Node{
        ushort x;
        ushort y;
        ushort parentX;
        ushort parentY;
        float gcost;
        float hcost;
        float fcost;

};


class Navigation
{
//Méthode
        public:
                Navigation();
                Navigation(Node src, Node dest);
                static bool isValid(int x, int y); //Permet de savoir si le noeud est obstacle ou non
                static bool isDestination(int x, int y, Node dest); //Permet de savoir si le noeud est la destination ou non
                static double calculateE(int x, int y, Node dest);//Permet de calculer la distance euclidienne entre deux noeuds
                static std::vector<Node> Astar(Node src, Node dest); //Coeur de l'algorithme A*
                static std::vector<Node> MakePath(std::array<std::array<Node,Y_MAX>,X_MAX> map, Node dest); //Permet de recréer le chemin
                static bool onTable(Node pos); //Permet de savoir si on est sur la table
                static void Print_path(std::vector<Node> usablePath); //Juste du débeugage permet d'afficher coordonnées par coordonnées un chemin
                static void Navigate_to_asserv(std::vector<Node>usablePath); //Permet de convertir un chemin en instruction asserv
                ~Navigation();

//Attributs
    private:
        Node src;
        Node dest;
};

#endif
