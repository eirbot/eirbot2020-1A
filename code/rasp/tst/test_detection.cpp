#include "test_detection.hpp"

void test_detection()
{
    TEST_BEGIN;
    GP2 test;
    printf("\n>> Test non complets dont les fonctions nécessitent des modifications <<\n");
    test.activate('a');
    test.disactivate('a');

    vector<obstacle> test_vector=fillVector();
    assert(test_vector.size()==27);

    TEST_END;
}
