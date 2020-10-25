#include "Protocole_nucleo.hpp"
#include "actionneur_nucleo.hpp"
#include "mbed.h"

#define DEBUG_ASS
//#define DEBUG_PRO

Timeout timeout_order;

Protocole::Protocole() {
    memset(readBuffer, 0, sizeof(readBuffer));
    _serial = new RawSerial(USBTX, USBRX);
    _serial->baud(115200);
    debug_serial = new RawSerial(D1, D0);
    debug_serial->baud(9600);
    debug_serial->printf("DEBUG\n");
    enable_callback(true);
    Protocole::state = INIT;
    Protocole::last_order = OTHER;
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
    char received_char = _serial->getc();
    if (received_char == 127) // Delete char
    {
        readBuffer[buf_index] = 0;
        buf_index = max(0, buf_index - 1);
    }
    else if(received_char == '\n')
    {
        readBuffer[buf_index] = received_char;
        readBuffer[buf_index+1] = 0;
        //enable_callback(false);
        order_ready_flag = true;
        buf_index = 0;
        return;
    }
    else
    {
        readBuffer[buf_index] = received_char;
        buf_index++;
    }

}

void Protocole::update_state() {
    #ifdef DEBUG_ASS
      debug_serial->printf(update_debug_string());
      //print_dbg();
    #endif
    if((Protocole::state == INIT || Protocole::state == WAIT_ORDER) && order_ready_flag == true) {
        order_ready_flag = false;
        parse();
    }
    else if(Protocole::state == WAIT_ASSERV) {
        if(get_state() == STOP) {
            if(last_order == PO) {
                _serial->printf("RPOOK\n");
                #ifdef DEBUG_PRO
                    debug_serial->printf("RPOOK\n");
                #endif
                state = WAIT_ORDER;
                timeout_order.detach();
            }
            else if(last_order == RO) {
                _serial->printf("RROOK\n");
                #ifdef DEBUG_PRO
                    debug_serial->printf("RROOK\n");
                #endif
                state = WAIT_ORDER;
                timeout_order.detach();
            }
        }
        else if(timeout_flag == true) {
            _serial->printf("ROUT\n");
            #ifdef DEBUG_PRO
                debug_serial->printf("ROUT\n");
            #endif
            timeout_flag = false;
            state = WAIT_ORDER;
            timeout_order.detach();
        }
    }
    else if(obstacle_flag == true) {
        obstacle_flag = false;
    }
}

void Protocole::parse() {
    float tmp_x = 0;
    float tmp_y = 0;
    float tmp_angle = 0;
    float KP_a;
    float KI_a;
    float KD_a;

    #ifdef DEBUG_ASS
      debug_serial->printf("PARSE\n");
    #endif
    #ifdef DEBUG_PRO
        debug_serial->printf(readBuffer);
    #endif
    //SET
    if(sscanf(readBuffer, "SPO%hd,%hd\n", &x, &y)) {
        tmp_x = ((float)x)/100;
        tmp_y = ((float)y)/100;
        if(state == INIT) {
            set_X0Y0(tmp_x, tmp_y);
            _serial->printf("RPOOK\n");
            state = WAIT_ORDER;
        }
        else {
            go_XY(tmp_x, tmp_y);
            state = WAIT_ASSERV;
            last_order = PO;
            timeout_order.attach(callback(this, &Protocole::set_timeout_flag), PROTO_TIMEOUT_DIST);
        }
    }
    else if(sscanf(readBuffer, "SRO%hd\n", &angle)) {
        tmp_angle = (float)angle;
        rotate(tmp_angle);
        state = WAIT_ASSERV;
        last_order = RO;
        timeout_order.attach(callback(this, &Protocole::set_timeout_flag), PROTO_TIMEOUT_ROT);
    }
    else if(sscanf(readBuffer, "SGA%c\n", &GP2_on)) {
        //GP2_on()
        _serial->printf("RGAOK\n");
    }
    else if(sscanf(readBuffer, "SAC%c,%c\n", &actionneur_id, &actionneur_etat)) {
        if(actionneur_id == '0') {
            if(actionneur_etat == '1') {
                activate_bras_droit(); //FIXME c le bien le droit ?
            }
            else {
                desactivate_bras_droit();
            }
        }
        else if(actionneur_id == '1') {
            if(actionneur_etat == '1') {
                activate_bras_gauche(); //FIXME c le bien le gauche ?
            }
            else {
                desactivate_bras_gauche();
            }
        }
        else if(actionneur_id == '2') {
            activate_pavillon();
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
        _serial->printf("VRO%hd\n", (short)get_angle());
    }
    else if(strcmp(readBuffer, "GGE\n") == 0) {
        _serial->printf("VGE%c,%c,%c\n", GP2_etats[0], GP2_etats[1], GP2_etats[2]);
    }
    else if(strcmp(readBuffer, "RESET\n") == 0) {
        set_state(RES);
        state = INIT;
        timeout_order.detach();
    }
    else if(sscanf(readBuffer, "SKA%f,%f,%f\n", &KP_a, &KI_a, &KD_a)) {
        set_KA(KP_a, KI_a, KD_a);
        _serial->printf("RKAOK%f,%f,%f\n", KP_a, KI_a, KD_a);
    }
    memset(readBuffer, 0, sizeof(readBuffer));
//    enable_callback(true);
}

void Protocole::set_timeout_flag() {
    timeout_flag = true;
}


//------- DEBUG --------

void Protocole::print_dbg() {
    for(unsigned int i = 0; i < sizeof(readBuffer); i++) {
        debug_serial->putc(readBuffer[i]);
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
    debug_serial->printf("P:etat=%5s ", etat_str);
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
    debug_serial->printf("P:last=%3s\n", etat_str);
}
