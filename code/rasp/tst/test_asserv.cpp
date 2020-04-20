#include "test_asserv.hpp"

void test_asserv()
{
    TEST_BEGIN;
    struct position src = {0,0};
    struct position dest = {50,50};
    int back=-5;
    back=Asservissement::go_to(dest,src);
    assert(back!=-5);

    struct position back_pos={-5,-5};
    back_pos=Asservissement::robot_position();
    assert(back_pos.x!=-5 || back_pos.y!=-5);

    short angle=-12;
    angle=Asservissement::angle();
    assert(angle!=-12);

    printf("\n>> Test non complets dont les fonctions nécessitent des modifications <<\n");
    Asservissement::rotate(50);
    Asservissement::initialise_x();
    Asservissement::initialise_y();
    TEST_END;
}
