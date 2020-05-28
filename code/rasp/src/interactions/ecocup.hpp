#ifndef __ECOCUP_H_
#define __ECOCUP_H_

#include "../navigation/navigation.hpp"
#include "actionneur.hpp"
#include "ecocup_pdv.hpp"

void ecocup_road(int taille, vector<obstacle> list_obstacles);
void ecocup_read(int taille);
void ecocup_take();

#endif // __ECOCUP_H_
