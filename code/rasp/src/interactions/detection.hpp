#ifndef __DETECTION_H__
#define __DETECTION_H__

#include "../navigation/world.hpp"
#include "../navigation/asserv.hpp"

/**
 * @file detection.hpp
 * @brief Fichier permettant d'interfacer avec les GP2*/

/**
* @class GP2
* @brief Contient les différentes méthodes pour initialiser, activer et désactiver les GP2 et détecter les obstacles
 */

class GP2{

    public:
    GP2();
    /**
    * @brief Active la détection
     */
    static void activate(char side); //Active la detection
    /**
    * @brief Désactive la détection
     */
    static void disactivate(char side); //Désactive la detection
    /**
    * @brief Une intéruption qui s'active lorsque l'un des GP2 activé détecte quelque chose
    * @param[out] list_obstacles: La liste des obstacles en cours, la fonction va la modifier pour ajouter un obstacle si besoin
    * @return Une liste d'obstacle actualisée avec les obstacles que les GP2 détectent
     */
    static void gp2Obstacle(char etats[3], struct position position,struct position dest); //Creer une interuption si les GP2 activés détectent quelque chose
    ~GP2();
   
};

#endif // __DETECTION_H__
