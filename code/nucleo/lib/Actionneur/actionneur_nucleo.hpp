#ifndef __ACTIONNEUR_H_
#define __ACTIONNEUR_H_
#include "mbed.h"
#define SERVO_PWM_PERIOD 60000
#define SERVO_INIT 4250
#define SERVO_LEFT 1900
#define SERVO_RIGHT 6550

/**
 * @file actionneur_nucleo.hpp
 * @brief Contient les fonctions permettant d'activer ou désactiver les actionneurs
 * @author*/

//DigitalOut pavillon_pin(LED1); //PG_0

/**
 * @brief Initialisation pavillon
 * @param pav_pin : pin de sortie qui commande le moteur*/
void desactivate_pavillon();

/**
 * @brief Sort le pavillon
 * @param servo: Le servomoteur associé au pavillon*/
void activate_pavillon();


void init_bras_pwm();
void activate_bras_droit();
void desactivate_bras_droit();
void activate_bras_gauche();
void desactivate_bras_gauche();

#endif // __ACTIONNEUR_H_
