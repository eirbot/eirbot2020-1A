#ifndef _MOTEUR_H
#define _MOTEUR_H
#include "mbed.h"
#define FREQ_MOTEUR 0.00005 //20kHz
#define VMOY 20
#define VMAX 50

int fonc_direction(const float consigne);

#endif