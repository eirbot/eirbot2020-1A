#ifndef __ACTIONNEUR_H__
#define __ACTIONNEUR_H__

#include "../navigation/protocole.hpp"

/**
 * @file actionneur.hpp
 * @brief Ce fichier contient la classe permettant de gérer les actionneurs
 * @author SD
 */

/**
 * @brief Contient toutes les méthodes permettant de gérer les actionneurs du robot */
/**
 * @brief Permet de demander au protocole la sortie de l'actionneur
 * @return Rien, à modifier pour la compatibilité avec le protocole
 */
void Gauche_activation(); //Sort l'actionneur et avance un peu pour activer le phare
/**
 * @brief Permet de demander au protocole la rentrée de l'actionneur
 * @return Rien, à modifier pour la compatibilité avec le protocole
 */
void Gauche_desactivation(); //Rentre l'actionneur

/**
 * @brief Contient toutes les méthodes permettant de gérer les actionneurs du robot */
/**
 * @brief Permet de demander au protocole la sortie de l'actionneur
 * @return Rien, à modifier pour la compatibilité avec le protocole
 */
void Droit_activation(); //Sort l'actionneur et avance un peu pour activer le phare
/**
 * @brief Permet de demander au protocole la rentrée de l'actionneur
 * @return Rien, à modifier pour la compatibilité avec le protocole
 */
void Droit_desactivation(); //Rentre l'actionneur


/**
 * @brief Permet de demander au protocole l'activation du pavillon
 * @return Rien, à modifier pour la compatibilité avec le protocole
 */
void Pavillon(); //Sort l'actioneur

#endif
