#include "asserv.hpp"

//Les printfs seront à modifier pour envoyer directement au protocol de comm.

extern vector<obstacle> list_obstacles;

int Asservissement::go_to(struct position dest)
{
    char etats[3];
    if(dest.x==42 && dest.y==55){
        return 2;
    }
    if(debug==1){
        debugPath.push_back({.x=(short) dest.x,.y= (short) dest.y,0,0,0,0,0});
    }
    int size=debugPath.size();
    printf("Envoie de la requête de déplacement vers x:%3d ; y:%3d ... ",dest.x,dest.y);
    int asserv_back=(int) Protocole.set_position((short) dest.x, (short) dest.y, etats,3);
    if(debug==1){
        if(abs(debugPath[size-1].x-debugPath[size-2].x)<3 && abs(debugPath[size-1].y-debugPath[size-2].y)<3){
            print_optimisated();
        }
    }
    //affichage(asserv_back);
    return Asservissement::call_back(asserv_back);
}

int Asservissement::call_back(int asserv_back)
{
    if(asserv_back==2){
        return 1;
    }
    if(asserv_back==3){
        return 2;
    }
    return 0;
}

void Asservissement::rotate(short angle)
{
    printf("Envoie de la requete de rotation de theta:%3d ............ ",angle);
    affichage(1);
}

struct position Asservissement::robot_position()
{
    printf("Envoie de la requete d'information sur la position ....... ");
    affichage(1);
    return {.x=43,.y=55};
}

short Asservissement::angle()
{
    printf("Envoie de la requete d'information sur l'angle ........... ");
    affichage(1);
    return 0; //Pour l'instant
}

void Asservissement::initialise_x()
{
    printf("Envoie de la requete d'initialisation en x ............... ");
    affichage(1);
}

void Asservissement::initialise_y()
{
    printf("Envoie de la requete d'initialisation en y ............... ");
    affichage(1);
}
