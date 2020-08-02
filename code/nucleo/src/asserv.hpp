#ifndef __ASSERV_
#define __ASSERV_
#include "mbed.h"
#ifndef PI
#define PI                 3.14159265358979f
#endif
#define COMMANDE_MAX 100
#define COMMANDE_MIN -100
float fonc_aserv_KP(const int lecture_vitesse, const int consigne, const float KP);
void asserv_vitesse_PI(const float KP, const float KI, const float Te, const float erreur, float *commande, float *Z1_in, float *Z1_out);
float gene_consPWM_sin(int freq, int offset, float gain, double t);
void limite(float*commande, int max, int min);
#endif //__ASSERV_

 // float *signal = (float *) malloc(sizeof(float)*10000);
 /*
  for(int i=0;i<=5000;i++){
      signal[i]=(sin(1000*2*PI*timer.read()));
    }
    for(int i=5000;i>=0;i--){
       pc.printf("%f;%f\n\r",timer.read(),signal[i]); 
    }
    while (1)
    {
     
    }
*/