#include "detection.hpp"

GP2::GP2():input(),activated(),distance_seuil()
{

}

GP2::GP2(enum GP2_name input,int activated,int distance_seuil):input(input),activated(activated),distance_seuil(distance_seuil)
{

}

void GP2::activate()
{
    printf("Envoie de la requète de d'activation des GP2 ............. ");
    affichage(Protocole::Etat::OK);
}

void GP2::disactivate()
{
    printf("Envoie de la requète de désactivation des GP2 ............ ");
    affichage(Protocole::Etat::OK);
}


vector<obstacle> GP2::gp2Obstacle(vector<obstacle> list_obstacles, struct position position)
{
    //On récupère la valeur de la nucléo
    int nucleo_value[3]={0,0,0}; //set:detection() pour récupérer l'information selon le protocole de com

    //Si il y a des informations on transforme ces dernières et on les place des deux tableaux (avant et arrière)
    struct GP2_information information_avant[3];
    for (int i=0; i < 3; i++) {
        information_avant[i].mask=(nucleo_value[i]%2);
        nucleo_value[i]=nucleo_value[i]/2;
        information_avant[i].mask+=(nucleo_value[i]%2);
        nucleo_value[i]=nucleo_value[i]/2;
        information_avant[i].mask+=(nucleo_value[i]%2);
        nucleo_value[i]=nucleo_value[i]/2;
        information_avant[i].mask+=(nucleo_value[i]%2);
        nucleo_value[i]=nucleo_value[i]/2;
        information_avant[i].input=(enum GP2_name) i;
    }

    //On trouve le mask le plus proche de nous
    // 4 -> 6 cm
    // 3 -> 10 cm
    // 2 -> 20 cm
    // 1 -> 50 cm
    // 0 -> rien
    short max_mask_avant=0;
    for (int i=0; i < 3; i++) {
        if(max_mask_avant<information_avant[i].mask){
            max_mask_avant=information_avant[i].mask;
        }
    }

    //On trouve maintenant la configuration (gauche, centre gauche, centre, centre droit, droit) et on place le nouvel obstacle
    short position_x=position.x;
    short position_y=position.y;
    short angle=Asservissement::angle();
    struct shape robot={34,34};
    short mask_to_distance;
    switch (max_mask_avant) {
        case 4:
            mask_to_distance=6;
            break;
        case 3:
            mask_to_distance=15;
            break;
        case 2:
            mask_to_distance=25;
            break;
        case 1:
            mask_to_distance=50;
            break;
    }
    mask_to_distance=130;
    angle=90;
    float calcul_x=position_x+(mask_to_distance+32)*cos(angle);
    float calcul_y=position_y+(mask_to_distance+32)*sin(angle);
    list_obstacles.push_back({(short)calcul_x, (short)calcul_y, &robot});
    return list_obstacles;
}


GP2::~GP2()
{

}
