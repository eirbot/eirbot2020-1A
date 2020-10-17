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
int success_reach;
int total_reach;
int timeout;
int robot_adv;
int timeout_after_timeout;
string side = "blue";

//time
float begin_time=0;
float delai=0;
float end=0;

//Définition des points d'interets
struct Node Phare_blue={20,20,0,0,0,0,0};
struct Node Phare_yellow={20,180,0,0,0,0,0};
struct Node Phare_blue_waypoint={50,45,0,0,0};
struct Node Manche_1_blue={23,(180),0,0,0,0,0};
struct Node Manche_2_blue={63,(180),0,0,0,0,0};
struct Node Manche_1_yellow={23,(20),0,0,0,0,0};
struct Node Manche_2_yellow={63,(20),0,0,0,0,0};

struct Node Port={20,(80),0,0,0,0,0};
struct Node Port_N={20,50,0,0,0,0,0};
struct Node Port_S={20,150,0,0,0,0,0};

// Définition des GP2


//Initialisation
void setup()
{
  printf("Je commence la calibration des GP2 \n");
  printf("Systèmes de detection .................................... ");
  print_success();
  Robot.detection('a', '1');

  //Information sur le côté de la table
  printf("Je récupère l'information du côté de la table \n");
  side="blue";
  Robot.calibration();

  //Mise du robot au point de départ
  printf("Je me déplace jusqu'au point de départ \n");
  go_to({.x=Port.x,.y=Port.y});
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

    go_to({.x=20,.y=80});
    //Module Phare
    printf("\033[33mJe pars du PORT et je vais au WAYPOINT \033[0m \n");
    Node pos_node={.x= (short) 20,.y= (short) 80, 0,0,0,0,0};
    Robot.move(pos_node,Phare_blue_waypoint,list_obstacles);

    printf("\033[33mJe pars du WAYPOINT et je vais au PHARE \033[0m \n");
    Robot.move(Phare_blue_waypoint,Phare_blue,list_obstacles);
    Robot.actionneur(0,1);
    go_to({.x=40,.y=20});
    Robot.actionneur(0, 0);
    if (!Robot.communication()) {
      printf("\033[34mLe phare n'a pas été activé, je réessaye \033[0m \n");
      Robot.actionneur(1, 1);
      go_to({.x=20,.y=20});
      Robot.actionneur(0, 1);
      go_to({.x=40,.y=20});
    }

    //Module Manche à air
    pos_node={.x= (short) 40,.y= (short) 20, 0,0,0,0,0};
    printf("\033[33mJe pars de PHARE et je vais à MANCHE_1 \033[0m \n");
    Robot.move(pos_node,Manche_1_blue,list_obstacles);
    Robot.actionneur(1, 1);
    printf("\033[33mJe pars de MANCHE_1 et je vais au MANCHE_2 \033[0m \n");
    go_to({.x=53,.y=180});
    Robot.actionneur(1, 0);
    break;
  }
  //Lecture de la boussole
  printf("\033[33mJe récupère l'information de la boussole \033[0m \n");
  int boussole=Robot.communication();
  vector<obstacle> list_obstacles_no_ecocup = fillVector_no_ecocup();

  printf("\033[33mJe pars du MANCHE_2 et je vais au PORT %d \033[0m \n",boussole);
  Node position={(short) 63,(short) 184,0,0,0,0,0};
  if (!Robot.communication()) {
    Robot.move(position,Port_N,list_obstacles_no_ecocup);
  }
  else if(Robot.communication()){
    Robot.move(position,Port_S,list_obstacles_no_ecocup);
  }
}

// //Boucle de jeu
// void loop_yellow()
// {
//   Navigation Navigation;
//   int temps=0;
//   vector<obstacle> list_obstacles = fillVector();
//   total_reach=4;
//   while ((clock()-begin_time)/CLOCKS_PER_SEC <= 90) {

//     auto pos=Robot.position();
//     pos.x=16;
//     pos.y=80;
//     Node pos_node={.x= (short) pos.x,.y= (short) pos.y,0,0,0,0,0};
//     //Module Phare
//     printf("\033[33mJe pars du PORT et je vais au PHARE \033[0m \n");
//     Robot.move(pos_node,Phare_yellow,list_obstacles);
//     go_to({.x=pos.x-1, .y=pos.y-1}, pos);
//     Robot.rotation(-90);
//     Robot.actionneur(1,1);
//     pos=Robot.position();
//     go_to({.x=pos.x+20,.y=pos.y},pos);
//     Robot.actionneur(1, 0);

//     //Module Manche à air

//     printf("\033[33mJe pars de PHARE et je vais à MANCHE_1 \033[0m \n");
//     Robot.move(pos_node,Manche_1_yellow,list_obstacles);
//     Robot.rotation(90);
//     Robot.actionneur(0, 1);
//     printf("\033[33mJe pars de MANCHE_1 et je vais au MANCHE_2 \033[0m \n");
//     pos=Robot.position();
//     go_to({.x=pos.x+50,.y=pos.y},pos);
//     Robot.actionneur(0, 0);

//     //Lecture de la boussole
//     printf("\033[33mJe récupère l'information de la boussole \033[0m \n");

//     break;
//   }
//   port_now(list_obstacles);
// }


class Protocole Protocole("/dev/ttyACM0");

int main(int argc, char *argv[]) {
  // setup();
  begin_time = clock();
  if (side=="blue") {
    loop_blue();
  }
  // else if(side=="yellow") {
  //   loop_yellow();
  // }
  delai=(clock()-begin_time)/CLOCKS_PER_SEC;
  printf("Temps d'execution \033[32m%f\033[0m secondes \n",delai);
  return 0;
}
