#ifndef __ASSERV_H_
#define __ASSERV_H_

#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <array>
#include <cfloat>
#include <stack>
#include <cstdlib>

#include  "affichage.hpp"
#include "world.hpp"
#include <vector>

using namespace std;

extern bool debug;
extern vector<Node> debugPath;

struct position{
    int x;
    int y;
};

class Asservissement
{
    public:
        static int go_to(struct position dest); //Permet au robot de se tourner vers la destination et d'aller à la destination
        static int call_back(int timeout, int detection); //Permet d'analyser le retour de l'asservissement
        static void rotate(short angle); //Permet de faire tourner le robot d'un certain angle (le type de angle est à définir)
        static struct position robot_position(); //Renvoie la position du robot
        static short angle(); //Renvoie l'angle du robot par rapport à la table (entre 0 et 360)
        static void initialise_x(); //Fait la calibration par rapport au grand coté de la table
        static void initialise_y(); //Fait la calibration par rapport au petit coté de la table
    private:

};

#endif
