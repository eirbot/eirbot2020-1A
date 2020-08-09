#include "actionneur_nucleo.hpp"


void activate_pavillon(PwmOut servo)
{
    //exemple fonctionnel
    servo.period_ms(60);         // Initialisation période
    servo.pulsewidth_us(1000);   // Initialisation en position 0
    wait_us(300000);
    servo.pulsewidth_us(1500);
    wait_us(300000);
    servo.pulsewidth_us(2000);
}

void activate_manche(PwmOut servo)
{
    servo.period_ms(20);
        //if (servo.position==position_min) {
            for(int i=0; i<1000; i += 10) {
                servo.pulsewidth_us(i);
            }
            return;
       // }
        // if (servo.position==position_moy) {
        //     for (int i=position_moy; i > position_min; i-=10) {
        //         servo.pulsewidth_us(i);
        //     }
        //     return;
        // }
}
