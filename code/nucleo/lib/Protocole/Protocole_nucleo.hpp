#ifndef __PROTOCOLE_H_
#define __PROTOCOLE_H_

#include "mbed.h"
#include "asserv.hpp"

/**
 * @file Protocole_nucleo.hpp
 * @brief Fichier principal du projet permet de communiquer entre la raspberry et la nucléo. Ce fichier est l'implémentation côté nucléo
 * @author Ptit Lu*/

enum protocol_state {INIT, WAIT_ORDER, WAIT_ASSERV};


/**
 * @class Protocole
 * @brief Contient toutes les méthodes permettant d'utiliser le protocole côté nucléo*/
class Protocole
{
    public:
        Protocole();
        ~Protocole();

        //robot variables
        short x;
        short y;
        short angle;
        char GP2_on;
        char GP2_etats[3];
        char actionneur_id;
        char actionneur_etat;

        //void poll();
        void update_state();
        void act();

    private:
        enum protocol_state state;
        char readBuffer[32];
        int buf_index = 0;
        //flags
        bool order_ready_flag = false;
        bool timeout_flag = false;
        RawSerial *_serial;
        void parse();
        void readByte();
};


#endif // __PROTOCOLE_H_
