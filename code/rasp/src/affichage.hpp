#ifndef __AFFICHAGE_H_
#define __AFFICHAGE_H_

#include <cstdio>
#include "detection.hpp"
#include "world.hpp"
#include "navigation.hpp"
#include "protocole.hpp"

/**
 * @file affichage.hpp
 * @brief Ce fichier sert uniquement à réaliser un affichage correcte lors de l'éxecution
 * @authro SD
 */

#ifndef TIMEOUT
#define TIMEOUT 0
#endif

#ifndef DETECTION
#define DETECTION 0
#endif

extern bool debug;

/**
 * @brief Permet d'afficher TIMEOUT en rouge
 */
void print_timeout();

/**
 * @brief Permet d'afficher SUCCESS en vert
 */
void print_success();

/**
 * @brief Permet d'afficher FAILED en rouge
 */
void print_fail();

/**
 * @brief Permet d'afficher DETECTION en orange
 */
void print_detection();

/**
 * @brief Permet d'afficher timeout/success/fail en fonction du retour du
 * protocole de communication
 * @param asserv_back: un entier correspondant au retour du prototocole, 1 pour
 * timeout, 2 pour détection, 3 pour problème majeur et 0 en cas normal
 */
void affichage(int asserv_back);

/**
 * @brief Permet de savoir si le point actuel du robot est le point prévu
 * @param result_x La coordonnée x du robot
 * @param result_y La coordonnée y du robot
 * @param dest_x La coordonnée x à comparer avec result_x
 * @param dest_y La coordonnée y à comparer avec result_y */
void good_port(short result_x, short result_y, short dest_x, short dest_y);

/**
 * @brief Permet d'afficher UNOPTIMIZED en orange*/
void print_optimisated();

/**
 * @brief Permet d'afficher un résumé d'une éxecution. Permet d'afficher le nombre de succès, de timeout, d'échec et de fois où le robot
 * est arrivé au point attendu. Si la variable debug est à 1 cela affiche aussi
 * le nombre de trajectoires non optimisée*/
void print_summarise();

#endif // __AFFICHAGE_H_
