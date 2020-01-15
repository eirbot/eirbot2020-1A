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

int main(int argc, char *argv[]);
short side(short y);
void test_libre();
void test_base();
void test_debug();

#endif // __TEST_H_
