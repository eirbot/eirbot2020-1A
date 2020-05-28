#ifndef __ROBOT_H_
#define __ROBOT_H_

#include "navigation/navigation.hpp"
#include "interactions/actionneur.hpp"
using namespace std;

/**
 * @file robot.hpp*/

/**
 * @class Robot
 * @brief Contient toutes les méthodes et les attributs du robot*/
class Robot{
    public:
        Robot();
        Robot(shape dimension);
        ~Robot();

        /**
         * @brief Taille du robot*/
        const struct shape dimension; //Largeur et longueur du robot
        /**
         * @brief Calibre en x et en y le robot */
        void calibration();
        /**
         * @brief Déplace le robot en utilisant l'Astar
         * @param src : début
         * @param dest : fin
         * @param list_obstacles : les obstacles à considérer */
        void move(Node src, Node dest, vector<obstacle> list_obstacles);
        /**
         * @brief Fait une rotation du robot
         * @param angle: angle à tourner */
        void rotation(short angle); //Permet de faire tourner le robot d'un certain angle (le type de angle est à définir)
        /**
         * @brief Demande la position du robot*/
        struct position position(); //Renvoie la position du robot
        /**
         * @brief Demande l'angle du robot par rapport à la table */
        short angle(); //Renvoie l'angle du robot par rapport à la table (entre 0 et 360)
        /**
         * @brief Active ou désactive la détection
         * @param cote: cote d'activation (avant / arrière)
         * @param activation: activer (1), désactiver (0)*/
        void detection(char cote, char activation);
        /**
         * @brief Sort ou rentre un actionneur
         * @param side: cote de l'actionneur à sortir
         * @param activation: activer ou désactiver l'actionneur*/
        void actionneur(int side,int activation);
        /**
         * @brief Active le pavillon*/
        void pavillon(int activation);
        /**
         * @brief En cours de construction*/
        void pince(int activation);
};

#endif // __ROBOT_H_
