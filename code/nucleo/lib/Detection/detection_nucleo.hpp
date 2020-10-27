#ifndef __DETECTION_NUCLEO_H_
#define __DETECTION_NUCLEO_H_

#include "mbed.h"


void get_etat_GP2(char etats[3], bool avant);
bool process_obstacle(short x, short  y, short alpha, char etats[3]);
char *update_debug_GP2();

#endif // __DETECTION_NUCLEO_H_
