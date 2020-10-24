#include <ServoTimer2.h>
#include <VirtualWire.h>

ServoTimer2 ServoBas1;
ServoTimer2 ServoBas2;
ServoTimer2 ServoCentre;
ServoTimer2 ServoHaut;

//Cablage
#define SERVOPinBas1 9
#define SERVOPinBas2 8
#define SERVOPinCentre 7
#define SERVOPinHaut 6
#define POTAR 5
#define MOTEUR 5

//Seuils pour les valeurs limites du potar et des servos
#define SEUIL_POTAR_BAS 150
#define SEUIL_POTAR_HAUT 500

#define SEUIL_HAUT_BAS1 30
#define SEUIL_BAS_BAS1 200
#define SEUIL_INTER_BAS1 (SEUIL_HAUT_BAS1 + SEUIL_BAS_BAS1)/2 - 30

#define SEUIL_HAUT_BAS2 152
#define SEUIL_BAS_BAS2 0

#define SEUIL_HAUT_CENTRE 50  //delta = -62
#define SEUIL_BAS_CENTRE 110
#define SEUIL_INTER_CENTRE 180

#define SEUIL_HAUT_HAUT 100  //delta = +96
#define SEUIL_BAS_HAUT 10
#define SEUIL_INTER_HAUT 140

//Etats du bras
#define BAS 0
#define HAUT 1

bool etat = BAS;   //Memoire de l'etat du bras
const char msg[8] = "31415926";   //Message envoyé par le phare pour confirmer l'ascention

int vitesse = 10; //en millisecondes

void setup() {
  ServoBas1.attach(SERVOPinBas1);
  ServoBas2.attach(SERVOPinBas2);
  ServoCentre.attach(SERVOPinCentre);
  ServoHaut.attach(SERVOPinHaut);

  ServoBas1.writeServo(SEUIL_BAS_BAS1);
  ServoBas2.writeServo(SEUIL_BAS_BAS2);
  ServoCentre.writeServo(SEUIL_BAS_CENTRE);
  ServoHaut.writeServo(SEUIL_BAS_HAUT);
  
  pinMode(MOTEUR, OUTPUT);
  digitalWrite(MOTEUR, LOW);

  vw_setup(2000);
  
  delay(1000);
}

void loop() {
  int val = analogRead(POTAR);
  if( val < SEUIL_POTAR_BAS || val > SEUIL_POTAR_HAUT) {
    if(elevation()){
      RF_OK();
    }
  }
  else {
    descente();
  }
}

bool elevation() { 
  if(!etat){
    int j;
    for(j = SEUIL_BAS_BAS1; j >= SEUIL_INTER_BAS1; j--){
      ServoBas1.writeServo(j);
      delay(vitesse);
    }
    delay(1000);
    for(int i = SEUIL_BAS_HAUT; i <= SEUIL_INTER_HAUT; i++) {
      ServoHaut.writeServo(i);
      ServoCentre.writeServo(map(i, SEUIL_BAS_HAUT, SEUIL_INTER_HAUT, SEUIL_BAS_CENTRE, SEUIL_INTER_CENTRE));
      delay(vitesse);
    }
    delay(1000);
    for(j = SEUIL_INTER_BAS1; j >= SEUIL_HAUT_BAS1; j--){
      ServoBas1.writeServo(j);
      if(j - SEUIL_HAUT_BAS1 < (SEUIL_INTER_CENTRE - SEUIL_HAUT_CENTRE)/2) {
        ServoCentre.writeServo(map(j, SEUIL_HAUT_BAS1+(SEUIL_INTER_CENTRE - SEUIL_HAUT_CENTRE)/2, SEUIL_HAUT_BAS1, SEUIL_INTER_CENTRE, SEUIL_HAUT_CENTRE));
        ServoHaut.writeServo(map(j, SEUIL_HAUT_BAS1+(SEUIL_INTER_CENTRE - SEUIL_HAUT_CENTRE)/2, SEUIL_HAUT_BAS1, SEUIL_INTER_HAUT, SEUIL_HAUT_HAUT));
      }
      delay(vitesse);
    }

    delay(1500);
    digitalWrite(MOTEUR, HIGH);
    etat = HAUT;
    
  }
  
  return etat;
}

void descente() {
  int servoBas1 = SEUIL_HAUT_BAS1;
  int servoBas2 = SEUIL_HAUT_BAS2;
  int servoCentre = SEUIL_HAUT_CENTRE;
  int servoHaut = SEUIL_HAUT_HAUT;

  digitalWrite(MOTEUR, LOW);
  
  while(etat){
    ServoBas1.writeServo(servoBas1++);
    //ServoBas2.write(servoBas2--);        //Non utilisé
    if (servoHaut != SEUIL_BAS_HAUT && servoBas1 > 60) {
      ServoHaut.writeServo(servoHaut--);
    }
    if (servoCentre != SEUIL_BAS_CENTRE ){
      ServoCentre.writeServo(servoCentre++);
    }
    
    if(servoBas1 == SEUIL_BAS_BAS1) {
      etat = BAS;
    }
    
    delay(vitesse);
  }
}

void RF_OK(){
  vw_send(msg, 8);
  vw_wait_tx();
  delay(5000);
}

