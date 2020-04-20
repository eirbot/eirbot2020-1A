#ifndef __DETECTION_H__
#define __DETECTION_H__

#include "world.hpp"
#include "asserv.hpp"

/**
 * @file detection.hpp
 * @brief Fichier permettant d'interfacer avec les GP2*/

// Pris sur les anciens dépots a modifier !!!!
// 1.0  -> 6 cm
// 0.4  -> 10 cm
// 0.72 -> 20 cm
// O.19 -> 50 cm

/**
 * @enum GP2_name
 * @brief Contient les noms des 6 GP2
 * @param gauche_avant: GP2 gauche à l'avant
 * @param centre_avant: GP2 central à l'avant
 * @param droite_avant: GP2 droite à l'avant
 * @param gauche_arriere: GP2 gauche à l'arrière
 * @param centre_arriere: GP2 central à l'arrière
 * @param droite_arriere: GP2 droite à l'arrière
 */
enum GP2_name {
  gauche_avant,
  centre_avant,
  droite_avant,
  gauche_arriere,
  centre_arriere,
  droite_arriere,
};

/**
* @struct GP2_information
* @brief J'ai oublié
* @param input: le nom d'un GP2
* @param mask: le mask appliqué à ce GP2
 */
struct GP2_information{
    enum GP2_name input;
    short mask; //Valeur entre 1 et 4
};

/**
* @class GP2
* @brief Contient les différentes méthodes pour initialiser, activer et désactiver les GP2 et détecter les obstacles
 */

class GP2{

    public:
    GP2();
    /**
    * @brief Initialise un GP2
    * @param input: le nom du GP2
    * @param activated: l'état du GP2, 1 activé, 0 désactivé
    * @param distance_seuil: paramètre la distance à laquelle le GP2 doit détecter
     */
    GP2(enum GP2_name input,int activated,int distance_seuil);
    /**
    * @brief Active la détection
     */
    static void activate(); //Active la detection
    /**
    * @brief Désactive la détection
     */
    static void disactivate(); //Désactive la detection
    /**
    * @brief Une intéruption qui s'active lorsque l'un des GP2 activé détecte quelque chose
    * @param[out] list_obstacles: La liste des obstacles en cours, la fonction va la modifier pour ajouter un obstacle si besoin
    * @return Une liste d'obstacle actualisée avec les obstacles que les GP2 détectent
     */
    static vector<obstacle> gp2Obstacle(std::vector<obstacle> list_obstacles, struct position position); //Creer une interuption si les GP2 activés détectent quelque chose
    ~GP2();
  private:
    /**
    * @brief Identifiant du GP2
     */
    enum GP2_name input; //identifiant du GP2
    /**
    * @brief Entier correspondant à l'activation
     */
    int activated; //0 si désactivé 1 sinon
    /**
    * @brief Entier correspondant à la distance de détection
     */
    int distance_seuil;
};

#endif // __DETECTION_H__
