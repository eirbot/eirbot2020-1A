#ifndef __PROTOCOLE_H_
#define __PROTOCOLE_H_

#include <termios.h>
#include <string>
#include "asserv.hpp"

#define READ_BUF_SIZE 32

/**
 * @file protocole.hpp
 * @brief Fichier central du projet, permet de faire la
 * communication entre la raspberry et la nucléo, ce fichier correspond à
 * l'interface côté raspberry
 * @author Ptit Lu*/

/**
 * @class Protocole
 * @brief Contient les méthodes pour envoyer ou obtenir des informations à la nucléo*/
class Protocole
{
        public:
        /**
         * @brief Permet d'initialiser la communication sur le port usb
         * @param device: nom du port usb, l'executable peut nécessité un
         * lancement en super utilisateur pour réussir à accéder au port usb
         * @bug Lors de la première exécution le protocole est mal initialisé,
         * lors de la deuxième éxécution il revient à son état normal*/
        Protocole(std::string device);
        ~Protocole();

        //ERROR c'est grave, si ça arrive c'est la merde
        //-> réception de données erronées
        /**
         * @enum Etat
         * @brief Permet de transmettre à la rasp les possibles erreurs du
         * protocole
         * @param OK: Tout c'est déroulé comme prévu
         * @param TIME_OUT: La nucléo à dépasser le temps qu'il lui était
         * accordé pour répondre
         * @param OBSTACLE: Les GP2 ont détecté un obstacle
         * @param ERROR: Une erreur fatale est survenue*/
        enum class Etat {OK, TIME_OUT, OBSTACLE, ERROR};

        // #################      SET      ###################

        /*
         * set_position
         * entrees:
         *   x et y en cm position absolue
         *   etats tableaux de char TODO: definir signification ou enum
         *   timeout en s
         * sortie:
         *   Etat OK, TIME_OUT, OBSTACLE ou ERROR
         */

        /**
         * @brief Permet de demander un changement de position à l'asservissement
         * @param x: le changement en x
         * @param y: le changement en y
         * @param[out] etats: TODO: définir signification ou enum
         * @param timeout: temps accordé à la nucléo pour répondre à la requette
         * @return Un état nous indiquant le résultat de la requette*/
        enum Etat set_position(short x, short y, char etats[3], int timeout);

        /*
         * set_detection_GP2
         * entrees:
         *   actif '1' = actif et '0' = desactive, /!\ caractère '1', pas 1
         * sortie:
         *   Etat OK, TIME_OUT, ou ERROR
         */
        /**
         * @brief Permet de demander l'activation où la désactivation des GP2
         * @param actif: '1' pour activer '0' pour désactiver /!\ caractère '1'
         * et non 1
         * @return Un état nous indiquant le résultat de la requête*/
        enum Etat set_detection_GP2(char actif);

        /*
         * set_angle
         * entrees:
         *   angle entre 0 et 360 deg
         * sortie:
         *   Etat OK, TIME_OUT, ou ERROR
         */
        /**
         * @brief Permet de demander une rotation du robot
         * @param angle: un angle compris entre 0 et 360°
         * @return Un état nous indiquant le résultat de la requête */
        enum Etat set_angle(short angle);

        /*
         * set_actionneur
         * entrees:
         *   id : identifiant : 0 bras, 1 pavillon
         *   on: 0 off, 1 on
         * sortie:
         *   Etat OK, TIME_OUT, ou ERROR */
         /**
          * @brief Permet de demander le déploiement d'un actionneur
          * @param id: l'actionneur en question 0 pour le bras 1 pour le pavillon
          * @param on: permet de demander l'activation (1) ou la désactivation (0)
          * @return Un état nous indiquant le résultat de la requête*/
        enum Etat set_actionneur(char id, char on);

        // #################      GET      ###################
        /*
         * get_*
         * entrees:
         *   pointeur vers la valeur à maj
         * sortie:
         *   Etat OK, TIME_OUT, ou ERROR
         */
        /**
         * @brief Permet de demander la valeur de l'angle
         * @param[out] angle: pointeur contenant la valeur de l'angle après
         * l'exécution de la fonction
         * @return Un état nous indiquant le résultat de la requête*/
        enum Etat get_angle(short *angle);
        /**
         * @brief Permet de demander la valeur de la position
         * @param[out] pos: pointeur contenant une structure position après
         * l'exécution de la fonction
         * @return Un état nous indiquant le résultat de la requête*/
        enum Etat get_position(struct position *pos);
        /**
         * @brief Permet de demander l'état des GP2
         * @param[out] etats: tableau contenant l'état des GP2 en activité rempli
         * après l'exécution de la fonction
         * @return Un état nous indiquant le résultat de la requête*/
        enum Etat get_etats_GP2(char etats[3]);
        /**
         * @brief Fonction permettant d'afficher le buffer à fin de debug
         */
        void print_buffer(char* buf); //debug

        private:
        int serial_port;
        void update_buffer();
        struct termios tty;
        char writeBuffer[64];
        char readBuffer[READ_BUF_SIZE];
        short GP2_etats[6];

        void send(const char *command, ...);
        int update_buffer(int timeout);
        void flush_buffer();
        void parse();
};

#endif // __PROTOCOLE_H_
