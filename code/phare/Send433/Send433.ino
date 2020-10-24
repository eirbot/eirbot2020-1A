//D12 pour send

#include <VirtualWire.h>
char msg[10] = "31415926";   //Message envoyé par le phare pour confirmer l'ascention

void setup() {
  // put your setup code here, to run once:
vw_setup(2000);
delay(1000);
pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  vw_send(msg, 10);
  vw_wait_tx();
  digitalWrite(13, LOW);
  delay(5000);
}
