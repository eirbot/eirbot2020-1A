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

/**
 * @brief Sort le pavillon
 * @param servo: Le servomoteur associé au pavillon*/
void activate_pavillon(PwmOut servo); //Met le pavillon dans l'autre configuration

/**
 * @brief Sort ou rentre le pavillon
 * @param serv: Le servomoteur associé au manche*/
void activate_manche(PwmOut serv); //Met le bras pour le manche dans l'autre configuration


#endif // __ACTIONNEUR_H_