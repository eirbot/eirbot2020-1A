#include "detection_nucleo.hpp"
#include "pinout.hpp"
#include "math.h"

const float SEUIL = 0.3;
float x_ob_dbg, y_ob_dbg, alpha_dbg;

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

void get_etat_GP2(char etats[3], bool avant) {
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
        }
        else {
            etats[i] = '0';
        }
    }
}

bool process_obstacle(short x, short y, short alpha, char etats[3]) {
    get_etat_GP2(etats, 1); //1=avant
    if (etats[1]=='1' && etats[2]=='1') {
        alpha-=10;
    }
    else if (etats[0]=='1' && etats[1]=='1') {
        alpha+=10;
    }
    else if (etats[1]=='1') {
        alpha+=0;
    }
    else if (etats[0]=='1'){
        alpha+=22;
    }
    else if (etats[2]=='1'){
        alpha-=22;
    }
    else {
        return false;
    }

    float calcul_x=x+30.*cos(alpha*M_PI/180);
    float calcul_y=y-30.*sin(alpha*M_PI/180);
    x_ob_dbg = calcul_x;
    y_ob_dbg = calcul_y;
    alpha_dbg = alpha;
    if (calcul_x >= 20 && calcul_y >= 20 && calcul_x <= 150 && calcul_y <= 180) {
        return true;
    }
    else{
        return false;
    }
}

char * update_debug_GP2() {
    snprintf(debug_str_GP2, 256, "1:%f 2:%f 3:%f xo:%f yo:%f a:%d\r\n", gp2_a1.read(), gp2_a2.read(), gp2_a3.read(), x_ob_dbg, y_ob_dbg, alpha_dbg);
    return debug_str_GP2;

}
