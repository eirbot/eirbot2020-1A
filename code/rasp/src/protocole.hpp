#ifndef __PROTOCOLE_H_
#define __PROTOCOLE_H_

#include <stdio.h>
#include <termios.h>
#include <vector>
#include <string>


class Protocole
{
    public:
        Protocole(std::string device);
        ~Protocole();

        // position
        void set_position(short x, short y); //x et y en cm
        std::vector<short> get_position(); //vector ou struct en retour ?

        //rotation
        void set_angle(short angle); // angle en deg entre 0 et 360 ?
        short get_angle();

        // GP2
        void set_seuils_GP2(char id, char palier, short distance);
        std::vector<short> get_etats_GP2();

    private:
        int serial_port;
        struct termios tty;
        char writeBuffer[64];
};

#endif // __PROTOCOLE_H_
