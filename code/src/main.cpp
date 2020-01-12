#include "main.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    Node src;
    src.x=50;
    src.y=50;
    Node dest;
    dest.x=atoi(argv[1]);
    dest.y=atoi(argv[2]);
    vector <obstacle> list_obstacles=World::fillVector();
    std::vector<Node> result;
    result=Navigation::Astar(src,dest,list_obstacles);
    if(result.size()!=0){
        Navigation::Navigate_to_asserv(result);
    }
    return 0;
}
