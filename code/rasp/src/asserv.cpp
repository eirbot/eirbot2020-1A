#include "asserv.hpp"

//Les printfs seront à modifier pour envoyer directement au protocol de comm.

extern vector<obstacle> list_obstacles;
int Asservissement::go_to(struct position dest)
{
    if(dest.x==38 && dest.y==58){
        return 2;
    }
    if(debug==1){
        debugPath.push_back({.x=(short) dest.x,.y= (short) dest.y,0,0,0,0,0});
    }
    int size=debugPath.size();
    printf("Envoie de la requête de déplacement vers x:%3d ; y:%3d ... ",dest.x,dest.y);
    if(debug==1){
        if(abs(debugPath[size-1].x-debugPath[size-2].x)<3 && abs(debugPath[size-1].y-debugPath[size-2].y)<3){
            print_optimisated();
        }
    }
    affichage(TIMEOUT,DETECTION);
    return Asservissement::call_back(TIMEOUT,DETECTION);
}

int Asservissement::call_back(int timeout, int detection)
{
    if(timeout==1){
        return 1;
    }
    if(detection==1){
        return 2;
    }
    return 0;
}

void Asservissement::rotate(short angle)
{
    printf("Envoie de la requete de rotation de theta:%3d ............ ",angle);
    affichage(TIMEOUT,DETECTION);
}

struct position Asservissement::robot_position()
{
    printf("Envoie de la requete d'information sur la position ....... ");
    affichage(TIMEOUT,DETECTION);
    return {.x=16,.y=80};
}

short Asservissement::angle()
{
    printf("Envoie de la requete d'information sur l'angle ........... ");
    affichage(TIMEOUT,DETECTION);
    return 0; //Pour l'instant
}

void Asservissement::initialise_x()
{
    printf("Envoie de la requete d'initialisation en x ............... ");
    affichage(TIMEOUT,DETECTION);
}

void Asservissement::initialise_y()
{
    printf("Envoie de la requete d'initialisation en y ............... ");
    affichage(TIMEOUT,DETECTION);
}
