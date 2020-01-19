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


//Gère le coté de la table
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
  printf("Je récupère l'information du côté de la table");

  //Initialisation de la position
  printf("Je commence ma calibration en position \n");
  Asservissement::initialise_x();
  Asservissement::initialise_y();
  printf("Calibration en position .................................. ");
  print_success();

  //Mise du robot au point de départ
  printf("Je me déplace jusqu'au point de départ \n");
  Asservissement::go_to({.x=Port.x,.y=Port.y});
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
  std::vector<Node> result;
  struct position position;
  struct Node my_position;

  //Aller jusqu'au phare
  result=Navigation::Astar(Port,Phare,list_obstacles);
  Navigation::Navigate_to_asserv(result,Phare);
  //Actionneur::Phare_activation(); //Sort l'actionneur et on avance un peu
  //Actionneur::Phare_desactivation(); //On rentre l'actionneur

  //Aller jusqu'au manche à air 1
  position=Asservissement::robot_position();
  my_position.x=Phare.x;//position.x;
  my_position.y=Phare.y;//position.y;
  result=Navigation::Astar(my_position,Manche_1,list_obstacles);
  Navigation::Navigate_to_asserv(result,Manche_1);
  //Actionneur::Manche_activation(); //Sort l'actionneur quand on est proche du premier manche

  //Aller jusqu'au manche à air 2
  position=Asservissement::robot_position();
  my_position.x=Manche_1.x;//position.x;
  my_position.y=Manche_1.y;//position.y;
  result=Navigation::Astar(my_position,Manche_2,list_obstacles);
  Navigation::Navigate_to_asserv(result,Manche_2);
  //Actionneur::Manche_desactivation(); //On rentre l'actioneur après avoir levé les 2 manches à air

  //Rentrer jusqu'au port
  position=Asservissement::robot_position();
  my_position.x=Manche_2.x;//position.x;
  my_position.y=Manche_2.y;//position.y;
  list_obstacles.erase(list_obstacles.begin());
  result=Navigation::Astar(my_position,Port_N,list_obstacles);
  //Penser à récupérer l'information du port d'arrivée
  Navigation::Navigate_to_asserv(result, Port_N);
}

int main(int argc, char *argv[]) {
  setup();
  loop();
  return 0;
}
