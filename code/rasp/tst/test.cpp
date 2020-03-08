#include "test.hpp"
using namespace std;

bool debug=false;
vector<Node> debugPath(2);
int total_optimized;
int unoptimized;
int total_deplacement;
int success_deplacement;
int total_reach;
int success_reach;
int timeout;
int robot_adv;
int timeout_after_timeout;
int which_side=0;

struct Node Phare={30,side(16),0,0,0,0,0};
struct Node Manche_1={23,side(184),0,0,0,0,0};
struct Node Manche_2={63,side(184),0,0,0,0,0};
struct Node Port={16,side(80),0,0,0,0,0};
struct Node Port_N={16,side(40),0,0,0,0,0};
struct Node Port_S={16,side(120),0,0,0,0,0};

short side(short y)
{
  if(which_side==1){
        return (Y_MAX-y);
    }
    return y;
}

void one_step(Node src, Node dest, vector<obstacle> list_obstacles)
{
  std::vector<Node> result;
  int back;
  result = Navigation::Astar(src, dest, list_obstacles);
  if (result.size()!= 0) {
    back=Navigation::Navigate_to_asserv(result,dest,list_obstacles);
    Navigation::back_effect(back,dest,list_obstacles);
    struct position my_position=Asservissement::robot_position();
    good_port(my_position.x, my_position.y, dest.x, dest.y);
    printf("\n");
  }
  else{
    printf("%lu \n",list_obstacles.size());
    list_obstacles=Navigation::stun(list_obstacles);
    printf("%lu \n",list_obstacles.size());
    back=Navigation::Navigate_to_asserv(result,dest,list_obstacles);
    Navigation::back_effect(back,dest,list_obstacles);
    struct position my_position=Asservissement::robot_position();
    good_port(my_position.x, my_position.y, dest.x, dest.y);
    list_obstacles=World::fillVector();
    printf("\n");
  }

}

void test_base()
{
  vector<obstacle> list_obstacles = World::fillVector();
  total_reach=4;
  printf("\033[33mJe pars du PORT et je vais au PHARE \033[0m \n");
  one_step(Port,Phare,list_obstacles);
  Actionneur::Phare_activation();
  Actionneur::Phare_desactivation();
  printf("\033[33mJe pars de PHARE et je vais à MANCHE_1 \033[0m \n");
  one_step(Phare,Manche_1,list_obstacles);
  Actionneur::Phare_activation();
  printf("\033[33mJe pars de MANCHE_1 et je vais au MANCHE_2 \033[0m \n");
  one_step(Manche_1,Manche_2,list_obstacles);
  Actionneur::Phare_desactivation();
  printf("\033[33mJe pars de MANCHE_2 et je vais au PORT \033[0m \n");
  one_step(Manche_2,Port,list_obstacles);
}


class Protocole Protocole("/dev/ttyACM0");

int main(int argc, char *argv[]) {
  if(argv[1]==NULL){
    printf("Les options possibles sont : \n");
    printf("'base ' : permet de tester le calcul du chemin complet de la stratégie \n");
    printf("'debug' : permet d'analyser de manière détaillée une trajectoire libre ou balisée via les mots clés 'Port' 'Phare' 'Manche_1' 'Manche_2' \n");
    return 0;
  }
  if(argc>2){
    if (strcmp(argv[2], "debug") == 0 || strcmp(argv[6], "debug") == 0 ||
        strcmp(argv[4], "debug") == 0) {
      debug = true;
      printf("Je rentre en mode debug \n");
    }
  }
  if(strcmp(argv[1],"base")==0){
    test_base();
    print_summarise();
  }
  return 0;
}
