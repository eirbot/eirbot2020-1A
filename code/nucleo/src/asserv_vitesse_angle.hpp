#ifndef __ASSERV_VITESSE_ANGLE
#define __ASSERV_VITESSE_ANGLE

#define RA 0.0763 //distance entre point milieu et la roue m
#define RC 0.13909 //distance entre point milieu et l'encodeur m
#define RR 0.0312 //rayon de la roue m
#define RW 0.01532 //rayon de l'encodeur m
#define INC_ENCODER 1024//nombre increment pour un tour d'encodeur
#define PI 3.1415926535
#define K1  (RW/RR)
#define K2  ((RW*RA)/(RR*RC))
#define KP_MG 15//15
#define KI_MG 0.05//0.05
#define KP_MD 15//15
#define KI_MD 0.05//0.05
#define KP_P 0
#define KI_P 0
#define KP_A 0
#define KI_A 0
void range(float*commande, int max, int min);
void lecture_Wc1_Wc2(Encoder &Encoder_Gauche,Encoder &Encoder_Droit,float*Wc1,float*Wc2,const float Te);
void lecture_V_W(float*Vitesse,float*W,const float Wc1,const float Wc2); 
void lecture_VG_VD(float*VG,float*VD,const float Vitesse,const float W);
void lecture_Distance_Angle(const float Vitesse,const float W,const float Te,float *Distance, float *Angle);
void get_posG(Encoder &Encoder_Gauche,int *posG);
void get_posD(Encoder &Encoder_Droit,int *posD);
float Asserv_V_MG(const float VG, const float ConsVG);
float Asserv_V_MD(const float VD, const float ConsVD);
float Asserv_Position(const float Position, const float ConsPosition);
float Asserv_Angle(const float Angle, const float ConsAngle);
#endif // __ASSERV_VITESSE_ANGLE