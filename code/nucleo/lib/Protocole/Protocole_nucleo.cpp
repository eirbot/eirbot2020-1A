#include "Protocole_nucleo.hpp"
#include "actionneur_nucleo.hpp"
#include "mbed.h"


Protocole::Protocole() {
    memset(readBuffer, 0, sizeof(readBuffer));
    _serial = new RawSerial(USBTX, USBRX);
    _serial->baud(115200);
    enable_callback(true);
    Protocole::state = WAIT_ORDER;
    Protocole::last_order = OTHER;
    _serial->printf("INIT\n");
    wait_us(100000);
}

Protocole::~Protocole() {
}

void Protocole::enable_callback(bool enable) {
    if(enable) {
        _serial->attach(callback(this, &Protocole::readByte), Serial::RxIrq);
    }
    else {
        _serial->attach(0, Serial::RxIrq);
    }
}

//FIXME verif buf_index
void Protocole::readByte() {
    char recived_char = _serial->getc();
    if (recived_char == 127) // Delete char
    {
        readBuffer[buf_index] = 0;
        buf_index = max(0, buf_index - 1);
    }
    else if(recived_char == '\n') 
    {
        readBuffer[buf_index+1] = 0;
        enable_callback(false);
        order_ready_flag = true;
        buf_index = 0;
        return;
    }
    else
    {
        readBuffer[buf_index] = recived_char;
        buf_index++;
    }

}

void Protocole::update_state() {
    // _serial->printf(update_debug_string());
    print_dbg();
    if(Protocole::state == WAIT_ORDER && order_ready_flag == true) {
        order_ready_flag = false;
        parse();
    }
    else if(Protocole::state == WAIT_ASSERV && get_state() == STOP) {
        if(last_order == PO) {
            _serial->printf("RPOOK\n");
            state = WAIT_ORDER;
        }
        else if(last_order == RO) {
            _serial->printf("RROOK\n");
            state = WAIT_ORDER;
        }

    }
    else if(obstacle_flag == true) {
    }
}


void Protocole::parse() {
    float tmp_x = 0;
    float tmp_y = 0;
    float tmp_angle = 0;

    _serial->printf("PARSE\n");
    //SET
    if(sscanf(readBuffer, "SPO%hd,%hd\n", &x, &y)) {
        tmp_x = ((float)x)/100;
        tmp_y = ((float)y)/100;
        go_XY(tmp_x, tmp_y);
        state = WAIT_ASSERV;
        last_order = PO;
    }
    else if(sscanf(readBuffer, "SRO%hd\n", &angle)) {
        tmp_angle = (float)angle;
        rotate(tmp_angle);
        state = WAIT_ASSERV;
        last_order = RO;
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
        get_XY(&tmp_x, &tmp_y);
        x = (short)(tmp_x*100);
        y = (short)(tmp_y*100);
        _serial->printf("VPO%hd,%hd\n", x, y);
    }
    else if(strcmp(readBuffer, "GRO\n") == 0) {
        angle = get_angle();
        _serial->printf("VRO%hd\n", angle);
    }
    else if(strcmp(readBuffer, "GGE\n") == 0) {
        _serial->printf("VGE%c,%c,%c\n", GP2_etats[0], GP2_etats[1], GP2_etats[2]);
    }
    else if(strcmp(readBuffer, "STOP\n") == 0) {
        set_state(RES);
    }
    memset(readBuffer, 0, sizeof(readBuffer));
    enable_callback(true);
}


//------- DEBUG --------

void Protocole::print_dbg() {
    for(unsigned int i = 0; i < sizeof(readBuffer); i++) {
        _serial->putc(readBuffer[i]);
    }
    char etat_str[16];
    switch(state) {
        case INIT:
            strncpy(etat_str, "INIT", 16);
            break;
        case WAIT_ORDER:
            strncpy(etat_str, "W_ORD", 16);
            break;
        case WAIT_ASSERV:
            strncpy(etat_str, "W_ASS", 16);
            break;
    }
    _serial->printf("P:etat=%5s ", etat_str);
    switch(last_order) {
        case PO:
            strncpy(etat_str, "PO", 16);
            break;
        case RO:
            strncpy(etat_str, "RO", 16);
            break;
        case OTHER:
            strncpy(etat_str, "OTH", 16);
            break;
    }
    _serial->printf("P:last=%3s\n", etat_str);
}
