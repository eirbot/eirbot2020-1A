#ifndef __AFFICHAGE_H_
#define __AFFICHAGE_H_

#include <cstdio>

#ifndef TIMEOUT
#define TIMEOUT 0
#endif

extern bool debug;

void print_timeout();

void print_success();

void print_fail();

void affichage(int timeout);

void good_port(short result_x, short result_y, short dest_x, short dest_y);

void print_optimisated();

void print_summarise();

#endif // __AFFICHAGE_H_
