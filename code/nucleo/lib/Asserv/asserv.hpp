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

//POsition, ROtation, STOP
//PO_ANGLE = premiere etape deplacement XY
//PO_DISTANCE = deuxieme etape XY
//RO = rotation seule
enum asserv_state {PO_ANGLE, PO_DISTANCE, RO, STOP};

void init_asserv(void);
void reset_asserv(void);
void set_pwm(void);
void set_consigne(char c);
void function_Asserv(void);
void print_debug_asserv(Serial &pc,char c);
int  get_feedback();


//set
void go_XY(float x_d, float y_d);
void rotate(float angle);

//get
void get_XY(float *x, float *y);

#endif // __ASSERV_H_
