#ifndef __MAIN__
#define __MAIN__

#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <array>
#include <cfloat>

#include "affichage.hpp"
#include "navigation.hpp"
#include "world.hpp"
#include "asserv.hpp"
#include "detection.hpp"
#include "actionneur.hpp"

/**
* @file main.hpp
* @brief Fichier principal pour l'execution de notre projet
* @author SD
*/

/**
* @brief Initialisation des différents éléments
 */
void setup();
/**
* @brief Boucle principale du projet
 */
void loop();
int main(int argc, char *argv[]);


#endif
