#include "test.hpp"
using namespace std;

int which_side=0;

short side(short y)
{
    if(which_side==1){
        return Y_MAX-y;
    }
    return y;
}

struct Node Phare={30,side(15),0,0,0,0,0};
struct Node Manche_1={23,side(185),0,0,0,0,0};
struct Node Manche_2={63,side(185),0,0,0,0,0};
struct Node Port={15,side(80),0,0,0,0,0};
int main(int argc, char *argv[]) {
  //Navigation src({63,185,0,0,0,0,0}), dest({(short) atoi(argv[1]), (short) atoi(argv[2]),0,0,0,0,0});
  vector<obstacle> list_obstacles = World::fillVector();

  std::vector<Node> result;
   printf("||| Je pars du Port et je vais au Phare ||| \n");
  result = Navigation::Astar(Port, Phare, list_obstacles);
  if (result.size() != 0) {
    Navigation::Navigate_to_asserv(result,Phare);
    printf("Je suis au Phare ! \n");

  }
  printf("||| Je pars du phare et je vais au Manche_1 ||| \n");
    result = Navigation::Astar(Phare, Manche_1, list_obstacles);
    if (result.size() != 0) {
      Navigation::Navigate_to_asserv(result,Manche_1);
      printf("Je suis au Manche_1 ! \n");
  }
  printf("||| Je pars du Manche_1 et je vais au Manche_2 ||| \n");
  result = Navigation::Astar(Manche_1, Manche_2, list_obstacles);
  if (result.size() != 0) {
    Navigation::Navigate_to_asserv(result,Manche_2);
    printf("Je suis au Manche_2 ! \n");

  }
  printf("||| Je pars du Manche_2 et je vais au Port ||| \n");
  result = Navigation::Astar(Manche_2, Port, list_obstacles);
  if (result.size() != 0) {
    //Navigation::Print_path(result);
    Navigation::Navigate_to_asserv(result,Port);
    printf("Je suis au Port ! \n");
      }


    return 0;
}
