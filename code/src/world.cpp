#include "world.hpp"

struct shape robot={30,30};
struct shape eco_cup={7,7};
struct shape stone_area={10,100};

std::vector<obstacle> World::fillVector()
{

    std::vector<obstacle> list_obstacles;
    list_obstacles.push_back({100,100,eco_cup});
    return list_obstacles;
}

bool World::who_here(short x, short y, struct shape shape,std::vector<obstacle> list_obstacles)
{
    short l=0;
    short m=0;
    short max_i=x+ROBOT_LENGTH/2+shape.length;
    short max_j=y+ROBOT_WIDTH/2+shape.width;
    if(x-ROBOT_LENGTH/2-shape.length>0){
        l=x-ROBOT_LENGTH/2-shape.length;
    }
    if(max_i>300){
        max_i=300;
    }
    if (y-ROBOT_WIDTH/2-shape.width>0) {
        m=y-ROBOT_WIDTH/2-shape.width;
    }
    if(max_j>200){
        max_j=200;
    }
    for(size_t k=0;k<list_obstacles.size();k++)
    {
        for (int i=l; i < max_i;i++) {
            for (int j=m; j < max_j; j++) {
                if (list_obstacles.operator[](k).center_x ==i &&
                    list_obstacles.operator[](k).center_y ==j &&
                    list_obstacles.operator[](k).shape.width == shape.width &&
                    list_obstacles.operator[](k).shape.length == shape.length){
                    return true;
                }
            }
        }
    }
    return false;
}

bool World::isValid(short x, short y, std::vector<obstacle> list_obstacles)
{
    if(x>270 || x<30 || y>170 || y<30){
        return false;
    }
    bool problem_ec=who_here(x,y,eco_cup,list_obstacles);
    //bool problem_rb=who_here(x,y,robot,list_obstacles);
    if (problem_ec==true) {
        return false;
    }
    return true;
}
