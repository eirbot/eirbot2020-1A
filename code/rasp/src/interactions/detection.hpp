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
    ~GP2();
   
};

#endif // __DETECTION_H__
