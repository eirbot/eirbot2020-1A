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


void GP2::gp2Obstacle(char etats[3], struct position position, struct position dest)
{
    GP2 GP2;
    //On récupère la valeur de la nucléo
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
    if (calcul_x >= 20 && calcul_y >= 20 && calcul_x <= 150 && calcul_y <= 180) {
        GP2.activate('a');
        go_to({30,100});
        go_to(dest);
        GP2.disactivate('r');
    }
    else{
        go_to(dest);
    }
    }
}


GP2::~GP2()
{

}
