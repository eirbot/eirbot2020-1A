#ifndef __ASSERV_H_
#define __ASSERV_H_

#include "mbed.h"
#include "encoder.hpp"
#include "moteur.hpp"
#include "asserv_vitesse_angle.hpp"
#include "math.h"

// TODO
// - goto_XY
// - rotate(angle)

//POsition, ROtation, STOP
//PO_ANGLE = premiere etape deplacement XY
//PO_DISTANCE = deuxieme etape XY
//ROT = rotation seule
//STOP = le robot garde sa position (s'il a de l'inertie il la compense)
//RES = asserv coupée
//INIT coordonnées absolues raz
enum asserv_state {PO_ANGLE, PO_DISTANCE, PO_STOP, ROT, STOP, RES, ASS_INIT, PO_RESET, ROT_RESET};

void init_asserv(void);
void reset_consigne(void); //update derniere position connue
void set_pwm(void);
void function_Asserv(void); //THE function
void update_state(void);
void set_state(enum asserv_state s);
void set_state_distance(void);
void set_state_rotation(void); //void void pour un callback
enum asserv_state get_state(void);
void set_consigne(char c);
void print_debug_asserv(Serial &pc,char c);
char *update_debug_string();

float XY_to_Distance(float x, float y);
float XY_to_Angle(float x, float y);

//set
void go_XY(float x_d, float y_d);
void rotate(float angle);

//get
void get_XY(float *x, float *y);
float get_angle();

#endif // __ASSERV_H_
