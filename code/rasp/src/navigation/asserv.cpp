#include "asserv.hpp"

//Les printfs seront à modifier pour envoyer directement au protocol de comm.

extern vector<obstacle> list_obstacles;

int go_to(struct position dest)
{
    char etats[3];
    if(debug==1){
        debugPath.push_back({.x=(short) dest.x,.y= (short) dest.y,0,0,0,0,0});
    }
    int size=debugPath.size();
    printf("Envoi de la requête de déplacement vers x:%3d ; y:%3d .... ",dest.x,dest.y);
    int timeout=15;
    int asserv_back=(int) Protocole.set_position((short) dest.x, (short) dest.y, etats,timeout);
    affichage(asserv_back);
    return call_back(asserv_back);
}

int call_back(int asserv_back)
{
    if(asserv_back==1){
        return 1;
    }
    if(asserv_back==2){
        return 2;
    }
    return 0;
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

void initialise_x()
{
    printf("Envoie de la requete d'initialisation en x ............... ");
    affichage(0);
}

void initialise_y()
{
    printf("Envoie de la requete d'initialisation en y ............... ");
    affichage(0);
}
