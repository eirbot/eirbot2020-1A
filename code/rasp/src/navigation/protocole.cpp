// parametrage port série https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

#include "protocole.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <cstdarg>
#include <ctime>


Protocole::Protocole(std::string device) {
    serial_port = open(device.c_str(), O_RDWR);

    memset(&tty, 0, sizeof tty);
    flush_buffer();

    // Read in existing settings, and handle any error
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty.c_cc[VTIME] = 1;  //50=5secondes  // 10=Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 115200 or 921600
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }

    usleep(10000);
    tcflush(serial_port, TCIOFLUSH);
    send("RESET\n");
}

Protocole::~Protocole() {
    close(serial_port);
}

// --------    PRIVATE       ------------
/*
 * command format comme dans //printf
 * ex: send("SPO%hd%hd\n", x, y)
 */
void Protocole::send(const char *command, ...) {
    std::va_list args;
    va_start(args, command);
    vsprintf(writeBuffer, command, args);
    va_end(args);
    //printf(writeBuffer);
    write(serial_port, writeBuffer, strlen(writeBuffer));
    // print_buffer(writeBuffer);
}

void Protocole::flush_buffer() {
    memset(&readBuffer, 0, READ_BUF_SIZE);
}

int Protocole::update_buffer(int timeout) {
    flush_buffer(); //fill with zeros
    // printf("update buffer\n");

    int n = 0;
    int n_total = 0;
    int n_timeout = 0;
    bool done = false;

    do {
        n = read(serial_port, readBuffer + n_total, READ_BUF_SIZE - 1);
        if(n == 0) {
           n_timeout++;
        }
        else if(n > 0) {
            n_total += n;
            if(readBuffer[n_total - 1] == '\n') done = true;
        }
        else {
            return 3;
        }
        //printf("n: %d\n", n);
        //printf("n_tot: %d\n", n_total);
        //printf("n_timeout: %d\r", n_timeout);
        //print_buffer(readBuffer);
    } while(done == false && n_timeout < timeout*10);


    if(done == true) return 1;
    else return -1;
}

void Protocole::print_buffer(char * buf) {
    for (int i = 0; i < READ_BUF_SIZE; i++) {
         printf(" %x ", buf[i] & 0xff);
    }
    printf("\n");
    printf(buf);
    printf("\n");
}


// ------    PUBLIC    --------
//GET
enum Protocole::Etat Protocole::get_position(struct position *pos) {
    short int x, y;
    send("GPO\n");
    if(update_buffer(1) == -1) return Etat::TIME_OUT;
    if(sscanf(readBuffer, "VPO%hd,%hd\n", &x, &y) == 2) {
        pos->x = x;
        pos->y = y;
        //printf("POS: x: %d, y: %d\n", x, y);
        return Etat::OK;
    }
    else {
        //printf("Erreur de parsing\n");
        return Etat::ERROR;
    }
}

enum Protocole::Etat Protocole::get_angle(short *angle) {
    send("GRO\n"); // angle absolu en deg
    if(update_buffer(1) == -1) return Etat::TIME_OUT;
    if(sscanf(readBuffer, "VRO%hd\n", angle) == 1) {
        //printf("RO: angle: %hd\n", *angle);
        return Etat::OK;
    }
    else if(strcmp(readBuffer, "RROOUT\n") == 0) {
        //printf("Time out position\n");
        return Etat::TIME_OUT;
    }
    else {
        //printf("Erreur de parsing\n");
        return Etat::ERROR;
    }
}

enum Protocole::Etat Protocole::get_etats_GP2(char etats[3]) {
    char e0, e1, e2;
    send("GGE\n"); //Get Gp2 Etats (short etats[])
    if(update_buffer(1) == -1) return Etat::TIME_OUT;
    if(sscanf(readBuffer, "VGE%c,%c,%c\n", &e0, &e1, &e2) == 3) {
        //printf("Etats GP2: %c, %c, %c\n", e0, e1, e2);
        etats[0] = e0;
        etats[1] = e1;
        etats[2] = e2;
        return Etat::OK;
    }
    else if(strcmp(readBuffer, "RGEOUT\n") == 0) {
        //printf("Time out set etat\n");
        return Etat::TIME_OUT;
    }
    else {
        //printf("Erreur de parsing\n");
        return Etat::ERROR;
    }
}

//SET
//rotation
enum Protocole::Etat Protocole::set_angle(short angle) {
    send("SRO%hd\n", angle); // angle absolu en deg
    if(update_buffer(30) == -1) return Etat::TIME_OUT;
    if(strcmp(readBuffer, "RROOK\n") == 0) {
        //printf("Confirmation set rotation\n");
        return Etat::OK;
    }
    else if(strcmp(readBuffer, "ROUT\n") == 0) {
        //printf("Time out rotation\n");
        return Etat::TIME_OUT;
    }
    else {
        //printf("Erreur de parsing\n");
        return Etat::ERROR;
    }
}


// GP2
enum Protocole::Etat Protocole::set_detection_GP2(char actif) {
    send("SGA%c\n", actif); //Set Gp2 seuils
    if(update_buffer(1) == -1) return Etat::TIME_OUT;
    if(strcmp(readBuffer, "RGAOK\n") == 0) {
        //printf("Confirmation set detection GP2\n");
        return Etat::OK;
    }
    else if(strcmp(readBuffer, "RGAOUT\n") == 0) {
        //printf("Time out detection\n");
        return Etat::TIME_OUT;
    }
    else {
        //printf("Erreur de parsing\n");
        return Etat::ERROR;
    }
}

// position
enum Protocole::Etat Protocole::set_position(short x, short y, char etats[3], int timeout) {
    char e0, e1, e2;
    send("SPO%hd,%hd\n", x, y);
    if(update_buffer(timeout) == -1) return Etat::TIME_OUT;
    if(strcmp(readBuffer, "RPOOK\n") == 0) {
        // printf("Confirmation set position\n");
        return Etat::OK;
    }
    else if(sscanf(readBuffer, "VGE%c,%c,%c\n", &e0, &e1, &e2) == 3) {
        //printf("Obstacle");
        etats[0] = e0;
        etats[1] = e1;
        etats[2] = e2;
        return Etat::OBSTACLE;
    }
    else if(strcmp(readBuffer, "ROUT\n") == 0) {
        return Etat::TIME_OUT;
    }
    else {
        //printf("Erreur de parsing\n");
        return Etat::ERROR;
    }
}


//actionneur
enum Protocole::Etat Protocole::set_actionneur(char id, char on) {
    send("SAC%c,%c\n", id, on); //Set Gp2 seuils
    if(update_buffer(1) == -1) return Etat::TIME_OUT;
    if(strcmp(readBuffer, "RACOK\n") == 0) {
        //printf("Confirmation set detection GP2\n");
        return Etat::OK;
    }
    else if(strcmp(readBuffer, "RACOUT\n") == 0) {
        //printf("Time out detection\n");
        return Etat::TIME_OUT;
    }
    else {
        //printf("Erreur de parsing\n");
        return Etat::ERROR;
    }

}
