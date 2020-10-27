#ifndef __DETECTION_NUCLEO_H_
#define __DETECTION_NUCLEO_H_

#include "mbed.h"

bool get_etat_GP2(char etats[3], bool avant);
char *update_debug_GP2();

#endif // __DETECTION_NUCLEO_H_
