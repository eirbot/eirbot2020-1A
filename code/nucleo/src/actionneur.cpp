#include "actionneur.hpp"

void activate_pavillon()
{
    Servo_pav.period_ms=20;
    for(int i=position_min; i<position_max; i += 10) {
        Servo_pav.pulsewidth_us(i);
    }
    return;
}

void activate_manche()
{
    Servo_man.period_ms=20;
        if (Servo_man.position==position_min) {
            for(int i=position_min; i<position_moy; i += 10) {
                Servo_man.pulsewidth_us(i);
            }
            return;
        }
        if (Servo_man.position==position_moy) {
            for (int i=position_moy; i > position_min; i-=10) {
                Servo_man.pulsewidth_us(i);
            }
            return;
        }
}
