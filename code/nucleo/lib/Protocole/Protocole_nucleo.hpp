#ifndef __PROTOCOLE_H_
#define __PROTOCOLE_H_

#include "mbed.h"

/**
 * @file Protocole_nucleo.hpp
 * @brief Fichier principal du projet permet de communiquer entre la raspberry et la nucléo. Ce fichier est l'implémentation côté nucléo
 * @author Ptit Lu*/

/**
 * @class Protocole
 * @brief Contient toutes les méthodes permettant d'utiliser le protocole côté nucléo*/
class Protocole
{
        public:
        Protocole();
        ~Protocole();
        short x;
        short y;
        short angle;
        char GP2_on;
        char GP2_etats[3];
        char actionneur_id;
        char actionneur_etat;

        void poll();

    private:
        char readBuffer[32];
        int buf_index = 0;
        BufferedSerial *_serial;
        void parse();
};


#endif // __PROTOCOLE_H_
