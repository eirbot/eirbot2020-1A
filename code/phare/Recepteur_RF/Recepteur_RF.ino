#include <VirtualWire.h>

#define PIN_PHARE 5
#define PIN_BALISE 6

const char msg_Phare[10] = "31415926";
const char msg_Balise_Sud[10] = "SUDE";
const char msg_Balise_Nord[10] = "NORE";

void setup() {
  // put your setup code here, to run once:
pinMode(PIN_PHARE, OUTPUT);
pinMode(PIN_BALISE, OUTPUT);
pinMode(13, OUTPUT);

digitalWrite(PIN_PHARE, LOW);
digitalWrite(PIN_BALISE, LOW);
digitalWrite(13, LOW);

vw_setup(2000);
vw_rx_start();
Serial.begin(9600);

delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

if (vw_get_message(buf, &buflen))
{
  int i = 0;
  int j = 0;
  int k = 0;
  
  //digitalWrite(13, HIGH);
  if(buflen == 8){
    for(i = 0; i< buflen; i++)
    {
      if(char(buf[i]) != msg_Phare[i]){
        break;
      }
    }
  }
  if(buflen == 4){
    for(j = 0; j< buflen; j++)
    {
      if(char(buf[j]) != msg_Balise_Sud[j]){
        break;
      }
    }
  }
  if(buflen == 4){
    for(k = 0; k< buflen; k++)
    {
      if(char(buf[k]) != msg_Balise_Nord[k]){
        break;
      }
    }
  }
  
  if(i == buflen){
    digitalWrite(PIN_PHARE, HIGH);
  }
  else if(j == buflen){
    digitalWrite(PIN_BALISE, LOW);
  }
  else if(k == buflen){
    digitalWrite(PIN_BALISE, HIGH);
  }
  else {}
  //digitalWrite(13, LOW);
}
}
