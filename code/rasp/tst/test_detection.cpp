#include "test_detection.hpp"

void test_detection()
{
    TEST_BEGIN;
    class GP2 test=GP2(centre_avant, 1, 10);

    printf("\n>> Test non complets dont les fonctions nécessitent des modifications <<\n");
    test.activate();
    test.disactivate();

    vector<obstacle> test_vector=World::fillVector();
    assert(test_vector.size()==27);

    test_vector=GP2::gp2Obstacle(test_vector, {30,50});
    assert(test_vector.size()>=27);
    TEST_END;
}
