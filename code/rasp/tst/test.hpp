#ifndef __TEST_H_
#define __TEST_H_

#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <array>
#include <cfloat>
#include <cstring>

#include "../src/navigation.hpp"
#include "../src/asserv.hpp"
#include "../src/detection.hpp"
#include "../src/actionneur.hpp"
#include "../src/affichage.hpp"
#include "../src/protocole.hpp"

int main(int argc, char *argv[]);
short side(short y);
void test_libre();
void test_base();
void test_debug();
void one_step(Node src, Node dest, vector<obstacle> list_obstacles); //Permet de réaliser une étape ie aller d'un noeud à l'autre
#endif // __TEST_H_
