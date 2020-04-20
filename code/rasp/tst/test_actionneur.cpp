#include "test_actionneur.hpp"

void test_actionneur()
{
    TEST_BEGIN;
    printf("\n>> Test non complets dont les fonctions nécessitent des modifications <<\n");
    Actionneur::Phare_activation();
    Actionneur::Phare_desactivation();
    Actionneur::Pavillon();
    TEST_END;
}
