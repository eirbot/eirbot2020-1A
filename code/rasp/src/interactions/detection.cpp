#include "detection.hpp"

extern class Protocole Protocole;

GP2::GP2():input(),activated(),distance_seuil()
{

}

GP2::GP2(enum GP2_name input,int activated,int distance_seuil):input(input),activated(activated),distance_seuil(distance_seuil)
{

}

void GP2::activate()
{
    printf("Envoie de la requète de d'activation des GP2 ............. ");
    int activate_back=(int) Protocole.set_detection_GP2('1');
    affichage(activate_back);
}

void GP2::disactivate()
{
    printf("Envoie de la requète de désactivation des GP2 ............ ");
    int disactivate_back=(int) Protocole.set_detection_GP2('0');
    affichage(disactivate_back);
}


vector<obstacle> GP2::gp2Obstacle(vector<obstacle> list_obstacles, struct position position)
{
    //On récupère la valeur de la nucléo
    char etats[3]={'0','0','0'}; //set:detection() pour récupérer l'information selon le protocole de com
    Protocole.get_etats_GP2(etats);
    if(etats[0]!='0' || etats[1]!='0' || etats[2]!='0'){
    //On trouve maintenant la configuration (gauche, centre gauche, centre, centre droit, droit) et on place le nouvel obstacle
    short position_x=position.x;
    short position_y=position.y;
    short the_angle=angle();

    if (etats[1]=='1' && etats[2]=='1') {
        the_angle+=22;
    }
    else if (etats[0]=='1' && etats[1]=='1') {
        the_angle-=22;
    }
    else if (etats[1]=='1') {
    }
    else if (etats[0]=='1'){
        the_angle-=45;
    }
    else if (etats[2]=='1'){
        the_angle+=45;
    }

    struct shape robot={34,34};
    float calcul_x=position_x+10*cos(the_angle);
    float calcul_y=position_y+10*sin(the_angle);
    list_obstacles.push_back({(short)calcul_x, (short)calcul_y, &robot});
    }
    else {

    }
    return list_obstacles;
}


GP2::~GP2()
{

}
