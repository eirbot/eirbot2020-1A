#include "main.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    Node src;
    src.x=0;
    src.y=0;
    Node dest;
    dest.x=atoi(argv[1]);
    dest.y=atoi(argv[2]);
    std::vector<Node> result;
    result=Navigation::Astar(src,dest);

    return 0;
}
