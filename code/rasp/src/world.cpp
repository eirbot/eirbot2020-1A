#include "world.hpp"



struct shape robot={32,32};
struct shape eco_cup={7,7};
struct shape stone_area={2,15};
struct shape stone_area_big={2,30};
std::vector<obstacle> World::fillVector()
{

    std::vector<obstacle> list_obstacles;
    list_obstacles.push_back({30,40,&eco_cup}); //Port nord 1
    list_obstacles.push_back({45,51,&eco_cup}); //45 51
    list_obstacles.push_back({67,10,&eco_cup});
    list_obstacles.push_back({95,40,&eco_cup});
    list_obstacles.push_back({200,40,&eco_cup});
    list_obstacles.push_back({233,10,&eco_cup});
    list_obstacles.push_back({255,51,&eco_cup});
    list_obstacles.push_back({270,40,&eco_cup});
    list_obstacles.push_back({110,80,&eco_cup});
    list_obstacles.push_back({190,80,&eco_cup});
    list_obstacles.push_back({45,108,&eco_cup});
    list_obstacles.push_back({30,120,&eco_cup}); //Port sud 12
    list_obstacles.push_back({127,120,&eco_cup});
    list_obstacles.push_back({173,120,&eco_cup});
    list_obstacles.push_back({255,108,&eco_cup});
    list_obstacles.push_back({270,120,&eco_cup});
    list_obstacles.push_back({106,165,&eco_cup});
    list_obstacles.push_back({133,165,&eco_cup});
    list_obstacles.push_back({166,165,&eco_cup});
    list_obstacles.push_back({193,165,&eco_cup});
    list_obstacles.push_back({100,195,&eco_cup});
    list_obstacles.push_back({139,195,&eco_cup});
    list_obstacles.push_back({160,195,&eco_cup});
    list_obstacles.push_back({199,195,&eco_cup});
    list_obstacles.push_back({89,192,&stone_area});
    list_obstacles.push_back({209,192,&stone_area});
    list_obstacles.push_back({150,185,&stone_area_big});
    return list_obstacles;
}

bool World::who_here(short x, short y, struct shape shape,std::vector<obstacle> list_obstacles)
{
    for(size_t k=0;k<list_obstacles.size();k++)
    {
        short center_x=list_obstacles.operator[](k).center_x;
        short center_y=list_obstacles.operator[](k).center_y;
        short shape_width=list_obstacles.operator[](k).shape->width;
        short shape_length=list_obstacles.operator[](k).shape->length;
        if (x < center_x + shape_length/2 &&
            x + robot.length/2 > center_x &&
            y < center_y + shape_width/2 &&
            robot.width/2 + y > center_y) {
            return true;
        }
    }
    return false;
}

bool World::isValid(short x, short y, std::vector<obstacle> list_obstacles)
{
    if(x>X_MAX-ROBOT_LENGTH/2 || x<ROBOT_LENGTH/2 || y>Y_MAX-ROBOT_WIDTH/2 || y<ROBOT_WIDTH/2){
        return false;
    }
    bool problem_ec=who_here(x,y,eco_cup,list_obstacles);
    bool problem_st=false;
    bool problem_stb=false;
    if((x-ROBOT_LENGTH>ROBOT_LENGTH/2 || x-ROBOT_LENGTH<X_MAX-ROBOT_LENGTH/2) && y-ROBOT_WIDTH <Y_MAX-ROBOT_WIDTH/2){
        problem_st=who_here(x,y,stone_area,list_obstacles);
        problem_stb=who_here(x,y,stone_area_big,list_obstacles);
    }
    if (problem_ec==true || problem_st==true || problem_stb==true) {
        return false;
    }
    return true;
}
