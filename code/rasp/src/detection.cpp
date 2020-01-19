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
    int nucleo_value[6]={0,0,0,0,0,0}; //set:detection() pour récupérer l'information selon le protocole de com
    int tot=0;
    for (int i=0; i < 6; i++) {
        if (nucleo_value[i]==0) {
            tot+=1; //Pas d'interuption
        }
    }
    if (tot==6) {
        return;
    }

    struct GP2_information information_avant[3];//nucleo_value normalement;
    struct GP2_information information_arriere[3];
    for (int i=0; i < 3; i++) {
        information_avant[i].mask_4=(nucleo_value[i]%2);
        nucleo_value[i]=nucleo_value[i]/2;
        information_avant[i].mask_3=(nucleo_value[i]%2);
        nucleo_value[i]=nucleo_value[i]/2;
        information_avant[i].mask_2=(nucleo_value[i]%2);
        nucleo_value[i]=nucleo_value[i]/2;
        information_avant[i].mask_1=(nucleo_value[i]%2);
        nucleo_value[i]=nucleo_value[i]/2;
        information_avant[i].input=(enum GP2_name) nucleo_value[i];

        information_arriere[i].mask_4=(nucleo_value[i+3]%2);
        nucleo_value[i]=nucleo_value[i+3]/2;
        information_arriere[i].mask_3=(nucleo_value[i+3]%2);
        nucleo_value[i]=nucleo_value[i+3]/2;
        information_arriere[i].mask_2=(nucleo_value[i+3]%2);
        nucleo_value[i]=nucleo_value[i+3]/2;
        information_arriere[i].mask_1=(nucleo_value[i+3]%2);
        nucleo_value[i]=nucleo_value[i+3]/2;
        information_arriere[i].input=(enum GP2_name) nucleo_value[i+3];
    }
    int max_mask_avant=0;
    int max_mask_arriere=0;
    for (int i=0; i < 3; i++) {
        max_mask_avant=4-information_avant[i].mask_1-information_avant[i].mask_2-information_avant[i].mask_3-information_avant[i].mask_4;
        max_mask_arriere=4-information_arriere[i].mask_1-information_arriere[i].mask_2-information_arriere[i].mask_3-information_arriere[i].mask_4;
    }

    list_obstacles.push_back(value_type &&__x)
}


//Creer une interuption si les GP2 activés détectent quelque chose


GP2::~GP2()
{

}
