#ifndef __ASSERV_H_
#define __ASSERV_H_

#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <array>
#include <cfloat>
#include <stack>

struct position{
    int x;
    int y;
};

class Asservissement
{
    public:
        static void go_to(struct position dest);
    private:

};

#endif
