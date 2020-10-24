//D11 pour Receive

#include <VirtualWire.h>
const char *msg = "31415926";   //Message envoyé par le phare pour confirmer l'ascention

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
vw_setup(2000);
vw_rx_start();
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("Attente");

vw_wait_rx(); // On attend de recevoir quelque chose
Serial.println("RECU");
byte buff[10];
byte len = 10;
if (vw_get_message(buff, &len)) { // Réception du paquet
  for(int i =0; i< 10; i++){
    Serial.print(char(buff[i]));
  }
}
}
