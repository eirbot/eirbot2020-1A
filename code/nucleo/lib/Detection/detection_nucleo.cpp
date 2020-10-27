#include "detection_nucleo.hpp"
#include "pinout.hpp"
#include "math.h"

const float SEUIL = 0.3;
float x_ob_dbg, y_ob_dbg, alpha_dbg;
bool flag_dbg;

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
int nb_sample = 0;
int etats_lisse[] = {0,0,0};


//return true if we must STOP
bool GP2_update(bool avant) {
    return false;
}

void get_etat_GP2(char etats[3], bool avant) {
    float read_tmp;
    nb_sample += 1;
    for(int i = 0; i < 3; i++) {
        if(avant) {
            read_tmp = pins[i].read();
        }
        else {
            read_tmp = pins[i+3].read();
        }

        if(read_tmp > SEUIL) {
            etats_lisse[i] += 1;
        }

        etats[i] = '0';
        if(nb_sample >= 10) {
            if(etats_lisse[i] >= 10) {
                etats[i] = '1';
                etats_lisse[i] = 0;
            }
        }
    }
    if(nb_sample >= 10) {
        nb_sample = 0;
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
        flag_dbg = false;
        return false;
    }

    float calcul_x=x+30.*cos(alpha*M_PI/180);
    float calcul_y=y-30.*sin(alpha*M_PI/180);
    x_ob_dbg = calcul_x;
    y_ob_dbg = calcul_y;
    alpha_dbg = alpha;
    if (calcul_x >= 20 && calcul_y >= 20 && calcul_x <= 150 && calcul_y <= 180) {
        flag_dbg = true;
        return true;
    }
    else{
        flag_dbg = false;
        return false;
    }
}

char * update_debug_GP2() {
    if(flag_dbg == true) {
        // snprintf(debug_str_GP2, 256, "OBSTACLE\n");
        snprintf(debug_str_GP2, 256, "n:%d 1:%f 2:%f 3:%f xo:%f yo:%f a:%f\r\n",
                 nb_sample, gp2_a1.read(), gp2_a2.read(), gp2_a3.read(), x_ob_dbg, y_ob_dbg, alpha_dbg);
    }
    else {
        snprintf(debug_str_GP2, 256, "n:%d\n", nb_sample);
    }
    return debug_str_GP2;

}
