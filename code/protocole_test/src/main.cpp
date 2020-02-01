#include "mbed.h"
#include "Protocole.hpp"


DigitalIn button(USER_BUTTON);
DigitalOut info_led(LED1);
DigitalOut debug_led(LED2);
DigitalOut data_led(LED3);
Protocole protocole;

void blink(DigitalOut led, unsigned char n, float delay) {
    for (unsigned char i = 0; i < n; i++) {
        led= 1;
        wait(delay);
        led = 0;
        wait(delay);
    }
}


int main(int argc, char *argv[]) {

    protocole.GP2_etats[0] = '1';
    protocole.GP2_etats[1] = '0';
    protocole.GP2_etats[2] = '1';

    while(1) {
        blink(info_led, 10, 0.1f);
    }


    return 0;
}
