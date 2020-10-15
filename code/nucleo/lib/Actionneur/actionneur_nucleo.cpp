#include "actionneur_nucleo.hpp"

DigitalOut pavillon_pin(LED1); //PG_0
Timeout timeout_pavillon;

void activate_manche(PwmOut servo)
{
    //exemple fonctionnel
    servo.period_ms(60);         // Initialisation période
    servo.pulsewidth_us(1000);   // Initialisation en position 0
    wait_us(300000);
    servo.pulsewidth_us(1500);
    wait_us(300000);
    servo.pulsewidth_us(2000);
}

void desactivate_pavillon() {
    pavillon_pin = 1;
}

void activate_pavillon() {
    pavillon_pin = 0; //logique inverse
    timeout_pavillon.attach(&desactivate_pavillon, 1);
}
