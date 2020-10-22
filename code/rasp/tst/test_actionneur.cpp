#include "test_actionneur.hpp"

void test_actionneur()
{
    TEST_BEGIN;
    Actionneur Actionneur;
    printf("\n>> Test non complets dont les fonctions nécessitent des modifications <<\n");
    Actionneur.Droit_activation();
    Actionneur.Droit_desactivation();
    Actionneur.Pavillon();
    TEST_END;
}
