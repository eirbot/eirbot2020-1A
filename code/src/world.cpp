#include "world.hpp"

struct shape robot={30,30};
struct shape eco_cup={7,7};
struct shape stone_area={10,100};

std::vector<obstacle> World::fillVector()
{

    std::vector<obstacle> list_obstacles;
    //list_obstacles.push_back({30,40,eco_cup});
    //list_obstacles.push_back({45,51,eco_cup}); //45 51
    //list_obstacles.push_back({67,10,eco_cup});
     //list_obstacles.push_back({95,40,eco_cup});
     list_obstacles.push_back({200,40,eco_cup});
     list_obstacles.push_back({233,10,eco_cup});
     list_obstacles.push_back({255,51,eco_cup});
    list_obstacles.push_back({270,40,eco_cup});
     list_obstacles.push_back({110,80,eco_cup});
    list_obstacles.push_back({190,80,eco_cup});
    list_obstacles.push_back({45,108,eco_cup});
    list_obstacles.push_back({30,120,eco_cup});
    list_obstacles.push_back({127,120,eco_cup});
    list_obstacles.push_back({173,120,eco_cup});
    list_obstacles.push_back({255,108,eco_cup});
    list_obstacles.push_back({270,120,eco_cup});
    list_obstacles.push_back({106,165,eco_cup});
    list_obstacles.push_back({133,165,eco_cup});
    list_obstacles.push_back({166,165,eco_cup});
    list_obstacles.push_back({193,165,eco_cup});
    list_obstacles.push_back({100,195,eco_cup});
    list_obstacles.push_back({139,195,eco_cup});
    list_obstacles.push_back({160,195,eco_cup});
    list_obstacles.push_back({199,195,eco_cup});
    return list_obstacles;
}

bool World::who_here(short x, short y, struct shape shape,std::vector<obstacle> list_obstacles)
{
    // short l=0;
    // short m=0;
    // short max_i=x+ROBOT_LENGTH/2+shape.length;
    // short max_j=y+ROBOT_WIDTH/2+shape.width;
    // if(x-ROBOT_LENGTH/2-shape.length>0){
    //     l=x-ROBOT_LENGTH/2-shape.length;
    // }
    // if(max_i>300){
    //     max_i=300;
    // }
    // if (y-ROBOT_WIDTH/2-shape.width>0) {
    //     m=y-ROBOT_WIDTH/2-shape.width;
    // }
    // if(max_j>200){
    //     max_j=200;
    // }
    for(size_t k=0;k<list_obstacles.size();k++)
    {
        short center_x=list_obstacles.operator[](k).center_x;
        short center_y=list_obstacles.operator[](k).center_y;
        short shape_width=list_obstacles.operator[](k).shape.width;
        short shape_length=list_obstacles.operator[](k).shape.length;
        if (x < center_x + shape_length/2 &&
            x + robot.length/2 > center_x &&
            y < center_y + shape_width/2 &&
            robot.width/2 + y > center_y) {
            return true;
        }
       // for (int i=l; i < max_i;i++) {
       //     for (int j=m; j < max_j; j++) {
       //         if (list_obstacles.operator[](k).center_x ==i &&
       //             list_obstacles.operator[](k).center_y ==j //&&
       //             //list_obstacles.operator[](k).shape.width == shape.width &&
       //             /*list_obstacles.operator[](k).shape.length == shape.length*/){
       //             return true;
       //         }
       //     }
       // }
    }
    return false;
}

bool World::isValid(short x, short y, std::vector<obstacle> list_obstacles)
{
    if(x>285 || x<15 || y>185 || y<15){
        return false;
    }
    bool problem_ec=who_here(x,y,eco_cup,list_obstacles);
    //bool problem_rb=who_here(x,y,robot,list_obstacles);
    if (problem_ec==true) {
        return false;
    }
    return true;
}
