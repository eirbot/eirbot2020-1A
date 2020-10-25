#include "actionneur_nucleo.hpp"
#include "pinout.hpp"

DigitalOut pavillon_pin(PC_6); //PG_0
PwmOut servoGauche(PA_3);
PwmOut servoDroit(PA_0);
Timeout timeout_pavillon;


void init_bras_pwm() {
    servoGauche.period_ms(20);         // Initialisation période
    servoDroit.period_ms(20);         // Initialisation période
    desactivate_bras_droit();
    desactivate_bras_gauche();
}

void activate_bras_droit() {
    servoDroit.pulsewidth_us(1500);   //90°
}
void desactivate_bras_droit() {
    servoDroit.pulsewidth_us(500);   // Initialisation en position 0

}

void activate_bras_gauche()
{
    servoGauche.pulsewidth_us(1500);  // 90°
}

void desactivate_bras_gauche() {
    servoGauche.pulsewidth_us(500);   // Initialisation en position 0
}

void desactivate_pavillon() {
    pavillon_pin = 1;
}

void activate_pavillon() {
    pavillon_pin = 0; //logique inverse
    timeout_pavillon.attach(&desactivate_pavillon, 1);
}
