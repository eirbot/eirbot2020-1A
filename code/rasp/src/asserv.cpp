#include "asserv.hpp"

//Les printfs seront à modifier pour envoyer directement au protocol de comm.

extern vector<obstacle> list_obstacles;

int Asservissement::go_to(struct position dest, struct position src)
{
    char etats[3];
    if(debug==1){
        debugPath.push_back({.x=(short) dest.x,.y= (short) dest.y,0,0,0,0,0});
    }
    int size=debugPath.size();
    printf("Envoi de la requête de déplacement vers x:%3d ; y:%3d ... ",dest.x,dest.y);
    int timeout=sqrt(pow((dest.x/100-src.x/100),2)+pow((dest.y/100-src.y/100),2));
    int asserv_back=(int) Protocole.set_position((short) dest.x, (short) dest.y, etats,timeout+2);
    if(debug==1){
        if(abs(debugPath[size-1].x-debugPath[size-2].x)<3 && abs(debugPath[size-1].y-debugPath[size-2].y)<3){
            print_optimisated();
        }
    }
    affichage(asserv_back);
    return Asservissement::call_back(asserv_back);
}

int Asservissement::call_back(int asserv_back)
{
    if(asserv_back==1){
        return 1;
    }
    if(asserv_back==2){
        return 2;
    }
    return 0;
}

void Asservissement::rotate(short angle)
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

struct position Asservissement::robot_position()
{
    struct position my_position;
    int position_back=(int) Protocole.get_position(&my_position);
    printf("Envoie de la requete d'information sur la position ....... ");
    affichage(position_back);
    return my_position;
}

short Asservissement::angle()
{
    short angle;
    int angle_back=(int) Protocole.get_angle(&angle);
    printf("Envoie de la requete d'information sur l'angle ........... ");
    affichage(angle_back);
    return angle; //Pour l'instant
}

void Asservissement::initialise_x()
{
    printf("Envoie de la requete d'initialisation en x ............... ");
    affichage(0);
}

void Asservissement::initialise_y()
{
    printf("Envoie de la requete d'initialisation en y ............... ");
    affichage(0);
}
