#include "asserv.hpp"

//Les printfs seront à modifier pour envoyer directement au protocol de comm.

extern vector<obstacle> list_obstacles;

int go_to(struct position dest)
{
    GP2 GP2;
    char etats[3];
    if(debug==1){
        debugPath.push_back({.x=(short) dest.x,.y= (short) dest.y,0,0,0,0,0});
    }
    int size=debugPath.size();
    printf("Envoi de la requête de déplacement vers x:%3d ; y:%3d .... ",dest.x,dest.y);
    int timeout=40;
    int asserv_back=(int) Protocole.set_position((short) dest.x, (short) dest.y, etats,timeout);
    affichage(asserv_back);
    if (asserv_back==1) {
        go_to({dest.x,dest.y});
    }
    else if (asserv_back==2) {
        GP2.disactivate('a');
        go_to({30,100});
        GP2.activate('a');
        go_to(dest);
    }
    return asserv_back;
}

void rotate(short angle)
{
    printf("Envoie de la requete de rotation de theta:%3d ............ ",angle);
    int rotate_back=(int) Protocole.set_angle(angle);
    if(rotate_back==1){
        print_timeout();
    }
    if(rotate_back==2){
        print_detection();
    }
    affichage(rotate_back);
}

struct position robot_position()
{
    struct position my_position;
    int position_back=(int) Protocole.get_position(&my_position);
    printf("Envoie de la requete d'information sur la position ....... ");
    affichage(position_back);
    return my_position;
}

short angle()
{
    short angle;
    int angle_back=(int) Protocole.get_angle(&angle);
    printf("Envoie de la requete d'information sur l'angle ........... ");
    affichage(angle_back);
    return angle; //Pour l'instant
}
