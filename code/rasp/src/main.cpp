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

//Initialisation
void setup()
{
  printf("Début de la phase d'initialisation \n");
  //Initialisation des GP2 et des interuptions
  printf("Je commence la calibration des GP2 \n");

  printf("Les systèmes de detection sont opérationnels \n");

  //Information sur le côté de la table
  printf("Je récupère l'information du côté de la table");

  //Initialisation de la position
  printf("Je commence ma calibration en position \n");
  //Asservissement::initialise_x();
  //Asservissement::initialise_y();
  printf("La calibration en position est réussie \n");

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
  Navigation::Navigate_to_asserv(result);
  Actionneur::Phare_activation(); //Sort l'actionneur et on avant un peu
  Actionneur::Phare_desactivation(); //On rentre l'actionneur

  //Aller jusqu'au manche à air 1
  position=Asservissement::robot_position();
  //mettre un check de diff entre ma position et la position théorique
  my_position.x=position.x;
  my_position.y=position.y;
  result=Navigation::Astar(my_position,Manche_1,list_obstacles);
  Navigation::Navigate_to_asserv(result);
  Actionneur::Manche_activation(); //Sort l'actionneur quand on est proche du premier manche

  //Aller jusqu'au manche à air 2
  position=Asservissement::robot_position();
  my_position.x=position.x;
  my_position.y=position.y;
  result=Navigation::Astar(my_position,Port,list_obstacles);
  Navigation::Navigate_to_asserv(result);
  Actionneur::Manche_desactivation(); //On rentre l'actioneur après avoir levé les 2 manches à air
  position=Asservissement::robot_position();
  //Faudra faire un choix levé de drapeau par intéruption ou à la fin du jeu ?
}

int main(int argc, char *argv[]) {
  setup();
  loop();
  return 0;
}
