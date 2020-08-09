#include "mbed.h"
#include <Protocole_nucleo.hpp>
#include <actionneur_nucleo.hpp>

DigitalOut LD1_led(LED1);
DigitalOut LD2_led(LED2);
DigitalOut LD3_led(LED3);
PwmOut Servo_pav(D3); //Pour l'actionneur du pavillon
PwmOut Servo_man(D5); //Pour l'actionneur du manche
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
    activate_pavillon(Servo_pav);
   // activate_manche(Servo_man);
   int cpt=1000;
    while(1) {
        cpt=cpt+10;
        blink(LD1_led, 10, 0.1f); //simulation d'activité
    }
    return 0;
}
