#include "asserv.hpp"

// Timer timer;
Ticker time_up;
Timeout timeout_po_stop;
PwmOut pwmMG(D5);
DigitalOut dirMG(D4);
DigitalOut breakMG(D3);
PwmOut pwmMD(D6);
DigitalOut dirMD(D2);
DigitalOut breakMD(D7);
Encoder Encoder_Droit=Encoder(TIM3);
Encoder Encoder_Gauche=Encoder(TIM4);

// ### Variables internes ###
float Te=0.001;
float Wc1=0;
float Wc2=0;
float Vitesse=0;
float W=0;
float VD=0;
float VG=0;
// Distance et Angle relatif au robot
float Distance=0;
float Angle=0;
float old_Distance=0;
float old_Angle=0;
float ConsV=0;
float ConsW=0;
float ConsVG=0;
float ConsVD=0;
float old_ConsVG=0;
float old_ConsVD=0;
float aG, aD;
float aG_max_tmp = 0; //TODO a retirer
float commande_Dis=0;
float commande_Angle=0;
float commande_PWMG_V;
float commande_PWMD_V;
float tab_lissage_MG[LEN_TAB_LISSAGE] ={0};
float tab_lissage_MD[LEN_TAB_LISSAGE] ={0};
float ConsVG_liss=0;
float ConsVD_liss=0;

// ### Consignes et feedback ###
// Distance et Angle désirés
// il en faut toujours un nul
// on ne fait pas deux type de mouvement en meme temps
float Cons_Dis=0;
float Cons_Angle=0;
// reset = 1 -> Distance = 0 et Angle = 0 et roue libre
int reset = 0;
// feedback_* = 1 -> robot arrivé à la consigne
int feedback_Angle = 0;
int feedback_Dis = 0;

// ### FSM et coordonnées absolues ###
enum asserv_state etat_asserv;
enum asserv_state precedent_etat_asserv;
//dernière position absolue connue
float x_0=0.16;
float y_0=0.80;
float alpha0=0;
//debug x,y courant
float x;
float y;
//objectif
float Obj_Angle;
float Obj_Dist;

char debug_string[256];


// ------ asservissement --------
void init_asserv() {
    pwmMD.period(FREQ_MOTEUR);
    pwmMG.period(FREQ_MOTEUR);
    time_up.attach(&function_Asserv, Te);
    set_state(RES);
}


void set_pwm() {
    if(commande_PWMD_V != 0) commande_PWMD_V += 4;
    if(commande_PWMG_V != 0) commande_PWMG_V += 4;
    dirMG=fonc_direction(commande_PWMG_V/100); //TODO offset 3 quand != 0
    pwmMG.write(abs(commande_PWMG_V/100));
    dirMD=fonc_direction(commande_PWMD_V/100);
    pwmMD.write(abs(commande_PWMD_V/100));
}


