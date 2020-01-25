#ifndef __PROTOCOLE_H_
#define __PROTOCOLE_H_

#include <stdio.h>
#include <termios.h>
#include <vector>
#include <string>
#include "asserv.hpp"

#define READ_BUF_SIZE 128


class Protocole
{
    public:
        Protocole(std::string device);
        ~Protocole();

        enum etat {OK, TIMEOUT, OBSTACLE};

        // position
        void set_position(short x, short y); //x et y en cm
        struct position get_position();

        //rotation
        void set_angle(short angle); // angle en deg entre 0 et 360 ? => plutot entre 0 et 360
        short get_angle();

        // GP2
        void set_seuils_GP2(char id, char palier, short distance);
        void get_etats_GP2();

    private:
        int serial_port;
        struct termios tty;
        char writeBuffer[64];
        char readBuffer[READ_BUF_SIZE];
        short GP2_etats[6];

        void send(const char *command, ...);
        void print_buffer(); //debug
        int update_buffer();
        void flush_buffer();
        void parse();
};

#endif // __PROTOCOLE_H_
