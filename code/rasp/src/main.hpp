#ifndef __MAIN__
#define __MAIN__

#include "actionneur.hpp"
#include "navigation.hpp"

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

/**
 * @brief Permet de réaliser une étape c'est à dire un déplacement d'un point principal à un autre point principal
 * @param src: le point de départ
 * @param dest: le point d'arrivée
 * @param list_obstacles: les obstacles sur le chemin*/
void one_step(Node src, Node dest, vector<obstacle> list_obstacles);


int main(int argc, char *argv[]);


#endif
