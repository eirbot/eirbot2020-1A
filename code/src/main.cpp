#include "main.hpp"
#include <iostream>

using namespace std;
class Navigation;
class World;

int main(int argc, char *argv[]) {
  Navigation src({50, 50,0,0,0,0,0}), dest({(short) atoi(argv[1]), (short) atoi(argv[2]),0,0,0,0,0});
  vector<obstacle> list_obstacles = World::fillVector();
  std::vector<Node> result;
  result = Navigation::Astar(src, dest, list_obstacles);
  if (result.size() != 0) {
    Navigation::Navigate_to_asserv(result);
    }
    return 0;
}
