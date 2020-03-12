#include "actionneur.hpp"


void activate_pavillon(PwmOut servo)
{
    servo.period_ms(20);         // Initialisation période
    servo.pulsewidth_us(1000);   // Initialisation en position 0
    wait(2);
    servo.pulsewidth_us(1500);
    wait(2);
    servo.pulsewidth_us(2000);
    // while(1){
    //     servo.pulsewidth_us(1200);   // Angle négatif
    //     wait(0.3);
    //     servo.pulsewidth_us(1800);   // Angle positif
    //     wait(0.5);
    // }
}

void activate_manche(PwmOut servo)
{
    servo.period_ms(20);
    servo.pulsewidth_ms(1);
    wait(2);
}

void desactivate_manche(PwmOut servo)
{
    servo.period_ms(20);
    servo.pulsewidth_ms(2);
    wait(2);
}
