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


Protocole::Protocole(std::string device) {
    serial_port = open(device.c_str(), O_RDWR);

    memset(&tty, 0, sizeof tty);
    memset(&readBuffer, 0, READ_BUF_SIZE);

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

    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 115200
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
}

Protocole::~Protocole() {
    close(serial_port);
}

// --------    PRIVATE       ------------
/*
 * command format comme dans printf
 * ex: send("SPO%hd%hd\n", x, y)
 */
void Protocole::send(const char *command, ...) {
    std::va_list args;
    va_start(args, command);
    vsprintf(writeBuffer, command, args);
    va_end(args);
    write(serial_port, writeBuffer, strlen(writeBuffer));
}

int Protocole::update_buffer() {
    return read(serial_port, readBuffer, READ_BUF_SIZE);
}

void Protocole::flush_buffer() {
    memset(&readBuffer, 0, READ_BUF_SIZE);
}

void Protocole::print_buffer() {
    for (int i = 0; i < READ_BUF_SIZE; i++) {
        printf(" %x ", readBuffer[i] & 0xff);
        if(i%10 == 0) printf("\n");
    }
    printf("\n");
    printf(readBuffer);
    printf("\n");
}


// ------    PUBLIC    --------

// position
void Protocole::set_position(short x, short y) {
    send("SPO%hd,%hd\n", x, y);
    usleep(100000);
    while(update_buffer()) {} //TODO: timeout local
    printf("Message recu\n");
    print_buffer();
    if(strcmp(readBuffer, "RPOOK\n") == 0) {
        printf("Confirmation set position\n");
    }
    else if(strcmp(readBuffer, "RPOOUT\n") == 0) {
        printf("Time out position\n");
    }
    flush_buffer();

}

struct position Protocole::get_position() {
    struct position pos = {.x = 0, .y = 0};
    send("GPO\n");
    return pos;
}

//rotation
void Protocole::set_angle(short angle) {
    send("SRO%hd\n", angle); // angle absolu en deg

    usleep(100000);
    while(update_buffer()) {} //TODO: timeout local
    printf("Message recu\n");
    print_buffer();
    if(strcmp(readBuffer, "RROOK\n") == 0) {
        printf("Confirmation set rotation\n");
    }
    else if(strcmp(readBuffer, "RPOOUT\n") == 0) {
        printf("Time out rotation\n");
    }
    flush_buffer();
}

short Protocole::get_angle() {
    send("GRO\n"); // angle absolu en deg
    return 0;
}

// GP2
void Protocole::set_seuils_GP2(char id, char palier, short distance) {
    send("SGS%c,%c,%hd\n", id, palier, distance); //Set Gp2 seuils
}

void Protocole::get_etats_GP2() {
    send("GGE\n"); //Get Gp2 Etats (short etats[])
}
