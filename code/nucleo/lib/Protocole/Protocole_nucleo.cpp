#include "Protocole_nucleo.hpp"
#include "actionneur_nucleo.hpp"
#include "mbed.h"


Protocole::Protocole() {
    _serial = new BufferedSerial(USBTX, USBRX);
    _serial->set_baud(115200);
    _serial->attach(this, &Protocole::poll, Serial::RxIrq);
    wait_us(100000);
}

Protocole::~Protocole() {
}

// ATTENTION fonction bloquante
// TODO gerer l'overflow du buffer
// le while risque de bloquer et faire foirer l'asserv...
void Protocole::poll() {
    while(_serial->readable()) {
        readBuffer[buf_index] = _serial->getc();
        if(readBuffer[buf_index] == '\n') {
            readBuffer[buf_index+1] = 0;
            buf_index = 0;
            parse();
            break;
        }
        buf_index++;
    }
}


void Protocole::parse() {
    //SET
    if(sscanf(readBuffer, "SPO%hd,%hd\n", &x, &y)) {
        _serial->printf("RPOOK\n");
    }
    else if(sscanf(readBuffer, "SRO%hd\n", &angle)) {
        _serial->printf("RROOK\n");
    }
    else if(sscanf(readBuffer, "SGA%c\n", &GP2_on)) {
        _serial->printf("RGAOK\n");
    }
    else if(sscanf(readBuffer, "SAC%c,%c\n", &actionneur_id, &actionneur_etat)) {
        if(actionneur_id == 0) {
            //activate_manche();
        }
        else if(actionneur_id == 0) {
            //activate_pavillon();
        }
        _serial->printf("RACOK\n");
    }
    //GET
    else if(strcmp(readBuffer, "GPO\n") == 0) {
        _serial->printf("VPO%hd,%hd\n", x, y);
    }
    else if(strcmp(readBuffer, "GRO\n") == 0) {
        _serial->printf("VRO%hd\n", angle);
    }
    else if(strcmp(readBuffer, "GGE\n") == 0) {
        _serial->printf("VGE%c,%c,%c\n", GP2_etats[0], GP2_etats[1], GP2_etats[2]);
    }
}
