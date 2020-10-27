#include "detection_nucleo.hpp"
#include "pinout.hpp"

const float SEUIL = 0.3;

//avant
AnalogIn gp2_a1(GP2_A1_PIN);
AnalogIn gp2_a2(GP2_A2_PIN);
AnalogIn gp2_a3(GP2_A3_PIN);

//arriere
AnalogIn gp2_r1(GP2_R1_PIN);
AnalogIn gp2_r2(GP2_R2_PIN);
AnalogIn gp2_r3(GP2_R3_PIN);

AnalogIn pins[] = {gp2_a1, gp2_a2, gp2_a3,
                   gp2_r1, gp2_r2, gp2_r3};

char debug_str_GP2[256];

//return true if we must STOP
bool GP2_update(bool avant) {
    return false;
}

bool get_etat_GP2(char etats[3], bool avant) {
    bool flag = false;
    float read_tmp;
    for(int i = 0; i < 3; i++) {
        if(avant) {
            read_tmp = pins[i].read();
        }
        else {
            read_tmp = pins[i+3].read();
        }

        if(read_tmp > SEUIL) {
            etats[i] = '1';
            flag = true;
        }
        else {
            etats[i] = '0';
        }
    }
    return flag;
}


char * update_debug_GP2() {
    snprintf(debug_str_GP2, 256, "1:%f 2:%f 3:%f\r\n", gp2_a1.read(), gp2_a2.read(), gp2_a3.read());
    return debug_str_GP2;

}
