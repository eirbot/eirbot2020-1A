#include "robot.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <cstdarg>
#include <string.h>


struct shape dimension_robot={32,32};

extern int pc;

LowLevel LowLevel;

Robot::Robot():dimension(dimension_robot)
{
}

Robot::~Robot()
{
   
}

string Robot::calibration()
{
    if (pc==0) {
        if(LowLevel.is_equipe_bleu()==0){
            return "blue";
        }
        else{
            return "yellow";
        }
    }
    else{
        return "blue";
    }
}

 void Robot::move(Node src, Node dest, vector<obstacle> list_obstacles)
 {
    Navigation Navigation;
    Navigation.one_step(src,dest,list_obstacles);
}

 void Robot::rotation(short angle) //Permet de faire tourner le robot d'un certain angle (le type de angle est à définir)
 {
     rotate(angle);
 }

struct position Robot::position() //Renvoie la position du robot
{
    return robot_position();
}
short Robot::angle_robot() //Renvoie l'angle du robot par rapport à la table (entre 0 et 360)
{
    return angle();
}


void Robot::detection(char cote, char activation)
{
    if (activation=='1') {
        GP2::activate(cote);
    }
    if (activation=='0') {
        GP2::disactivate(cote);
    }
}

void Robot::actionneur(int cote,int activation)
{
    Actionneur Actionneur;
    if (cote==0 && activation==1) {
        Actionneur.Gauche_activation();
    }
    if (cote==0 && activation==0) {
        Actionneur.Gauche_desactivation();
    }
    if (cote==1 && activation==1){
        Actionneur.Droit_activation();
    }
    if (cote==1 && activation==0) {
        Actionneur.Droit_desactivation();
    }

}

void Robot::pavillon(int activation)
{
    Actionneur Actionneur;
    if (activation==1) {
        Actionneur.Pavillon();
    }
    if (activation==0){
        Actionneur.Pavillon();
    }
}

int Robot::communication_phare()
{
    if (!pc) {
        return LowLevel.phare_active();
    }
    else{
        return 0;
    }
}

int Robot::communication_boussole()
{
    if (!pc) {
        return LowLevel.boussole_nord();
    }
    else{
        return 0;
    }
}

 void pince(int activation)
 {
     printf("Pince en cours de développement \n");
 }

int Robot::depart()
{
    if(!pc){
        return LowLevel.is_depart();
    }
    else{
        return 1;
    }
}

void Robot::setup_score(){
    serial_port_cmpt = open("/dev/ttyS0", O_RDWR);

    memset(&tty_cmpt, 0, sizeof tty_cmpt);

    // Read in existing settings, and handle any error
    if(tcgetattr(serial_port_cmpt, &tty_cmpt) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    tty_cmpt.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty_cmpt.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty_cmpt.c_cflag |= CS8; // 8 bits per byte (most common)
    tty_cmpt.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty_cmpt.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty_cmpt.c_lflag &= ~ICANON;
    tty_cmpt.c_lflag &= ~ECHO; // Disable echo
    tty_cmpt.c_lflag &= ~ECHOE; // Disable erasure
    tty_cmpt.c_lflag &= ~ECHONL; // Disable new-line echo
    tty_cmpt.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty_cmpt.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty_cmpt.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty_cmpt.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty_cmpt.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty_cmpt.c_cc[VTIME] = 1;  //50=5secondes  // 10=Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty_cmpt.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 115200 or 921600
    cfsetispeed(&tty_cmpt, B9600);
    cfsetospeed(&tty_cmpt, B9600);

    // Save tty_cmpt settings, also checking for error
    if (tcsetattr(serial_port_cmpt, TCSANOW, &tty_cmpt) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }

    usleep(10000);
    tcflush(serial_port_cmpt, TCIOFLUSH);
}

void Robot::set_score(int score){
    printf("J'affiche le score %d \n",score);
    write(serial_port_cmpt, &score, 1);
}

void Robot::add_score(int add){
    Robot::score+=add;
    set_score(Robot::score);
}
