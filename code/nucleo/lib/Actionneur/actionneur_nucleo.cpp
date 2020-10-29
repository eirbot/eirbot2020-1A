#include "actionneur_nucleo.hpp"
#include "pinout.hpp"

DigitalOut pavillon_pin(PAVILLON_PIN); //PG_0
PwmOut servoGauche(BRAS_G_PIN);
PwmOut servoDroit(BRAS_D_PIN);
Timeout timeout_pavillon;


void init_bras_pwm() {
    servoGauche.period_ms(20);         // Initialisation période
    servoDroit.period_ms(20);         // Initialisation période
    desactivate_bras_droit();
    desactivate_bras_gauche();
}

void activate_bras_droit() {
    servoDroit.pulsewidth_us(600);   //90° old = 600
}
void desactivate_bras_droit() {
    servoDroit.pulsewidth_us(1500);   // Initialisation en position 0

}

void activate_bras_gauche()
{
    servoGauche.pulsewidth_us(1200);  // 90° //old=1200
}

void desactivate_bras_gauche() {
    servoGauche.pulsewidth_us(500);   // Initialisation en position 0
}

void desactivate_pavillon() {
    pavillon_pin = 1;
}

void activate_pavillon() {
    pavillon_pin = 0; //logique inverse
    timeout_pavillon.attach(&desactivate_pavillon, 0.7);
}
