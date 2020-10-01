#ifndef __ASSERV_H_
#define __ASSERV_H_

#include "mbed.h"
#include "encoder.hpp"
#include "moteur.hpp"
#include "asserv_vitesse_angle.hpp"
#include "math.h"

// TODO
// - avoir un feedback sur le deroulement de lasserv : destination atteinte ou non, position actuelle ?
// - goto_XY
// - rotate(angle)
//
//

void init_asserv(void);
void set_pwm(void);
void set_consigne(char c);
void function_Asserv(void);
void print_debug_asserv(Serial &pc,char c);

void go_XY(int xd, int yd, int x0, int y0, int alpha0,
           float *distance, float *angle, char *direction);

#endif // __ASSERV_H_