int sign(float x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void function_Asserv(void)
{
    lecture_Wc1_Wc2(Encoder_Gauche,Encoder_Droit,&Wc1,&Wc2,Te);
    lecture_VG_VD(&VG,&VD,Wc1,Wc2);
    lecture_V_W(&Vitesse,&W,Wc1,Wc2);
    lecture_Distance_Angle(Vitesse,W,Te,&Distance,&Angle,reset);
    commande_Dis = Asserv_Position(Distance,Cons_Dis,reset,&feedback_Dis);
    commande_Angle = Asserv_Angle(Angle,Cons_Angle,reset,&feedback_Angle);
    ConsVG=((commande_Dis/Te)-(commande_Angle/Te)*RA);
    ConsVD=((commande_Angle/Te)*RA)+((commande_Dis/Te));

    //limiteur acceleration
    aG = ConsVG - old_ConsVG;
    aD = ConsVD - old_ConsVD;
    aG_max_tmp = max(aG_max_tmp, aG);
    if(abs(aG) > A_MAX) {
        ConsVG = old_ConsVG + sign(aG)*A_MAX;
    }
    if(abs(aD) > A_MAX) {
        ConsVD = old_ConsVD + sign(aD)*A_MAX;
    }

    old_ConsVG = ConsVG;
    old_ConsVD = ConsVD;
    //ConsVG_liss=lissage(ConsVG,tab_lissage_MG,LEN_TAB_LISSAGE );
    //ConsVD_liss=lissage(ConsVD,tab_lissage_MD,LEN_TAB_LISSAGE );
    commande_PWMG_V=Asserv_V_MG(VG,ConsVG,reset);
    commande_PWMD_V=Asserv_V_MD(VD,ConsVD,reset);
    set_pwm();
    if(feedback_Angle == 1 || feedback_Dis == 1) update_state();
}

void reset_consigne() {
    Cons_Dis = 0;
    Cons_Angle = 0;
    Distance = 0;
    Angle = 0;
    old_Distance = 0;
    old_Angle = 0;
}

// ---------- FSM -----------
// gere les transitions
void update_state() {
    if(etat_asserv == PO_ANGLE && feedback_Angle == 1) {
        set_state(PO_STOP); //on laisse stabiliser, on quittera l'état grace au timeout
        timeout_po_stop.attach(&set_state_distance, 0.1);
    }
    // else if(etat_asserv == PO_STOP && feedback_Angle == 1 && feedback_Dis == 1) {
    //     set_state(PO_DISTANCE);
    // }
    else if(etat_asserv == PO_DISTANCE && feedback_Dis == 1) {
        set_state(STOP);
    }
    else if (etat_asserv == ROT && feedback_Angle == 1) {
        set_state(STOP);
    }
    // else if (etat_asserv == STOP && feedback_Angle == 1 && feedback_Dis == 1) {
    //     set_state(RES);
    // }
    //pas de else, on garde l'état précédent
}

void set_state_distance(void) { //void void pour un callback
    set_state(PO_DISTANCE);
}

void set_state(enum asserv_state s) {
    precedent_etat_asserv = etat_asserv;
    etat_asserv = s;
    reset = 0;
    switch(s) {
        case PO_STOP:
        case STOP:
            get_XY(&x_0, &y_0);
            alpha0 = alpha0 + Angle - old_Angle;
            old_Distance = Distance;
            old_Angle = Angle;
            //reset_consigne();
            //reset=1;
            // Cons_Dis = Distance; //prend les parametres courants comme consigne
            // Cons_Angle = Angle;
            break;
        case ROT:
        case PO_ANGLE:
            Cons_Angle += Obj_Angle;
            break;
        case PO_DISTANCE:
            Cons_Dis += Obj_Dist;
            break;
        case RES:
            reset = 1;
            reset_consigne();
            commande_PWMD_V=0;
            commande_PWMG_V=0;
            x_0=0.16;
            y_0=0.80;
            alpha0=0;
            break;
    }
}

enum asserv_state get_state(void) {
    return etat_asserv;
}


//---------- CONVERSION relatif/absolu -------------
//XY en m, return en m
float XY_to_Distance(float x, float y) {
    return sqrt(pow(x - x_0, 2) + pow(y - y_0, 2));
}

//XY en m, return en radiannnnns
float XY_to_Angle(float x, float y) {
    float alpha = (-atan2(y-y_0, x-x_0) - alpha0);
    // if(abs(alpha) > M_PI) {
    //     return -signbit(alpha)*(2*M_PI-alpha);
    // }
    // else {
    //     return alpha;
    // }
    return alpha;
}

//XY en m
void get_XY(float *x, float *y) {
    *x = x_0 + (Distance - old_Distance) * cos(alpha0+Angle-old_Angle);
    *y = y_0 - (Distance - old_Distance) * sin(alpha0+Angle-old_Angle);
}

//angle en degré
float get_angle() {
    return (alpha0 + Angle - old_Angle)*180/M_PI; //Angle=0 normalement
}

//---------- deplacement -------------
/*
 * go_XY
 * x_dest, y_dest : destination (coordonnee depuis rasp) (en m)
 */
void go_XY(float x_dest, float y_dest) {
    Obj_Dist = XY_to_Distance(x_dest, y_dest);
    Obj_Angle = XY_to_Angle(x_dest, y_dest);
    set_state(PO_ANGLE);
    // //si on fait un angle de plus de 90 degre, on inverse le sens de marche du robot
    // if(Obj_Angle > M_PI/2 || Obj_Angle < -M_PI/2) {
    //     Obj_Angle = Obj_Angle + M_PI;
    //     Obj_Dist = -Obj_Dist;
    // }
    // pose problème pour savoir où sont les actionneurs lol
}

//angle en degrés
void rotate(float angle) {
    Obj_Angle = (alpha0 + angle)*M_PI/180;
    Obj_Dist = 0;
    set_state(ROT);
}

//--------- DEBUG ------------
void set_consigne(char c) {
    if ( c=='z') {
        Cons_Dis=0.5;
        Cons_Angle=(PI/180)*0;
        reset=0;
    }
    else if ( c=='s') {
        Cons_Dis=-0.5;
        Cons_Angle=(PI/180)*0;
        reset=0;
    }
    else if ( c=='q'){
        Cons_Dis=0;
        Cons_Angle=(PI/180)*90;
        reset=0;
    }
    else if ( c=='d'){
        Cons_Dis=0;
        Cons_Angle=(PI/180)*-90;
        reset=0;
    }
    else if (c==' '){
        get_XY(&x_0, &y_0);
        alpha0 = alpha0 + Angle;
        commande_PWMD_V=0;
        commande_PWMG_V=0;
        Distance = 0;
        Angle = 0;
        Cons_Dis=Distance;
        Cons_Angle=Angle;
        reset = 1;
    }
    else if (c=='r'){
        reset = 1;
        get_XY(&x_0, &y_0);
        alpha0 = alpha0 + Angle;
        Cons_Dis = 0;
        Cons_Angle = 0;
        Distance = 0;
        Angle = 0;
    }
    else if (c=='1') {
        go_XY(0.30, 0.90);
    }
    else if (c=='2') {
        go_XY(0.80, 0.90);
    }
}

char * update_debug_string() {
    // char etat_str[16];
    // switch(etat_asserv) {
    //     case STOP:
    //         strncpy(etat_str, "STOP", 16);
    //         break;
    //     case ROT:
    //         strncpy(etat_str, "ROT", 16);
    //         break;
    //     case PO_ANGLE:
    //         strncpy(etat_str, "PO_ANG", 16);
    //         break;
    //     case PO_STOP:
    //         strncpy(etat_str, "PO_STOP", 16);
    //         break;
    //     case PO_DISTANCE:
    //         strncpy(etat_str, "PO_DIS", 16);
    //         break;
    //     case RES:
    //         strncpy(etat_str, "RES", 16);
    //         break;
    // }
    // snprintf(debug_string, 256,
    //          "x_0=%4.2f y_0=%4.2f alpha_0=%4.2f Obj_Dist=%4.2f Obj_Angle=%5.2f Dist=%4.2f Angle=%4.2f fb_Dis=%1d fb_Angle=%1d etat=%6s ",
    //          x_0, y_0, alpha0, Obj_Dist, Obj_Angle, Distance, Angle, feedback_Dis, feedback_Angle, etat_str);

    snprintf(debug_string, 256, "ConsVG=%5.3f ConsVD=%5.3f D=%5.3f A=%5.3f OD=%5.3f OA=%5.3f\r\n", ConsVG, ConsVD, Distance-old_Distance, Angle - old_Angle, Obj_Dist, Obj_Angle);
    return debug_string;

}

void print_debug_asserv(Serial &pc,char c)
{
    pc.printf("aG_max=%5.3f aG=%5.3f aD=%5.3f VG=%5.3f VD=%5.2f\r\n", aG_max_tmp, aG, aD, VG, VD);
    // pc.printf("c==%c VG=%f VD=%f ConsVG=%f ConsVD=%f Vitesse=%f W=%f Distance=%f Angle=%f cmd_G=%f cmd_D=%f T=%f  \n\r",c,VG,VD,ConsVG,ConsVD,Vitesse,W,Distance,(Angle*(180/PI)),commande_PWMG_V,commande_PWMD_V,T);
    // pc.printf("c==%c Distance=%f Angle=%f  ",
    //           c, Distance, (Angle*(180/PI)));
    // get_XY(&x, &y);
    // pc.printf("Obj_Dist=%f Obj_Angle=%f ", Obj_Dist, Obj_Angle);
    // pc.printf("X0=%f Y0=%f alpha0=%f ", x_0, y_0, alpha0*180/PI);

    // switch(etat_asserv) {
    //     case STOP:
    //         pc.printf("etat=STOP ");
    //         break;
    //     case ROT:
    //         pc.printf("etat=ROT ");
    //         break;
    //     case PO_ANGLE:
    //         pc.printf("etat=PO_ANGLE ");
    //         break;
    //     case PO_DISTANCE:
    //         pc.printf("etat=PO_DISTANCE ");
    //         break;
    //     case RES:
    //         pc.printf("etat=RES ");
    //         break;
    // }
    // pc.printf("Err=%f fb_Dis=%d fb_Angle=%d ",
    //           Cons_Dis-Distance, feedback_Dis, feedback_Angle);
    // pc.printf("X=%f Y=%f \r\n", x*100, y*100);
}
