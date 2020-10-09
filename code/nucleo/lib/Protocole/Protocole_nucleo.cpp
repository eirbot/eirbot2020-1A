#include "Protocole_nucleo.hpp"
#include "actionneur_nucleo.hpp"
#include "mbed.h"


Protocole::Protocole() {
    _serial = new RawSerial(USBTX, USBRX);
    _serial->baud(115200);
    _serial->attach(callback(this, &Protocole::readByte), Serial::RxIrq);
    Protocole::state = INIT;
    wait_us(100000);
}

Protocole::~Protocole() {
}

// ATTENTION fonction bloquante
// TODO gerer l'overflow du buffer
// le while risque de bloquer et faire foirer l'asserv...
// void Protocole::poll() {
//     while(_serial->readable()) {
//         readBuffer[buf_index] = _serial->getc();
//         if(readBuffer[buf_index] == '\n') {
//             readBuffer[buf_index+1] = 0;
//             buf_index = 0;
//             parse();
//             break;
//         }
//         buf_index++;
//     }
// }

//FIXME verif buf_index
void Protocole::readByte() {
    readBuffer[buf_index] = _serial->getc();
    buf_index++;
    if(readBuffer[buf_index] == '\n') {
        readBuffer[buf_index+1] = 0;
        order_ready_flag = true;
    }
}

void Protocole::update_state() {
    if(order_ready_flag == true) {
        buf_index = 0;
        parse();
    }
    else if(feedback_flag == true) {

    }
    else if(timeout_flag == true) {

    }
    else if(obstacle_flag == true) {
    }
}

void Protocole::act() {
    if(Protocole::state == WAIT_ASSERV) {
        if(get_state() == STOP) {
            // _serial->printf("")
           // if(get_obstacle() == 0) {
           //     Protocole::state = FAIL;
           // }
           // else {
           //     Protocole::state = SUCCESS;
           // }
        }
    }
}


void Protocole::parse() {
    //SET
    if(sscanf(readBuffer, "SPO%hd,%hd\n", &x, &y)) {
        go_XY(x/100, y/100); //conversion cm -> m
        state = WAIT_ASSERV;
        _serial->printf("RPOOK\n");
    }
    else if(sscanf(readBuffer, "SRO%hd\n", &angle)) {
        rotate(angle);
        state = WAIT_ASSERV;
        _serial->printf("RROOK\n");
    }
    else if(sscanf(readBuffer, "SGA%c\n", &GP2_on)) {
        //GP2_on()
        _serial->printf("RGAOK\n");
    }
    else if(sscanf(readBuffer, "SAC%c,%c\n", &actionneur_id, &actionneur_etat)) {
        if(actionneur_id == 0) {
            //activate_manche();
        }
        else if(actionneur_id == 1) {
            //activate_pavillon();
        }
        _serial->printf("RACOK\n");
    }
    //GET
    else if(strcmp(readBuffer, "GPO\n") == 0) {
        get_XY((float*)&x, (float*)&y);
        _serial->printf("VPO%hd,%hd\n", x, y);
    }
    else if(strcmp(readBuffer, "GRO\n") == 0) {
        angle = get_angle();
        _serial->printf("VRO%hd\n", angle);
    }
    else if(strcmp(readBuffer, "GGE\n") == 0) {
        _serial->printf("VGE%c,%c,%c\n", GP2_etats[0], GP2_etats[1], GP2_etats[2]);
    }
}


//------- DEBUG --------

void Protocole::print_dbg() {

}
