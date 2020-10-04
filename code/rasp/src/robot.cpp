#include "robot.hpp"


struct shape dimension_robot={32,32};

Robot::Robot():dimension(dimension_robot)
{

}

Robot::~Robot()
{
   
}

void Robot::calibration()
{
    //Initialisation de la position
    printf("Je commence ma calibration en position \n");
    printf("Calibration en position .................................. ");
    initialise_x();
    initialise_y();
    print_success();
}

 void Robot::move(Node src, Node dest, vector<obstacle> list_obstacles)
 {
    Navigation Navigation;
    Navigation.one_step(src,dest,list_obstacles);
}

 void Robot::rotation(short angle) //Permet de faire tourner le robot d'un certain angle (le type de angle est à définir)
 {
     rotate(angle);
 }

struct position Robot::position() //Renvoie la position du robot
{
    return robot_position();
}
short Robot::angle_robot() //Renvoie l'angle du robot par rapport à la table (entre 0 et 360)
{
    return angle();
}


void Robot::detection(char cote, char activation)
{
    if (activation=='1') {
        GP2::activate();
    }
    if (activation=='0') {
        GP2::disactivate();
    }
}

void Robot::actionneur(int cote,int activation)
{
    if (cote==0 && activation==1) {
        Gauche_activation();
    }
    if (cote==0 && activation==0) {
        Gauche_desactivation();
    }
    if (cote==1 && activation==1){
        Droit_activation();
    }
    if (cote==1 && activation==1) {
        Droit_activation();
    }

}

void pavillon(int activation)
{
    if (activation==1) {
        Pavillon();
    }
    if (activation==0){
        Pavillon();
    }
}

 void pince(int activation)
 {
     printf("Pince en cours de développement \n");
 }
