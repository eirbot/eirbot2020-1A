#include "main.hpp"
#include <iostream>

using namespace std;
class Navigation;
class World;

struct Node Phare={30,15,0,0,0,0,0};
struct Node Manche_1={23,185,0,0,0,0,0};
struct Node Manche_2={63,185,0,0,0,0,0};
struct Node Port={15,80,0,0,0,0,0};

int main(int argc, char *argv[]) {
  Navigation src({63,185,0,0,0,0,0}), dest({(short) atoi(argv[1]), (short) atoi(argv[2]),0,0,0,0,0});
  vector<obstacle> list_obstacles = World::fillVector();
  std::vector<Node> result;
  // printf("||| Je pars du Port et je vais au Phare ||| \n");
  result = Navigation::Astar(Port, Phare, list_obstacles);
  if (result.size() != 0) {
    Navigation::Print_path(result);
    Navigation::Navigate_to_asserv(result);
  }
  // printf("||| Je pars du phare et je vais au Manche_1 ||| \n");
  //   result = Navigation::Astar(Phare, Manche_1, list_obstacles);
  //   if (result.size() != 0) {

  //     Navigation::Print_path(result);
  //     Navigation::Navigate_to_asserv(result);
  // }
  // printf("||| Je pars du Manche_1 et je vais au Manche_2 ||| \n");
  // result = Navigation::Astar(Manche_1, Manche_2, list_obstacles);
  // if (result.size() != 0) {
  //   Navigation::Navigate_to_asserv(result);
  // }
  // printf("||| Je pars du Manche_2 et je vais au Port ||| \n");
  // result = Navigation::Astar(Manche_2, Port, list_obstacles);
  // if (result.size() != 0) {
  //   Navigation::Navigate_to_asserv(result);
  // }


    return 0;
}
