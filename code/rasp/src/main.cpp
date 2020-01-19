#include "main.hpp"

using namespace std;
class Navigation;
class World;
class Actionneur;

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
struct Node Phare={30,side(15),0,0,0,0,0};
struct Node Manche_1={23,side(185),0,0,0,0,0};
struct Node Manche_2={63,side(185),0,0,0,0,0};
struct Node Port={15,side(80),0,0,0,0,0};
struct Node Port_N={15,side(40),0,0,0,0,0};
struct Node Port_S={15,side(120),0,0,0,0,0};

// Définition des GP2
GP2 GP2_1(1,0,50), GP2_2(2,0,50), GP2_3(3,0,50), GP2_4(4,0,50), GP2_5(5,0,50), GP2_6(6,0,50);
Ticker GP2_check(GP2::gp2Obstacle,1000);

//Initialisation
void setup()
{
  printf("Début de la phase d'initialisation \n");
  //Initialisation des GP2 et des interuptions
  printf("Je commence la calibration des GP2 \n");
  GP2_1.activate(); GP2_2.activate(); GP2_3.activate(); //Activation des GP2 avant
  GP2_check.start();
  printf("Systèmes de detection");
  print_success();
  //Information sur le côté de la table
  printf("Je récupère l'information du côté de la table");

  //Initialisation de la position
  printf("Je commence ma calibration en position \n");
  Asservissement::initialise_x();
  Asservissement::initialise_y();
  printf("Calibration en position");
  print_success();

  //Mise du robot au point de départ
  printf("Je me déplace jusqu'au point de départ \n");
  Asservissement::go_to({.x=Port.x,.y=Port.y});
  //Asservissement::rotate(0);
  printf("Je suis prêt !");
}

//Boucle de jeu
void loop()
{
  int temps=0;
  vector<obstacle> list_obstacles = World::fillVector();
  std::vector<Node> result;
  struct position position;
  struct Node my_position;
  //Aller jusqu'au port
  result=Navigation::Astar(Port,Phare,list_obstacles);
  Navigation::Navigate_to_asserv(result,Phare);
  Actionneur::Phare_activation(); //Sort l'actionneur et on avant un peu
  Actionneur::Phare_desactivation(); //On rentre l'actionneur

  //Aller jusqu'au manche à air 1
  position=Asservissement::robot_position();
  //mettre un check de diff entre ma position et la position théorique
  my_position.x=position.x;
  my_position.y=position.y;
  result=Navigation::Astar(my_position,Manche_1,list_obstacles);
  Navigation::Navigate_to_asserv(result,Manche_1);
  Actionneur::Manche_activation(); //Sort l'actionneur quand on est proche du premier manche

  //Aller jusqu'au manche à air 2
  position=Asservissement::robot_position();
  my_position.x=position.x;
  my_position.y=position.y;
  result=Navigation::Astar(my_position,Manche_2,list_obstacles);
  Navigation::Navigate_to_asserv(result,Manche_2);
  Actionneur::Manche_desactivation(); //On rentre l'actioneur après avoir levé les 2 manches à air

  //Rentrer jusqu'au port
  position=Asservissement::robot_position();
  my_position.x=position.x;
  my_position.y=position.y;
  result=Navigation::Astar(my_position,Port,list_obstacles);
  Navigation::Navigate_to_asserv(result, Port_N);
}

int main(int argc, char *argv[]) {
  setup();
  loop();
  return 0;
}
