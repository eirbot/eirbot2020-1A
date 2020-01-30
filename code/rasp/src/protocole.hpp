#ifndef __PROTOCOLE_H_
#define __PROTOCOLE_H_

#include <stdio.h>
#include <termios.h>
#include <vector>
#include <string>
#include "asserv.hpp"

#define READ_BUF_SIZE 32


class Protocole
{
    public:
        Protocole(std::string device);
        ~Protocole();

        //ERROR c'est grave, si ça arrive c'est la merde
        //-> réception de données erronées
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
        enum Etat set_position(short x, short y, char etats[3], int timeout);

        /*
         * set_detection_GP2
         * entrees:
         *   actif '1' = actif et '0' = desactive, /!\ caractère '1', pas 1
         * sortie:
         *   Etat OK, TIME_OUT, ou ERROR
         */
        enum Etat set_detection_GP2(char actif);

        /*
         * set_angle
         * entrees:
         *   angle entre 0 et 360 deg
         * sortie:
         *   Etat OK, TIME_OUT, ou ERROR
         */
        enum Etat set_angle(short angle);

        // #################      GET      ###################
        /*
         * get_*
         * entrees:
         *   pointeur vers la valeur à maj
         * sortie:
         *   Etat OK, TIME_OUT, ou ERROR
         */
        enum Etat get_angle(short *angle);
        enum Etat get_position(struct position *pos);
        enum Etat get_etats_GP2(char etats[3]);

    private:
        int serial_port;
        void update_buffer();
        struct termios tty;
        char writeBuffer[64];
        char readBuffer[READ_BUF_SIZE];
        short GP2_etats[6];

        void send(const char *command, ...);
        void print_buffer(); //debug
        int update_buffer(int timeout);
        void flush_buffer();
        void parse();
};

#endif // __PROTOCOLE_H_
