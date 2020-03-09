#ifndef __ACTIONNEUR_H_
#define __ACTIONNEUR_H_
#include "mbed.h"
#include "Servo.h"

PwmOut Servo_pav(D4);
PwmOut Servo_man(D5);

const int position_min=1000;
const int position_quart=1250;
const int position_moy=1500;
const int position_max=2000;

void activate_pavillon(PwmOut servo); //Met le pavillon dans l'autre configuration

void activate_manche(PwmOut serv); //Met le bras pour le manche dans l'autre configuration


#endif // __ACTIONNEUR_H_
