#ifndef __WORLD_H_
#define __WORLD_H_

#include "asserv.hpp"


#define ROBOT_WIDTH 30
#define ROBOT_LENGTH 30


struct Node{
        short x;
        short y;
        short parentX;
        short parentY;
        float gcost;
        float hcost;
        float fcost;

};

struct shape{
    short width;
    short length;
};

struct obstacle{
    short center_x;
    short center_y;
    struct shape shape;
};


class World{
    public:
        static std::vector<obstacle> fillVector(); //Permet de remplir un vecteur avec la liste des obstacles
        static bool who_here(short x, short y,struct shape shape, std::vector<obstacle> list_obstacles); //Permet de savoir si un obstacle rentre en conflit avec le robot
        static bool isValid(short x, short y,std::vector<obstacle> list_obstacles); //Renvoie faux si la case n'est pas valide
    private:
       
    
};


#endif
