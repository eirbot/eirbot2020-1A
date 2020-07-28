#include "main.hpp"

#include <time.h>

#include <unistd.h>

using namespace std;
class Navigation;
class GP2;
class Robot Robot;

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

//time
float begin_time=0;
float delai=0;
float end=0;

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


void port_now(vector<obstacle> list_obstacles)
{
  std::vector<Node> result;
  struct position my_position=Robot.position();
  //TODO : changer 63 et side 184
  struct Node position={(short) 63,(short) side(184),0,0,0,0,0};
  Robot.move(position,Port,list_obstacles);
}

//Initialisation
void setup()
{
  printf("Je commence la calibration des GP2 \n");
  printf("Systèmes de detection .................................... ");
  print_success();
  Robot.detection('a', '1');

  //Information sur le côté de la table
  printf("Je récupère l'information du côté de la table \n");

  Robot.calibration();

  //Mise du robot au point de départ
  printf("Je me déplace jusqu'au point de départ \n");
  go_to({.x=Port.x,.y=Port.y},robot_position());
  Robot.rotation(0);
  printf("Déplacement au point de départ");
  print_success();
}

//Boucle de jeu
void loop()
{
  Navigation Navigation;
  int temps=0;
  vector<obstacle> list_obstacles = fillVector();
  total_reach=4;
  while ((clock()-begin_time)/CLOCKS_PER_SEC <= 90) {

    //Module Phare
    printf("\033[33mJe pars du PORT et je vais au PHARE \033[0m \n");
    Robot.move(Port,Phare,list_obstacles);
    Robot.actionneur(which_side, 1);
    Robot.actionneur(which_side, 0);
    //Module Manche à aire
    printf("\033[33mJe pars de PHARE et je vais à MANCHE_1 \033[0m \n");
    Robot.move(Phare,Manche_1,list_obstacles);
    Robot.actionneur(which_side, 1);
    printf("\033[33mJe pars de MANCHE_1 et je vais au MANCHE_2 \033[0m \n");
    Robot.move(Manche_1,Manche_2,list_obstacles);
    Robot.actionneur(which_side, 0);

    //Module eco cup
    // printf("\033[33mJe commence le ramassage des écocups \033[0m \n");
    // ecocup_road(8, Robot);
    break;
  }
  port_now(list_obstacles);
}

class Protocole Protocole("/dev/ttyACM0");

int main(int argc, char *argv[]) {
  setup();
  begin_time = clock();
  loop();
  delai=(clock()-begin_time)/CLOCKS_PER_SEC;
  printf("Temps d'execution %f secondes \n",delai);
  return 0;
}
