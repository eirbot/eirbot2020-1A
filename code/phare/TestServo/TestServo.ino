#include <Servo.h>

Servo ServoBas1;
Servo ServoBas2;
Servo ServoCentre;
Servo ServoHaut;

int potar = 5;
int val;

void setup() {
ServoBas1.attach(9);
ServoBas2.attach(8);
ServoCentre.attach(7);
ServoHaut.attach(6);
Serial.begin(9600);
delay(1000);
}

void loop() {
Serial.print("Servo : ");
val = analogRead(potar);
val = map(val, 0, 1023, 0, 200);
Serial.println(val);
ServoHaut.write(val);

delay(100);
}
