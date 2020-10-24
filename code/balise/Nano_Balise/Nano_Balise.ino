#include <VirtualWire.h>

#define PIN_RASP_ORI 3
#define PIN_RASP_LOCK 4

const char msg_Balise_Sud[4] = "SUDE";
const char msg_Balise_Nord[4] = "NORE";

void setup() {
  
pinMode(PIN_RASP_ORI, INPUT);
pinMode(13, OUTPUT);

digitalWrite(13, LOW);

vw_setup(2000);

delay(1000);
}

void loop() {
  if(analogRead(PIN_RASP_LOCK) > 600){
    if(analogRead(PIN_RASP_ORI) > 600){
      RF_OK_S();
    }
    else{
      RF_OK_N();
    }
  }

}

void RF_OK_S(){
  digitalWrite(13, HIGH);
  vw_send(msg_Balise_Sud, 4);
  vw_wait_tx();
  delay(4000);
  digitalWrite(13, LOW);
}


void RF_OK_N(){
  digitalWrite(13, HIGH);
  vw_send(msg_Balise_Nord, 4);
  vw_wait_tx();
  delay(4000);
  digitalWrite(13, LOW);
}
