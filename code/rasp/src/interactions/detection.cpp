#include "detection.hpp"

extern class Protocole Protocole;

GP2::GP2()
{

}


void GP2::activate(char side)
{
    printf("Envoie de la requète de d'activation des GP2 ............. ");
    int activate_back=(int) Protocole.set_detection_GP2('1');
    affichage(activate_back);
}

void GP2::disactivate(char side)
{
    printf("Envoie de la requète de désactivation des GP2 ............ ");
    int disactivate_back=(int) Protocole.set_detection_GP2('0');
    affichage(disactivate_back);
}



GP2::~GP2()
{

}
