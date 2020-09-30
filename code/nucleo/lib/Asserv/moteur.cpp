#include "mbed.h"
#include "moteur.hpp"


float abs_PWM (float consigne_PWM )
{
    if(consigne_PWM<0) {
      return -consigne_PWM;
    } else {
       return consigne_PWM;
    }
}

int fonc_direction(const float consigne)
{
    if(consigne>=0.0f){
       return 1; 
    } 
    else{
       return 0; 
    }
    
}

/*
void conCharReceived(Serial &pc,char **c)
{
    *c=atoi(pc.getc());
    
}
void commande_pc(Serial &pc,char c,float *consigne_vitesseG, float*consigne_vitesseD)
{
   pc.attach(&conCharReceived);
    if ( c=='\t') {
      *consigne_vitesseG =0;
      *consigne_vitesseD =0;
    }else if ( c=='z') {
      *consigne_vitesseG =VMOY;
      *consigne_vitesseD =VMOY;
    }else if(c=='b'){
      *consigne_vitesseG =-VMAX;
      *consigne_vitesseD =VMAX;
    }else if(c=='v'){
      *consigne_vitesseG =VMAX;
      *consigne_vitesseG =VMAX;
    }else if ( c=='d') {
      *consigne_vitesseG =VMOY;
      *consigne_vitesseD=-VMOY;    
    }else if ( c=='q') {
      *consigne_vitesseG =-VMOY;
      *consigne_vitesseD =VMOY;
    }
    else if ( c=='s') {
      *consigne_vitesseG =-VMOY;
      *consigne_vitesseD =-VMOY;
    }else {
       *consigne_vitesseG =0;//gene_consPWM_sin(2,0,0.2,i);
       *consigne_vitesseD =0;//gene_consPWM_sin(2,0,0.2,i);
    }
}
*/