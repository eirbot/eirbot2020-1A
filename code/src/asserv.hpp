#ifndef __ASSERV_H_
#define __ASSERV_H_

#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <array>
#include <cfloat>
#include <stack>

struct position{
    int x;
    int y;
};

class Asservissement
{
    public:
        static void go_to(struct position dest); //Permet au robot de se tourner vers la destination et d'aller à la destination
        static void rotate(short angle); //Permet de faire tourner le robot d'un certain angle (le type de angle est à définir)
        static struct position robot_position(); //Renvoie la position du robot
        static void backward(); //Met les moteurs en marche arrière
        static void forward(); //Met les moteurs en marche avant
        static void initialise_x(); //Fait la calibration par rapport au grand coté de la table
        static void initialise_y(); //Fait la calibration par rapport au petit coté de la table
    private:

};

#endif
