#include "mbed.h"
#include "encoder.hpp"
#include "asserv_vitesse_angle.hpp"

//coeff de correction odometrie
const float correc = 5/19.92;

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
  if (reset==1){
    *Distance =0;
    *Angle=0;
  }else{
    *Distance=((*Distance)+Vitesse*Te); //Distance parcourt par le robot
    *Angle=((*Angle)+W*Te); //Angle du robot
  }
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

float Asserv_V_MG(const float VG, const float ConsVG, int reset)
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
    range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
  }
  return  Commande;
}

float Asserv_V_MD(const float VD, const float ConsVD,int reset)
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
    range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
  }
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
