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
string side = "blue";

//time
float begin_time=0;
float delai=0;
float end=0;

//Définition des points d'interets
struct Node Phare_blue={30,16,0,0,0,0,0};
struct Node Phare_yellow={30,184,0,0,0,0,0};
struct Node Manche_1_blue={23,(184),0,0,0,0,0};
struct Node Manche_2_blue={63,(184),0,0,0,0,0};
struct Node Manche_1_yellow={23,(16),0,0,0,0,0};
struct Node Manche_2_yellow={63,(16),0,0,0,0,0};

struct Node Port={16,(80),0,0,0,0,0};

// Définition des GP2


void port_now(vector<obstacle> list_obstacles)
{
  std::vector<Node> result;
  struct position my_position=Robot.position();
  //TODO : changer 63 et side 184
  struct Node position={(short) 63,(short) 184,0,0,0,0,0};
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
void loop_blue()
{
  Navigation Navigation;
  int temps=0;
  vector<obstacle> list_obstacles = fillVector();
  total_reach=4;
  while ((clock()-begin_time)/CLOCKS_PER_SEC <= 90) {

    auto pos=Robot.position();
    pos.x=16;
    pos.y=80;
    Node pos_node={.x= (short) pos.x,.y= (short) pos.y,0,0,0,0,0};
    //Module Phare
    printf("\033[33mJe pars du PORT et je vais au PHARE \033[0m \n");
    Robot.move(pos_node,Phare_blue,list_obstacles);
    go_to({.x=pos.x-1, .y=pos.y-1}, pos);
    Robot.rotation(-90);
    Robot.actionneur(0,1);
    pos=Robot.position();
    go_to({.x=pos.x+20,.y=pos.y},pos);
    Robot.actionneur(0, 0);

    //Module Manche à air

    printf("\033[33mJe pars de PHARE et je vais à MANCHE_1 \033[0m \n");
    Robot.move(pos_node,Manche_1_blue,list_obstacles);
    Robot.rotation(90);
    Robot.actionneur(1, 1);
    printf("\033[33mJe pars de MANCHE_1 et je vais au MANCHE_2 \033[0m \n");
    pos=Robot.position();
    go_to({.x=pos.x+50,.y=pos.y},pos);
    Robot.actionneur(1, 0);

    //Lecture de la boussole
    printf("\033[33mJe récupère l'information de la boussole \033[0m \n");

    break;
  }
  port_now(list_obstacles);
}

//Boucle de jeu
void loop_yellow()
{
  Navigation Navigation;
  int temps=0;
  vector<obstacle> list_obstacles = fillVector();
  total_reach=4;
  while ((clock()-begin_time)/CLOCKS_PER_SEC <= 90) {

    auto pos=Robot.position();
    pos.x=16;
    pos.y=80;
    Node pos_node={.x= (short) pos.x,.y= (short) pos.y,0,0,0,0,0};
    //Module Phare
    printf("\033[33mJe pars du PORT et je vais au PHARE \033[0m \n");
    Robot.move(pos_node,Phare_yellow,list_obstacles);
    go_to({.x=pos.x-1, .y=pos.y-1}, pos);
    Robot.rotation(-90);
    Robot.actionneur(1,1);
    pos=Robot.position();
    go_to({.x=pos.x+20,.y=pos.y},pos);
    Robot.actionneur(1, 0);

    //Module Manche à air

    printf("\033[33mJe pars de PHARE et je vais à MANCHE_1 \033[0m \n");
    Robot.move(pos_node,Manche_1_yellow,list_obstacles);
    Robot.rotation(90);
    Robot.actionneur(0, 1);
    printf("\033[33mJe pars de MANCHE_1 et je vais au MANCHE_2 \033[0m \n");
    pos=Robot.position();
    go_to({.x=pos.x+50,.y=pos.y},pos);
    Robot.actionneur(0, 0);

    //Lecture de la boussole
    printf("\033[33mJe récupère l'information de la boussole \033[0m \n");

    break;
  }
  port_now(list_obstacles);
}


class Protocole Protocole("/dev/ttyACM0");

int main(int argc, char *argv[]) {
  setup();
  begin_time = clock();
  if (side=="blue") {
    loop_blue();
  }
  else if(side=="yellow") {
    loop_yellow();
  }
  delai=(clock()-begin_time)/CLOCKS_PER_SEC;
  printf("Temps d'execution %f secondes \n",delai);
  return 0;
}
