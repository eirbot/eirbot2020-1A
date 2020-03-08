#ifndef __PROTOCOLE_H_
#define __PROTOCOLE_H_

#include "mbed.h"

class Protocole
{
    public:
        Protocole();
        ~Protocole();

        short x, y, angle;
        char GP2_on;
        char GP2_etats[3];
        char actionneur_id;
        char actionneur_etat;

        void poll();

    private:
        char readBuffer[32];
        int buf_index = 0;
        RawSerial *_serial;
        void parse();
};


#endif // __PROTOCOLE_H_
