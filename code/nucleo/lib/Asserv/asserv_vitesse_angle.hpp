#ifndef __ASSERV_VITESSE_ANGLE
#define __ASSERV_VITESSE_ANGLE

#define PI 3.1415926535
#define INC_ENCODER 1000//nombre increment pour un tour d'encodeur
#define MAX_LIM_ERR_INTE 10000000
#define MIN_LIM_ERR_INTE -10000000
#define MAX_LIM_COMMANDE  100 //100
#define MIN_LIM_COMMANDE -100 //-100
#define OVERFLOW_ENCODEUR 32500
#define LEN_TAB_LISSAGE 15 //6
#define LIM_ERR_DIS 0.002 //0.2
#define LIM_ERR_ANGLE (PI/180)*1 //0.2

#define RA 0.074 //distance entre point milieu et la roue en mètre
#define RC 0.135 //distance entre point milieu et l'encodeur en mètre
#define RR 0.0312 //rayon de la roue en mètre
#define RW 0.01532 //rayon de l'encodeur en mètre

#define K1  (RW/RR) //simplification 1
#define K2  ((RW*RA)/(RR*RC)) //simplification 2

//nouvelle asserv
// #define KP_MG 14//14 //coefficient proportionnel Asserv Vitesse Moteur Gauche
// #define KI_MG 0.15//0.15  //coefficient intégral Asserv Vitesse Moteur Gauche
// #define KP_MD 14//14 //coefficient proportionnel Asserv Vitesse Moteur Droit
// #define KI_MD 0.15//0.15 //coefficient intégral  Asserv Vitesse Moteur Droit

// #define KP_Pos   0.00175 //0.0007 coefficient proportionnel Asserv Position (Distance)
// #define KI_Pos   0//0 coefficient intégral Asserv Position (Distance)
// #define KD_Pos   1//1 coefficient dérivé Asserv Position (Distance)
// #define KP_Angle 0.00175// 0.00175 coefficient proportionnel Asserv Position (Angle)
// #define KI_Angle 0.000001// 0.000001 coefficient intégral Asserv Position (Angle)
// #define KD_Angle 40//40//coefficient dérivé Asserv Position (Angle)

//ancienne asserv
// #define KP_MG 18//18 //coefficient proportionnel Asserv Vitesse Moteur Gauche
// #define KI_MG 0.15//0.15  //coefficient intégral Asserv Vitesse Moteur Gauche
// #define KP_MD 18//18 //coefficient proportionnel Asserv Vitesse Moteur Droit
// #define KI_MD 0.15//0.15 //coefficient intégral  Asserv Vitesse Moteur Droit

// #define KP_Pos  0.0007 //0.0007 coefficient proportionnel Asserv Position (Distance)
// #define KI_Pos 0//coefficient intégral Asserv Position (Distance)
// #define KD_Pos 0//coefficient intégral Asserv Position (Distance)
// #define KP_Angle 0.00083// 0.00082 coefficient proportionnel Asserv Position (Angle)
// #define KI_Angle 0// 0.000008 coefficient intégral Asserv Position (Angle)
// #define KD_Angle 0//40//coefficient dérivé Asserv Position (Angle)

//asserv courante
#define KP_MG 18//18 //coefficient proportionnel Asserv Vitesse Moteur Gauche
#define KI_MG 0.15//0.15  //coefficient intégral Asserv Vitesse Moteur Gauche
#define KP_MD 18//18 //coefficient proportionnel Asserv Vitesse Moteur Droit
#define KI_MD 0.15//0.15 //coefficient intégral  Asserv Vitesse Moteur Droit

#define KP_Pos  0.0007 //0.0007 coefficient proportionnel Asserv Position (Distance)
#define KI_Pos 0 //coefficient intégral Asserv Position (Distance)
#define KD_Pos 0 //coefficient intégral Asserv Position (Distance)
// #define KP_Angle 0.00070 // 0.00175 coefficient proportionnel Asserv Position (Angle)
// #define KI_Angle 0.000001 // 0.000001 coefficient intégral Asserv Position (Angle)
// #define KD_Angle 10 //40//coefficient dérivé Asserv Position (Angle)
#define KP_Angle 0.00083// 0.00082 coefficient proportionnel Asserv Position (Angle)
#define KI_Angle 0 // coefficient intégral Asserv Position (Angle)
#define KD_Angle 0//40//coefficient dérivé Asserv Position (Angle)

void range(float*commande, int max, int min); //limite la plage d'une valeur entre min et max
int interval_err(const float lim,const float err);//Renvoie 1 si l'erreur est dans l'intervalle
void lecture_Wc1_Wc2(Encoder &Encoder_Gauche,Encoder &Encoder_Droit,float*Wc1,float*Wc2,const float Te); //lecture des encodeur Gauche et Droit au rythme Te
void lecture_V_W(float*Vitesse,float*W,const float Wc1,const float Wc2); //lecture de la vitesse et de la vitesse angulaire, en fonction des vitesse angulaire encodeur Wc1 et Wc2
void lecture_VG_VD(float*VG,float*VD,const float Vitesse,const float W); //lectute de la vitesse du moteur gauche et droit 
void lecture_Distance_Angle(const float Vitesse,const float W,const float Te,float *Distance, float *Angle, int reset); //lecture de la distance parcourue, et de l'angle parcourue
void get_posG(Encoder &Encoder_Gauche,int *posG); //supprime l'overflow à -32,768; 32,767 inc 
void get_posD(Encoder &Encoder_Droit,int *posD);  //supprime l'overflow à -32,768; 32,767 inc
float Asserv_V_MG(const float VG, const float ConsVG,int reset); //Asserv de Vitesse Moteur Gauche
float Asserv_V_MD(const float VD, const float ConsVD,int reset); //Asserv de Vitesse Moteur Droit
float Asserv_Position(const float Position, const float ConsPosition,int reset,int *feedback); //Asserv de Position Distance
float Asserv_Angle(const float Angle, const float ConsAngle,int reset,int *feedback); //Asserv de Position Angle
float lissage(const float in,float tab[],int len);//Permet de crée une rampe sur le front des commandes de vitesse
#endif // __ASSERV_VITESSE_ANGLE
