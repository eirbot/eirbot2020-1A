#include "main.hpp"
#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace std::chrono;

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
bool in_port=false;
int pc=1;
std::chrono::steady_clock::time_point BeginMeasurement;

//Définition des points d'interets
struct Node Phare_blue={20,20,0,0,0,0,0};
struct Node Phare_yellow={20,180,0,0,0,0,0};
struct Node Phare_blue_waypoint={50,45,0,0,0,0,0};
struct Node Phare_yellow_waypoint={50,155,0,0,0,0,0};
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
  Robot.detection('a', '1');

  //Information sur le côté de la table
  printf("Je récupère l'information du côté de la table \n");
  side=Robot.calibration();
  printf("Je suis du côté %c \n",side[0]);

  printf("Je vérifie que mes bras fonctionnent \n");
  Robot.actionneur(0, 1);
  Robot.actionneur(0, 0);
  Robot.actionneur(1, 1);
  Robot.actionneur(1, 0);

  while (Robot.depart()==0) {
      printf("Je suis pret en attente du départ ! \n");
  }
  BeginMeasurement=steady_clock::now();
  struct itimerval timer;
  timer.it_value.tv_sec=95;
  timer.it_value.tv_usec=0;
  timer.it_interval.tv_sec=0;
  timer.it_interval.tv_usec=0;
  setitimer(ITIMER_VIRTUAL, &timer, 0);
}

void timer_handler (int signum)
{
  printf("TIMED OUT ! \n");
  if (in_port==false) {
    if (Robot.communication_phare()==0) {
      go_to({.x=20,.y=50});
    }
    else if(Robot.communication_phare()==1){
      go_to({.x=20,.y=150});
    }
  }
  Robot.pavillon(1);
}

//Boucle de jeu
void loop_blue(std::chrono::steady_clock::time_point BeginMeasurement)
{
  Navigation Navigation;
  int temps=0;
  vector<obstacle> list_obstacles = fillVector();
  go_to({.x=20,.y=80});
  //Module Phare
  printf("\033[33mJe pars du PORT et je vais au WAYPOINT \033[0m \n");
  Node pos_node={.x= (short) 20,.y= (short) 80, 0,0,0,0,0};
  Robot.move(pos_node,Phare_blue_waypoint,list_obstacles);

  printf("\033[33mJe pars du WAYPOINT et je vais au PHARE \033[0m \n");
  Robot.detection('a', '0');
  Robot.move(Phare_blue_waypoint,Phare_blue,list_obstacles);
  Robot.actionneur(0,1);
  go_to({.x=40,.y=20});
  Robot.actionneur(0, 0);
  if (Robot.communication_phare()==false) {
    Robot.actionneur(1, 1);
    go_to({.x=20,.y=20});
    Robot.actionneur(1,0);
  }

  //Module Manche à air
  printf("\033[33mJe pars de PHARE et je vais à MANCHE_1 \033[0m \n");
  Robot.detection('a', '1');
  go_to({.x=70,.y=110 });
  Robot.detection('a', '0');
  go_to({.x=23,.y=178});
  Robot.actionneur(1, 1);
  go_to({.x=53,.y=178});
  Robot.actionneur(0, 1);
  Robot.detection('a', '1');

  printf("\033[33mJe récupère l'information de la boussole \033[0m \n");
  int boussole=Robot.communication_boussole();
  vector<obstacle> list_obstacles_no_ecocup = fillVector_no_ecocup();

  printf("\033[33mJe pars du MANCHE_2 et je vais au PORT %d \033[0m \n",boussole);
  Node position={(short) 53,(short) 184,0,0,0,0,0};
  if (boussole==false) {
    Robot.move(position,Port_S,list_obstacles_no_ecocup);
  }
  else if(boussole==true){
    Robot.move(position,Port_N,list_obstacles_no_ecocup);
  }
  in_port=true;
  auto delai = steady_clock::now() - BeginMeasurement;
  std::cout << "Temps total d'execution " << duration_cast<milliseconds>(delai).count() << " ms" << '\n';
  while (1) {

  }
}

// void loop_yellow(std::chrono::steady_clock::time_point BeginMeasurement)
// {
//   bool in_port=false;
//   Navigation Navigation;
//   int temps=0;
//   vector<obstacle> list_obstacles = fillVector();

//     go_to({.x=20,.y=80});
//     //Module Phare
//     printf("\033[33mJe pars du PORT et je vais au WAYPOINT \033[0m \n");
//     Node pos_node={.x= (short) 20,.y= (short) 80, 0,0,0,0,0};
//     Robot.move(pos_node,Phare_yellow_waypoint,list_obstacles);

//     printf("\033[33mJe pars du WAYPOINT et je vais au PHARE \033[0m \n");
//     Robot.detection('a', '0');
//     Robot.move(Phare_yellow_waypoint,Phare_yellow,list_obstacles);
//     Robot.actionneur(0,1);
//     go_to({.x=40,.y=20});
//     Robot.actionneur(0, 0);

//     if (!Robot.communication()) {
//       printf("\033[34mLe phare n'a pas été activé, je réessaye \033[0m \n");
//       Robot.actionneur(1, 1);
//       go_to({.x=20,.y=20});
//       Robot.actionneur(0, 1);
//       go_to({.x=40,.y=20});
//     }

//     //Module Manche à air
//     printf("\033[33mJe pars de PHARE et je vais à MANCHE_1 \033[0m \n");
//     Robot.detection('a', '1');
//     Robot.move({(short) 40, (short) 20, 0,0,0,0,0},Manche_1_yellow,list_obstacles);
//     Robot.actionneur(1, 1);
//     printf("\033[33mJe pars de MANCHE_1 et je vais au MANCHE_2 \033[0m \n");
//     go_to({.x=53,.y=180});
//     Robot.actionneur(1, 0);
//     Robot.detection('a', '0');

//   //Lecture de la boussole
//   printf("\033[33mJe récupère l'information de la boussole \033[0m \n");
//   int boussole=Robot.communication();
//   vector<obstacle> list_obstacles_no_ecocup = fillVector_no_ecocup();

//   printf("\033[33mJe pars du MANCHE_2 et je vais au PORT %d \033[0m \n",boussole);
//   Node position={(short) 63,(short) 184,0,0,0,0,0};
//   if (Robot.communication()==0) {
//     Robot.move(position,Port_N,list_obstacles_no_ecocup);
//   }
//   else if(Robot.communication()==1){
//     Robot.move(position,Port_S,list_obstacles_no_ecocup);
//   }
//   in_port=true;
//   auto delai = steady_clock::now() - BeginMeasurement;
//   std::cout << "Temps total d'execution " << duration_cast<milliseconds>(delai).count() << " ms" << '\n';




//   if (in_port==false) {
//     if (Robot.communication()==0) {
//       go_to({.x=20,.y=50});
//     }
//     else if(Robot.communication()==1){
//       go_to({.x=20,.y=150});
//     }
//   }
//   Robot.pavillon(1);
//   delai = steady_clock::now() - BeginMeasurement;
//   std::cout << "Temps total d'execution " << duration_cast<milliseconds>(delai).count() << " ms" << '\n';
// }


class Protocole Protocole("/dev/ttyACM0");

int main(int argc, char *argv[]) {

  setup();
  struct sigaction sa;
  memset(&sa,0, sizeof(sa));
  sa.sa_handler = &timer_handler;
  sigaction(SIGVTALRM, &sa,0);
  if (side=="blue") {
    loop_blue(BeginMeasurement);
  }
  else if(side=="yellow") {
    // loop_yellow(BeginMeasurement);
  }


  return 0;
}
