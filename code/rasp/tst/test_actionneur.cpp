#include "test_actionneur.hpp"

void test_actionneur()
{
    TEST_BEGIN;
    printf("\n>> Test non complets dont les fonctions nécessitent des modifications <<\n");
    Phare_activation();
    Phare_desactivation();
    Pavillon();
    TEST_END;
}
