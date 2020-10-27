#ifndef __ASSERV_H_
#define __ASSERV_H_

#include <iostream>
#include <math.h>
#include <array>
#include <cfloat>
#include <stack>

#include  "../affichage.hpp"
#include "world.hpp"
#include "protocole.hpp"
#include "../interactions/detection.hpp"

/**
 * @file asserv.hpp
 * @brief Fichier d'interface avec l'asservissement, permet d'utiliser le protocole de communication pour demander des informations ou envoyer des ordres à la nucléo
 * @author SD
 * */
using namespace std;


extern bool debug;
extern vector<Node> debugPath;
extern class Protocole Protocole;

/**
 * @brief Simple structure permettant de définir une position
 * @param x: La coordonnée x de la postion
 * @param y: La coordonnée y de la position*/
struct position{
    int x;
    int y;
};

/**
 * @brief Permet de transmettre au protocole l'ordre de se déplacer
 * @param dest: la position à atteindre
 * @param src: la position
 * @return Le code d'erreur associé au traitement de l'ordre par le protocole*/
int go_to(struct position dest); //Permet au robot de se tourner vers la destination et d'aller à la destination
/**
 * @brief Permet d'analyser le retour de l'asservissement et d'adopter un comportement en conséquence
 * @param asserv_back: entier de retour de l'asservissement 0: normal 1: timeout 2:detection 3:panique*/
int call_back(int asserv_back); //Permet d'analyser le retour de l'asservissement
/**
 * @brief Permet d'ordonner la rotation du robot
 * @param angle: l'angle en degrés*/
void rotate(short angle); //Permet de faire tourner le robot d'un certain angle (le type de angle est à définir)
/*
** @brief Permet de demander l'information sur la position du robot
** @return Une structure position contenant la position actuelle du robot
*/
struct position robot_position(); //Renvoie la position du robot
/**
 * @brief Permet de demander l'information sur l'angle du robot par rapport à la table
 * @return un short entre 0 et 360° */
short angle(); //Renvoie l'angle du robot par rapport à la table (entre 0 et 360)

#endif
