#include <Servo.h>

Servo ServoBas1;
Servo ServoBas2;
Servo ServoCentre;
Servo ServoHaut;

int potarPinBas = 0;
int potarPinCentre = 1;
int potarPinHaut = 2;
int val;

void setup() {
  // put your setup code here, to run once:
ServoBas1.attach(2);
ServoBas2.attach(3);
ServoCentre.attach(4);
ServoHaut.attach(5);
Serial.begin(9600);
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
int val = analogRead(0);
if(val < 30){
  ServoBas1.write(26);
  ServoBas2.write(154);
  ServoCentre.write(45);
  delay(1000);
  ServoHaut.write(36);
  delay(1000);
}
else if(val > 100){
  ServoHaut.write(180);
  delay(1000);
  ServoCentre.write(200);
  ServoBas1.write(180);
  ServoBas2.write(0);
  delay(1000);
}
Serial.println(val);
delay(100);
}
