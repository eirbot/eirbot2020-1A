#include "robot.hpp"
#include <stdlib.h>

struct shape dimension_robot={32,32};

extern int pc;

LowLevel LowLevel;

Robot::Robot():dimension(dimension_robot)
{
}

Robot::~Robot()
{
   
}

string Robot::calibration()
{
    if (pc==0) {
        if(LowLevel.is_equipe_bleu()==0){
            return "blue";
        }
        else{
            return "yellow";
        }
    }
    else{
        return "blue";
    }
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
    Actionneur Actionneur;
    if (cote==0 && activation==1) {
        Actionneur.Gauche_activation();
    }
    if (cote==0 && activation==0) {
        Actionneur.Gauche_desactivation();
    }
    if (cote==1 && activation==1){
        Actionneur.Droit_activation();
    }
    if (cote==1 && activation==0) {
        Actionneur.Droit_desactivation();
    }

}

void Robot::pavillon(int activation)
{
    Actionneur Actionneur;
    if (activation==1) {
        Actionneur.Pavillon();
    }
    if (activation==0){
        Actionneur.Pavillon();
    }
}

int Robot::communication_phare()
{
    if (!pc) {
        return LowLevel.phare_active();
    }
    else{
        return 1;
    }
}

int Robot::communication_boussole()
{
    if (!pc) {
        return LowLevel.boussole_nord();
    }
    else{
        return 0;
    }
}

 void pince(int activation)
 {
     printf("Pince en cours de développement \n");
 }

int Robot::depart()
{
    if(!pc){
        return LowLevel.is_depart();
    }
    else{
        return 1;
    }
}
