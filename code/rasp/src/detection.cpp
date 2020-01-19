#include "detection.hpp"

GP2::GP2():input(),activated(),distance_seuil()
{

}

GP2::GP2(enum GP2_name input,int activated,int distance_seuil):input(input),activated(activated),distance_seuil(distance_seuil)
{

}

void GP2::activate(GP2 input)
{
    input.activated=1;
    printf("Envoie de la requète de d'activation du GP2 : %d \n", input.input);
}

void GP2::disactivate(GP2 input)
{
    input.activated=0;
    printf("Envoie de la requète de désactivation du GP2 : %d \n", input.input);
}

extern vector<obstacle> list_obstacles;

static void gp2Obstacle()
{
    //On récupère la valeur de la nucléo
    int nucleo_value[6]={0,0,0,0,0,0}; //set:detection() pour récupérer l'information selon le protocole de com
    int tot=0;

    // On vérifie si il y a des informations
    for (int i=0; i < 6; i++) {
        if (nucleo_value[i]==0) {
            tot+=1; //Pas d'interuption
        }
    }
    if (tot==6) {
        return;
    }

    //Si il y a des informations on transforme ces dernières et on les place des deux tableaux (avant et arrière)
    struct GP2_information information_avant[3];
    struct GP2_information information_arriere[3];
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

        information_arriere[i].mask=(nucleo_value[i+3]%2);
        nucleo_value[i]=nucleo_value[i+3]/2;
        information_arriere[i].mask+=(nucleo_value[i+3]%2);
        nucleo_value[i]=nucleo_value[i+3]/2;
        information_arriere[i].mask+=(nucleo_value[i+3]%2);
        nucleo_value[i]=nucleo_value[i+3]/2;
        information_arriere[i].mask+=(nucleo_value[i+3]%2);
        nucleo_value[i]=nucleo_value[i+3]/2;
        information_arriere[i].input=(enum GP2_name) (i+3);
    }

    //On trouve le mask le plus proche de nous
    // 4 -> 6 cm
    // 3 -> 10 cm
    // 2 -> 20 cm
    // 1 -> 50 cm
    // 0 -> rien
    short max_mask_avant=0;
    short max_mask_arriere=0;
    for (int i=0; i < 3; i++) {
        if(max_mask_avant<information_avant[i].mask){
            max_mask_avant=information_avant[i].mask;
        }
        if (max_mask_arriere < information_arriere[i].mask){
            max_mask_arriere = information_arriere[i].mask;
        }
    }

    //On trouve maintenant la configuration (gauche, centre gauche, centre, centre droit, droit) et on place le nouvel obstacle
    short position_x=Asservissement::robot_position().x;
    short position_y=Asservissement::robot_position().y;
    short angle=Asservissement::angle();
    struct shape robot={34,34};
    float calcul_x=position_x+(max_mask_avant+32)*cos(angle);
    float calcul_y=position_y+(max_mask_avant+32)*sin(angle);
    list_obstacles.push_back({(short)calcul_x, (short)calcul_y, &robot});
}

//Creer une interuption si les GP2 activés détectent quelque chose


GP2::~GP2()
{

}
