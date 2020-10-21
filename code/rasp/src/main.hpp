#ifndef __MAIN__
#define __MAIN__

#include <ctime>
#include <chrono>

#include <unistd.h>
#include "interactions/ecocup.hpp"
#include "robot.hpp"
/**
* @file main.hpp
* @brief Fichier principal pour l'execution de notre projet
* @author SD
*/

void parse_opts(int argc, char *argv[], int *pc, string *side);

/**
* @brief Initialisation des différents éléments
 */
void setup();
/**
* @brief Boucle principale du projet
 */
void loop_blue(std::chrono::steady_clock::time_point BeginMeasurement);

void loop_yellow(std::chrono::steady_clock::time_point BeginMeasurement);


int main(int argc, char *argv[]);


#endif
