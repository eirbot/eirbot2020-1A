#include "asserv.hpp"

Timer timer;
Ticker time_up;
PwmOut pwmMG(D5);
DigitalOut dirMG(D4);
DigitalOut breakMG(D3);
PwmOut pwmMD(D6);
DigitalOut dirMD(D2);
DigitalOut breakMD(D7);
Encoder Encoder_Droit=Encoder(TIM3);
Encoder Encoder_Gauche=Encoder(TIM4);

float Te=0.001;
float T=0;
float Wc1=0;
float Wc2=0;
float Vitesse=0;
float W=0;
float VD=0;
float VG=0;
float Distance=0;
float Angle=0;
float Distance_ABS=0;
float Angle_ABS=0;
float ConsV=0;
float ConsW=0;
float ConsVG=0;
float ConsVD=0;
float Cons_Dis=0;
float Cons_Angle=0;
float commande_Dis=0;
float commande_Angle=0;
float commande_PWMG_V;
float commande_PWMD_V;
float tab_lissage_MG[LEN_TAB_LISSAGE] ={0};
float tab_lissage_MD[LEN_TAB_LISSAGE] ={0};
float ConsVG_liss=0;
float ConsVD_liss=0;
int  reset =0;
int feedback_Angle=0;
int feedback_Dis =0;

void init_asserv() {
    pwmMD.period(FREQ_MOTEUR);
    pwmMG.period(FREQ_MOTEUR);
    timer.start();
    time_up.attach(&function_Asserv, Te);
}

void set_pwm() {
    dirMG=fonc_direction(commande_PWMG_V/100);
    pwmMG.write(abs(commande_PWMG_V/100));
    dirMD=fonc_direction(commande_PWMD_V/100);
    pwmMD.write(abs(commande_PWMD_V/100));
}

void function_Asserv(void)
{
    T=T+Te;
    lecture_Wc1_Wc2(Encoder_Gauche,Encoder_Droit,&Wc1,&Wc2,Te);
    lecture_VG_VD(&VG,&VD,Wc1,Wc2);
    lecture_V_W(&Vitesse,&W,Wc1,Wc2);
    lecture_Distance_Angle(Vitesse,W,Te,&Distance,&Angle,reset);
    commande_Dis = Asserv_Position(Distance,Cons_Dis,reset,feedback_Dis);
    commande_Angle = Asserv_Angle(Angle,Cons_Angle,reset,feedback_Angle);
    ConsVG=((commande_Dis/Te)-(commande_Angle/Te)*RA);
    ConsVD=((commande_Angle/Te)*RA)+((commande_Dis/Te));
    //ConsVG_liss=lissage(ConsVG,tab_lissage_MG,LEN_TAB_LISSAGE );
    //ConsVD_liss=lissage(ConsVD,tab_lissage_MD,LEN_TAB_LISSAGE );
    commande_PWMG_V=Asserv_V_MG(VG,ConsVG,reset);
    commande_PWMD_V=Asserv_V_MD(VD,ConsVD,reset);
}

void set_consigne(char c) {
    if ( c=='g') {
        Cons_Dis=1;
        Cons_Angle=(PI/180)*0;
        reset=0;
    }
    else if ( c=='r'){
        Cons_Dis=0;
        Cons_Angle=(PI/180)*90;
        reset=0;
    }
    else if (c=='s'){
        Cons_Dis=0;
        Cons_Angle=(PI/180)*0;
        Angle = 0;
        Distance = 0;
        reset=1;
    }
    else {
        reset=1;
    }
    
}
void print_debug_asserv(Serial &pc,char c)
{
    pc.printf("c==%c VG=%f VD=%f ConsVG=%f ConsVD=%f Vitesse=%f W=%f Distance=%f Angle=%f cmd_G=%f cmd_D=%f T=%f  \n\r",c,VG,VD,ConsVG,ConsVD,Vitesse,W,Distance,(Angle*(180/PI)),commande_PWMG_V,commande_PWMD_V,T);
}

/*
 * go_XY
 * xd, yd : destination (coordonnee depuis rasp)
 * x0, y0 : precedente coordonnee du robot
 * alpha0 : precedent angle
 * distance, angle : resultat de la transformation (angle en radian)
 * char inversion 1=devant du robot devient le derriere
 */
void go_XY(int xd, int yd, int x0, int y0, int alpha0,
           float *distance, float *angle, char *direction) {
    *distance = sqrt(pow(xd - x0, 2) + pow(yd - y0, 2));
    *angle = -atan2(yd-y0, xd-x0) - alpha0;
    // *direction = 0;
    //si on fait un angle de plus de 90 degre, on inverse le sens de marche du robot
    // if(*angle > M_PI/2 || *angle < -M_PI/2) {
    //     *angle = *angle + M_PI;
    //     *direction = 1;
    // }
}
