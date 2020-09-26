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
PwmOut pwmMG(D5);
DigitalOut dirMG(D4);
DigitalOut breakMG(D3);
PwmOut pwmMD(D6);
DigitalOut dirMD(D2);
DigitalOut breakMD(D7);
Encoder Encoder_Droit=Encoder(TIM3);
Encoder Encoder_Gauche=Encoder(TIM4);
//Serial pc(SERIAL_TX, SERIAL_RX);
Serial pc(D1,D0);

volatile char   c = '\0'; // Initialized to the NULL character

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
void conCharReceived(void)
{
    c=pc.getc();
}



void function_Asserv(void)
{ T=T+Te;
  lecture_Wc1_Wc2(Encoder_Gauche,Encoder_Droit,&Wc1,&Wc2,Te);
  lecture_VG_VD(&VG,&VD,Wc1,Wc2);
  lecture_V_W(&Vitesse,&W,Wc1,Wc2);
  lecture_Distance_Angle(Vitesse,W,Te,&Distance,&Angle);
  commande_Dis = Asserv_Position(Distance,Cons_Dis,reset);
  commande_Angle = Asserv_Angle(Angle,Cons_Angle,reset);
  ConsVG=((commande_Dis/Te)-(commande_Angle/Te)*RA);
  ConsVD=((commande_Angle/Te)*RA)+((commande_Dis/Te));
  //ConsVG_liss=lissage(ConsVG,tab_lissage_MG,LEN_TAB_LISSAGE );
  //ConsVD_liss=lissage(ConsVD,tab_lissage_MD,LEN_TAB_LISSAGE );
  commande_PWMG_V=Asserv_V_MG(VG,ConsVG,reset);
  commande_PWMD_V=Asserv_V_MD(VD,ConsVD,reset);
}

  int main() 
{
  pwmMD.period(FREQ_MOTEUR);
  pwmMG.period(FREQ_MOTEUR);
  timer.start();
  //Vitesse=0.5;
  //W=0;
  //ConsVG=((Vitesse)-((W)*RA));
  //ConsVD=(((W)*RA)+(Vitesse));
  time_up.attach(&function_Asserv, Te);
  while(1) {
  pc.attach(&conCharReceived);
  if ( c=='\t') {
    Cons_Dis=1;
    Cons_Angle=(PI/180)*0;
   /* ConsV=0;
    ConsW=(PI/180)*90;
    ConsVG=ConsV-ConsW*RA;
    ConsVD=ConsW*RA+ConsV;*/
    //ConsVG=((ConsV*3.8)-((ConsW)*RA*1.95));
    //ConsVD=(((ConsW)*RA*1.95)+(ConsV*3.8));
    
  
    reset =0;
  }else if ( c=='s'){

    //commande_PWMG_V=0;
    //commande_PWMD_V=0;
    reset=1;
  }else{
    //commande_PWMG_V=0;
    //commande_PWMD_V=0;
    reset=1;
  }
  
  
  //pc.printf("%f\n\r",(Angle*(180/2*PI)));
  pc.printf("c==%c VG=%f VD=%f ConsVG=%f ConsVD=%f Vitesse=%f W=%f Distance=%f Angle=%f cmd_G=%f cmd_D=%f T=%f , Cons_Angle=%f, Angle=%f \n\r",c,VG,VD,ConsVG,ConsVD,Vitesse,W,Distance,(Angle*(180/PI)),commande_PWMG_V,commande_PWMD_V,T,Cons_Angle,Angle);
  //pc.printf("Wc1=%f Wc2=%f \n\r",Wc1,Wc2);
  //pc.printf("ec1=%d ec2=%d \n\r",Encoder_Gauche.get(),Encoder_Droit.get());
  //commande_PWMG=10;
  //commande_PWMD=10;
 
  dirMG=fonc_direction(commande_PWMG_V/100);
  pwmMG.write(abs(commande_PWMG_V/100));
  dirMD=fonc_direction(commande_PWMD_V/100);
  pwmMD.write(abs(commande_PWMD_V/100));
  }
}




