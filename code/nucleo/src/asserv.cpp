#include "mbed.h"
#include "asserv.hpp"


float fonc_aserv_KP(const int lecture_vitesse, const int consigne, const float KP)
{
  float cmd=0;
  cmd=(consigne-lecture_vitesse)*KP;
  
  if(cmd < 0) cmd=0;
  else if(cmd > 1) cmd = 1;
  return cmd;
}
void limite(float*commande, int max, int min)
{
  if(*commande>max)*commande=max;
  if(*commande<min)*commande=min;
}
void asserv_vitesse_PI(const float KP, const float KI, const float Te, const float erreur, float *commande, float *Z1_in, float *Z1_out)
{
  float a1=(2*KP-KI*Te)/2;
  float a0=(2*KP+KI*Te)/2;
  *commande=(*Z1_out+((erreur*a0)+(a1*(*Z1_in))));
  limite(commande,100,-100);
  *Z1_out=*commande;
  *Z1_in=erreur;
 
}

float gene_consPWM_sin(int freq, int offset, float gain, double t)
{
   return ((gain*sin(2*PI*freq*t))+offset);
}


//pwmMoteur.write(consigne_PWM);
   // pwmMoteur.write(0.20);