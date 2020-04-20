#include "main.hpp"

using namespace std;
class Navigation;
class World;
class Actionneur;
class GP2;

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

short side(short y)
{
    if(which_side==1){
        return Y_MAX-y;
    }
    return y;
}


//Définition des points d'interets
struct Node Phare={30,side(16),0,0,0,0,0};
struct Node Manche_1={23,side(184),0,0,0,0,0};
struct Node Manche_2={63,side(184),0,0,0,0,0};
struct Node Port={16,side(80),0,0,0,0,0};
struct Node Port_N={16,side(40),0,0,0,0,0};
struct Node Port_S={16,side(120),0,0,0,0,0};

// Définition des GP2


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

//Initialisation
void setup()
{
  printf("Début de la phase d'initialisation \n");
  //Initialisation des GP2 et des interuptions
  printf("Je commence la calibration des GP2 \n");
  GP2::activate();
  printf("Systèmes de detection .................................... ");
  print_success();

  //Information sur le côté de la table
  printf("Je récupère l'information du côté de la table \n");

  //Initialisation de la position
  printf("Je commence ma calibration en position \n");
  Asservissement::initialise_x();
  Asservissement::initialise_y();
  printf("Calibration en position .................................. ");
  print_success();

  //Mise du robot au point de départ
  printf("Je me déplace jusqu'au point de départ \n");
  Asservissement::go_to({.x=Port.x,.y=Port.y},Asservissement::robot_position());
  Asservissement::rotate(0);
  printf("Déplacement au point de départ");
  print_success();
  printf("Je suis prêt ! \n");
}

//Boucle de jeu
void loop()
{
  int temps=0;
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

class Protocole Protocole("/dev/ttyS0");

int main(int argc, char *argv[]) {
  setup();
  loop();
  return 0;
}
