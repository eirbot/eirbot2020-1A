#ifndef __ACTIONNEUR_H_
#define __ACTIONNEUR_H_
#include "mbed.h"
#define SERVO_PWM_PERIOD 60000
#define SERVO_INIT 4250
#define SERVO_LEFT 1900
#define SERVO_RIGHT 6550

void activate_pavillon(PwmOut servo); //Met le pavillon dans l'autre configuration

void activate_manche(PwmOut serv); //Met le bras pour le manche dans l'autre configuration
void desactivate_manche(PwmOut servo);


#endif // __ACTIONNEUR_H_
