#include "mbed.h"
#include "encoder.hpp"
#include "asserv_vitesse_angle.hpp"

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

void lecture_Wc1_Wc2(Encoder &Encoder_Gauche,Encoder &Encoder_Droit,float*Wc1,float*Wc2,const float Te)
{
    *Wc1=(Encoder_Gauche.diff()*((2*PI)/INC_ENCODER))/Te;//vitesse angulaire endodeur 1 en rad/s
    *Wc2=(Encoder_Droit.diff()*((2*PI)/INC_ENCODER))/Te; //vitesse angulaire endodeur 2 en rad/s
}
void lecture_V_W(float*Vitesse,float*W,const float Wc1,const float Wc2)
{
    *Vitesse=(RW/2)*(Wc1+Wc2);//vitesse robot en cm/s
    *W=(RW/(2*RC))*(Wc2-Wc1); //vitesse angulaire robot rad/s
}
void lecture_VG_VD(float*VG,float*VD,const float Wc1,const float Wc2)
{
    //*VG=((Vitesse)-((W)*RA)); //vitesse roue gauche cm/s
    //*VD=(((W)*RA)+(Vitesse)); //vitesse roue droite cm/s

    *VG=(((RW/2)*(Wc1+Wc2))-(((RW/(2*RC))*(Wc2-Wc1))*RA)); //vitesse roue gauche cm/s
    *VD=((((RW/(2*RC))*(Wc2-Wc1))*RA)+((RW/2)*(Wc1+Wc2))); //vitesse roue droite cm/s
}
void lecture_Distance_Angle(const float Vitesse,const float W,const float Te,float *Distance, float *Angle)
{
    *Distance=((*Distance)+Vitesse*Te); //Distance parcourt par le robot
    *Angle=((*Angle)+W*Te); //Angle du robot
}

void get_posG(Encoder &Encoder_Gauche,int *posG)
{
   int getG=0;
   static int SgetG=0;
   getG=Encoder_Gauche.get();
  if((getG>=32500) || (getG<=-32500)){
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
  if((getD>=32500) || (getD<=-32500)){
    SgetD=SgetD+getD;
    Encoder_Droit.reset();
  }else{
    *posD=SgetD+getD;
  }
}


float Asserv_V_MG(const float VG, const float ConsVG)
{
    float Err=0;
    float static S_Err=0;
    float Commande=0;
    Err=ConsVG-VG;
    S_Err=S_Err+Err;
    range(&S_Err,10000000,-10000000);
    Commande=KP_MG*Err+KI_MG*S_Err;
    range((&Commande),100,-100);
    return  Commande;
}

float Asserv_V_MD(const float VD, const float ConsVD)
{
    float Err=0;
    float static S_Err=0;
    float Commande=0;
    Err=ConsVD-VD;
    S_Err=S_Err+Err;
    range(&S_Err,10000000,-10000000);
    Commande=KP_MD*Err+KI_MD*S_Err;
    range((&Commande),100,-100);
    return  Commande;
}
float Asserv_Position(const float Position, const float ConsPosition)
{
  float Err=0;
  float static S_Err=0;
  float Commande=0;
  S_Err=S_Err+Err;
  range(&S_Err,10000000,-10000000);
  Commande=KP_P*Err+KI_P*S_Err;
  range((&Commande),100,-100);
  return Commande;
}

float Asserv_Angle(const float Angle, const float ConsAngle)
{
  float Err=0;
  float static S_Err=0;
  float Commande=0;
  S_Err=S_Err+Err;
  range(&S_Err,10000000,-10000000);
  Commande=KP_A*Err+KI_A*S_Err;
  range((&Commande),100,-100);
  return Commande;
}