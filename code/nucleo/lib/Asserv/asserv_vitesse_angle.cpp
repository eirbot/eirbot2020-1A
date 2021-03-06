#include "mbed.h"
#include "encoder.hpp"
#include "asserv_vitesse_angle.hpp"

//coeff de correction odometrie
const float correc = 5/19.92;


// #define KP_Angle 0.00083// 0.00082 coefficient proportionnel Asserv Position (Angle)
// #define KI_Angle 0// 0.000008 coefficient intégral Asserv Position (Angle)
// #define KD_Angle 0//40//coefficient dérivé Asserv Position (Angle)
// #define KP_Angle 0.00175// 0.00175 coefficient proportionnel Asserv Position (Angle)
// #define KI_Angle 0.000001// 0.000001 coefficient intégral Asserv Position (Angle)
// #define KD_Angle 40//40//coefficient dérivé Asserv Position (Angle)
float KP_Angle = 0.00083;// 0.00082 coefficient proportionnel Asserv Position (Angle)
float KI_Angle =  0; // coefficient intégral Asserv Position (Angle)
float KD_Angle = 0;//40//coefficient dérivé Asserv Position (Angle)

void set_KA(float kp, float ki, float kd) {
  KP_Angle = kp;
  KI_Angle = ki;
  KD_Angle = kd;
}


void range(float*commande, int max, int min)
{
  if(*commande>max)
  {
    *commande=max;
  }
  if(*commande<min)
  {
    *commande=min;
  }
}
int interval_err(const float lim,const float err)
{
  return ((-lim<err) && (err<lim)); //return 1 si -lim<err<lim
}

void lecture_Wc1_Wc2(Encoder &Encoder_Gauche,Encoder &Encoder_Droit,float*Wc1,float*Wc2,const float Te)
{
  *Wc1=Encoder_Gauche.diff()*((2*PI)/(INC_ENCODER*Te));//vitesse angulaire endodeur 1 en rad/s
  *Wc2=Encoder_Droit.diff()*((2*PI)/(INC_ENCODER*Te)); //vitesse angulaire endodeur 2 en rad/s
}
void lecture_V_W(float*Vitesse,float*W,const float Wc1,const float Wc2)
{
  *Vitesse=((RW/2)*(Wc1+Wc2))*correc ;//vitesse robot en m/s
  *W=((RW/(2*RC))*(Wc2-Wc1))*correc; //vitesse angulaire robot m/s
}
void lecture_VG_VD(float*VG,float*VD,const float Wc1,const float Wc2)
{
  //*VG=((Vitesse)-((W)*RA)); //vitesse roue gauche m/s
  //*VD=(((W)*RA)+(Vitesse)); //vitesse roue droite m/s

  *VG=((((RW/2)*(Wc1+Wc2)))*correc-(((RW/(2*RC))*(Wc2-Wc1)*correc)*RA)); //vitesse roue gauche m/s
  *VD=((((RW/(2*RC))*(Wc2-Wc1)*correc)*RA)+((RW/2)*(Wc1+Wc2))*correc); //vitesse roue droite m/s
}

void lecture_Distance_Angle(const float Vitesse,const float W,const float Te,float *Distance, float *Angle, int reset)
{ 
  *Distance=((*Distance)+Vitesse*Te); //Distance parcourt par le robot
  *Angle=((*Angle)+W*Te); //Angle du robot
}


/*
  void get_posG(Encoder &Encoder_Gauche,int *posG)
  {
  int getG=0;
  static int SgetG=0;
  getG=Encoder_Gauche.get();
  if((getG>=OVERFLOW_ENCODEUR) || (getG<=-OVERFLOW_ENCODEUR)){
  SgetG=SgetG+getG;
  Encoder_Gauche.reset();
  }else{
  *posG=SgetG+getG;
  }
  }
  void get_posD(Encoder &Encoder_Droit,int *posD)
  {
  int getD=0;
  static int SgetD=0;
  getD=Encoder_Droit.get();
  if((getD>=OVERFLOW_ENCODEUR) || (getD<=-OVERFLOW_ENCODEUR)){
  SgetD=SgetD+getD;
  Encoder_Droit.reset();
  }else{
  *posD=SgetD+getD;
  }
  }
*/
float lissage(const float in,float tab[],int len)
{ 
  float Sum=0;
  for(int i=0; i<5; i++){
    tab[i]=tab[i+1];
  }
  tab[len-1]=in;
  for(int i=0; i<len; i++){
    Sum=Sum+tab[i];
  }
  return  (Sum/len);
}

float Asserv_V_MG(const float VG, const float ConsVG, int reset, float *ass_fbD)
{
  float Err=0;
  float static S_Err=0;
  float Commande=0;
  if(reset==1){
    S_Err=0;
    Commande=0;
  }else{
    Err=(ConsVG-VG);
    S_Err=S_Err+Err;
    range(&S_Err,MAX_LIM_ERR_INTE, MIN_LIM_ERR_INTE);
    Commande=KP_MG*Err+KI_MG*S_Err;
    if(Commande > 0) {
      Commande += 4;
    }
    else if(Commande < 0) {
      Commande -= 4;
    }
    else {
      Commande = 0;
    }
    range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
  }
  *ass_fbD = S_Err;
  return  Commande;
}

float Asserv_V_MD(const float VD, const float ConsVD,int reset, float *ass_fbG)
{
  float Err=0;
  float static S_Err=0;
  float Commande=0;
  if(reset==1){
    S_Err=0;
    Commande=0;
  }else{
    Err=(ConsVD-VD);
    S_Err=S_Err+Err;
    range(&S_Err,MAX_LIM_ERR_INTE, MIN_LIM_ERR_INTE);
    Commande=KP_MD*Err+KI_MD*S_Err;
    if(Commande > 0) {
      Commande += 4;
    }
    else if(Commande < 0) {
      Commande -= 4;
    }
    else {
      Commande = 0;
    }
    range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
  }
  *ass_fbG = S_Err;
  return  Commande;
}
float Asserv_Position(const float Position, const float ConsPosition,int reset,int *feedback)
{
  float Err=0;
  float static Err_old=0;
  float static diff_Err=0;
  float static S_Err=0;
  float Commande=0;
  if(reset==1){
    *feedback=0;
    S_Err=0;
    diff_Err=0;
    Err_old=0;
    Commande=0;
  }else{
    Err=ConsPosition-Position;
    diff_Err=Err-Err_old;
    Err_old=Err;
    *feedback=interval_err(LIM_ERR_DIS,Err);
    S_Err=S_Err+Err;
    range(&S_Err,MAX_LIM_ERR_INTE, MIN_LIM_ERR_INTE);
    Commande=KP_Pos*Err+KI_Pos*S_Err+KD_Pos*diff_Err;
    range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
  }
  return Commande;
}

float Asserv_Angle(const float Angle, const float ConsAngle,int reset,int *feedback)
{
  float Err=0;
  float static Err_old=0;
  float static diff_Err=0;
  float static S_Err=0;
  float Commande=0;
  
  if(reset==1){
    *feedback=0;
    S_Err=0;
    Commande=0;
    diff_Err=0;
    Err_old=0;
  }else{
    Err=ConsAngle-Angle;
    diff_Err = Err-Err_old;
    Err_old=Err;
    *feedback=interval_err(LIM_ERR_ANGLE,Err);
    S_Err=S_Err+Err;
    range(&S_Err,MAX_LIM_ERR_INTE, MIN_LIM_ERR_INTE);
    Commande=KP_Angle*Err+KI_Angle*S_Err+KD_Angle*diff_Err;
    range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
  }
  return Commande;
}
