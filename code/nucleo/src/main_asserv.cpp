//
// Created by CopperBot on 16/01/2020.
//
#include "mbed.h"
#include "encoder.hpp"
#include "moteur.hpp"
#include "asserv.hpp"
#include "asserv_vitesse_angle.hpp"
#include "math.h"
 
Timer timer;
Ticker time_up;
PwmOut pwmMD(D5);
DigitalOut dirMD(D4);
DigitalOut breakMD(D3);
PwmOut pwmMG(D6);
DigitalOut dirMG(D2);
DigitalOut breakMG(D7);
Encoder Encoder_Droit=Encoder(TIM4);
Encoder Encoder_Gauche=Encoder(TIM3);
//Serial pc(SERIAL_TX, SERIAL_RX);
Serial pc(D1,D0);

volatile char   c = '\0'; // Initialized to the NULL character

float Te=0.001;
float Wc1=0;
float Wc2=0;
float Vitesse=0;
float W=0;
float VD=0;
float VG=0;
float Distance=0;
float Angle=0;
float ConsVG=0;
float ConsVD=0;
float commande_PWMG=0;
float commande_PWMD=0;

void conCharReceived(void)
{
  c=pc.getc();
}

void function_Asserv(void)
{

  //lecture_V_W(&Vitesse,&W,Wc1,Wc2);
  //lecture_Distance_Angle(Vitesse,W,Te,&Distance,&Angle);
  lecture_Wc1_Wc2(Encoder_Gauche,Encoder_Droit,&Wc1,&Wc2,Te);
  //lecture_V_W(&Vitesse,&W,Wc1,Wc2);
  lecture_VG_VD(&VG,&VD,Wc1,Wc2);


  commande_PWMG=Asserv_V_MG(VG,ConsVG);
  commande_PWMD=Asserv_V_MD(VD,ConsVD);
  

  
}

int main() {

  pwmMD.period(FREQ_MOTEUR);
  pwmMG.period(FREQ_MOTEUR);
  timer.start();
  Vitesse=1.2;
  W=0;
  ConsVG=((Vitesse)-((W)*RA));
  ConsVD=(((W)*RA)+(Vitesse));
  //time_up.attach(&function_Asserv, Te);
  while(1) {
    pc.attach(&conCharReceived);
    pc.printf("VG=%f VD=%f errG=%f errD=%f\n\r",VG,VD,((ConsVG-VG)*100)/ConsVG,((ConsVD-VD)*100)/ConsVD);
    commande_PWMG=10;
    commande_PWMD=10;
    dirMG=fonc_direction(commande_PWMG/100);
    pwmMG.write(abs(commande_PWMG/100));
    dirMD=fonc_direction(commande_PWMD/100);
    pwmMD.write(abs(commande_PWMD/100));
  }

}
