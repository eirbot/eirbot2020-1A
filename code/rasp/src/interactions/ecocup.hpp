#ifndef __ECOCUP_H_
#define __ECOCUP_H_

#include "ecocup_pdv.hpp"
#include "../robot.hpp"

/**
 * @file ecocup.hpp
 * @brief Fichier codant les techniques utilisées pour ramasser les écocups*/

/**
 * @brief Permet de calculer le chemin le plus court pour ramasser les écocups
 * @param taille: le nombre d'écocups à ramasser
 * @param Robot: le robot*/
void ecocup_road(int taille, Robot Robot);

/**
 * @brief Lit le fichier des eco cups et met dans une matrices les informations utiles
 * @param taille: nombre d'éco cup à ramasser*/
void ecocup_read(int taille);

/**
 * @brief En construction : permet de ramasser une eco cup*/
void ecocup_take();

#endif // __ECOCUP_H_
