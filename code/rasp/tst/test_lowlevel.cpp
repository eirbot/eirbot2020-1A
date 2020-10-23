#include "test_lowlevel.hpp"

void test_lowlevel(){
    TEST_BEGIN;
    LowLevel LowLevel;
    bool a = LowLevel.is_depart();
    bool b = LowLevel.is_equipe_bleu();
    bool c = LowLevel.phare_active();
    bool d = LowLevel.boussole_nord();
    printf("Départ %d, Équipe %d, Phare %d, Boussolle %d \n",a,b,c,d);
    TEST_END;
}
