#include "mbed.h"
// #include "drivers/Serial.h"


DigitalIn button(USER_BUTTON);
DigitalOut info_led(LED1);
DigitalOut debug_led(LED2);
DigitalOut data_led(LED3);
RawSerial _serial(USBTX, USBRX);
short x, y, angle;
char GP2_on;
char GP2_etats[3] = {'1', '0', '1'};

char readBuffer[64];
int buf_index = 0;

void blink(DigitalOut led, unsigned char n, float delay) {
    for (unsigned char i = 0; i < n; i++) {
        led= 1;
        wait(delay);
        led = 0;
        wait(delay);
    }
}

void parse() {
    data_led = 1;
    //SET
    if(sscanf(readBuffer, "SPO%hd,%hd\n", &x, &y)) {
        _serial.printf("RPOOK\n");
    }
    else if(sscanf(readBuffer, "SRO%hd\n", &angle)) {
        _serial.printf("RROOK\n");
    }
    else if(sscanf(readBuffer, "SGA%c\n", &GP2_on)) {
        _serial.printf("RGAOK\n");
    }
    //GET
    else if(strcmp(readBuffer, "GPO\n") == 0) {
        _serial.printf("VPO%hd,%hd\n", x, y);
    }
    else if(strcmp(readBuffer, "GRO\n") == 0) {
        _serial.printf("VRO%hd\n", angle);
    }
    else if(strcmp(readBuffer, "GGE\n") == 0) {
        _serial.printf("VGE%c,%c,%c\n", GP2_etats[0], GP2_etats[1], GP2_etats[2]);
    }
    data_led = 0;
}

/*
 * S = Set
 * G = Get
 * V = Valeur : RPO10,10
 * R = Reponse : RPOOK, RPOOUT,
 */
void poll() {
    while(_serial.readable()) {
        readBuffer[buf_index] = _serial.getc();
        if(readBuffer[buf_index] == '\n') {
            readBuffer[buf_index+1] = 0;
            buf_index = 0;
            parse();
            break;
        }
        buf_index++;
    }
}

int main(int argc, char *argv[]) {
    _serial.baud(115200);
    _serial.attach(&poll, Serial::RxIrq);

    while(1) {
        blink(info_led, 10, 0.1f);
        if(button.read()) {
            blink(data_led, 5, 0.05f);
            _serial.printf("x: %hd, y: %hd\n", x, y);
            _serial.printf("angle: %hd\n", angle);
            _serial.printf("detection GP2: %c\n", GP2_on);
        }
    }


    return 0;
}
