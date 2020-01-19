#ifndef __DETECTION_H__
#define __DETECTION_H__


#include <stdio.h>
#include <math.h>
#include "world.hpp"
#include "asserv.hpp"
// Pris sur les anciens dépots a modifier !!!!
// 1.0  -> 6 cm
// 0.4  -> 10 cm
// 0.72 -> 20 cm
// O.19 -> 50 cm

enum GP2_name {
  gauche_avant,
  centre_avant,
  droite_avant,
  gauche_arriere,
  centre_arriere,
  droite_arriere,
};

struct GP2_information{
    enum GP2_name input;
    short mask; //Valeur entre 1 et 4
};

class GP2{

    public:
                GP2();
                GP2(enum GP2_name input,int activated,int distance_seuil);
                static void activate(); //Active la detection
                static void disactivate(); //Désactive la detection
                static void gp2Obstacle(); //Creer une interuption si les GP2 activés détectent quelque chose
                ~GP2();
    private:
        enum GP2_name input; //identifiant du GP2
        int activated; //0 si désactivé 1 sinon
        int distance_seuil;
};

#endif // __DETECTION_H__
