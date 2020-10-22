#include "test_asserv.hpp"

void test_asserv()
{
    TEST_BEGIN;
    struct position src = {0,0};
    struct position dest = {50,50};
    int back=-5;
    back=go_to(dest);
    assert(back!=-5);

    struct position back_pos={-5,-5};
    back_pos=robot_position();
    assert(back_pos.x!=-5 || back_pos.y!=-5);

    short the_angle=-12;
    the_angle=angle();
    assert(the_angle!=-12);

    printf("\n>> Test non complets dont les fonctions nécessitent des modifications <<\n");
    rotate(50);
    TEST_END;
}
