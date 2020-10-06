#include "asserv.hpp"

// Timer timer;
Ticker time_up;
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
float ConsV=0;
float ConsW=0;
float ConsVG=0;
float ConsVD=0;
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
//dernière position absolue connue
float x_0=16;
float y_0=80;
float alpha0=0;
//debug x,y courant
float x;
float y;
//objectif
float Obj_Angle;
float Obj_Dist;



void init_asserv() {
    pwmMD.period(FREQ_MOTEUR);
    pwmMG.period(FREQ_MOTEUR);
    time_up.attach(&function_Asserv, Te);
    set_state(STOP);
}

void reset_asserv() {
    get_XY(&x_0, &y_0);
    alpha0 = alpha0 + Angle;
    reset = 1;
}

void set_pwm() {
    dirMG=fonc_direction(commande_PWMG_V/100);
    pwmMG.write(abs(commande_PWMG_V/100));
    dirMD=fonc_direction(commande_PWMD_V/100);
    pwmMD.write(abs(commande_PWMD_V/100));
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
    //ConsVG_liss=lissage(ConsVG,tab_lissage_MG,LEN_TAB_LISSAGE );
    //ConsVD_liss=lissage(ConsVD,tab_lissage_MD,LEN_TAB_LISSAGE );
    commande_PWMG_V=Asserv_V_MG(VG,ConsVG,reset);
    commande_PWMD_V=Asserv_V_MD(VD,ConsVD,reset);
    set_pwm();
    if(feedback_Angle == 1 || feedback_Dis == 1) update_state();
}


// TODO update consigne
void update_state() {
    if(etat_asserv == PO_ANGLE && feedback_Angle == 1) {
        set_state(PO_DISTANCE);
    }
    else if(etat_asserv == PO_DISTANCE && feedback_Dis == 1) {
        set_state(STOP);
    }
    else if (etat_asserv == ROT && feedback_Angle == 1) {
        set_state(STOP);
    }
    //pas de else, on garde l'état précédent
}

void set_state(enum asserv_state s) {
    reset_asserv();
    etat_asserv = s;
    switch(s) {
        case STOP:
            break;
        case ROT:
        case PO_ANGLE:
            Cons_Angle = Obj_Angle;
            break;
        case PO_DISTANCE:
            Cons_Dis = Obj_Dist;
            break;
    }
}



//---------- CONVERSION relatif/absolu -------------
float XY_to_Distance(float x, float y) {
    return sqrt(pow(x - x_0, 2) + pow(y - y_0, 2));
}

float XY_to_Angle(float x, float y) {
    return -atan2(y-y_0, x-x_0) - alpha0;
}

void get_XY(float *x, float *y) {
    *x = x_0 + Distance * cos(alpha0+Angle) * 100;
    *y = y_0 - Distance * sin(alpha0+Angle) * 100;
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
    //si on fait un angle de plus de 90 degre, on inverse le sens de marche du robot
    if(Obj_Angle > M_PI/2 || Obj_Angle < -M_PI/2) {
        Obj_Angle = Obj_Angle + M_PI;
        Obj_Dist = -Obj_Dist;
    }
}


/*
 * rotate
 * angle en deg
 */
void rotate(float angle) {
    Obj_Angle = alpha0 + angle;
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
        Cons_Dis=Distance;
        Cons_Angle=Angle;
        // reset_asserv(); quand on reset on prend pas en compte l'inertie...
    }
    else {
    }
}

void print_debug_asserv(Serial &pc,char c)
{
    // pc.printf("c==%c VG=%f VD=%f ConsVG=%f ConsVD=%f Vitesse=%f W=%f Distance=%f Angle=%f cmd_G=%f cmd_D=%f T=%f  \n\r",c,VG,VD,ConsVG,ConsVD,Vitesse,W,Distance,(Angle*(180/PI)),commande_PWMG_V,commande_PWMD_V,T);
    pc.printf("=========\r\n");
    pc.printf("c==%c Distance=%f Angle=%f  \n\r",
              c, Distance, (Angle*(180/PI)));
    get_XY(&x, &y);
    pc.printf("X0=%f Y0=%f\r\n", x_0, y_0);

    switch(etat_asserv) {
        case STOP:
            pc.printf("etat=STOP\r\n");
            break;
        case ROT:
            pc.printf("etat=ROT\r\n");
            break;
        case PO_ANGLE:
            pc.printf("etat=PO_ANGLE\r\n");
            break;
        case PO_DISTANCE:
            pc.printf("etat=PO_DISTANCE\r\n");
            break;
    }
    pc.printf("Err=%f fb_Dis=%d fb_Angle=%d\r\n\n",
              Cons_Dis-Distance, feedback_Dis, feedback_Angle);
    pc.printf("X=%f Y=%f\r\n", x, y);
    pc.printf("=========\r\n\n");
}
