#include "mbed.h"
#include "platform/ATCmdParser.h"
#include "drivers/Serial.h"


DigitalOut info_led(LED1);
DigitalOut debug_led(LED2);
Serial *_serial;
ATCmdParser *_parser;
short x, y, angle, dist;
char id, palier;

void blink(DigitalOut led, unsigned char n, float delay) {
    for (unsigned char i = 0; i < n; i++) {
        led= 1;
        wait(delay);
        led = 0;
        wait(delay);
    }
}

/*
 * S = Set
 * G = Get
 * V = Valeur : RPO10,10
 * R = Reponse : RPOOK, RPOOUT,
 */
void poll() {
    if(_parser->recv("GPO")) {
        _parser->send("VPO%hd, %hd", x, y);
        return;
    }
    blink(debug_led, 3, 0.05f);
    if(_parser->recv("SPO%hd,%hd", &x, &y)) { //13*8bits = 104 octets -> Ttrans = 104/115200 = 1 ms
        _parser->send("RPOOK");
        return;
    }
    if(_parser->recv("SRO%hd", &angle)) {
        _parser->send("RROOK");
        return;
    }
    if(_parser->recv("GRO")) {
        _parser->send("RRO%hd", angle);
        return;
    }
    if(_parser->recv("GGE")) {
        _parser->send("VGE0,1,2,3");
        return;
    }
    if(_parser->recv("SGS%c,%c,%hd", &id, &palier, &dist)) {
        _parser->send("RGSOK");
        return;
    }
}

int main(int argc, char *argv[]) {
    _serial = new Serial(USBTX, USBRX);
    _serial->baud(115200);
    _parser = new ATCmdParser(_serial);
    _parser->set_delimiter("\n");
    _parser->set_timeout(500);
    _parser->debug_on(1);

    //_serial->attach(&poll, Serial::RxIrq);

//    _parser->oob("SPO%hd,%hd\n", set_pos);
//    _parser->process_oob();

    while(1) {
        blink(info_led, 10, 0.1f);
        poll();
    }


    return 0;
}
