#include "asserv.hpp"

//Les printfs seront à modifier pour envoyer directement au protocol de comm.

void Asservissement::go_to(struct position dest)
{
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
    affichage(TIMEOUT);
    if(debug==1){

    }
}


void Asservissement::rotate(short angle)
{
    printf("Envoie de la requete de rotation de theta:%d",angle);
    affichage(TIMEOUT);
}
